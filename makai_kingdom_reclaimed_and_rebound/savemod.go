/*

The save files are compressed using zstd

Decompression:
(This can fail on some zstd version, alternative is to use ark archiver)
zstd -d SAVE000.dat -o SAVE000.bin

Compression:
zstd SAVE000.bin -o SAVE000.dat

*/

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
)

func main() {
	log.SetFlags(0)
	log.SetPrefix("makai-kingdom-savemod: ")

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
	fmt.Fprintln(os.Stderr, "usage: [options] SAVE000.dat")
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
	HL    uint64
}

type Stat struct {
	HP  uint32
	SP  uint32
	Atk uint32
	Def uint32
	Int uint32
	Res uint32
	Tec uint32
}

type Char struct {
	HP0           uint32
	SP0           uint32
	HP1           uint32
	SP1           uint32
	Base          Stat
	Reincarnation uint32
	Stat          Stat
	Unk0          [12]byte
	Mana          uint32
	Unk1          [0x15a]byte
	Lvl           uint32
	Unk2          [0x11c]byte
}

func decode(name string) (*File, error) {
	b, err := os.ReadFile(name)
	if err != nil {
		return nil, err
	}

	n := len(b)
	if n != 262144 {
		return nil, fmt.Errorf("%v: invalid save file size", name)
	}

	f := &File{
		Data: b,
	}

	var ch Char
	for i := range CHARS {
		o := STATS + i*CHARSIZE
		r := bytes.NewReader(b[o:])
		binary.Read(r, binary.LittleEndian, &ch)
		if ch.HP0 == 0 && ch.HP1 == 0 {
			break
		}
		f.Chars = append(f.Chars, ch)
	}

	f.HL = binary.LittleEndian.Uint64(b[HL:])
	return f, nil
}

func (f *File) dumpstats(ch *Stat) {
	fmt.Printf("HP: %d\n", ch.HP)
	fmt.Printf("SP: %d\n", ch.SP)
	fmt.Printf("Atk: %d\n", ch.Atk)
	fmt.Printf("Def: %d\n", ch.Def)
	fmt.Printf("Int: %d\n", ch.Int)
	fmt.Printf("Res: %d\n", ch.Res)
	fmt.Printf("Tec: %d\n", ch.Tec)
}

func (f *File) Dump() {
	for i, ch := range f.Chars {
		o := STATS + i*CHARSIZE
		fmt.Printf("Char #%d (%#x)\n", i+1, o)
		fmt.Printf("Lvl: %d\n", ch.Lvl)
		fmt.Printf("Mana: %d\n", ch.Mana)
		fmt.Printf("HP: %d/%d\n", ch.HP0, ch.HP1)
		fmt.Printf("SP: %d/%d\n", ch.SP0, ch.SP1)
		fmt.Printf("Base\n")
		f.dumpstats(&ch.Base)
		fmt.Printf("Stats\n")
		f.dumpstats(&ch.Stat)
		fmt.Println()
	}
	fmt.Printf("HL: %d\n", f.HL)
}

func (f *File) MaxOut() {
	fmt.Println("MAX OUT!")

	for i, ch := range f.Chars {
		ch.HP0 = 9_999_999
		ch.HP1 = 9_999_999
		ch.SP0 = 9_999_999
		ch.SP1 = 9_999_999
		ch.Mana = 9_999_999

		ch.Base.HP = 9_999_999
		ch.Base.SP = 9_999_999
		ch.Base.Atk = 9_999_999
		ch.Base.Def = 9_999_999
		ch.Base.Int = 9_999_999
		ch.Base.Res = 9_999_999
		ch.Base.Tec = 9_999_999

		ch.Stat = ch.Base

		o := STATS + i*CHARSIZE
		copy(f.Data[o:], makebytes(ch))
	}

	f.HL = math.MaxInt64 >> 1
	copy(f.Data[HL:], makebytes(f.HL))
}

func makebytes(v any) []byte {
	w := new(bytes.Buffer)
	binary.Write(w, binary.LittleEndian, v)
	return w.Bytes()
}

const (
	HL       = 0x2d0
	STATS    = 0x354
	CHARS    = 127
	CHARSIZE = 0x2d8
)
