package main

import (
	"encoding/binary"
	"flag"
	"fmt"
	"log"
	"os"
)

var (
	statOffset  = flag.Uint64("s", 0, "stat offset")
	moneyOffset = flag.Uint64("m", 0, "money offset")
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

	powerup(data, *statOffset, *moneyOffset)

	name := flag.Arg(0)
	if flag.NArg() >= 2 {
		name = flag.Arg(1)
	}
	err = os.WriteFile(name, data, 0644)
	ck(err)
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

func powerup(data []byte, statOffset, moneyOffset uint64) {
	s := Stat{
		Attack:   9999,
		Defense:  9999,
		Strength: 9999,
		Magic:    9999,
		Vitality: 9999,
		Agility:  9999,
		Luck:     9999,
	}
	for i := range s.Health {
		s.Health[i] = 65536
	}
	m := uint32(0x6fffffff)

	if moneyOffset > 0 {
		if moneyOffset+4 >= uint64(len(data)) {
			log.Fatal("invalid money offset")
		}
		binary.LittleEndian.PutUint32(data[moneyOffset:], m)
	}

	if statOffset > 0 {
		o := statOffset
		for i := 0; i < 4; i++ {
			xo := o
			for j := range s.Health {
				binary.LittleEndian.PutUint32(data[o:], s.Health[j])
				o += 4
			}
			binary.LittleEndian.PutUint32(data[o:], s.Attack)
			binary.LittleEndian.PutUint32(data[o+4:], s.Defense)
			binary.LittleEndian.PutUint32(data[o+8:], s.Strength)
			binary.LittleEndian.PutUint32(data[o+12:], s.Magic)
			binary.LittleEndian.PutUint32(data[o+16:], s.Vitality)
			binary.LittleEndian.PutUint32(data[o+20:], s.Agility)
			binary.LittleEndian.PutUint32(data[o+24:], s.Luck)
			o = xo + 224
		}
	}
}

type Stat struct {
	Health   [7]uint32
	Attack   uint32
	Defense  uint32
	Strength uint32
	Magic    uint32
	Vitality uint32
	Agility  uint32
	Luck     uint32
}
