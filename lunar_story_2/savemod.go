package main

import (
	"bytes"
	"encoding/binary"
	"flag"
	"fmt"
	"log"
	"os"
)

var (
	maxout = flag.Bool("maxout", false, "max out")
)

func main() {
	log.SetFlags(0)
	log.SetPrefix("lunar-story-2-savemod: ")

	flag.Usage = usage
	flag.Parse()
	if flag.NArg() != 1 {
		usage()
	}

	f, err := decode(flag.Arg(0))
	check(err)

	f.Dump()

	if *maxout {
		f.MaxOut()
		err := os.WriteFile(flag.Arg(0), f.Data, 0644)
		check(err)
	}
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: [options] cardxx_SAVE_DATA")
	flag.PrintDefaults()
	os.Exit(2)
}

func check(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

type File struct {
	Data  []byte
	Chars []Char
}

type Char struct {
	XP     uint32
	NextXP uint32
	HP     uint16
	MaxHP  uint16
	MP     uint16
	MaxMP  uint16
}

func checksum(data []byte) uint32 {
	sum := uint32(0)
	for i := range data {
		sum += uint32(data[i])
	}
	return sum
}

func decode(name string) (*File, error) {
	const sig = "EX"

	b, err := os.ReadFile(name)
	if err != nil {
		return nil, err
	}

	if len(b) != 0x2000 {
		return nil, fmt.Errorf("%v: save file too small", name)
	}

	if bytes.Compare(b[:len(sig)], []byte(sig)) != 0 {
		return nil, fmt.Errorf("%v: invalid header signature", name)
	}

	f := &File{
		Data: b,
	}

	var ch Char
	for _, o := range STATS {
		r := bytes.NewReader(b[o:])
		binary.Read(r, binary.LittleEndian, &ch)
		f.Chars = append(f.Chars, ch)
	}

	return f, nil
}

func (f *File) Dump() {
}

func (f *File) MaxOut() {
	fmt.Println("MAX OUT!")
	for i, ch := range f.Chars {
		copy(f.Data[STATS[i]:], makebytes(ch))
	}
}

func makebytes(v any) []byte {
	w := new(bytes.Buffer)
	binary.Write(w, binary.LittleEndian, v)
	return w.Bytes()
}

const (
	GOLD = 0x9c4
)

var STATS = []int{
	0x314, // hiro
	0x3d8, // ronfar
	0x49c, // jean
	0x560, // leo
	0x624, // lemina
	0x6e8, // gwyn
}
