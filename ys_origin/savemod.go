// http://aluigi.altervista.org/papers.htm

package main

import (
	"bytes"
	"encoding/binary"
	"flag"
	"fmt"
	"hash/crc32"
	"log"
	"math"
	"os"
)

var (
	level  = flag.Int("l", 5e5, "set level")
	crypt  = flag.Bool("e", false, "encrypt")
	maxout = flag.Bool("m", false, "max out")
)

func main() {
	log.SetFlags(0)
	log.SetPrefix("yso-savemod: ")

	flag.Parse()
	if flag.NArg() < 1 {
		usage()
	}

	b, err := os.ReadFile(flag.Arg(0))
	check(err)

	if !*crypt {
		err = decode(b)
		check(err)
	}

	f := newfile(b)
	if *maxout {
		f.MaxOut(uint32(*level))
	}
	f.Dump()

	if *crypt {
		f.Data = encode(f.Data)
	}

	if flag.NArg() >= 2 {
		err = os.WriteFile(flag.Arg(1), f.Data, 0644)
		check(err)
	}
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: [options] save.nacci output")
	flag.PrintDefaults()
	os.Exit(2)
}

func check(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

type File struct {
	Data []byte
	Stat Stat
}

type Stat struct {
	Level uint32
	HP    uint32
	MP    uint32
	MaxHP uint32
	MaxMP uint32
	Exp   uint32
	SP    uint32
}

func encrypt(v uint32, b []byte) {
	for i := range b {
		v *= 0x3d09
		b[i] += byte(v >> 16)
	}
}

func decrypt(v uint32, b []byte) {
	for i := range b {
		v *= 0x3d09
		b[i] -= byte(v >> 16)
	}
}

func decode(b []byte) error {
	const sig = "YsO"

	if len(b) != 8136 {
		return fmt.Errorf("invalid save file size")
	}

	if bytes.Compare(b[:len(sig)], []byte(sig)) != 0 {
		return fmt.Errorf("invalid header signature")
	}

	crc := crc32.Checksum(b[0x30:0x60], crc32.IEEETable)
	yscrc := binary.LittleEndian.Uint32(b[0x0c:])
	if crc != yscrc {
		return fmt.Errorf("crc1 mismatch: %#x %#x\n", crc, yscrc)
	}

	x := binary.LittleEndian.Uint32(b[0x10:])
	decrypt(x, b[0x30:0xd0])

	crc = crc32.Checksum(b[0xd0:0x1fc8], crc32.IEEETable)
	yscrc = binary.LittleEndian.Uint32(b[0xc4:])
	if crc != yscrc {
		return fmt.Errorf("crc2 mismatch: %#x %#x\n", crc, yscrc)
	}

	y := binary.LittleEndian.Uint32(b[0xc0:])
	decrypt(y, b[0xd0:])

	return nil
}

func encode(p []byte) []byte {
	b := append([]byte{}, p...)
	x := binary.LittleEndian.Uint32(b[0x10:])
	y := binary.LittleEndian.Uint32(b[0xc0:])

	encrypt(y, b[0xd0:])
	binary.LittleEndian.PutUint32(b[0xc4:], crc32.Checksum(b[0xd0:], crc32.IEEETable))

	encrypt(x, b[0x30:0xd0])
	binary.LittleEndian.PutUint32(b[0x0c:], crc32.Checksum(b[0x30:0x60], crc32.IEEETable))

	return b
}

func newfile(b []byte) *File {
	f := &File{Data: b}
	r := bytes.NewReader(b[DISPLAY_STAT:])
	binary.Read(r, binary.LittleEndian, &f.Stat)
	return f
}

func (f *File) Dump() {
	s := &f.Stat
	fmt.Printf("Level:      %v\n", s.Level)
	fmt.Printf("Exp:        %v\n", s.Exp)
	fmt.Printf("HP:         %v/%v\n", s.HP, s.MaxHP)
	fmt.Printf("MP:         %v/%v\n", s.MP, s.MaxMP)
	fmt.Printf("SP:         %v\n", s.SP)
}

func (f *File) MaxOut(level uint32) {
	fmt.Println("MAX OUT!")

	f.Stat.Level = level
	f.Stat.SP = math.MaxInt32
	copy(f.Data[DISPLAY_STAT:], makebytes(f.Stat))
	binary.LittleEndian.PutUint32(f.Data[SP:], f.Stat.SP)
	binary.LittleEndian.PutUint32(f.Data[LEVEL:], f.Stat.Level)
}

func makebytes(v any) []byte {
	w := new(bytes.Buffer)
	binary.Write(w, binary.LittleEndian, v)
	return w.Bytes()
}

const (
	DISPLAY_STAT = 0x34
	SP           = 0x48c
	LEVEL        = 0x490
)
