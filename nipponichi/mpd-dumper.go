// stores map files
package main

import (
	"flag"
	"fmt"
	"log"
	"os"

	"github.com/qeedquan/go-media/archive/nipponichi/mpd"
)

func main() {
	flag.Usage = usage
	flag.Parse()
	if flag.NArg() != 1 {
		usage()
	}

	err := dump(flag.Arg(0))
	if err != nil {
		log.Fatal(err)
	}
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: mpd-dumper [options] input")
	flag.PrintDefaults()
	os.Exit(2)
}

func dump(input string) error {
	fd, err := os.Open(input)
	if err != nil {
		return err
	}
	defer fd.Close()

	m, err := mpd.Decode(fd)
	if err != nil {
		return err
	}
	show(m)
	return nil
}

func show(m *mpd.Map) {
	fmt.Printf("Chunks: %d\n", len(m.Chunks))
	for i, chunk := range m.Chunks {
		fmt.Printf("#%d\n", i)
		fmt.Printf("  Map Offset %v\n", chunk.Header.MapOff)
		fmt.Printf("  Number of Tiles %d\n", chunk.Header.NumTiles)
		fmt.Printf("  Index %d\n", chunk.Header.Index)
		fmt.Println()
	}
	fmt.Printf("Actors: %d\n", len(m.Actors))
	for i, actor := range m.Actors {
		fmt.Printf("#%d\n", i)
		fmt.Printf("  ID %d\n", actor.ID)
		fmt.Printf("  Level %d\n", actor.Level)
		fmt.Printf("  Position (%d, %d)\n", actor.X, actor.Z)
		fmt.Printf("  Rotation (%d)\n", actor.Rotation)
		fmt.Printf("  AI (%d)\n", actor.AI)
		fmt.Printf("  Appearance (%d)\n", actor.Appearance)
		fmt.Printf("  Items (%v)\n", actor.Items)
		fmt.Printf("  Magic (%v)\n", actor.Magic)
	}
}
