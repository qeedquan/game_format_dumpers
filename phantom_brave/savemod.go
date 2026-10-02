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
	maxOut = flag.Bool("m", false, "max out")
)

func main() {
	log.SetPrefix("phatom-brave-savemod: ")
	log.SetFlags(0)

	flag.Usage = usage
	flag.Parse()
	if flag.NArg() < 1 {
		usage()
	}

	data, err := os.ReadFile(flag.Arg(0))
	ck(err)

	save, err := NewSave(data)
	ck(err)

	spew.Dump(save.Char)

	if *maxOut {
		save.MaxOut()

		name := flag.Arg(0)
		if flag.NArg() > 1 {
			name = flag.Arg(1)
		}
		err = os.WriteFile(name, save.Data[:], 0644)
		ck(err)
	}
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: [options] file")
	flag.PrintDefaults()
	os.Exit(2)
}

func ck(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

type Date struct {
	Hour uint8
	Min  uint8
	Sec  uint8
	Dec  uint8
}

type Lds struct {
	Char0     [19]byte
	Lvl       [2]uint16
	Episode   uint8
	ClearFlag [2]uint8
	Cleared   [2]uint8
	Char1     [19]byte
}

type Save struct {
	Data     [0xc9fe8]byte
	Type     uint8
	Checksum uint64
	Date     Date
	Lds      Lds
	Money    uint64
	Char     []Char
}

type Stat struct {
	HP     uint64
	Atk    uint32
	Def    uint32
	Int    uint32
	Res    uint32
	Spd    uint32
	Status [4]byte
}

type Char struct {
	Name        [23]byte
	Class       [25]byte
	Checksum    [4]byte
	CurHP       uint64
	DisplayStat Stat
	Stat        Stat
	Unk         [8]byte
	Mana        uint32
}

func NewSave(data []byte) (*Save, error) {
	s := &Save{}
	if len(data) != len(s.Data) {
		return nil, fmt.Errorf("invalid file size")
	}
	copy(s.Data[:], data)

	v0 := binary.LittleEndian.Uint16(data[16*2:])
	v1 := binary.LittleEndian.Uint16(data[17*2:])
	v2 := data[39]
	if v0 != 0 && v1 != 0 && (v2 <= 0x63 || v2 == 0xff) && data[40] <= 0x63 && data[37] <= 0x37 {
		s.Type = 0
	} else {
		s.Type = 18
	}

	read(data[0x000:], &s.Checksum)
	read(data[0x2c0:], &s.Money)
	read(data[0x9:], &s.Date)
	read(data[0xd:], &s.Lds)

	n := 0x2f0
	for {
		if n >= len(data) {
			break
		}

		var c Char
		read(data[n:], &c)
		if c.Name[0] == 0 {
			break
		}

		s.Char = append(s.Char, c)
		n += 0x2d0
	}

	return s, nil
}

func (s *Save) MaxOut() {
	s.Money = 999999999999
	for i := range s.Char {
		c := &s.Char[i]
		c.CurHP = 99999999
		c.Mana = 0x7fffffff

		p := &c.DisplayStat
		p.HP = 9999999
		p.Atk = 9999999
		p.Def = 9999999
		p.Int = 9999999
		p.Res = 9999999
		p.Spd = 9999999

		p = &c.Stat
		p.HP = 9999999
		p.Atk = 9999999
		p.Def = 9999999
		p.Int = 9999999
		p.Res = 9999999
		p.Spd = 9999999
	}
	s.sync()
}

func (s *Save) sync() {
	p := s.Data[:]

	write(p[0x2c0:], s.Money)
	n := 0x2f0
	for i := range s.Char {
		write(p[n:], s.Char[i])
		n += 0x2d0
	}
}

func read(p []byte, v interface{}) {
	r := bytes.NewReader(p)
	binary.Read(r, binary.LittleEndian, v)
}

func write(p []byte, v interface{}) {
	binary.Write(binWriter(p), binary.LittleEndian, v)
}

type binWriter []byte

func (b binWriter) Write(p []byte) (int, error) {
	copy(b[:], p)
	return len(p), nil
}
