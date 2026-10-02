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
	log.SetPrefix("lunar-story-savemod: ")

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
	fmt.Fprintln(os.Stderr, "usage: [options] cardxx_LUNAR000")
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
	HP               uint16
	MaxHP            uint16
	MP               uint16
	MaxMP            uint16
	Attack           uint16
	Defense          uint16
	Agility          uint16
	Wisdom           uint16
	MagicEnhance     uint16
	NumAttack        uint8
	Range            uint8
	BaseAttack       uint8
	BaseDefense      uint8
	BaseAgility      uint8
	BaseWisdom       uint8
	BaseMagicEnhance uint8
	BaseNumAttack    uint8
	BaseRange        uint8
	BaseLuck         uint8
	Level            uint8
	Luck             uint8
	Weapon           uint8
	Armor            uint8
	Shield           uint8
	Helmet           uint8
	Accessory        [2]uint8
	Pad0             [6]uint8
	Spell            [8]uint8
	Pad1             [6]uint8
	Exp              uint32
	NextExp          uint32
}

func checksum(data []byte) uint32 {
	sum := uint32(0)
	for i := 0; i+3 < len(data); i += 4 {
		sum += binary.LittleEndian.Uint32(data[i:])
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

	f.Checksum = checksum(f.Data[:len(f.Data)-4])

	return f, nil
}

func (f *File) Dump() {
	for i, ch := range f.Chars {
		off := STATS[i]
		fmt.Printf("Char #%v (%#x)\n", i+1, off)
		fmt.Printf("Level: %v\n", ch.Level)
		fmt.Printf("Exp: %v (Next: %v)\n", ch.Exp, ch.NextExp)
		fmt.Printf("HP: %v/%v\n", ch.HP, ch.MaxHP)
		fmt.Printf("MP: %v/%v\n", ch.MP, ch.MaxMP)
		fmt.Printf("Attack: %v [%v]\n", ch.Attack, ch.BaseAttack)
		fmt.Printf("Defense: %v [%v]\n", ch.Defense, ch.BaseDefense)
		fmt.Printf("Agility: %v [%v]\n", ch.Agility, ch.BaseAgility)
		fmt.Printf("Wisdom: %v [%v]\n", ch.Wisdom, ch.BaseWisdom)
		fmt.Printf("Magic Enhance: %v [%v]\n", ch.MagicEnhance, ch.BaseMagicEnhance)
		fmt.Printf("Num Attack: %v [%v]\n", ch.NumAttack, ch.BaseNumAttack)
		fmt.Printf("Range: %v [%v]\n", ch.Range, ch.BaseRange)
		fmt.Printf("Luck: %v [%v]\n", ch.Luck, ch.BaseLuck)
		fmt.Printf("Weapon: %d\n", ch.Weapon)
		fmt.Printf("Armor: %d\n", ch.Armor)
		fmt.Printf("Shield: %d\n", ch.Shield)
		fmt.Printf("Helmet: %d\n", ch.Helmet)
		fmt.Printf("Accessory: %d\n", ch.Accessory)
		fmt.Printf("Spell: %d\n", ch.Spell)
		fmt.Printf("\n")
	}
	fmt.Printf("Gold: %v\n", binary.LittleEndian.Uint32(f.Data[MONEY:]))
	fmt.Printf("Checksum: %#x\n", f.Checksum)
}

func (f *File) MaxOut() {
	fmt.Println("MAX OUT!")
	for i, ch := range f.Chars {
		ch.HP = 999
		ch.MaxHP = 999
		ch.MP = 999
		ch.MaxMP = 999

		ch.Attack = 999
		ch.Defense = 999
		ch.Agility = 999
		ch.Wisdom = 999
		ch.MagicEnhance = 999

		ch.NumAttack = 255
		ch.Range = 255
		ch.Luck = 255

		ch.BaseAttack = 255
		ch.BaseDefense = 255
		ch.BaseAgility = 255
		ch.BaseWisdom = 255
		ch.BaseMagicEnhance = 255
		ch.BaseRange = 255
		ch.BaseLuck = 255
		ch.BaseNumAttack = 255

		copy(f.Data[STATS[i]:], makebytes(ch))
	}
	binary.LittleEndian.PutUint32(f.Data[MONEY:], 99_999_999)

	off := len(f.Data) - 4
	f.Checksum = checksum(f.Data[:off])
	binary.LittleEndian.PutUint32(f.Data[off:], f.Checksum)
}

func makebytes(v any) []byte {
	w := new(bytes.Buffer)
	binary.Write(w, binary.LittleEndian, v)
	return w.Bytes()
}

const (
	MONEY = 0x714
)

var STATS = []int{
	0x318, // char 0
	0x358, // alex
	0x398, // nash
	0x3d8, // jessica
	0x418, // mia
	0x458, // kyle
	0x498, // luna
	0x4d8, // ramus
	0x518, // ghaleon
	0x558, // laike
	0x598, // tempest
	0x5d8, // dragon master alex
}
