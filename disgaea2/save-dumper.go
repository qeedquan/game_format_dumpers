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
	z    nipponichi.Slide
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

var (
	encrypt = flag.Bool("e", false, "encrypt input")
	seed    = flag.Uint64("s", 1, "seed for rng")
)

func main() {
	log.SetFlags(0)
	log.SetPrefix("save-dumper: ")

	flag.Usage = usage
	flag.Parse()
	if flag.NArg() != 2 {
		usage()
	}

	src, err := os.ReadFile(flag.Arg(0))
	ck(err)

	crypt := NewCrypt()
	crypt.Seed = *seed

	var dst []byte
	if *encrypt {
		dst, err = crypt.Encrypt(src)
	} else {
		dst, err = crypt.Decrypt(src)
	}
	ck(err)

	err = os.WriteFile(flag.Arg(1), dst, 0644)
	ck(err)
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
