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
	maxout    = flag.Bool("maxout", false, "max out")
	weaponize = flag.Bool("weaponize", false, "get good weapons")
	itemize   = flag.Bool("itemize", false, "get good items")
)

const (
	SNAKE = 1 + iota
	POLAR_STAR
	FIREBALL
	MACHINE_GUN
	MISSLE_LAUNCHER
	MISSILES_BAD
	BUBBLER
	UNKNOWN_BAD
	BLADE
	SUPER_MISSILE
	SUPER_MISSLE_BAD
	NEMESIS
	SPUR
	HAJIME_BAD
)

const (
	ARTHURS_KEY = 1 + iota
	MAP_SYSTEM
	SANTAS_KEY
	SILVER_LOCKET
	BEAST_FANG
	LIFE_CAPSULE
	ID_CARD
	JELLYFISH_JUICE
	RUSTED_KEY
	GUM_KEY
	GUM_BASE
	CHARCOAL
	BOMB
	DOG
	LIFE_POT
	CURE_ALL
	CLINIC_KEY
	BOOSTER_V08
	ARMS_BARRIER
	TURBOCHARGE
	AIR_TANK
	X290_COUNTER
	BOOSTER_V2
	MIMIGA_MASK
	TELEPORTER_ROOM_KEY
	SUES_LETTER
	CONTROLLER
	BROKEN_SPRINKLER
	SPRINKLER
	TOW_ROPE
	MEDAL_OF_THE_RED_ORGE
	MISTER_LITTLE
	MUSHROOM_BADGE
	MA_PIGNON
	CURLY_PANTIES
	ALIEN_MEDAL
	CHAKO_ROUGE
	WHIMSICAL_STAR
	IRON_BOND
)

func main() {
	log.SetFlags(0)
	log.SetPrefix("cave-story-savemod: ")

	flag.Usage = usage
	flag.Parse()
	if flag.NArg() != 1 {
		usage()
	}

	f, err := decode(flag.Arg(0))
	check(err)

	f.Dump()

	if *weaponize {
		f.Weaponize()
	}
	if *itemize {
		f.Itemize()
	}
	if *maxout {
		f.MaxOut()
	}
	if *maxout || *weaponize || *itemize {
		err := os.WriteFile(flag.Arg(0), f.Data, 0644)
		check(err)
	}
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: [options] profile.dat")
	flag.PrintDefaults()
	os.Exit(2)
}

func check(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

type File struct {
	Data      []byte
	MaxHealth uint32
	CurHealth uint32
	Weapons   []Weapon
	Items     []uint32
}

type Weapon struct {
	Type    uint32
	Level   uint32
	Exp     uint32
	MaxAmmo uint32
	CurAmmo uint32
}

func decode(name string) (*File, error) {
	b, err := os.ReadFile(name)
	if err != nil {
		return nil, err
	}

	if len(b) < 1540 {
		return nil, fmt.Errorf("%v: save file too small", name)
	}

	f := &File{
		Data: b,
	}

	f.MaxHealth = binary.LittleEndian.Uint32(b[MAX_HEALTH:])
	f.CurHealth = binary.LittleEndian.Uint32(b[CUR_HEALTH:])

	// 6 is the number of weapons player can get in a normal game
	// but the save slots allow for more
	for i := range 8 {
		var w Weapon
		r := bytes.NewReader(b[WEAPONS+0x14*i:])
		binary.Read(r, binary.LittleEndian, &w)
		f.Weapons = append(f.Weapons, w)
	}

	for i := range 24 {
		var p uint32
		r := bytes.NewReader(b[ITEMS+0x4*i:])
		binary.Read(r, binary.LittleEndian, &p)
		f.Items = append(f.Items, p)
	}

	return f, nil
}

func (f *File) Dump() {
	fmt.Printf("Health: %d/%d\n", f.CurHealth, f.MaxHealth)
	fmt.Println()
	for i, w := range f.Weapons {
		fmt.Printf("Weapon #%d\n", i)
		fmt.Printf("Type: %d\n", w.Type)
		fmt.Printf("Level: %d\n", w.Level)
		fmt.Printf("EXP: %d\n", w.Exp)
		fmt.Printf("Ammo: %d/%d\n", w.CurAmmo, w.MaxAmmo)
		fmt.Println()
	}
	fmt.Println()
	for i, p := range f.Items {
		fmt.Printf("Item %d: %d\n", i, p)
	}
}

func (f *File) MaxOut() {
	fmt.Println("MAX OUT!")

	f.CurHealth = 32000
	f.MaxHealth = 32000
	binary.LittleEndian.PutUint32(f.Data[CUR_HEALTH:], f.CurHealth)
	binary.LittleEndian.PutUint32(f.Data[MAX_HEALTH:], f.MaxHealth)

	for i := range f.Weapons {
		w := &f.Weapons[i]
		w.Level = 3
		w.Exp = 99999
		w.MaxAmmo = 0
		switch w.Type {
		case NEMESIS:
			w.Level = 1
			w.Exp = 0
		}
		copy(f.Data[WEAPONS+0x14*i:], makebytes(w))
	}
}

func (f *File) Weaponize() {
	fmt.Println("WEAPONIZE!")

	list := []uint32{SPUR, BLADE, SNAKE, SUPER_MISSILE, BUBBLER, FIREBALL, NEMESIS, MACHINE_GUN}
	for i := range f.Weapons {
		w := &f.Weapons[i]
		w.Type = list[i]
		w.Exp = 99999
		w.Level = 3
		w.MaxAmmo = 0
	}
}

func (f *File) Itemize() {
	fmt.Println("ITEMIZE!")

	list := []uint32{
		BOOSTER_V2, WHIMSICAL_STAR, CHAKO_ROUGE, ALIEN_MEDAL,
		MEDAL_OF_THE_RED_ORGE, LIFE_POT, ARMS_BARRIER, CURLY_PANTIES,
		X290_COUNTER,
	}
loop:
	for i := range list {
		n := -1
		for j := range f.Items {
			if f.Items[j] == list[i] {
				continue loop
			}
			if n == -1 && f.Items[j] == 0 {
				n = j
			}
		}
		if n >= 0 {
			f.Items[n] = list[i]
		}
	}

	seen := make(map[uint32]bool)
	for i, p := range f.Items {
		if seen[p] {
			f.Items[i] = 0
		}
		seen[p] = true
	}

	copy(f.Data[ITEMS:], makebytes(f.Items))
}

func makebytes(v any) []byte {
	w := new(bytes.Buffer)
	binary.Write(w, binary.LittleEndian, v)
	return w.Bytes()
}

const (
	MAX_HEALTH = 0x1c
	CUR_HEALTH = 0x20
	WEAPONS    = 0x38
	ITEMS      = 0xd8
)
