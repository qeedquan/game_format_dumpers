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
	log.SetPrefix("grandia-2-savemod: ")

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
	fmt.Fprintln(os.Stderr, "usage: [options] save.vms")
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
	Lvl   uint16
	Exp   uint32
	Next  uint32
	MaxHP uint16
	HP    uint16
	MaxMP uint16
	MP    uint16
	MaxSP uint16
	SP    uint16
	Str   uint16
	Vit   uint16
	Agi   uint16
	Spd   uint16
	Mag   uint16
	Men   uint16
}

func decode(name string) (*File, error) {
	const sig = "GRANDIA2"

	b, err := os.ReadFile(name)
	if err != nil {
		return nil, err
	}

	if len(b) < 4000 {
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
	for i, ch := range f.Chars {
		fmt.Printf("Char #%v\n", i+1)
		fmt.Printf("Lvl %v\n", ch.Lvl)
		fmt.Printf("Exp %v\n", ch.Exp)
		fmt.Printf("Next %v\n", ch.Next)
		fmt.Printf("HP %v/%v\n", ch.HP, ch.MaxHP)
		fmt.Printf("MP %v/%v\n", ch.MP, ch.MaxMP)
		fmt.Printf("SP %v/%v\n", ch.SP, ch.MaxSP)
		fmt.Printf("Str %v\n", ch.Str)
		fmt.Printf("Agi %v\n", ch.Agi)
		fmt.Printf("Mag %v\n", ch.Mag)
		fmt.Printf("Vit %v\n", ch.Vit)
		fmt.Printf("Spd %v\n", ch.Spd)
		fmt.Printf("Men %v\n", ch.Men)
		fmt.Printf("\n")
	}

	fmt.Printf("Special Coins: %v\n", binary.LittleEndian.Uint32(f.Data[SPECIAL_COINS:]))
	fmt.Printf("Magic Coins:   %v\n", binary.LittleEndian.Uint32(f.Data[MAGIC_COINS:]))
	fmt.Printf("Gold:          %v\n", binary.LittleEndian.Uint32(f.Data[GOLD:]))
}

func (f *File) MaxOut() {
	fmt.Println("MAX OUT!")

	for i, ch := range f.Chars {
		ch.MaxHP = 9999
		ch.HP = 9999
		ch.MaxMP = 999
		ch.MP = 999
		ch.MaxSP = 999
		ch.SP = 999
		ch.Str = 999
		ch.Agi = 999
		ch.Mag = 999
		ch.Vit = 999
		ch.Men = 999
		ch.Spd = 999
		copy(f.Data[STATS[i]:], makebytes(ch))
	}

	binary.LittleEndian.PutUint32(f.Data[SPECIAL_COINS:], 99999)
	binary.LittleEndian.PutUint32(f.Data[MAGIC_COINS:], 99999)
	binary.LittleEndian.PutUint32(f.Data[GOLD:], 9999999)
}

func makebytes(v any) []byte {
	w := new(bytes.Buffer)
	binary.Write(w, binary.LittleEndian, v)
	return w.Bytes()
}

const (
	SPECIAL_COINS = 0x2c4
	MAGIC_COINS   = 0x2c8
	GOLD          = 0x2c0
)

var STATS = []int{
	0x31a, // ryudo
	0x386, // elena
	0x3f2, // millenia
	0x45e, // roan 1
	0x4ca, // tio
	0x536, // mareg
	0x5a2, // roan 2
}
