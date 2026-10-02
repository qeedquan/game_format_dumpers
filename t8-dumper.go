// dumps T8 graphics file from
// martian memory game
// http://dragontech.sourceforge.net/index.php?main=martian
package main

import (
	"bufio"
	"encoding/binary"
	"flag"
	"fmt"
	"image"
	"image/color"
	"image/png"
	"io"
	"os"
	"path/filepath"
)

var (
	status = 0
)

func main() {
	flag.Usage = usage
	flag.Parse()
	if flag.NArg() < 1 {
		usage()
	}

	for _, name := range flag.Args() {
		f, err := decode(name)
		if !ek(err) {
			ek(dump(f, tr(name)))
		}
	}
	os.Exit(status)
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: <t8_file> ...")
	flag.PrintDefaults()
	os.Exit(2)
}

func ek(err error) bool {
	if err != nil {
		fmt.Fprintln(os.Stderr, "t8-dumper:", err)
		status = 1
		return true
	}
	return false
}

type Header struct {
	Magic   [6]byte
	Width   uint16
	Height  uint16
	Palette [768]uint8
}

type File struct {
	Header
	Pixels []uint8
}

func decode(name string) (*File, error) {
	f, err := os.Open(name)
	if err != nil {
		return nil, err
	}
	defer f.Close()

	r := bufio.NewReader(f)

	t := new(File)
	err = binary.Read(r, binary.BigEndian, &t.Header)
	if err != nil {
		return nil, err
	}

	if string(t.Magic[:]) != "T-1000" {
		return nil, fmt.Errorf("invalid magic %q", t.Magic)
	}

	t.Pixels = make([]byte, int(t.Width)*int(t.Height))
	_, err = io.ReadAtLeast(r, t.Pixels, len(t.Pixels))
	if err != nil {
		return nil, err
	}

	return t, nil
}

func tr(name string) string {
	ext := filepath.Ext(name)
	xname := name[:len(name)-len(ext)] + ".png"
	if xname == name {
		xname += ".png"
	}
	return xname
}

func dump(t *File, name string) error {
	m := image.NewRGBA(image.Rect(0, 0, int(t.Width), int(t.Height)))
	for y := 0; y < int(t.Height); y++ {
		for x := 0; x < int(t.Width); x++ {
			n := int(t.Pixels[y*int(t.Width)+x]) * 3
			c := color.RGBA{
				t.Palette[n],
				t.Palette[n+1],
				t.Palette[n+2],
				255,
			}
			m.Set(x, y, c)
		}
	}

	f, err := os.Create(name)
	if err != nil {
		return err
	}

	err = png.Encode(f, m)
	xerr := f.Close()
	if err != nil {
		return err
	}

	return xerr
}
