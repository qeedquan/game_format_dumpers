package main

import (
	"flag"
	"fmt"
	"log"
	"os"
	"path/filepath"

	"github.com/qeedquan/go-media/archive/nipponichi/dsarcfl"
)

var (
	version = flag.Int("v", 2, "specify format version")
	outdir  = flag.String("o", ".", "output directory")
)

func main() {
	log.SetFlags(0)
	log.SetPrefix("dsarcfl-dumper: ")

	flag.Usage = usage
	flag.Parse()
	if flag.NArg() < 1 {
		usage()
	}

	f, err := os.Open(flag.Arg(0))
	check(err)
	defer f.Close()

	z, err := dsarcfl.Decode(f, *version)
	check(err)

	for _, e := range z.Entries {
		name := filepath.Join(*outdir, e.Name)
		dir := filepath.Dir(name)
		os.MkdirAll(dir, 0755)

		fmt.Printf("%s size=%d\n", name, e.Size)
		err = os.WriteFile(name, e.Data, 0644)
		if err != nil {
			fmt.Printf("failed to write %v: %v\n", name, err)
		}
	}
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: [options] file")
	flag.PrintDefaults()
	os.Exit(2)
}

func check(err error) {
	if err != nil {
		log.Fatal(err)
	}
}
