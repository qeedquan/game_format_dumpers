// the format is from yanesdk ver 2
// a game engine
// http://yanesdkdotnet.sourceforge.jp/ new one uses .net and zip
// http://bm98.yaneu.com/links/ygs/ this one is the one that this tool was made to rip

// made to rip
// http://werk-zwei.jp/railgun/
package main

import (
	"bytes"
	"encoding/binary"
	"flag"
	"fmt"
	"image"
	"image/color"
	"image/png"
	"io"
	"os"
	"path/filepath"
	"reflect"
	"strings"
)

func main() {
	flag.Usage = usage
	flag.Parse()
	if flag.NArg() != 2 {
		usage()
	}

	infile, outdir := flag.Arg(0), flag.Arg(1)
	y := NewYane()
	err := y.Open(infile)
	if err != nil {
		die("%v", err)
	}
	err = y.Dump(outdir)
	if err != nil {
		die("%v", err)
	}
	defer y.Close()
}

func usage() {
	die("usage: <file> <outdir>")
}

func printf(format string, args ...interface{}) {
	fmt.Printf(format+"\n", args...)
}

func die(format string, args ...interface{}) {
	printf(format, args...)
	os.Exit(1)
}

// YANE

// YANE format is the file format that is an archive to contain
// other formats, can be compressed in lzss
// format type

// the main file struct
type Yane struct {
	Type     string
	NumFiles uint32
	Entries  []YaneEntry

	canCompress bool
	handle      *os.File
	entrd       func(io.Reader, *YaneEntry) error
}

// an entry
type YaneEntry struct {
	Name    string
	Start   uint32
	Size    uint32
	ArcSize uint32
}

// this is the raw data entry in the file
type yaneEntry struct {
	Name  [32]byte
	Start uint32
	Size  uint32
}

type yaneEntryEx struct {
	Name    [32]byte
	Start   uint32
	Size    uint32
	ArcSize uint32
}

type yaneEntryDx struct {
	Name    [256]byte
	Start   uint32
	Size    uint32
	ArcSize uint32
}

// magic length
const yaneMagicLen = 8

var yane = []struct {
	typ         string
	canCompress bool
	entrd       func(io.Reader, *YaneEntry) error
}{
	{"yanepack", false, yaneReadEntry},
	{"yanepkEx", true, yaneReadEntryEx},
	{"yanepkDx", true, yaneReadEntryDx},
}

// new yane
func NewYane() *Yane {
	return &Yane{}
}

// open a yane file
func (y *Yane) Open(fn string) (err error) {
	y.handle, err = os.Open(fn)
	if err != nil {
		return
	}

	r := y.handle
	var buf [yaneMagicLen]byte
	n, err := r.Read(buf[:])
	if err != nil {
		return
	}
	if l := len(buf); n != l {
		err = fmt.Errorf("failed read: %v %v", n, l)
		return
	}

	for _, v := range yane {
		if string(buf[:]) == v.typ {
			y.Type = v.typ
			y.canCompress = v.canCompress
			y.entrd = v.entrd
			break
		}
	}
	if y.Type == "" {
		err = fmt.Errorf("unrecognized format: %v", buf)
		return
	}

	err = binary.Read(r, binary.LittleEndian, &y.NumFiles)
	if err != nil {
		return
	}
	printf("number of files: %v", y.NumFiles)

	for i := uint32(0); i < y.NumFiles; i++ {
		y.Entries = append(y.Entries, YaneEntry{})
		e := &y.Entries[i]
		err = y.entrd(r, e)
		if err != nil {
			return
		}
	}

	return
}

// close
func (y *Yane) Close() {
	y.handle.Close()
}

// get all data and put it in a dir
func (y *Yane) Dump(root string) (err error) {
	err = os.MkdirAll(root, 0755)
	if err != nil {
		return
	}

	lzss := NewLZSS()
	for _, e := range y.Entries {
		printf("%v", e)
		dir, _ := filepath.Split(e.Name)
		dir = filepath.Join(root, dir)
		err = os.MkdirAll(dir, 0755)
		if err != nil {
			return
		}

		var w *os.File
		dir = filepath.Join(root, e.Name)
		w, err = os.Create(dir)
		if err != nil {
			return
		}

		_, err = y.handle.Seek(int64(e.Start), io.SeekStart)
		if err != nil {
			return
		}

		var n int
		buf := make([]byte, e.ArcSize)
		n, err = y.handle.Read(buf)
		if err != nil {
			return
		}
		if n != len(buf) {
			printf("warning: mismatched sized: %v %v", n, len(buf))
		}

		if y.canCompress && e.Size != e.ArcSize {
			buf = lzss.Decode(buf, int(e.Size))
		}

		_, err = w.Write(buf)
		if err != nil {
			return
		}
		w.Close()

		switch ext := filepath.Ext(e.Name); ext {
		case ".yga":
			name := filepath.Join(root, e.Name[:len(e.Name)-3]+"png")
			w, err = os.Create(name)
			if err != nil {
				return
			}

			var img image.Image
			img, err = YGAToImage(buf)
			if err != nil {
				return
			}
			err = png.Encode(w, img)
			if err != nil {
				return
			}
			w.Close()
		}
	}

	return
}

