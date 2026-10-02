// dump mpak files, used in
// http://tomatoes.sourceforge.net/
package main

import (
	"encoding/binary"
	"flag"
	"fmt"
	"io"
	"math"
	"os"
	"path/filepath"
	"strings"
)

func main() {
	flag.Usage = usage
	dir := flag.String("o", ".", "output to directory")
	flag.Parse()

	if flag.NArg() < 1 {
		usage()
	}

	for i := 0; i < flag.NArg(); i++ {
		extract(*dir, flag.Arg(i))
	}
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: [options] <mpakfile> ...")
	flag.PrintDefaults()
	os.Exit(1)
}

func extract(dir, name string) {
	f, err := os.Open(name)
	if err != nil {
		fmt.Fprintf(os.Stderr, "unpack: %v\n", err)
		return
	}
	defer f.Close()

	r, err := NewReader(f)
	if err != nil {
		if _, ok := err.(crcError); !ok {
			fmt.Fprintf(os.Stderr, "unpack: %v: %v\n", name, err)
			return
		}
		fmt.Fprintf(os.Stderr, "unpack: warning: %v: %v\n", name, err)
	}

	for _, file := range r.Files {
		name := filepath.Join(dir, file.Name)
		err = writeFile(name, file.Open())
		if err != nil {
			fmt.Fprintf(os.Stderr, "unpack: %v: %v\n", name, err)
			continue
		}
		fmt.Println(name)
	}
}

func writeFile(name string, r io.Reader) error {
	os.MkdirAll(filepath.Dir(name), 0755)

	w, err := os.Create(name)
	if err != nil {
		return err
	}

	_, err = io.Copy(w, r)
	xerr := w.Close()
	if err == nil {
		err = xerr
	}

	return err
}

type File struct {
	Name   string
	Offset int64
	Size   int64
	r      io.ReaderAt
}

func (f *File) Open() io.Reader {
	return io.NewSectionReader(f.r, f.Offset, f.Size)
}

type Reader struct {
	Files []*File
}

func NewReader(r io.ReaderAt) (*Reader, error) {
	b := binReader{
		r: io.NewSectionReader(r, 0, math.MaxUint32),
	}

	var h struct {
		Sig         [4]byte
		Crc         uint32
		TableOffset uint32
	}
	b.Read(&h)
	if b.err != nil {
		return nil, b.err
	}

	if string(h.Sig[:]) != "MPK1" {
		return nil, fmt.Errorf("invalid magic %q", h.Sig)
	}

	var files []*File
	var numFiles, offset uint32
	var filename [256]byte
	var length uint8

	b.Seek(int64(h.TableOffset), io.SeekStart)
	b.Read(&numFiles)
	if b.err != nil {
		return nil, b.err
	}

	for i := uint32(0); i < numFiles; i++ {
		b.Read(&length)
		b.Read(filename[:length])
		b.Read(&offset)
		if b.err != nil {
			return nil, b.err
		}

		files = append(files, &File{
			Name:   strings.TrimRight(string(filename[:length]), "\x00"),
			Offset: int64(offset),
			r:      r,
		})
	}

	if len(files) == 0 {
		return nil, fmt.Errorf("file contains zero entries")
	}

	for i := 0; i < len(files)-1; i++ {
		files[i].Size = files[i+1].Offset - files[i].Offset
	}
	files[len(files)-1].Size = int64(h.TableOffset) - files[len(files)-1].Offset

	for i := range files {
		if files[i].Size <= 0 {
			return nil, fmt.Errorf("entry %v contains invalid size of %v bytes", i+1, files[i].Size)
		}
	}

	var err error
	crc, _ := crc32(io.NewSectionReader(r, 8, math.MaxUint32))
	if h.Crc != crc {
		err = crcError{h.Crc, crc}
	}

	return &Reader{
		Files: files,
	}, err
}

type binReader struct {
	r   io.ReadSeeker
	err error
}

func (b *binReader) Read(x interface{}) {
	if b.err != nil {
		return
	}
	b.err = binary.Read(b.r, binary.LittleEndian, x)
}

func (b *binReader) Seek(off int64, whence int) {
	if b.err != nil {
		return
	}
	_, b.err = b.r.Seek(off, whence)
}

type crcError struct {
	want, got uint32
}

func (c crcError) Error() string {
	return fmt.Sprintf("crc32 mismatched! file: %#x computed: %#x", c.want, c.got)
}

var (
	crcTable [256]uint32
)

func init() {
	for n := range crcTable {
		crc := uint32(n)
		for i := 8; i > 0; i-- {
			if crc&1 != 0 {
				crc = (crc >> 1) ^ 0xedb88320
			} else {
				crc >>= 1
			}
		}
		crcTable[n] = crc
	}
}

func calcCrc(crc uint32, buf []byte) uint32 {
	for _, v := range buf {
		t1 := (crc >> 8) & 0x00ffffff
		t2 := crcTable[(crc^uint32(v))&0xff]
		crc = t1 ^ t2
	}
	return crc
}

func crc32(r io.Reader) (crc uint32, err error) {
	var buf [16384]byte
	var n int

	crc = uint32(0xffffffff)
	for {
		n, err = r.Read(buf[:])
		if n > 0 {
			crc = calcCrc(crc, buf[:n])
		}
		if err == io.EOF {
			err = nil
			break
		}
		if err != nil {
			break
		}
	}
	crc ^= 0xffffffff

	return
}
