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
	nchars = flag.Int("nchars", 3, "number of characters")
	offset = flag.Int("offset", 0, "constant offset to apply")
)

func main() {
	defer func() {
		if err := recover(); err != nil {
			log.Fatal("invalid offset parameter")
		}
	}()

	log.SetFlags(0)
	log.SetPrefix("la-pucelle-ragnarok-savemod: ")

	flag.Parse()
	if flag.NArg() != 1 {
		usage()
	}

	f, err := decode(flag.Arg(0), *nchars, *offset)
	check(err)

	f.Dump()

	if *maxout {
		f.MaxOut()
		err := os.WriteFile(flag.Arg(0), f.Data, 0644)
		check(err)
	}
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: [options] save.slot")
	flag.PrintDefaults()
	os.Exit(2)
}

func check(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

type File struct {
	Data   []byte
	Chars  []Char
	Offset int
}

type Stat struct {
	Lvl uint32
	HP  uint32
	SP  uint32
	Atk uint32
	Int uint32
	Def uint32
	Spd uint32
	Hit uint32
	Res uint32
}

type Char struct {
	Base Stat
	Stat Stat
}

func decode(name string, nchars int, offset int) (*File, error) {
	b, err := os.ReadFile(name)
	if err != nil {
		return nil, err
	}

	if len(b) < 400*1024 {
		return nil, fmt.Errorf("%v: save file too small", name)
	}

	f := &File{
		Data:   b,
		Offset: offset,
	}

	var ch Char
	for i := 0; i < nchars; i++ {
		o := (CHAR + offset) + CHARSIZE*i
		if o >= len(b) {
			break
		}
		r := bytes.NewReader(b[o:])
		binary.Read(r, binary.LittleEndian, &ch)
		f.Chars = append(f.Chars, ch)
	}

	return f, nil
}

func (*File) dumpstat(s *Stat) {
	fmt.Printf("Lvl %v\n", s.Lvl)
	fmt.Printf("HP  %v\n", s.HP)
	fmt.Printf("SP  %v\n", s.SP)
	fmt.Printf("Atk %v\n", s.Atk)
	fmt.Printf("Int %v\n", s.Int)
	fmt.Printf("Def %v\n", s.Def)
	fmt.Printf("Spd %v\n", s.Spd)
	fmt.Printf("Hit %v\n", s.Hit)
	fmt.Printf("Res %v\n", s.Res)
}

func (f *File) Dump() {
	for i, ch := range f.Chars {
		fmt.Printf("Char #%v\n", i+1)
		fmt.Printf("- Base Stat\n")
		f.dumpstat(&ch.Base)
		fmt.Printf("- Stat\n")
		f.dumpstat(&ch.Stat)
		fmt.Println()
	}

	fmt.Printf("PR: %v\n", binary.LittleEndian.Uint64(f.Data[f.Offset+PR:]))
}

func (f *File) maxstats(s *Stat) {
	val := uint32(99999999)
	s.Lvl = 9999
	s.HP = val
	s.SP = val
	s.Atk = val
	s.Int = val
	s.Def = val
	s.Spd = val
	s.Hit = val
	s.Res = val
}

func (f *File) MaxOut() {
	fmt.Println("MAX OUT!")

	for i, ch := range f.Chars {
		f.maxstats(&ch.Base)
		f.maxstats(&ch.Stat)
		copy(f.Data[(CHAR+f.Offset)+CHARSIZE*i:], makebytes(ch))
	}
	binary.LittleEndian.PutUint64(f.Data[PR+f.Offset:], 9999999999999999)
}

func makebytes(v any) []byte {
	w := new(bytes.Buffer)
	binary.Write(w, binary.LittleEndian, v)
	return w.Bytes()
}

// offsets can get shifted as new characters get added/removed
// but they are only shifted by a constant
const (
	CHAR     = 0x19c92
	CHARSIZE = 0x768
	PR       = 0x6d88a
)
