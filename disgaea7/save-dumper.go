package main

import (
	"bytes"
	"encoding/binary"
	"encoding/json"
	"flag"
	"fmt"
	"log"
	"math"
	"os"
	"reflect"

	"github.com/davecgh/go-spew/spew"
	"github.com/qeedquan/go-media/archive/nipponichi"
)

var flags struct {
	Encrypt bool
	MaxOut  bool
	OffFile string
}

func main() {
	log.SetFlags(0)
	log.SetPrefix("save-dumper: ")

	flag.BoolVar(&flags.Encrypt, "e", false, "encrypt input")
	flag.BoolVar(&flags.MaxOut, "m", false, "max out")
	flag.StringVar(&flags.OffFile, "o", "", "specify offset file")
	flag.Usage = usage
	flag.Parse()
	if flag.NArg() < 2 {
		usage()
	}

	src, err := os.ReadFile(flag.Arg(0))
	ck(err)

	var offs Offs
	if !flags.Encrypt {
		if flags.OffFile == "" {
			log.Fatal("Offset file needs to be specified")
		}

		offs, err = readoffs(flags.OffFile)
		ck(err)
	}

	var data []byte
	if flags.Encrypt {
		data, err = encode(src)
		ck(err)
	} else {
		data, err = decode(src)
		ck(err)
		handle(data, &offs)
	}

	err = os.WriteFile(flag.Arg(1), data, 0644)
	ck(err)
}

func handle(data []byte, offs *Offs) {
	if flags.MaxOut {
		maxout(data, offs)
	}
	dumpstats(data, offs)
}