// read one entry
func yaneReadEntry(r io.Reader, e *YaneEntry) (err error) {
	var ya yaneEntry
	err = binary.Read(r, binary.LittleEndian, &ya)
	if err != nil {
		return
	}
	*e = YaneEntry{Name: string(ya.Name[:]), Start: ya.Start,
		Size: ya.Size, ArcSize: ya.Size}
	yaneCleanEntry(e)
	return
}

// specific read functions to deal with different yane versions
func yaneReadEntryEx(r io.Reader, e *YaneEntry) (err error) {
	var ya yaneEntryEx
	err = binary.Read(r, binary.LittleEndian, &ya)
	if err != nil {
		return
	}
	*e = YaneEntry{Name: string(ya.Name[:]), Start: ya.Start,
		Size: ya.Size, ArcSize: ya.ArcSize}
	yaneCleanEntry(e)
	return
}

func yaneReadEntryDx(r io.Reader, e *YaneEntry) (err error) {
	var ya yaneEntryDx
	err = binary.Read(r, binary.LittleEndian, &ya)
	if err != nil {
		return
	}
	*e = YaneEntry{Name: string(ya.Name[:]), Start: ya.Start,
		Size: ya.Size, ArcSize: ya.ArcSize}
	yaneCleanEntry(e)
	return
}

func yaneCleanEntry(e *YaneEntry) {
	e.Name = strings.TrimRight(e.Name, "\x00")
	e.Name = strings.Replace(e.Name, "\\", "/", -1)
	e.Name = filepath.Clean(e.Name)
}

// YGA

// if it is compressed, it is compressed using lzss

// yga format
type YGA struct {
	Magic        uint32 // "yga"
	Width        uint32 // width
	Height       uint32 // height
	Compress     uint32 // is compressed?
	OrigSize     uint32 // original size
	CompressSize uint32 // compressed size
}

// magic
const (
	ygaMagic = 0x616779
)

// convert a yga buffer to an image
func YGAToImage(b []byte) (image.Image, error) {
	var yga YGA

	r := bytes.NewBuffer(b)
	binary.Read(r, binary.LittleEndian, &yga)

	if yga.Magic != ygaMagic {
		return nil, fmt.Errorf("yga magic doesn't match: 0x%X", yga.Magic)
	}

	b = b[int(reflect.TypeOf(yga).Size()):]
	if yga.Compress > 0 {
		lzss := NewLZSS()
		b = lzss.Decode(b, int(yga.OrigSize))
	}

	img := image.NewRGBA(image.Rect(0, 0, int(yga.Width), int(yga.Height)))
	for i, y := 0, 0; y < int(yga.Height); y++ {
		for x := 0; x < int(yga.Width); x++ {
			img.Set(x, y, color.RGBA{b[i+2], b[i+1], b[i], b[i+3]})
			i += 4
		}
	}

	printf("\tyga: %v size: %v", yga, len(b))

	return img, nil
}

// LZSS

// all the formats is compressed with lzss
const (
	lzssRingBufferSize = 4096
	lzssLongestMatch   = 18
)

type LZSS struct {
	text []byte
}

func NewLZSS() *LZSS {
	return &LZSS{
		text: make([]byte, lzssRingBufferSize+lzssLongestMatch-1),
	}
}

func (l *LZSS) Decode(src []byte, size int) (dst []byte) {
	dst = make([]byte, size)
	for i := range l.text {
		l.text[i] = 0
	}

	r := lzssRingBufferSize - lzssLongestMatch
	flag := uint32(0)

	var a, b int
	var c byte
	for {
		if flag >>= 1; flag&256 == 0 {
			if a >= len(src) {
				break
			}
			c, a = src[a], a+1
			flag = uint32(c) | 0xFF00
		}

		if flag&1 != 0 {
			if a >= len(src) {
				break
			}
			c, a = src[a], a+1
			dst[b], b = c, b+1
			if b == len(dst) {
				break
			}

			l.text[r], r = c, (r+1)&(lzssRingBufferSize-1)
		} else {
			if a >= len(src) {
				break
			}
			i, j := int(src[a]), int(src[a+1])
			a += 2

			i |= ((j & 0xF0) << 4)
			j = (j & 0x0F) + 2
			for k := 0; k <= j; k++ {
				c = l.text[(i+k)&(lzssRingBufferSize-1)]
				dst[b], b = c, b+1
				if b == len(dst) {
					break
				}

				l.text[r], r = c, (r+1)&(lzssRingBufferSize-1)
			}
		}
	}
	return
}
