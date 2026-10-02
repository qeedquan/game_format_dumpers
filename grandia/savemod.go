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
	log.SetPrefix("grandia-savemod: ")

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
	fmt.Fprintln(os.Stderr, "usage: [options] save")
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
	Lvl   uint8
	Exp   uint32
	Next  uint16
	MaxHP uint16
	HP    uint16
	Str   uint16
	Vit   uint16
	Wit   uint16
	Agi   uint16
	MaxSP uint16
	SP    uint16
}

func decode(name string) (*File, error) {
	b, err := os.ReadFile(name)
	if err != nil {
		return nil, err
	}

	if len(b) < 3500 {
		return nil, fmt.Errorf("%v: save file too small", name)
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
	for i, ch := range f.Chars {
		fmt.Printf("Char #%v\n", i+1)
		fmt.Printf("Lvl %v\n", ch.Lvl)
		fmt.Printf("Exp %v\n", ch.Exp)
		fmt.Printf("HP %v/%v\n", ch.HP, ch.MaxHP)
		fmt.Printf("SP %v/%v\n", ch.SP, ch.MaxSP)
		fmt.Printf("Str %v\n", ch.Str)
		fmt.Printf("Vit %v\n", ch.Vit)
		fmt.Printf("Wit %v\n", ch.Wit)
		fmt.Printf("Agi %v\n", ch.Agi)
		fmt.Printf("\n")
	}

	fmt.Printf("Gold: %v\n", binary.LittleEndian.Uint32(f.Data[GOLD:]))
}

func (f *File) MaxOut() {
	fmt.Println("MAX OUT!")

	for i, ch := range f.Chars {
		ch.MaxHP = 999
		ch.HP = 999
		ch.MaxSP = 999
		ch.SP = 999
		ch.Str = 999
		ch.Vit = 999
		ch.Wit = 999
		ch.Agi = 999
		copy(f.Data[STATS[i]:], makebytes(ch))
	}

	binary.LittleEndian.PutUint32(f.Data[GOLD:], 9999999)
}

func makebytes(v any) []byte {
	w := new(bytes.Buffer)
	binary.Write(w, binary.LittleEndian, v)
	return w.Bytes()
}

const (
	GOLD = 0x330
)

var STATS = []int{
	0x493, // justin
	0x593, // sue
}
