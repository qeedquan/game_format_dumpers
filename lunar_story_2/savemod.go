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
	Data     []byte
	Chars    []Char
	Checksum uint32
}

type Char struct {
	XP     uint32
	NextXP uint32

	// stats are based on levels, will get overwritten after loading
	HP           uint16
	MaxHP        uint16
	MP           uint16
	MaxMP        uint16
	Attack       uint16
	Attacks      uint16
	Defense      uint16
	Agility      uint16
	Speed        uint16
	Wisdom       uint16
	MagicDefense uint16
	Range        uint16
	Luck         uint16
	Unk          [0xa0]byte
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

	f.Checksum = checksum(f.Data[0x300:])

	return f, nil
}

func (f *File) Dump() {
	for i, ch := range f.Chars {
		off := STATS[i]
		fmt.Printf("Char #%v (%#x)\n", i+1, off)
		fmt.Printf("XP: %v (Next: %v)\n", ch.XP, ch.NextXP)
		fmt.Printf("HP: %v/%v\n", ch.HP, ch.MaxHP)
		fmt.Printf("MP: %v/%v\n", ch.MP, ch.MaxMP)
		fmt.Printf("Attack: %v\n", ch.Attack)
		fmt.Printf("Attacks: %v\n", ch.Attacks)
		fmt.Printf("Defense: %v\n", ch.Defense)
		fmt.Printf("Agility: %v\n", ch.Agility)
		fmt.Printf("Speed: %v\n", ch.Speed)
		fmt.Printf("Wisdom: %v\n", ch.Wisdom)
		fmt.Printf("Magic Defense: %v\n", ch.MagicDefense)
		fmt.Printf("Range: %v\n", ch.Range)
		fmt.Printf("Luck: %v\n", ch.Luck)
		fmt.Println()
	}
	fmt.Printf("Gold: %d\n", binary.LittleEndian.Uint32(f.Data[GOLD:]))
	fmt.Printf("Checksum: %#x\n", f.Checksum)
}

func (f *File) MaxOut() {
	fmt.Println("MAX OUT!")
	for i, ch := range f.Chars {
		ch.XP = 999_999_999
		copy(f.Data[STATS[i]:], makebytes(ch))
	}
	binary.LittleEndian.PutUint32(f.Data[GOLD:], 99_999_999)
	f.Checksum = checksum(f.Data[0x300:])
	binary.LittleEndian.PutUint32(f.Data[0x204:], f.Checksum)
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
	0x7ac, // lucia
}
