// dumps disgaea 2 pc/psp dat files
// https://github.com/ProgSys/pg_disatools/wiki/PSPFS_v1
package main

import (
	"bufio"
	"encoding/binary"
	"flag"
	"fmt"
	"io"
	"os"
	"path/filepath"
	"strings"
)

var (
	output = flag.String("o", "", "output to directory")

	status = 0
)

func main() {
	flag.Usage = usage
	flag.Parse()
	if flag.NArg() < 1 {
		usage()
	}
	os.MkdirAll(*output, 0755)
	for _, name := range flag.Args() {
		ek(dump(name))
	}
	os.Exit(status)
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: pspfsv1 [options] file ...")
	flag.PrintDefaults()
	os.Exit(2)
}

func ek(err error) bool {
	if err != nil {
		fmt.Fprintln(os.Stderr, "pspfsv1:", err)
		status = 1
		return true
	}
	return false
}

func fk(archive, name string, err error) bool {
	if err != nil {
		if flag.NArg() > 0 {
			fmt.Fprintf(os.Stderr, "%s: %s: %v\n", archive, name, err)
		} else {
			fmt.Fprintf(os.Stderr, "%s: %v\n", name, err)
		}
		status = 1
		return true
	}
	return false
}

type header struct {
	Magic   [8]byte
	Size    uint32
	Unknown uint32
}

type file struct {
	Name     [40]byte
	DecSize  uint32
	FileSize uint32
	Off      uint32
}

func dump(archive string) error {
	fd, err := os.Open(archive)
	if err != nil {
		return err
	}
	defer fd.Close()

	r := bufio.NewReader(fd)

	var hdr header
	err = binary.Read(r, binary.LittleEndian, &hdr)
	if err != nil {
		return err
	}
	if string(hdr.Magic[:]) != "PSPFS_V1" {
		return fmt.Errorf("invalid magic, got %q", hdr.Magic)
	}

	var files []file
	for i := uint32(0); i < hdr.Size; i++ {
		var file file
		err = binary.Read(r, binary.LittleEndian, &file)
		if err != nil {
			return err
		}
		files = append(files, file)
	}

	fmt.Printf("total number of files: %d\n", hdr.Size)
	for _, f := range files {
		name := strings.TrimRight(string(f.Name[:]), "\x00")
		name = strings.TrimRight(name, " ")
		name = strings.ToLower(name)
		name = filepath.Join(*output, name)

		fmt.Printf("dumping %q\n", name)
		w, err := os.Create(name)
		if fk(archive, name, err) {
			continue
		}

		fd.Seek(int64(f.Off), io.SeekStart)
		r = bufio.NewReader(fd)
		_, err = io.Copy(w, r)
		if fk(archive, name, err) {
			continue
		}

		err = w.Close()
		fk(archive, name, err)
	}

	return nil
}
