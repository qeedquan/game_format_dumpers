/*

Uncompress:
cat SAVE.dat | unzstd > save.bin

Compress:
zstd save.bin -o SAVE.dat

*/

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
	log.SetPrefix("grandia-savemod: ")

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
	LV    uint16
	MaxHP uint32
	MaxMP uint32
	HP    uint32
	MP    uint32
	SAT   uint32
	SDF   uint32
	LAT   uint32
	SPD   uint32
	HIT   uint32
	LDF   uint32
}

func decode(name string) (*File, error) {
	b, err := os.ReadFile(name)
	if err != nil {
		return nil, err
	}

	if len(b) < 0x10000 {
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

	return f, nil
}

func (f *File) Dump() {
	for i, ch := range f.Chars {
		fmt.Printf("Char #%v\n", i+1)
		fmt.Printf("LV %v\n", ch.LV)
		fmt.Printf("HP %v/%v\n", ch.HP, ch.MaxHP)
		fmt.Printf("HP %v/%v\n", ch.MP, ch.MaxMP)
		fmt.Printf("SAT %v\n", ch.SAT)
		fmt.Printf("LAT %v\n", ch.LAT)
		fmt.Printf("HIT %v\n", ch.HIT)
		fmt.Printf("SDF %v\n", ch.SDF)
		fmt.Printf("LDF %v\n", ch.LDF)
		fmt.Printf("SPD %v\n", ch.SPD)
		fmt.Printf("\n")
	}

	fmt.Printf("Display Total LV: %v\n", binary.LittleEndian.Uint32(f.Data[DISPLAY_TOTAL_LV:]))
	fmt.Printf("Total LV: %v\n", binary.LittleEndian.Uint32(f.Data[TOTAL_LV:]))
	fmt.Printf("Gold: %v\n", binary.LittleEndian.Uint64(f.Data[MONEY:]))
	fmt.Printf("Living Expense: %v\n", binary.LittleEndian.Uint32(f.Data[LIVING_EXPENSE:]))
}

func (f *File) MaxOut() {
	fmt.Println("MAX OUT!")
	binary.LittleEndian.PutUint32(f.Data[DISPLAY_TOTAL_LV:], 999_999)
	binary.LittleEndian.PutUint32(f.Data[TOTAL_LV:], 999_999)
	binary.LittleEndian.PutUint64(f.Data[MONEY:], 999_999_999_999)
	binary.LittleEndian.PutUint32(f.Data[LIVING_EXPENSE:], 999_999_999)
}

func makebytes(v any) []byte {
	w := new(bytes.Buffer)
	binary.Write(w, binary.LittleEndian, v)
	return w.Bytes()
}

const (
	DISPLAY_TOTAL_LV = 0x20
	TOTAL_LV         = 0x7bc68
	MONEY            = 0x2f8
	LIVING_EXPENSE   = 0x94854
)

var STATS = []int{
	0x215a,
}
