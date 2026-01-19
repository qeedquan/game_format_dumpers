// http://aluigi.altervista.org/papers.htm

package main

import (
	"bytes"
	"encoding/binary"
	"flag"
	"fmt"
	"hash/crc32"
	"log"
	"os"
)

var (
	level  = flag.Int("l", 65535, "set level")
	crypt  = flag.Bool("e", false, "encrypt")
	maxout = flag.Bool("m", false, "max out")
)

func main() {
	log.SetFlags(0)
	log.SetPrefix("ysof-savemod: ")

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
		f.MaxOut(uint16(*level))
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
	Gold  uint32
	Level uint16
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
	const sig = "Ys3"

	if len(b) != 7208 {
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
	decrypt(x, b[0x30:0xbc])

	crc = crc32.Checksum(b[0xbc:0x1c28], crc32.IEEETable)
	yscrc = binary.LittleEndian.Uint32(b[0xb0:])
	if crc != yscrc {
		return fmt.Errorf("crc2 mismatch: %#x %#x\n", crc, yscrc)
	}

	y := binary.LittleEndian.Uint32(b[0xac:])
	decrypt(y, b[0xbc:])

	return nil
}

func encode(p []byte) []byte {
	b := append([]byte{}, p...)
	x := binary.LittleEndian.Uint32(b[0x10:])
	y := binary.LittleEndian.Uint32(b[0xac:])

	encrypt(y, b[0xbc:])
	binary.LittleEndian.PutUint32(b[0xb0:], crc32.Checksum(b[0xbc:], crc32.IEEETable))

	encrypt(x, b[0x30:0xbc])
	binary.LittleEndian.PutUint32(b[0x0c:], crc32.Checksum(b[0x30:0x60], crc32.IEEETable))

	return b
}

func newfile(b []byte) *File {
	f := &File{Data: b}
	r := bytes.NewReader(b[STAT:])
	binary.Read(r, binary.LittleEndian, &f.Stat)
	return f
}

func (f *File) Dump() {
	s := &f.Stat
	fmt.Printf("Display Level: %v\n", binary.LittleEndian.Uint16(f.Data[DISPLAY_LEVEL:]))
	fmt.Printf("Gold:          %v\n", s.Gold)
	fmt.Printf("Level:         %v\n", s.Level)
}

func (f *File) MaxOut(level uint16) {
	fmt.Println("MAX OUT!")

	f.Stat = Stat{
		Gold:  9999999,
		Level: level,
	}
	copy(f.Data[STAT:], makebytes(f.Stat))

	binary.LittleEndian.PutUint16(f.Data[DISPLAY_LEVEL:], level)
}

func makebytes(v any) []byte {
	w := new(bytes.Buffer)
	binary.Write(w, binary.LittleEndian, v)
	return w.Bytes()
}

const (
	DISPLAY_LEVEL = 0x34
	STAT          = 0x294
)
