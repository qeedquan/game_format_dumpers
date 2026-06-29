// based on https://github.com/luxrck/rgssad
// known games using this format:
// https://radialapps.com/linux/aveyond34.html
package main

import (
	"encoding/binary"
	"flag"
	"fmt"
	"io"
	"log"
	"math"
	"os"
	"path/filepath"
)

var (
	status = 0
)

func main() {
	log.SetFlags(0)
	log.SetPrefix("rgssad-dumper: ")
	flag.Usage = usage
	flag.Parse()
	if flag.NArg() != 2 {
		usage()
	}
	ck(extract(flag.Arg(0), flag.Arg(1)))
}

func ek(err error) bool {
	if err != nil {
		fmt.Fprintln(os.Stderr, "rgssad-dumper:", err)
		status = 1
		return true
	}
	return false
}

func ck(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: rgssad-dumper [options] infile outdir")
	flag.PrintDefaults()
	os.Exit(2)
}

func extract(infile, outdir string) error {
	f, err := os.Open(infile)
	if err != nil {
		return err
	}
	defer f.Close()

	a, err := NewArchive(f)
	if err != nil {
		return fmt.Errorf("%v: %v", infile, err)
	}

	for _, p := range a.Files {
		name := filepath.Join(outdir, p.Name)
		dir := filepath.Dir(name)
		fmt.Println(name)

		os.MkdirAll(dir, 0755)
		w, err := os.Create(name)
		if ek(err) {
			continue
		}
		_, err = io.Copy(w, &p)
		ek(err)
		ek(w.Close())
	}

	return nil
}

type Archive struct {
	Files []File
}

type File struct {
	*io.SectionReader
	Name   string
	Size   uint32
	Offset int64
	Seed   uint32

	Mask  uint32
	Magic uint32
}

func NewArchive(r io.ReaderAt) (*Archive, error) {
	var hdr struct {
		Magic   [6]byte
		_       byte
		Version byte
	}

	sr := io.NewSectionReader(r, 0, math.MaxInt64)
	err := binary.Read(sr, binary.BigEndian, &hdr)
	if err != nil {
		return nil, err
	}

	if string(hdr.Magic[:]) != "RGSSAD" {
		return nil, fmt.Errorf("invalid magic, got %q", hdr.Magic)
	}

	var files []File
	switch hdr.Version {
	case 1, 2:
		files = rgssad12(sr)
	default:
		return nil, fmt.Errorf("unsupported rgssad version %d", hdr.Version)
	}
	for i := range files {
		files[i].SectionReader = io.NewSectionReader(r, files[i].Offset, int64(files[i].Size))
	}

	return &Archive{
		Files: files,
	}, nil
}

func advance(magic *uint32) uint32 {
	old := *magic
	*magic = *magic*7 + 3
	return old
}

func rgssad12(sr *io.SectionReader) []File {
	magic := uint32(0xdeadcafe)

	var files []File
	for {
		var n uint32
		err := binary.Read(sr, binary.LittleEndian, &n)
		if err != nil {
			break
		}
		n ^= advance(&magic)

		b := make([]byte, n)
		err = binary.Read(sr, binary.LittleEndian, b)
		if err != nil {
			break
		}

		for i := range b {
			b[i] ^= uint8(advance(&magic))
			if b[i] == '\\' {
				b[i] = '/'
			}
		}
		err = binary.Read(sr, binary.LittleEndian, &n)
		if err != nil {
			break
		}
		n ^= advance(&magic)
		o, _ := sr.Seek(0, io.SeekCurrent)

		_, err = sr.Seek(int64(n), io.SeekCurrent)
		if err != nil {
			break
		}
		files = append(files, File{
			Name:   string(b),
			Size:   n,
			Offset: o,
			Seed:   magic,
			Magic:  magic,
		})
	}
	return files
}

func (f *File) Read(b []byte) (n int, err error) {
	n, err = f.SectionReader.Read(b)
	for i := 0; i < n; i++ {
		b[i] ^= uint8(f.Magic >> (f.Mask * 8))
		if f.Mask++; f.Mask == 4 {
			advance(&f.Magic)
			f.Mask = 0
		}
	}
	return
}

func (f *File) Seek(offset int64, whence int) (int64, error) {
	if offset != 0 || whence != io.SeekStart {
		return -1, fmt.Errorf("seek: only resetting the stream is supported")
	}

	f.Magic = f.Seed
	f.Mask = 0
	return f.SectionReader.Seek(offset, whence)
}
