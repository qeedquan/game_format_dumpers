// dumps cpa format from
// http://nooskewl.ca/crystal-picnic/
package main

import (
	"compress/gzip"
	"flag"
	"fmt"
	"io"
	"os"
	"path/filepath"
)

var (
	outputDir = flag.String("o", "dump", "output to directory")

	status = 0
)

func main() {
	flag.Usage = usage
	flag.Parse()
	if flag.NArg() < 1 {
		usage()
	}
	for _, name := range flag.Args() {
		ek(extract(*outputDir, name))
	}
	os.Exit(status)
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: [-o dir] <cpa_file>")
	flag.PrintDefaults()
	os.Exit(2)
}

func ek(err error) {
	if err != nil {
		fmt.Fprintln(os.Stderr, "cpa-dumper:", err)
		status = 1
	}
}

func xk(name string, err error) bool {
	if err == nil {
		return false
	}
	fmt.Fprintln(os.Stderr, "cpa-dumper: failed to extract file %s: %s", name, err)
	status = 1
	return true
}

type Entry struct {
	Size int64
	Name string
}

func extract(dir, name string) error {
	err := uncompress(dir, name)
	if err != nil {
		return err
	}

	f, err := os.Open(filepath.Join(dir, basename(name)))
	if err != nil {
		return err
	}
	defer f.Close()

	var off int64
	fmt.Fscan(f, &off)
	f.Seek(off, io.SeekCurrent)

	var entries []Entry
	for {
		var size int64
		var name string

		n, err := fmt.Fscanf(f, "%d %s", &size, &name)
		if err == io.EOF || n != 2 {
			break
		}
		if err != nil {
			return err
		}
		entries = append(entries, Entry{size, name})
	}

	f.Seek(0, io.SeekStart)
	fmt.Fscan(f, &off)
	for _, e := range entries {
		name := filepath.Join(dir, e.Name)
		os.MkdirAll(filepath.Dir(name), 0755)

		w, err := os.Create(name)
		if xk(e.Name, err) {
			continue
		}

		_, err = io.CopyN(w, f, e.Size)
		xk(e.Name, err)
	}

	return nil
}

func uncompress(dir, name string) error {
	f, err := os.Open(name)
	if err != nil {
		return err
	}
	defer f.Close()

	r, err := gzip.NewReader(f)
	if err != nil {
		return err
	}

	os.MkdirAll(dir, 0755)
	w, err := os.Create(filepath.Join(dir, basename(name)))
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

func basename(name string) string {
	base := filepath.Base(name)
	ext := filepath.Ext(base)
	return base[:len(base)-len(ext)]
}
