package main

import (
	"bytes"
	"encoding/binary"
	"flag"
	"fmt"
	"log"
	"math"
	"os"

	"github.com/davecgh/go-spew/spew"
	"github.com/qeedquan/go-media/archive/nipponichi"
)

var flags struct {
	Encrypt bool
	MaxOut  bool
}

func main() {
	log.SetFlags(0)
	log.SetPrefix("save-dumper: ")

	flag.BoolVar(&flags.Encrypt, "e", false, "encrypt input")
	flag.BoolVar(&flags.MaxOut, "m", false, "max out")
	flag.Usage = usage
	flag.Parse()
	if flag.NArg() < 2 {
		usage()
	}

	src, err := os.ReadFile(flag.Arg(0))
	ck(err)

	var data []byte
	if flags.Encrypt {
		handle(src)
		data, err = encode(src)
	} else {
		data, err = decode(src)
		handle(data)
	}
	ck(err)

	err = os.WriteFile(flag.Arg(1), data, 0644)
	ck(err)
}

func handle(data []byte) {
	if flags.MaxOut {
		maxout(data)
	}
	dumpstats(data)
}

func ck(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

func usage() {
	fmt.Fprintln(os.Stderr, "Disgaea 5 Save Dumper")
	fmt.Fprintln(os.Stderr, "usage: [options] infile outfile")
	flag.PrintDefaults()
	os.Exit(2)
}

type Stat struct {
	Atk uint64
	Def uint64
	Int uint64
	Res uint64
	Hit uint64
	Spd uint64
}

type Mastery struct {
	Exp   uint32
	Level uint8
	Flags [3]byte // controls rank/usability of weapons
}

type Char struct {
	Exp                 uint64
	Unk1                [0xbb8]byte
	Name                [52]byte
	Title               [52]byte
	Unk2                [0x2098]byte
	CurHP               uint64
	CurMP               uint64
	MaxHP               uint64
	MaxMP               uint64
	Stat                Stat
	DisplayHP           uint64
	DisplayMP           uint64
	DisplayStat         Stat
	BoostHP             uint64
	BoostMP             uint64
	BoostStat           Stat
	Unk3                [0x10]byte
	Mastery             [10]Mastery
	Mana                uint32
	Level               uint32
	Unk4                [0x12]byte
	ElementalResistance [4]byte
	Unk5                [4]byte
	Jump                [2]byte
	Move                [2]byte
	Counter             [2]byte
	Throw               [2]byte
	Critical            [2]byte
	Unk6                [0x14]byte
	ReincarnationLevel  uint32
	ReincarnationCount  uint32
	Unk7                [4]byte
	EnemyKillCount      uint32
	AllyKillCount       uint32
	DeathCount          uint32
	MaxDamage           uint64
	TotalDamage         uint64
	Unk8                [0x1f4]byte
	DisplayLevel        uint32
	Unk9                [0x10]byte
	Aptitude            [8]uint16
	DisplayAptitude     [8]uint16
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

func putval(src []byte, off int, val interface{}) {
	var size int
	switch val.(type) {
	case uint8:
		size = 1
	case uint16:
		size = 2
	case uint32:
		size = 4
	case uint64:
		size = 8
	default:
		panic("unreachable")
	}
	if off+size >= len(src) {
		return
	}
	binary.Write(binWriter(src[off:]), binary.LittleEndian, val)
}

const (
	maxchars     = 128
	charoff      = 0x23b480
	charsize     = 0x4750
	moneyoff     = 0xbd8
	itemptsoff   = 0xbf0
	itemflooroff = 0x87a3b0
)

func dumpstats(src []byte) {
	fmt.Println("Dumping Stats:")

	printval("Money", src, moneyoff, 8)
	printval("Item Points", src, itemptsoff, 8)
	printval("Item Floor", src, itemflooroff, 2)

	for i := 0; i < maxchars; i++ {
		var ch Char

		off := charoff + i*charsize
		if off >= len(src) {
			break
		}

		r := bytes.NewBuffer(src[off:])
		binary.Read(r, binary.LittleEndian, &ch)
		if ch.Name[0] == 0 {
			break
		}

		fmt.Printf("Character %d (%#x-%#x)\n", i+1, off, off+charsize)
		spew.Dump(ch)
	}
}

func maxout(src []byte) {
	fmt.Println("Max Out!")

	putval(src, moneyoff, uint64(math.MaxInt64))
	putval(src, itemptsoff, uint64(math.MaxInt64))
	putval(src, itemflooroff, uint16(9999))

	for i := 0; i < maxchars; i++ {
		var ch Char

		off := charoff + i*charsize
		if off >= len(src) {
			break
		}

		r := bytes.NewBuffer(src[off:])
		binary.Read(r, binary.LittleEndian, &ch)
		if ch.Name[0] == 0 {
			break
		}

		val := uint64(math.MaxInt64)
		ch.CurHP = val
		ch.CurMP = val
		ch.MaxHP = val
		ch.MaxMP = val
		ch.Stat = Stat{
			Atk: val,
			Def: val,
			Int: val,
			Res: val,
			Hit: val,
			Spd: val,
		}
		ch.DisplayHP = ch.MaxHP
		ch.DisplayMP = ch.MaxMP
		ch.DisplayStat = ch.Stat

		val = 100000000
		ch.BoostHP = 100000000000
		ch.BoostMP = 100000000000
		ch.BoostStat = Stat{
			Atk: val,
			Def: val,
			Int: val,
			Res: val,
			Hit: val,
			Spd: val,
		}
		for i := range ch.Mastery {
			m := &ch.Mastery[i]
			m.Exp = math.MaxInt32
			m.Level = 100
			m.Flags[0] = 0x3f
			m.Flags[1] = 0x3f
			m.Flags[2] = 0x3f
		}

		ch.Mana = math.MaxInt32
		ch.Exp = math.MaxInt64
		ch.Level = math.MaxInt32
		ch.DisplayLevel = ch.Level
		ch.Jump = [2]byte{0xff, 0xff}
		ch.Counter = [2]byte{0xff, 0xff}
		ch.Move = [2]byte{0xff, 0xff}
		ch.Throw = [2]byte{0xff, 0xff}
		ch.Critical = [2]byte{0xff, 0xff}

		ch.ReincarnationLevel = math.MaxInt32
		ch.ReincarnationCount = math.MaxInt16
		ch.EnemyKillCount = math.MaxInt32
		ch.AllyKillCount = math.MaxInt16
		ch.MaxDamage = math.MaxInt64
		ch.TotalDamage = math.MaxInt64
		for i := range ch.ElementalResistance {
			ch.ElementalResistance[i] = 100
		}
		for i := range ch.Aptitude {
			ch.Aptitude[i] = math.MaxInt16
		}
		ch.DisplayAptitude = ch.Aptitude

		binary.Write(binWriter(src[off:]), binary.LittleEndian, &ch)
	}
}

type binWriter []byte

func (b binWriter) Write(p []byte) (int, error) {
	copy(b[:], p)
	return len(p), nil
}

const (
	hdrsz  = 0x1c0
	xorsig = 0xe5b2688acb279ca6
)

var xorkey = []byte{0x37, 0x6a, 0xd4, 0xf6, 0xe3, 0xcb, 0x6f, 0xe7}

func encode(src []byte) ([]byte, error) {
	if len(src) < hdrsz {
		return nil, fmt.Errorf("input too small")
	}
	hdr := append([]byte{}, src[:hdrsz]...)

	var yk nipponichi.YKCMP
	enc, err := yk.Encode("S2", src[hdrsz:])
	if err != nil {
		return nil, err
	}
	arrxor(enc, xorkey)

	w := new(bytes.Buffer)
	w.Write(hdr)
	binary.Write(w, binary.LittleEndian, uint64(xorsig))
	w.Write(enc)

	buf := w.Bytes()
	size := len(buf) - hdrsz

	binary.LittleEndian.PutUint64(hdr[0x38:], uint64(size))
	enchdr(hdr)
	copy(buf, hdr)

	fmt.Println("Encoding Stats: ")
	fmt.Println("  Total Size:", len(buf))
	fmt.Println("  Payload size:", size)

	return buf, nil
}

func decode(src []byte) ([]byte, error) {
	const (
		magic1 = "NIS_DISGAEA5_COMPLETE_SAVEDATA_"
		magic2 = "NIS_DISGAEA5_TRIAL_SAVEDATA_"
	)

	buf := append([]byte{}, src...)
	if len(buf) < hdrsz {
		return nil, fmt.Errorf("save file too short")
	}

	dechdr(buf[:hdrsz])
	if !bytes.HasPrefix(buf, []byte(magic1)) && !bytes.HasPrefix(buf, []byte(magic2)) {
		return nil, fmt.Errorf("invalid save header: %q", buf[:32])
	}

	size := binary.LittleEndian.Uint64(buf[0x38:])
	if size < hdrsz || size > uint64(len(buf)-hdrsz) {
		return nil, fmt.Errorf("invalid save size: %v bytes", size)
	}

	payload := buf[hdrsz:]
	sig := binary.LittleEndian.Uint64(payload)
	if sig == xorsig {
		arrxor(payload[8:], xorkey)
	}

	var yk nipponichi.YKCMP
	dec, err := yk.Decode(payload[8:size])
	if err != nil {
		return nil, err
	}

	dst := make([]byte, hdrsz+len(dec))
	copy(dst, buf[:hdrsz])
	copy(dst[hdrsz:], dec)

	fmt.Println("Decoding Stats:")
	fmt.Println("  Payload size: ", size)
	fmt.Println("  Decoded size: ", len(dec))

	return dst, nil
}

func enchdr(src []byte) {
	for i := range src {
		src[i] = (src[i]>>4)&0x0f | (src[i]<<4)&0xf0
		src[i] ^= 0xf0
	}
}

func dechdr(src []byte) {
	for i := range src {
		src[i] ^= 0xf0
		src[i] = (src[i]>>4)&0x0f | (src[i]<<4)&0xf0
	}
}

func arrxor(src, xor []byte) {
	for i := range src {
		src[i] ^= xor[i%len(xor)]
	}
}
