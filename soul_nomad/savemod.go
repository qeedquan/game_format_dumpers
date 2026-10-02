package main

import (
	"bytes"
	"encoding/binary"
	"flag"
	"fmt"
	"log"
	"math"
	"os"
)

var (
	maxout = flag.Bool("maxout", false, "max out")
	maxval = flag.Int("maxval", 900_000, "set max value")
)

func main() {
	log.SetFlags(0)
	log.SetPrefix("soul-nomad-savemod: ")

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
	fmt.Fprintln(os.Stderr, "usage: [options] SAVE.dat")
	flag.PrintDefaults()
	os.Exit(2)
}

func check(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

type File struct {
	Data   []byte
	Header Header
	Chars  []Char
}

type Header struct {
	Seed     uint32
	Checksum uint32
	Unk      [0x40]byte
}

type Base struct {
	MaxHP uint32
	Stm   uint32
	HP    uint32
	Unk1  uint32
	Atk   uint32
	Def   uint32
	Int   uint32
	Spd   uint32
	Hit   uint32
	Res   uint32
}

type Stat struct {
	HP  uint32
	Act uint32
	Atk uint32
	Def uint32
	Int uint32
	Spd uint32
	Hit uint32
	Res uint32
}

type Char struct {
	Base Base
	Stat Stat
	Unk  [0x250]byte
}

func checksum(seed uint32, data []byte) uint32 {
	val := uint64(0)
	for i := uint32(0); i <= 32; i++ {
		val += checksum1(seed+i, data)
	}
	return uint32(val)
}

func checksum1(seed uint32, data []byte) uint64 {
	val := uint64(seed)
	res := uint64(0)
	for range 0x1000 {
		val = (val * 0x6d) + 0x3ff
		idx := val % uint64(len(data))
		res += uint64(data[idx])
	}
	return res
}

func decode(name string) (*File, error) {
	b, err := os.ReadFile(name)
	if err != nil {
		return nil, err
	}

	if len(b) != 0x80180 {
		return nil, fmt.Errorf("%v: invalid save file size", name)
	}

	f := &File{
		Data: b,
	}

	r := bytes.NewReader(b[:])
	binary.Read(r, binary.LittleEndian, &f.Header)

	var ch Char
	for i := range CHARS {
		o := STATS + i*CHARSIZE
		r := bytes.NewReader(b[o:])
		binary.Read(r, binary.LittleEndian, &ch)
		f.Chars = append(f.Chars, ch)
	}

	return f, nil
}

func (f *File) Dump() {
	for i, ch := range f.Chars {
		o := STATS + i*CHARSIZE
		fmt.Printf("Char #%d (%#x)\n", i+1, o)
		fmt.Printf("Base\n")
		fmt.Printf("HP: %d/%d\n", ch.Base.HP, ch.Base.MaxHP)
		fmt.Printf("Unk1: %d\n", ch.Base.Unk1)
		fmt.Printf("Stm: %d\n", ch.Base.Stm)
		fmt.Printf("Atk: %d\n", ch.Base.Atk)
		fmt.Printf("Def: %d\n", ch.Base.Def)
		fmt.Printf("Int: %d\n", ch.Base.Int)
		fmt.Printf("Spd: %d\n", ch.Base.Spd)
		fmt.Printf("Hit: %d\n", ch.Base.Hit)
		fmt.Printf("Res: %d\n", ch.Base.Res)
		fmt.Printf("Stats\n")
		fmt.Printf("HP: %d\n", ch.Stat.HP)
		fmt.Printf("Act: %d\n", ch.Stat.Act)
		fmt.Printf("Atk: %d\n", ch.Stat.Atk)
		fmt.Printf("Def: %d\n", ch.Stat.Def)
		fmt.Printf("Int: %d\n", ch.Stat.Int)
		fmt.Printf("Spd: %d\n", ch.Stat.Spd)
		fmt.Printf("Hit: %d\n", ch.Stat.Hit)
		fmt.Printf("Res: %d\n", ch.Stat.Res)
		fmt.Println()
	}
	fmt.Printf("Seed:      %#x\n", f.Header.Seed)
	fmt.Printf("Checksum:  %#x\n", f.Header.Checksum)
	fmt.Printf("GP:        %v\n", binary.LittleEndian.Uint32(f.Data[GP:]))
}

func (f *File) MaxOut() {
	fmt.Println("MAX OUT!")
	for i, ch := range f.Chars {
		o := STATS + i*CHARSIZE
		val := uint32(*maxval)
		ch.Base.MaxHP = val
		ch.Base.HP = val
		ch.Stat.HP = val

		ch.Base.Atk = val
		ch.Base.Def = val
		ch.Base.Int = val
		ch.Base.Spd = val
		ch.Base.Hit = val
		ch.Base.Res = val

		ch.Stat.Atk = val
		ch.Stat.Def = val
		ch.Stat.Int = val
		ch.Stat.Spd = val
		ch.Stat.Hit = val
		ch.Stat.Res = val

		copy(f.Data[o:], makebytes(ch))
	}

	f.Header.Checksum = checksum(f.Header.Seed, f.Data[0x48:])
	copy(f.Data[:], makebytes(f.Header))
	binary.LittleEndian.PutUint32(f.Data[GP:], math.MaxInt32)
}

func makebytes(v any) []byte {
	w := new(bytes.Buffer)
	binary.Write(w, binary.LittleEndian, v)
	return w.Bytes()
}

const (
	GP       = 0x248
	STATS    = 0xfe4
	CHARS    = 200
	CHARSIZE = 0x298
)
