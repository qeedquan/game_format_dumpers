package main

import (
	"bytes"
	"encoding/binary"
	"flag"
	"fmt"
	"log"
	"os"

	"github.com/davecgh/go-spew/spew"
)

var (
	fixup = flag.Bool("f", false, "do fixup on save file and output to new file")
	maxim = flag.Uint("m", 0, "bitmask for max attributes during fixup (0x1 - max exp, 0x2 - max stats, 0x4 - max gil)")
	uid   = flag.Uint("u", 123, "specify uid")
)

func main() {
	log.SetFlags(0)
	log.SetPrefix("savemod: ")

	flag.Usage = usage
	flag.Parse()
	if flag.NArg() < 1 {
		usage()
	}

	data, err := os.ReadFile(flag.Arg(0))
	ck(err)

	sv, err := NewSave(data, uint32(*uid))
	ck(err)

	if *fixup {
		data = sv.Fixup()
		sv, _ = NewSave(data, uint32(*uid))

		name := flag.Arg(0)
		if flag.NArg() > 1 {
			name = flag.Arg(1)
		}
		err := os.WriteFile(name, data, 0644)
		ck(err)
	}

	spew.Dump(sv.Slots)
}

func ck(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: [options] infile [outfile]")
	flag.PrintDefaults()
	os.Exit(2)
}

type Save struct {
	Data  [0xc0000]byte
	Slots [0x21]Slot
	UID   uint32
}

type Slot struct {
	Status   int
	Offset   int
	Checksum uint32
	Gil      uint32
	Stats    [32]Stat
}

type Stat struct {
	Offset int
	Exp    uint32
	Lvl    uint8
	MaxHP  uint16
	CurHP  uint16
	MaxMP  uint16
	CurMP  uint16
	Str    uint8
	Sta    uint8
	Spd    uint8
	Int    uint8
	Spr    uint8
}

func NewSave(data []byte, uid uint32) (*Save, error) {
	z := &Save{
		UID: uid,
	}

	if len(z.Data) != len(data) {
		return nil, fmt.Errorf("invalid data length, expected %#x bytes but got %#x bytes!", len(z.Data), len(data))
	}
	copy(z.Data[:], data)

	magic := []byte("cd1000\x00BABil")
loop:
	for i := range z.Slots {
		s := &z.Slots[i]
		s.Offset = 0x42f0 * i
		s.Status = 1

		p := data[s.Offset:]

		s.Gil = binary.LittleEndian.Uint32(p[0x3a88:])

		x := 0x1d0
		for i := range s.Stats {
			t := &s.Stats[i]
			t.Exp = binary.LittleEndian.Uint32(p[x:])
			t.Lvl = p[x+4]
			t.MaxHP = binary.LittleEndian.Uint16(p[x+6:])
			t.CurHP = binary.LittleEndian.Uint16(p[x+8:])
			t.MaxMP = binary.LittleEndian.Uint16(p[x+290:])
			t.CurMP = binary.LittleEndian.Uint16(p[x+16:])

			y := x + 284
			t.Str = p[y]
			t.Sta = p[y+1]
			t.Spd = p[y+2]
			t.Int = p[y+3]
			t.Spr = p[y+4]
			t.Offset = x
			x += 0x130
		}

		if bytes.Compare(p[:len(magic)], magic) != 0 || p[0x14] != 0x22 {
			continue
		}

		v := 0
		for i := 0x26; p[i] != 0; i += 0x14 {
			if v++; v >= 5 {
				s.Status = 2
				continue loop
			}
		}

		end := binary.LittleEndian.Uint32(data[0x20:])
		if end != 0x42cc {
			continue
		}

		s.Checksum = binary.LittleEndian.Uint32(data[0x1c:])
		if s.Checksum != z.checksum(data[0x24:end+0x24])+z.UID {
			s.Status = 1
			continue
		}

		s.Status = 3
	}

	return z, nil
}

func (z *Save) checksum(buf []byte) uint32 {
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

func (z *Save) Fixup() []byte {
	data := make([]byte, len(z.Data))
	copy(data, z.Data[:])

	stat := Stat{
		Exp:   9999999,
		MaxHP: 9999,
		CurHP: 9999,
		MaxMP: 999,
		CurMP: 999,
		Str:   99,
		Sta:   99,
		Spd:   99,
		Int:   99,
		Spr:   99,
	}

	statOffsets := []int{
		// ceodore 1
		160,   // cecil
		464,   // hooded man
		768,   // rosa
		1376,  // cid
		3808,  // ceodore
		6848,  // biggs
		7152,  // wedge
		9888,  // black mage
		10192, // white mage

		// rydia 1
		52480, // rydia
		55824, // luca
		58864, // calca
		59168, // brina

		// yang 1
		104800, // yang
		106928, // ursula
		111488, // monk a
		111792, // monk b
		113920, // monk c

		// palom 1
		156512, // palom
		158944, // leonora

		// edge 1
		208528, // edge
		211264, // gekkou
		211568, // izayoi
		211872, // zangetsu
		212176, // tsukinowa

		// porom 1
		258112, // rydia
		259328, // palam (teen)
		259632, // porom (teen)
		262368, // kain
		266928, // white mage
		267232, // black mage
		267536, // palam
		267840, // porom

		// edward 1
		310128, // edward
		313472, // haley
		320464, // guard 1
		320768, // guard 2
		321072, // guard 3

		// kain 1
		360320, // hooded man
		363664, // ceodore
		361232, // cid
		365184, // kain

		// lunarians 1
		414464, // fusoya
		420544, // golbez

		// crystals 1
		467088, // luca
		463744, // rydia
		465568, // edge
		471952, // man in black
	}
	for _, o := range statOffsets {
		stat.Offset = o
		z.setStats(data, stat, *maxim)
	}

	gilOffsets := []int{
		0x3a88,  // ceodore 1
		0x10358, // rydia 1
		0x1CC28, // yang 1
		0x294F8, // palom 1
		0x35DC8, // edge 1
		0x42698, // porom 1
		0x4EF68, // edward 1
		0x68108, // lunarian 1
		0x749D8, // crystals 1
		0x75670, // crystals 2
	}
	if *maxim&0x4 != 0 {
		for _, o := range gilOffsets {
			binary.LittleEndian.PutUint32(data[o:], 9999999)
		}
	}

	for _, s := range z.Slots {
		p := data[s.Offset:]
		v := z.checksum(p[0x24:0x42cc+0x24]) + z.UID

		binary.LittleEndian.PutUint32(p[0x20:], 0x42cc)
		binary.LittleEndian.PutUint32(p[0x1c:], v)
	}

	return data
}

func (z *Save) setStats(data []byte, stat Stat, mask uint) {
	t := &stat

	if mask&0x1 != 0 {
		x := t.Offset
		p := data[x:]
		binary.LittleEndian.PutUint32(p[0:], t.Exp)
	}

	if mask&0x2 != 0 {
		x := t.Offset
		p := data[x:]
		binary.LittleEndian.PutUint16(p[6:], t.MaxHP)
		binary.LittleEndian.PutUint16(p[8:], t.CurHP)
		binary.LittleEndian.PutUint16(p[290:], t.MaxMP)
		binary.LittleEndian.PutUint16(p[16:], t.CurMP)

		y := x + 284
		p = data[y:]
		p[0] = t.Str
		p[1] = t.Sta
		p[2] = t.Spd
		p[3] = t.Int
		p[4] = t.Spr
	}
}
