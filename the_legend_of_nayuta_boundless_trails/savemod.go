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
	log.SetPrefix("legends-of-nayuta-savemod: ")

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
	fmt.Fprintln(os.Stderr, "usage: [options] savedata.dat")
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
	Level    uint16
	Mira     uint32
	Items    []uint16
	Checksum [2]uint32
}

func decode(name string) (*File, error) {
	b, err := os.ReadFile(name)
	if err != nil {
		return nil, err
	}

	n := len(b)
	if n != 819200 {
		return nil, fmt.Errorf("%v: invalid save file", name)
	}

	f := &File{
		Data: b,
	}

	f.Level = binary.LittleEndian.Uint16(b[LEVEL:])
	f.Mira = binary.LittleEndian.Uint32(b[MIRA:])
	for i := 0; i < NUM_ITEMS; i++ {
		f.Items = append(f.Items, binary.LittleEndian.Uint16(b[ITEMS+i*2:]))
	}

	f.Checksum[0] = binary.LittleEndian.Uint32(b[n-8:])
	f.Checksum[1] = binary.LittleEndian.Uint32(b[n-4:])

	return f, nil
}

func (f *File) Dump() {
	fmt.Printf("Level: %d\n", f.Level)
	fmt.Printf("Mira: %d\n", f.Mira)
	for i := range f.Items {
		fmt.Printf("Item %d: %d\n", i+1, f.Items[i])
	}
	fmt.Printf("Checksum: %#x\n", f.Checksum)
}

func (f *File) MaxOut() {
	fmt.Println("MAX OUT!")

	f.Level = 99
	copy(f.Data[LEVEL:], makebytes(f.Level))

	f.Mira = 9999999
	copy(f.Data[MIRA:], makebytes(f.Mira))

	for i := range f.Items {
		if f.Items[i] != 0 && f.Items[i] < 99 {
			f.Items[i] = 99
		}
	}
	copy(f.Data[ITEMS:], makebytes(f.Items))

	n := len(f.Data)
	f.Checksum = checksum(f.Data[:n-8])
	copy(f.Data[n-8:], makebytes(f.Checksum))
}

func makebytes(v any) []byte {
	w := new(bytes.Buffer)
	binary.Write(w, binary.LittleEndian, v)
	return w.Bytes()
}

func checksum(b []byte) [2]uint32 {
	var c0, c1 uint32
	n := len(b)
	i := 0
	for ; i+3 < n; i += 4 {
		c0 += binary.LittleEndian.Uint32(b[i:])
		c1 += ^binary.LittleEndian.Uint32(b[i:])
	}

	var v uint32
	for ; i < n; i++ {
		v = (v << 8) | uint32(b[i])
	}
	if v != 0 {
		c0, c1 = c0+v, c1+^v
	}
	return [2]uint32{c0, c1}
}

const (
	LEVEL     = 0x4
	MIRA      = 0x394
	ITEMS     = 0x54a8
	NUM_ITEMS = 512
)
