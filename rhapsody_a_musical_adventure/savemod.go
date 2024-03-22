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
	log.SetPrefix("rhapsody-savemod: ")

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
	Sig   uint32
}

type Char struct {
	Exp      uint32
	SkillExp uint32
	MaxHP    uint16
	MaxMP    uint16
	HP       uint16
	MP       uint16
	Off      uint16
	Def      uint16
	Agi      uint16
	Int      uint16
	Lvl      uint8
	Skill    uint8
	Mov      uint8
	Unk      [8]uint8
}

func decode(name string) (*File, error) {
	const sig = "\x00\x00\x00\x00"

	b, err := os.ReadFile(name)
	if err != nil {
		return nil, err
	}

	if len(b) < 5000 {
		return nil, fmt.Errorf("%v: save file too small", name)
	}

	if bytes.Compare(b[:len(sig)], []byte(sig)) != 0 {
		return nil, fmt.Errorf("%v: invalid header signature", name)
	}

	size := binary.LittleEndian.Uint32(b[4:]) + 8
	if int(size) != len(b) {
		return nil, fmt.Errorf("%v: size field does not match file size: %v vs %v bytes", name, size, len(b))
	}

	sum1 := checksum(b[0x208:], 0x20)
	sum2 := checksum(b[0x288:], 0x260)
	if sum1 != 0 || sum2 != 0 {
		return nil, fmt.Errorf("%v: checksum does not sum to zero: %#x %#x", name, sum1, sum2)
	}

	sig1 := binary.LittleEndian.Uint32(b[0x280:])
	sig2 := binary.LittleEndian.Uint32(b[0xc04:])
	sig3 := binary.LittleEndian.Uint32(b[len(b)-4:])
	if sig1 != sig2 || sig2 != sig3 {
		return nil, fmt.Errorf("%v: signature mismatch: %#x %#x %#x", name, sig1, sig2, sig3)
	}

	f := &File{
		Data: b,
		Sig:  sig1,
	}

	for off := CHAROFF; ; off += CHARSIZE {
		var ch Char

		r := bytes.NewReader(b[off:])
		err := binary.Read(r, binary.LittleEndian, &ch)
		if err != nil || ch.Lvl == 0 {
			break
		}
		f.Chars = append(f.Chars, ch)
	}

	return f, nil
}

func (f *File) Dump() {
	fmt.Printf("Signature: %#x\n\n", f.Sig)

	for i, ch := range f.Chars {
		fmt.Printf("Char #%v\n", i+1)
		fmt.Printf("Lvl %v\n", ch.Lvl)
		fmt.Printf("Exp %v\n", ch.Exp)
		fmt.Printf("Skill Exp %v\n", ch.SkillExp)
		fmt.Printf("HP %v/%v\n", ch.HP, ch.MaxHP)
		fmt.Printf("MP %v/%v\n", ch.MP, ch.MaxMP)
		fmt.Printf("Off   %d\n", ch.Off)
		fmt.Printf("Def   %d\n", ch.Def)
		fmt.Printf("Agi   %d\n", ch.Agi)
		fmt.Printf("Int   %d\n", ch.Int)
		fmt.Printf("Mov   %d\n", ch.Mov)
		fmt.Printf("Skill %d\n", ch.Skill)
		fmt.Printf("Unk   %v\n", ch.Unk)
		fmt.Printf("\n")
	}

	fmt.Printf("Display Inotium: %v\n", binary.LittleEndian.Uint32(f.Data[DISPLAY_INOTIUM:]))
	fmt.Printf("Inotium:         %v\n", binary.LittleEndian.Uint32(f.Data[INOTIUM:]))
}

func (f *File) MaxOut() {
	fmt.Println("MAX OUT!")

	for i, ch := range f.Chars {
		ch.MaxHP = 9999
		ch.MaxMP = 9999
		ch.HP = 9999
		ch.MP = 9999
		ch.Off = 999
		ch.Def = 999
		ch.Agi = 999
		ch.Int = 999
		ch.Mov = 99

		off := CHAROFF + CHARSIZE*i
		copy(f.Data[off:], makebytes(ch))
	}

	binary.LittleEndian.PutUint32(f.Data[DISPLAY_INOTIUM:], 999999999)
	binary.LittleEndian.PutUint32(f.Data[INOTIUM:], 999999999)

	f.syncChecksum()
}

func (f *File) syncChecksum() {
	sum := checksum(f.Data[0x288:], 0x25f)
	sum = ^sum + 1
	binary.LittleEndian.PutUint32(f.Data[0xc04:], sum)
	binary.LittleEndian.PutUint32(f.Data[0x280:], sum)
	binary.LittleEndian.PutUint32(f.Data[len(f.Data)-4:], sum)

	sum = checksum(f.Data[0x208:], 0x1f)
	sum = ^sum + 1
	binary.LittleEndian.PutUint32(f.Data[0x284:], sum)
}

func makebytes(v any) []byte {
	w := new(bytes.Buffer)
	binary.Write(w, binary.LittleEndian, v)
	return w.Bytes()
}

func checksum(b []byte, n int) uint32 {
	c := uint32(0)
	for i := 0; i < 4*n; i += 4 {
		c += binary.LittleEndian.Uint32(b[i:])
	}
	return c
}

const (
	DISPLAY_INOTIUM = 0x20c
	INOTIUM         = 0x2a0

	CHAROFF  = 0x6ac
	CHARSIZE = 36
)
