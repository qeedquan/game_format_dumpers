package main

import (
	"bytes"
	"encoding/binary"
	"flag"
	"fmt"
	"log"
	"os"
	"strings"
)

var (
	maxout = flag.Bool("maxout", false, "max out")
)

func main() {
	log.SetPrefix("ff3-savemod: ")
	log.SetFlags(0)

	flag.Usage = usage
	flag.Parse()
	if flag.NArg() != 1 {
		usage()
	}

	f, err := decode(flag.Arg(0))
	check(err)

	if *maxout {
		maximize(f)
		err = os.WriteFile(flag.Arg(0), f.Data, 0644)
		check(err)
	}
}

func check(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: [options] save.bin")
	flag.PrintDefaults()
	os.Exit(2)
}

func decode(name string) (*File, error) {
	const (
		sig = "cd1000\x00EUReKa"
	)

	b, err := os.ReadFile(name)
	if err != nil {
		return nil, err
	}

	if len(b) != 0x10000 {
		return nil, fmt.Errorf("invalid save size: %d bytes", len(b))
	}

	f := &File{
		Data: b,
	}
	n := 0
	for {
		i := bytes.Index(b[n:], []byte(sig))
		if i < 0 {
			break
		}

		s := Slot{
			Off: n + i,
		}

		r := bytes.NewReader(b[n+i:])
		err := binary.Read(r, binary.LittleEndian, &s.Header)
		if err != nil {
			return nil, err
		}

		s.Data = make([]byte, s.Size)
		err = binary.Read(r, binary.LittleEndian, s.Data)
		if err != nil {
			return nil, err
		}

		f.Slots = append(f.Slots, s)
		n += i + len(sig)
	}

	fmt.Printf("Found %d slots\n", len(f.Slots))
	for i := range f.Slots {
		s := &f.Slots[i]
		if s.Size < SLOTSIZE {
			continue
		}

		s.GIL = binary.LittleEndian.Uint32(s.Data[GIL:])

		p := Stat{}
		for _, o := range STATS {
			r := bytes.NewReader(s.Data[o:])
			binary.Read(r, binary.LittleEndian, &p)
			s.Stats = append(s.Stats, p)
		}

		r := bytes.NewReader(s.Data[TITLE:])
		binary.Read(r, binary.LittleEndian, &s.Title)

		r = bytes.NewReader(s.Data[ITEM:])
		for {
			var e Item
			err := binary.Read(r, binary.LittleEndian, &e)
			if err != nil || e.Amount == 0 {
				break
			}
			s.Items = append(s.Items, e)
		}

		t := &s.Title
		fmt.Printf("GIL         %d\n", s.GIL)
		fmt.Printf("Title Data % x\n", t.Data)
		fmt.Printf("\n")

		for j, p := range s.Stats {
			fmt.Println()
			fmt.Printf("Stat Offset %#x\n", STATS[j])
			fmt.Printf("Exp         %d\n", p.Exp)
			fmt.Printf("Max HP      %d\n", p.MaxHP)
			fmt.Printf("Cur HP      %d\n", p.CurHP)
			fmt.Printf("MP          % d\n", p.MP)
			fmt.Printf("Atk         % d\n", p.Str)
			fmt.Printf("Sta         % d\n", p.Vit)
			fmt.Printf("Spd         % d\n", p.Agi)
			fmt.Printf("Spr         % d\n", p.Spr)
			fmt.Printf("Int         % d\n", p.Int)
			fmt.Println()
		}

		fmt.Println()
		fmt.Printf("Items (%d)\n", len(s.Items))
		for _, e := range s.Items {
			fmt.Printf("ID %03d Amount %3d Attr %#x\n", e.ID, e.Amount, e.Attr)
		}
		fmt.Println()

		fmt.Printf("%s\n", strings.Repeat("-", 20))
	}

	return f, nil
}

func checksum(buf []byte) uint32 {
	c := uint32(0)
	x := uint32(0)
	y := uint32(0)

	i := 0
	for ; i+7 < len(buf); i += 8 {
		x += binary.LittleEndian.Uint32(buf[i:])
		y += binary.LittleEndian.Uint32(buf[i+4:])
	}

	n := uint(0)
	for ; i < len(buf); i++ {
		c |= uint32(buf[i] << (8 * n))
		n++
	}

	return c + x + y
}

func maximize(f *File) {
	fmt.Println("MAX OUT!")
	for i := range f.Slots {
		s := &f.Slots[i]
		if s.Size < SLOTSIZE {
			continue
		}

		for j := range s.Stats {
			p := &s.Stats[j]
			p.Exp = 9999999
			p.MaxHP = 9999
			p.CurHP = 9999
			for k := range p.MP {
				p.MP[k] = 99
			}
			for k := 0; k < 2; k++ {
				p.Str[k] = 99
				p.Agi[k] = 99
				p.Vit[k] = 99
				p.Int[k] = 99
				p.Spr[k] = 99
			}
			copy(s.Data[STATS[j]:], makebytes(p))
		}

		for j := range s.Items {
			e := &s.Items[j]
			e.Amount = 99
		}
		copy(s.Data[ITEM:], makebytes(s.Items))

		binary.LittleEndian.PutUint32(s.Data[GIL:], 9999999)

		s.Checksum = checksum(s.Data)
		copy(f.Data[s.Off:], slot2bytes(s))
	}
}

func slot2bytes(s *Slot) []byte {
	w := new(bytes.Buffer)
	binary.Write(w, binary.LittleEndian, &s.Header)
	binary.Write(w, binary.LittleEndian, s.Data)
	return w.Bytes()
}

func makebytes(v any) []byte {
	w := new(bytes.Buffer)
	binary.Write(w, binary.LittleEndian, v)
	return w.Bytes()
}

type File struct {
	Data  []byte
	Slots []Slot
}

type Header struct {
	Magic    [13]byte
	Unk      [15]byte
	Checksum uint32
	Size     uint32
}

type Slot struct {
	Header
	Off        int
	DisplayGIL uint32
	GIL        uint32
	Title      Title
	Stats      []Stat
	Items      []Item
	Data       []byte
}

type Title struct {
	Data [0x40]byte
}

type Stat struct {
	Name  [35]byte
	Lvl   uint8
	Exp   uint32
	Unk1  [4]byte
	CurHP uint32
	MaxHP uint32
	MP    [8]byte
	Unk2  [16]byte
	Str   [2]uint8
	Vit   [2]uint8
	Agi   [2]uint8
	Int   [2]uint8
	Spr   [2]uint8
	Unk3  [674]uint8
}

type Item struct {
	Amount uint16
	ID     uint8
	Attr   uint8
}

const (
	SLOTSIZE = 15000
	TITLE    = 0x0
	GIL      = 0x192c
	ITEM     = 0xc2e
)

var STATS = []int{
	0x3c,  // luneth
	0x334, // arc
	0x62c, // refia
	0x924, // ingus
}