func ck(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

func usage() {
	fmt.Fprintln(os.Stderr, "Disgaea 7 Save Dumper")
	fmt.Fprintln(os.Stderr, "usage: [options] infile outfile")
	flag.PrintDefaults()
	os.Exit(2)
}

type Offs struct {
	Money int
	RP    int
	Chars []int
	Juice int
}

type Juice struct {
	Exp  uint64
	Unk1 [0x12]byte
	Mana uint64
	Unk2 [0x12]byte
	HP   uint64
	Unk3 [0x12]byte
	SP   uint64
	Unk4 [0x1f]byte
	Atk  uint64
	Unk5 [0x12]byte
	Def  uint64
	Unk6 [0x12]byte
	Int  uint64
	Unk7 [0x12]byte
	Res  uint64
	Unk8 [0x12]byte
	Hit  uint64
	Unk9 [0x12]byte
	Spd  uint64
}

type Char struct {
	HP      uint64
	Unk1    [0x9]byte
	MaxHP   uint64
	Unk2    [0x23]byte
	SP      uint64
	Unk3    [0x9]byte
	MaxSP   uint64
	Unk4    [0x3d]byte
	BaseHP  uint64
	Unk5    [0x124]byte
	BoostHP uint64
	Unk6    [0x4a]byte
	BaseMP  uint64
	Unk7    [0x124]byte
	BoostSP uint64
	Unk8    [0x57]byte
	BaseAtk uint64
	Unk9    [0x124]byte
	Atk     uint64
	Unk10   [0x4a]byte
	BaseDef uint64
	Unk11   [0x124]byte
	Def     uint64
	Unk12   [0x4a]byte
	BaseInt uint64
	Unk13   [0x124]byte
	Int     uint64
	Unk14   [0x4a]byte
	BaseRes uint64
	Unk15   [0x124]byte
	Res     uint64
	Unk16   [0x4a]byte
	BaseHit uint64
	Unk17   [0x124]byte
	Hit     uint64
	Unk18   [0x4a]byte
	BaseSpd uint64
	Unk19   [0x124]byte
	Spd     uint64
	Unk20   [0x1f]byte
	Lvl     uint32
	Unk21   [0x4e]byte
	Exp     uint64
	Unk22   [0x12]byte
	Mana    uint64
}

func printval(name string, src []byte, off, size int) {
	if off+size >= len(src) {
		return
	}

	var val uint64
	switch size {
	case 1:
		val = uint64(src[off])
	case 2:
		val = uint64(binary.LittleEndian.Uint16(src[off:]))
	case 4:
		val = uint64(binary.LittleEndian.Uint32(src[off:]))
	case 8:
		val = uint64(binary.LittleEndian.Uint64(src[off:]))
	default:
		panic("unreachable")
	}
	fmt.Printf("%s: %v\n", name, val)
}

func putval(src []byte, off int, val any) {
	rv := reflect.TypeOf(val)
	size := int(rv.Size())
	if off+size >= len(src) {
		return
	}
	binary.Write(binWriter(src[off:]), binary.LittleEndian, val)
}

func dumpstats(src []byte, offs *Offs) {
	fmt.Println("Dumping Stats:")

	printval("Money", src, offs.Money, 8)
	printval("RP", src, offs.RP, 8)

	if offs.Juice > 0 && offs.Juice < len(src) {
		var ju Juice
		r := bytes.NewBuffer(src[offs.Juice:])
		binary.Read(r, binary.LittleEndian, &ju)
		fmt.Printf("Juice Extract\n (%#x)", offs.Juice)
		spew.Dump(ju)
	}

	for i, off := range offs.Chars {
		var ch Char

		r := bytes.NewBuffer(src[off:])
		binary.Read(r, binary.LittleEndian, &ch)

		fmt.Printf("Character %d (%#x)\n", i+1, off)
		spew.Dump(ch)
	}
}

func maxout(src []byte, offs *Offs) {
	fmt.Println("Max Out!")

	putval(src, offs.Money, uint64(math.MaxInt64))
	putval(src, offs.RP, uint64(math.MaxInt64))

	if offs.Juice > 0 && offs.Juice < len(src) {
		var ju Juice
		r := bytes.NewBuffer(src[offs.Juice:])
		binary.Read(r, binary.LittleEndian, &ju)
		ju.HP = math.MaxInt64
		ju.SP = math.MaxInt64
		ju.Atk = math.MaxInt64
		ju.Def = math.MaxInt64
		ju.Int = math.MaxInt64
		ju.Spd = math.MaxInt64
		ju.Res = math.MaxInt64
		ju.Hit = math.MaxInt64
		ju.Mana = math.MaxInt64
		ju.Exp = math.MaxInt64
		binary.Write(binWriter(src[offs.Juice:]), binary.LittleEndian, &ju)
	}

	for _, off := range offs.Chars {
		var ch Char

		r := bytes.NewBuffer(src[off:])
		binary.Read(r, binary.LittleEndian, &ch)

		ch.HP = math.MaxInt64
		ch.SP = math.MaxInt64
		ch.MaxHP = math.MaxInt64
		ch.MaxSP = math.MaxInt64
		ch.BaseAtk = math.MaxInt64
		ch.BaseDef = math.MaxInt64
		ch.BaseInt = math.MaxInt64
		ch.BaseRes = math.MaxInt64
		ch.BaseSpd = math.MaxInt64
		ch.BaseHit = math.MaxInt64
		ch.BaseHP = math.MaxInt64
		ch.BaseMP = math.MaxInt64
		ch.Atk = math.MaxInt64
		ch.Def = math.MaxInt64
		ch.Int = math.MaxInt64
		ch.Res = math.MaxInt64
		ch.Spd = math.MaxInt64
		ch.Hit = math.MaxInt64
		ch.Mana = math.MaxInt64
		ch.Exp = math.MaxInt64

		binary.Write(binWriter(src[off:]), binary.LittleEndian, &ch)
	}
}

type binWriter []byte

func (b binWriter) Write(p []byte) (int, error) {
	copy(b[:], p)
	return len(p), nil
}

func encode(src []byte) ([]byte, error) {
	var yk nipponichi.YKCMP
	enc, err := yk.Encode("lzma", src)
	if err != nil {
		return nil, err
	}

	fmt.Println("Encoding Stats: ")
	fmt.Println("  Total Size:", len(enc))

	return enc, nil
}

func decode(src []byte) ([]byte, error) {
	var yk nipponichi.YKCMP
	dst, err := yk.Decode(src)
	if err != nil {
		return nil, err
	}

	fmt.Println("Decoding Stats:")
	fmt.Println("  Decoded size: ", len(dst))

	return dst, nil
}

func readoffs(name string) (offs Offs, err error) {
	buf, err := os.ReadFile(name)
	if err != nil {
		return
	}

	err = json.Unmarshal(buf, &offs)
	return
}
