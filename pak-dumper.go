// dump id software pak files

package main

import (
	"encoding/binary"
	"flag"
	"fmt"
	"io"
	"os"
	"path/filepath"
	"strings"
)

type Header struct {
	Sig [4]byte
	Off uint32
	Len uint32
}

type Dir struct {
	Name [56]byte
	Off  uint32
	Len  uint32
}

func main() {
	dir := flag.String("o", ".", "output to directory")
	flag.Usage = usage
	flag.Parse()
	if flag.NArg() < 1 {
		usage()
	}

	status := 0
	for i := 0; i < flag.NArg(); i++ {
		err := unpack(flag.Arg(i), *dir)
		if err != nil {
			status = 1
		}
	}
	os.Exit(status)
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: [options] file ...")
	flag.PrintDefaults()
	os.Exit(1)
}

func unpack(name, dir string) error {
	f, err := os.Open(name)
	if err != nil {
		return errf("%v", err)
	}
	defer f.Close()

	var h Header
	err = binary.Read(f, binary.LittleEndian, &h)
	if err != nil {
		return errf("%v: %v", name, err)
	}

	if h.Sig != [4]byte{'P', 'A', 'C', 'K'} {
		return errf("%v: invalid magic, expected PACK but got %q", name, h.Sig)
	}

	if h.Len%64 != 0 {
		return errf("%v: corrupted pak file, length field not aligned to 64 bytes, got %v bytes", name, h.Len)
	}

	_, err = f.Seek(int64(h.Off), io.SeekStart)
	if err != nil {
		return errf("%v: %v", name, err)
	}

	var xerr error
	check := func(prefix string) {
		if err != nil {
			if prefix == "" {
				fmt.Fprintf(os.Stderr, "%v\n", err)
			} else {
				fmt.Fprintf(os.Stderr, "%v: %v\n", prefix, err)
			}
			xerr = err
		}
	}

	var d Dir
	for i := uint32(0); i < h.Len/64; i++ {
		err = binary.Read(f, binary.LittleEndian, &d)
		if err != nil {
			check(name)
			continue
		}

		var wpos int64
		wpos, err = f.Seek(0, io.SeekCurrent)
		check(name)

		_, err = f.Seek(int64(d.Off), io.SeekStart)
		check(name)

		filename := strings.TrimRight(string(d.Name[:]), "\x00")
		filename = filepath.Join(dir, filename)
		os.MkdirAll(filepath.Dir(filename), 0755)

		var w *os.File
		w, err = os.Create(filename)
		check("")

		if err == nil {
			_, err = io.CopyN(w, f, int64(d.Len))
			check(filename)

			err = w.Close()
			check(filename)
		}

		_, err = f.Seek(wpos, io.SeekStart)
		check(name)

		if xerr == nil {
			fmt.Println(filename)
		}
	}

	if xerr != nil {
		return xerr
	}

	return nil
}

func errf(format string, args ...interface{}) error {
	err := fmt.Errorf(format, args...)
	fmt.Fprintln(os.Stderr, err)
	return err
}
