// imy file stores compressed assets (animations, etc)
package main

import (
	"bytes"
	"flag"
	"fmt"
	"log"
	"os"

	"github.com/qeedquan/go-media/archive/nipponichi/imy"
)

func main() {
	flag.Usage = usage
	flag.Parse()
	if flag.NArg() != 2 {
		usage()
	}

	err := dump(flag.Arg(0), flag.Arg(1))
	if err != nil {
		log.Fatal(err)
	}
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: imy-dumper [options] input output")
	flag.PrintDefaults()
	os.Exit(2)
}

func dump(input, output string) error {
	fd, err := os.Open(input)
	if err != nil {
		return err
	}
	defer fd.Close()

	archive, err := imy.Decode(fd)
	if err != nil {
		return err
	}

	buf := new(bytes.Buffer)
	for _, entry := range archive.Entries {
		buf.Write(entry.Data)
	}
	return os.WriteFile(output, buf.Bytes(), 0644)
}
