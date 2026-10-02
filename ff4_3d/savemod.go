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
	uid    = flag.Int("uid", 123, "specify user id")
	maxout = flag.Bool("maxout", false, "max out")
)

func main() {
	log.SetPrefix("ff4-savemod: ")
	log.SetFlags(0)

	flag.Usage = usage
	flag.Parse()
	if flag.NArg() != 1 {
		usage()
	}

	f, err := decode(flag.Arg(0))
	check(err)

	if *maxout {
		maximize(f, uint32(*uid))
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
		sig = "cd1000\x00BABil"
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
		if s.Size != SLOTSIZE {
			continue
		}

		s.DisplayGIL = binary.LittleEndian.Uint32(s.Data[GILDP:])
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
		fmt.Printf("Display GIL %d\n", s.DisplayGIL)
		fmt.Printf("GIL         %d\n", s.GIL)
		fmt.Printf("Time %d:%02d\n", t.Data[4], t.Data[5])
		fmt.Printf("Title Data % x\n", t.Data)

		fmt.Printf("\n")
		for j, d := range t.Display {
			fmt.Printf("Display %d\n", j)
			fmt.Printf("Char ID %#x\n", d.ID)
			fmt.Printf("Max HP  %d\n", d.MaxHP)
			fmt.Printf("Cur HP  %d\n", d.CurHP)
			fmt.Printf("Max MP  %d\n", d.MaxMP)
			fmt.Printf("Cur MP  %d\n", d.CurMP)
			fmt.Printf("\n")
		}

		for j, p := range s.Stats {
			fmt.Println()
			fmt.Printf("Stat Offset %#x\n", STATS[j])
			fmt.Printf("Exp         %d\n", p.Exp)
			fmt.Printf("Max HP      %d\n", p.MaxHP)
			fmt.Printf("Max MP      %d\n", p.MaxMP)
			fmt.Printf("Cur HP      %d\n", p.CurHP)
			fmt.Printf("Cur MP      %d\n", p.CurMP)
			fmt.Printf("Atk         %d\n", p.Str)
			fmt.Printf("Sta         %d\n", p.Sta)
			fmt.Printf("Spd         %d\n", p.Spd)
			fmt.Printf("Spr         %d\n", p.Spr)
			fmt.Printf("Int         %d\n", p.Int)
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

func maximize(f *File, uid uint32) {
	fmt.Println("MAX OUT!")
	for i := range f.Slots {
		s := &f.Slots[i]
		if s.Size != SLOTSIZE {
			continue
		}

		for j := range s.Title.Display {
			d := &s.Title.Display[j]
			d.MaxHP = 9999
			d.CurHP = 9999
			d.MaxMP = 999
			d.CurMP = 999
		}
		copy(s.Data[TITLE:], makebytes(s.Title))

		for j := range s.Stats {
			p := &s.Stats[j]
			p.Exp = 9999999
			p.MaxHP = 9999
			p.CurHP = 9999
			p.MaxMP = 999
			p.CurMP = 999
			p.Str = 99
			p.Sta = 99
			p.Spd = 99
			p.Int = 99
			p.Spr = 99
			copy(s.Data[STATS[j]:], makebytes(p))
		}

		for j := range s.Items {
			e := &s.Items[j]
			e.Amount = 99
		}
		copy(s.Data[ITEM:], makebytes(s.Items))

		binary.LittleEndian.PutUint32(s.Data[GILDP:], 9999999)
		binary.LittleEndian.PutUint32(s.Data[GIL:], 9999999)

		s.Checksum = checksum(s.Data) + uid
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
	Magic    [12]byte
	Unk      [16]byte
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

type Display struct {
	ID    uint32
	CurHP uint16
	MaxHP uint16
	CurMP uint16
	MaxMP uint16
	Pad   [8]byte
}

type Title struct {
	Display [5]Display
	Data    [0x24]byte
}

type Stat struct {
	Exp   uint32
	Lvl   uint8
	Unk1  [3]byte
	MaxHP uint32
	CurHP uint32
	CurMP uint32
	MaxMP uint32
	Unk2  [0x1ae]byte
	Str   uint8
	Sta   uint8
	Spd   uint8
	Int   uint8
	Spr   uint8
	Unk3  [8]byte
}

type Item struct {
	Amount uint16
	ID     uint8
	Attr   uint8
}

const (
	SLOTSIZE = 15772
	TITLE    = 0x0
	GILDP    = 0x64
	GIL      = 0x22dc
	ITEM     = 0x1ace
)

var STATS = []int{
	0x7c,   // cecil (dark)
	0x250,  // cecil (light)
	0x424,  // kain
	0x5f8,  // rosa
	0x7cc,  // rydia
	0xb74,  // tellah
	0xd48,  // parom
	0xf1c,  // palom
	0x10f0, // edward
	0x12c4, // yang
	0x1498, // cid
	0x166c, // edge
	0x1840, // fusoya
}
