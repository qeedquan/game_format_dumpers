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
	fmt.Fprintln(os.Stderr, "Disgaea 4 Save Dumper")
	fmt.Fprintln(os.Stderr, "usage: [options] infile outfile")
	flag.PrintDefaults()
	os.Exit(2)
}

type Stat struct {
	HP  uint64
	MP  uint64
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
	Unk1                [0x70]byte
	Exp                 uint64
	Unk2                [0x104]byte
	Weapon              [0x100]byte
	Unk3                [0x100]byte
	Etc1                [0x100]byte
	Unk4                [0x100]byte
	Etc2                [0x100]byte
	Unk5                [0x100]byte
	Etc3                [0xfc]byte
	Name                [64]byte
	Class               [64]byte
	Unk6                [0x478]byte
	MaxHP               uint64
	MaxMP               uint64
	Stat                Stat
	Base                Stat
	MaxMana             uint64
	Mana                uint64
	Unk7                [0x388]byte
	Level               uint16
	Unk8                [19]byte
	ElementalResistance [3]int8
	Jump                [2]uint8
	Move                [2]uint8
	Counter             [2]uint8
	Throw               [2]uint8
	Range               [2]uint8
	Unk9                [0x1e]byte
	ReincarnationLevel  uint32
	ReincarnationCount  [2]uint16
	Unk10               [0x161c]byte
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
	maxchars = 128
	charoff  = 0x1200
	charsize = 0x2800
	moneyoff = 0x11b8
)

func dumpstats(src []byte) {
	fmt.Println("Dumping Stats:")

	printval("Money", src, moneyoff, 8)

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

	putval(src, moneyoff, uint64(9999999999999))

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

		val := uint64(100000000000)
		ch.Exp = math.MaxInt64
		ch.MaxHP = val
		ch.MaxMP = val
		ch.Stat = Stat{
			HP:  val,
			MP:  val,
			Atk: val,
			Def: val,
			Int: val,
			Res: val,
			Hit: val,
			Spd: val,
		}
		ch.Base = ch.Stat
		ch.MaxMana = val
		ch.Mana = val
		ch.Jump = [2]uint8{99, 99}
		ch.Move = [2]uint8{99, 99}
		ch.Counter = [2]uint8{99, 99}
		ch.Throw = [2]uint8{99, 99}
		ch.Range = [2]uint8{99, 99}

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
		magic1 = "NIS_DISGAEA4_COMPLETE_SAVEDATA_"
		magic2 = "NIS_DISGAEA4_TRIAL_SAVEDATA_"
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
