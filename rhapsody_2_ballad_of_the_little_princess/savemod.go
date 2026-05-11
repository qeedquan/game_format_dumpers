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
	log.SetPrefix("rhapsody2-savemod: ")

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
	ID        uint16
	HP        uint16
	Exp       uint32
	Unk1      [2]byte
	Puppet    [3]uint16 // puppet id
	Unk2      [4]byte
	Equipment [3]uint16 // item id
	Unk3      [0x16]byte
}

func decode(name string) (*File, error) {
	const sig = "\x00\x00\x00\x00"

	b, err := os.ReadFile(name)
	if err != nil {
		return nil, err
	}

	if len(b) < 8192 {
		return nil, fmt.Errorf("%v: save file too small", name)
	}

	if bytes.Compare(b[:len(sig)], []byte(sig)) != 0 {
		return nil, fmt.Errorf("%v: invalid header signature", name)
	}

	size := binary.LittleEndian.Uint32(b[4:])
	if int(size) != len(b)-16 {
		return nil, fmt.Errorf("%v: size field does not match file size: %v vs %v bytes", name, size, len(b))
	}

	f := &File{
		Data: b,
	}

	for off := CHAROFF; ; off += CHARSIZE {
		var ch Char
		r := bytes.NewReader(b[off:])
		err := binary.Read(r, binary.LittleEndian, &ch)
		if err != nil || ch.Exp == 0 {
			break
		}
		f.Chars = append(f.Chars, ch)
	}

	return f, nil
}

func (f *File) Dump() {
	for i, ch := range f.Chars {
		fmt.Printf("Char #%v %#x\n", i+1, CHAROFF+CHARSIZE*i)
		fmt.Printf("ID: % d\n", ch.ID)
		fmt.Printf("Exp: %d\n", ch.Exp)
		fmt.Printf("Equipment: % x\n", ch.Equipment)
		fmt.Printf("Puppet: % x\n", ch.Puppet)
		fmt.Printf("Unk1: % d\n", ch.Unk1)
		fmt.Printf("Unk2: % d\n", ch.Unk2)
		fmt.Printf("Unk3: % d\n", ch.Unk3)
		fmt.Printf("\n")
	}

	fmt.Printf("Display Inotium: %v\n", binary.LittleEndian.Uint32(f.Data[DISPLAY_INOTIUM:]))
	fmt.Printf("Inotium:         %v\n", binary.LittleEndian.Uint32(f.Data[INOTIUM:]))
}

func (f *File) MaxOut() {
	fmt.Println("MAX OUT!")

	// the stats are based on level
	for i, ch := range f.Chars {
		off := CHAROFF + CHARSIZE*i
		ch.Exp = 9999999
		copy(f.Data[off:], makebytes(ch))
	}

	binary.LittleEndian.PutUint32(f.Data[DISPLAY_INOTIUM:], 99999999)
	binary.LittleEndian.PutUint32(f.Data[INOTIUM:], 99999999)

	f.syncChecksum()
}

func (f *File) syncChecksum() {
	sum := checksum(f.Data[0x410:], 0x1f)
	sum = ^sum + 1
	binary.LittleEndian.PutUint32(f.Data[0x48c:], sum)
}

func makebytes(v any) []byte {
	w := new(bytes.Buffer)
	binary.Write(w, binary.LittleEndian, v)
	return w.Bytes()
}

func checksum(b []byte, n int) uint32 {
	c := uint32(0)
	for i := 0; i+3 < len(b) && i < 4*n; i += 4 {
		c += binary.LittleEndian.Uint32(b[i:])
	}
	return c
}

const (
	DISPLAY_INOTIUM = 0x418
	INOTIUM         = 0x498

	CHAROFF  = 0x1610
	CHARSIZE = 0x30
)
