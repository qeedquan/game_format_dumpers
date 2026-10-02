package main

import (
	"bytes"
	"encoding/binary"
	"flag"
	"fmt"
	"log"
	"os"

	"github.com/qeedquan/go-media/archive/nipponichi"
)

type Crypt struct {
	r    nipponichi.Frand
	z    nipponichi.Compress
	Seed uint64
	Sig  []byte
}

var cryptSig = []byte{
	0x56, 0x02, 0x80, 0x57, 0x84, 0xf1, 0x2a, 0x88,
	0xea, 0x45, 0x2a, 0xb0, 0x3c, 0xa1, 0x58, 0x0d,
	0x35, 0x45, 0xa1, 0x61, 0x12, 0x2a, 0x0a, 0x78,
	0x14, 0x23, 0x65, 0xe3, 0x4a, 0x23, 0xae, 0x4a,
}

func NewCrypt() *Crypt {
	return &Crypt{
		Sig: append([]byte{}, cryptSig...),
	}
}

func (c *Crypt) Encrypt(src []byte) ([]byte, error) {
	c.r.Seed(c.Seed)

	dst, err := c.z.Encode2(src)
	if err != nil {
		return nil, err
	}

	var b [6]byte
	for i := range b {
		b[i] = uint8(c.r.Random(0xff))
	}
	xor := binary.LittleEndian.Uint32(b[:4])

	size := ((len(dst) + 3) / 4) * 4
	for i := 0; i < size; i += 4 {
		value := binary.LittleEndian.Uint32(dst[i:])
		binary.LittleEndian.PutUint32(dst[i:], xor^value)
	}

	buf := make([]byte, size+0x30)
	copy(buf, c.Sig[:0x20])
	binary.LittleEndian.PutUint32(buf[0x20:], xor)
	binary.LittleEndian.PutUint32(buf[0x24:], uint32(b[4])|uint32(b[5])<<16)
	binary.LittleEndian.PutUint32(buf[0x28:], uint32((len(dst)+3)/4))
	binary.LittleEndian.PutUint32(buf[0x2c:], uint32(len(dst)))
	copy(buf[0x30:], dst)

	return buf, nil
}

func (c *Crypt) Decrypt(src []byte) ([]byte, error) {
	if len(src) < len(c.Sig) || bytes.Compare(src[:len(c.Sig)], c.Sig) != 0 {
		return nil, fmt.Errorf("buffer not does not have encryption signature")
	}

	size := binary.LittleEndian.Uint32(src[0x28:]) * 4
	buf := make([]byte, size)
	copy(buf, src[0x30:])

	xor := binary.LittleEndian.Uint32(src[0x20:])
	for i := 0; i < len(buf); i += 4 {
		value := binary.LittleEndian.Uint32(buf[i:])
		binary.LittleEndian.PutUint32(buf[i:], xor^value)
	}

	realsize := binary.LittleEndian.Uint32(src[0x2c:])
	return c.z.Decode2(buf[:realsize], 0xffffffff)
}

type Save struct {
	Data  []byte
	Char  []Char
	Money uint64
}

type Char struct {
	Exp         uint32
	Unk1        [1472]uint8
	CurHP       uint32
	CurSP       uint32
	DisplayStat Stat
	Stat        Stat
	Unk2        [0x20]uint8
	Mana        uint32
	Unk3        [0x4a]uint8
	JM          [2]uint8
	MV          [2]uint8
	Counter     [2]uint8
	Unk4        [64]uint8
}

type Stat struct {
	HP  uint32
	SP  uint32
	Atk uint32
	Def uint32
	Int uint32
	Spd uint32
	Hit uint32
	Res uint32
}

func NewSave(data []byte) (*Save, error) {
	if len(data) < 128*1024 {
		return nil, fmt.Errorf("invalid save file size")
	}

	s := &Save{
		Data: make([]byte, len(data)),
	}
	copy(s.Data, data)
	read(data[0x290:], &s.Money)

	n := 0xbb8
	for i := 0; i < 32; i++ {
		var c Char
		read(data[n:], &c)
		s.Char = append(s.Char, c)
		n += 0x6b8
	}

	return s, nil
}

func (s *Save) MaxOut() {
	s.Money = 9999999999999
	for i := range s.Char {
		c := &s.Char[i]
		c.JM = [2]uint8{99, 99}
		c.MV = [2]uint8{99, 99}
		c.Counter = [2]uint8{99, 99}
		c.Mana = 99999999

		p := &s.Char[i].DisplayStat
		p.Atk = 99999999
		p.Def = 99999999
		p.Int = 99999999
		p.Spd = 99999999
		p.Hit = 99999999
		p.Res = 99999999

		p = &s.Char[i].Stat
		p.HP = 99999999
		p.SP = 99999999
		p.Atk = 99999999
		p.Def = 99999999
		p.Int = 99999999
		p.Spd = 99999999
		p.Hit = 99999999
		p.Res = 99999999
	}
	s.sync()
}

func (s *Save) sync() {
	p := s.Data
	write(p[0x290:], s.Money)
	n := 0xbb8
	for i := range s.Char {
		write(p[n:], &s.Char[i])
		n += 0x6b8
	}
}

func read(p []byte, v interface{}) {
	r := bytes.NewBuffer(p)
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

var (
	dump   = flag.Bool("d", false, "decrypt file")
	maxOut = flag.Bool("m", false, "max out")
)

func main() {
	log.SetFlags(0)
	log.SetPrefix("savemod: ")

	flag.Usage = usage
	flag.Parse()
	if flag.NArg() < 1 {
		usage()
	}

	src, err := os.ReadFile(flag.Arg(0))
	ck(err)

	crypt := NewCrypt()
	crypt.Seed = 1

	dst, err := crypt.Decrypt(src)
	ck(err)

	if *dump {
		if flag.NArg() < 2 {
			usage()
		}
		err := os.WriteFile(flag.Arg(1), dst, 0644)
		ck(err)
	}

	save, err := NewSave(dst)
	ck(err)

	if *maxOut {
		save.MaxOut()
		name := flag.Arg(0)
		if flag.NArg() > 1 {
			name = flag.Arg(1)
		}

		data, err := crypt.Encrypt(save.Data)
		ck(err)

		err = os.WriteFile(name, data, 0644)
		ck(err)
	}
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: [options] infile outfile")
	flag.PrintDefaults()
	os.Exit(2)
}

func ck(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
