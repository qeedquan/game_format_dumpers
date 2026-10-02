/*

The save files are compressed using zstd

Decompression:
zstd -d savedata.dat -o savedata.bin

Compression:
zstd savedata.bin -o savedata.dat

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
	dp     = flag.Uint64("dp", 0, "specify amount of dp")
)

func main() {
	log.SetFlags(0)
	log.SetPrefix("trails-from-zero-savemod: ")

	flag.Usage = usage
	flag.Parse()
	if flag.NArg() != 1 {
		usage()
	}

	f, err := decode(flag.Arg(0))
	check(err)

	f.Dump()

	if *maxout {
		f.MaxOut(*dp)
		err := os.WriteFile(flag.Arg(0), f.Data, 0644)
		check(err)
	}
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: [options] savedata.bin")
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
	Sepith   []uint16
	DP       uint64
	Mira     uint64
	Medal    uint64
	Checksum [2]uint32
}

type Char struct {
	MaxHP uint32
	HP    uint32
	Lv    uint16
	MaxEP uint16
	EP    uint16
	CP    uint16
	Exp   uint32
	Str   uint16
	Def   uint16
	Ats   uint16
	Adf   uint16
	Dex   uint16
	Agl   uint16
	Mov   uint16
	Spd   uint16
	Dex2  uint16
	Agl2  uint16
	Unk   [0x10]byte
}

func decode(name string) (*File, error) {
	b, err := os.ReadFile(name)
	if err != nil {
		return nil, err
	}

	n := len(b)
	if n < 155624 {
		return nil, fmt.Errorf("%v: save file too small", name)
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

	var v uint16
	for _, o := range SEPITH {
		r := bytes.NewReader(b[o:])
		binary.Read(r, binary.LittleEndian, &v)
		f.Sepith = append(f.Sepith, v)
	}

	f.DP = binary.LittleEndian.Uint64(b[DP:])
	f.Mira = binary.LittleEndian.Uint64(b[MIRA:])
	f.Medal = binary.LittleEndian.Uint64(b[MEDAL:])

	f.Checksum[0] = binary.LittleEndian.Uint32(b[n-8:])
	f.Checksum[1] = binary.LittleEndian.Uint32(b[n-4:])

	return f, nil
}

func (f *File) Dump() {
	for i, ch := range f.Chars {
		fmt.Printf("Char #%v\n", i+1)
		fmt.Printf("Lv %v\n", ch.Lv)
		fmt.Printf("HP %v/%v\n", ch.HP, ch.MaxHP)
		fmt.Printf("EP %v/%v\n", ch.EP, ch.MaxEP)
		fmt.Printf("CP %v\n", ch.CP)
		fmt.Printf("Exp %v\n", ch.Exp)
		fmt.Printf("Str %v\n", ch.Str)
		fmt.Printf("Def %v\n", ch.Def)
		fmt.Printf("Ats %v\n", ch.Ats)
		fmt.Printf("Adf %v\n", ch.Adf)
		fmt.Printf("Dex %v (%v)\n", ch.Dex, ch.Dex2)
		fmt.Printf("Agl %v (%v)\n", ch.Agl, ch.Agl2)
		fmt.Printf("Mov %v\n", ch.Mov)
		fmt.Printf("Spd %v\n", ch.Spd)
		fmt.Printf("Unk %# x\n", ch.Unk)
		fmt.Printf("\n")
	}

	fmt.Printf("Sepith: % d\n", f.Sepith)
	fmt.Printf("DP: %d\n", f.DP)
	fmt.Printf("Mira: %d\n", f.Mira)
	fmt.Printf("Medal: %d\n", f.Medal)
	fmt.Printf("\n")
	fmt.Printf("Checksum: %#x\n", f.Checksum)
}

func (f *File) MaxOut(dp uint64) {
	fmt.Println("MAX OUT!")
	for i, ch := range f.Chars {
		ch.Exp = math.MaxInt32
		copy(f.Data[STATS[i]:], makebytes(ch))
	}

	for i, sp := range f.Sepith {
		sp = 9999
		copy(f.Data[SEPITH[i]:], makebytes(sp))
	}

	if dp > 0 {
		f.DP = dp
	}
	f.Mira = 99999999
	f.Medal = 99999999
	copy(f.Data[DP:], makebytes(f.DP))
	copy(f.Data[MIRA:], makebytes(f.Mira))
	copy(f.Data[MEDAL:], makebytes(f.Medal))

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
	DP    = 0x19ba8
	MIRA  = 0x19bb8
	MEDAL = 0x19bc0
)

var STATS = []int{
	0x98,  // lloyd
	0xcc,  // elie
	0x100, // tio
	0x134, // randy
	0x19c, // yin
	0x1d0, // estelle
	0x204, // joshua
	0x238, // noel
	0x26c, // dudley
}

var SEPITH = []int{
	0x19bc8,
	0x19bcc,
	0x19bd0,
	0x19bd4,
	0x19bd8,
	0x19bdc,
	0x19be0,
}
