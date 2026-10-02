// stores textures/normals/geometries
package main

import (
	"flag"
	"fmt"
	"os"
	"path/filepath"

	"github.com/qeedquan/go-media/archive/nipponichi/mpp"
)

var (
	outdir  = flag.String("o", "", "output to directory")
	listing = flag.Bool("l", false, "show file listing only")

	status = 0
)

func main() {
	flag.Usage = usage
	flag.Parse()
	if flag.NArg() < 1 {
		usage()
	}
	os.MkdirAll(*outdir, 0755)
	for _, name := range flag.Args() {
		err := dump(name)
		if err != nil {
			fmt.Println(err)
		}
	}
	os.Exit(status)
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: mpp-dumper [options] file ...")
	flag.PrintDefaults()
	os.Exit(2)
}

func dump(name string) error {
	fd, err := os.Open(name)
	if err != nil {
		return err
	}
	defer fd.Close()

	archive, err := mpp.Decode(fd)
	if err != nil {
		return err
	}

	fmt.Printf("total number of files: %d\n", len(archive.Entries))
	fmt.Printf("# textures %d\n", archive.NumTextures)
	if archive.HasNormals != 0 {
		fmt.Printf("# normal %d\n", archive.NumTextures)
	}
	fmt.Printf("# geometries %d\n", archive.NumGeoms)
	fmt.Println()
	for _, entry := range archive.Entries {
		if *listing {
			fmt.Printf("%s\n", entry.Name)
			fmt.Printf("%d bytes\n", len(entry.Data))
			fmt.Printf("%#x offset\n", entry.Off)
			fmt.Println()
			continue
		}

		fmt.Printf("dumping %q\n", entry.Name)
		entryname := filepath.Join(*outdir, entry.Name)
		err := os.WriteFile(entryname, entry.Data, 0644)
		if err != nil {
			fmt.Println(err)
			continue
		}
	}
	return nil
}
