package main

import (
	"bytes"
	"encoding/binary"
	"flag"
	"fmt"
	"io"
	"log"
	"os"
	"path/filepath"
)

type File struct {
	off  uint64
	noff uint64
	size uint64
	meta [3]uint64
	name string
	data []byte
}

var (
	status = 0

	listFiles = flag.Bool("l", false, "only list the files")
)

func main() {
	log.SetFlags(0)
	log.SetPrefix("pak-dumper: ")
	flag.Usage = usage
	flag.Parse()

	switch flag.NArg() {
	case 1:
		if !*listFiles {
			usage()
		}
	case 2:
		if *listFiles {
			usage()
		}
	default:
		usage()
	}

	f := unpack(flag.Arg(0))
	if *listFiles {
		for i := range f {
			fmt.Printf("%v: size: %v offset: %#x\n", f[i].name, f[i].size, f[i].off)
		}
	} else {
		for i := range f {
			name := filepath.Join(flag.Arg(1), f[i].name)
			os.MkdirAll(filepath.Dir(name), 0755)
			fmt.Printf("writing file: %v\n", name)
			err := os.WriteFile(name, f[i].data, 0644)
			if err != nil {
				fmt.Fprintln(os.Stderr, err)
				status = 1
			}
		}
	}
	os.Exit(status)
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: [options] file.pak [dumpdir]")
	flag.PrintDefaults()
	os.Exit(2)
}

func get(r io.Reader, v interface{}) {
	err := binary.Read(r, binary.LittleEndian, v)
	if err != nil {
		log.Fatal(err)
	}
}

func get4(r io.Reader) uint32 {
	var v uint32
	get(r, &v)
	return v
}

func get8(r io.Reader) uint64 {
	var v uint64
	get(r, &v)
	return v
}

func seek(s io.Seeker, offset int64, whence int) int64 {
	n, err := s.Seek(offset, whence)
	if err != nil {
		log.Fatal(err)
	}
	return n
}

func unpack(name string) []File {
	b, err := os.ReadFile(name)
	if err != nil {
		log.Fatal(err)
	}

	r := bytes.NewReader(b)
	n := get8(r) >> 32
	o := get8(r)
	s := get8(r)

	f := make([]File, n)

	seek(r, int64(o), os.SEEK_SET)
	for i := range f {
		f[i].off = get8(r)
	}

	seek(r, int64(s), os.SEEK_SET)
	for i := range f {
		f[i].noff = get8(r)
	}

	for i := range f {
		seek(r, int64(f[i].off), os.SEEK_SET)
		f[i].size = get8(r)
		for j := range f[i].meta {
			f[i].meta[j] = get8(r)
		}
		f[i].data = make([]byte, f[i].size)
		_, err := io.ReadAtLeast(r, f[i].data, int(f[i].size))
		if err != nil {
			log.Fatal(err)
		}
	}

	for i := range f {
		seek(r, int64(f[i].noff), os.SEEK_SET)
		var name string
		for {
			ch, err := r.ReadByte()
			if err != nil {
				log.Fatal(err)
			}
			if ch == 0 {
				break
			}
			name += string(ch)
		}
		f[i].name = name
	}

	return f
}
