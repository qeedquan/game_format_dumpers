// solar2d car archive dumper

package main

import (
	"flag"
	"fmt"
	"log"
	"os"
	"path/filepath"

	"github.com/qeedquan/go-media/archive/solar2d/car"
)

func main() {
	log.SetFlags(0)
	log.SetPrefix("car-dumper: ")

	flag.Usage = usage
	flag.Parse()
	if flag.NArg() != 2 {
		usage()
	}

	f, err := os.Open(flag.Arg(0))
	check(err)
	defer f.Close()

	a, err := car.Decode(f)
	check(err)

	dir := flag.Arg(1)
	err = os.MkdirAll(dir, 0755)
	check(err)

	for _, e := range a.Entries {
		file := filepath.Join(dir, e.Name)
		fmt.Printf("Writing %s\n", file)
		err = os.WriteFile(file, e.Data, 0644)
		if err != nil {
			fmt.Println("Error: ", err)
		}
	}
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: [options] <archive.car> <directory>")
	flag.PrintDefaults()
	os.Exit(2)
}

func check(err error) {
	if err != nil {
		log.Fatal(err)
	}
}
