package main

import (
	"bytes"
	"encoding/binary"
	"flag"
	"fmt"
	"io/ioutil"
	"log"
	"os"

	"../go/nipponichi"
)

type Frand struct {
	rnum           uint64
	rn, r1, r2, r3 uint64
}

type Frand2 struct {
	unum               uint64
	rn2, r12, r22, r32 uint64
}

func divqr64(a, b uint64) (quo, rem uint64) {
	if b == 0 {
		return 0, 0
	}
	return a / b, a % b
}

func mulshi128(a, b uint64) uint64 {
	_, hi := mul128(a, b)
	return hi >> 31
}

func mul128(a, b uint64) (lo, hi uint64) {
	a_lo := uint64(uint32(a))
	a_hi := uint64(a >> 32)
	b_lo := uint64(uint32(b))
	b_hi := uint64(b >> 32)

	a_x_b_hi := a_hi * b_hi
	a_x_b_mid := a_hi * b_lo
	b_x_a_mid := b_hi * a_lo
	a_x_b_lo := a_lo * b_lo

	carry_bit := (uint64(uint32(a_x_b_mid)) +
		uint64(uint32(b_x_a_mid)) +
		(a_x_b_lo >> 32)) >> 32

	lo = a * b
	hi = a_x_b_hi +
		(a_x_b_mid >> 32) + (b_x_a_mid >> 32) +
		carry_bit

	return
}

func (fr *Frand) Random(limit uint32) uint64 {
	const K = 0x8000000080000001

	var H uint64

	if fr.rn++; fr.rn <= 2 {
		goto L3
	}
	fr.rn = 0
L1:
	H = 0x8000000080000001
L2:
	fr.rnum = fr.rnum*0x36d + 0xe021
	H = mulshi128(fr.rnum, H)
	fr.r2 = fr.rnum - ((H << 32) - H)
	fr.rnum = fr.rnum*0x36d + 0xe021

	H = mulshi128(fr.rnum, K)
	fr.r3 = fr.rnum - ((H << 32) - H)

	if limit == 0 {
		return 0
	}
	_, H = divqr64(fr.r1+fr.r2+fr.r3, uint64(limit))
	return H
L3:
	if fr.rn == 0 {
		goto L1
	}
	fr.rnum = fr.rnum*0x36d + 0xe021
	H = mulshi128(fr.rnum, K)
	H = fr.rnum - ((H << 32) - H)
	fr.r1 = H
	if fr.rn == 0x1 {
		goto L2
	}

	fr.rnum = fr.rnum*0x36d + 0xe021
	H = mulshi128(fr.rnum, K)
	fr.r2 = fr.rnum - ((H << 32) - H)

	if limit == 0 {
		return 0
	}
	_, H = divqr64(fr.r1+fr.r2+fr.r3, uint64(limit))
	return H
}

// Seed is a linear sequence of the form
// y = a*x + b, to see this, do x_n+1 - x_n
// to get the constants.
func (fr *Frand) Seed(seed uint64) {
	const K = 0x8000000080000001

	fr.rn = 0

	A := seed*0x36d + 0xe021
	H := mulshi128(A, K)
	fr.r1 = A - ((H << 32) - H)

	A = (A * 0x36d) + 0xe021
	H = mulshi128(A, K)
	fr.r2 = A - ((H << 32) - H)

	A = (A * 0x36d) + 0xe021
	fr.rnum = A

	H = mulshi128(A, K)
	fr.r3 = A - ((H << 32) - H)
}

func (fr *Frand) GetSeed() uint64 {
	return fr.rnum
}

type Crypt struct {
	r    Frand
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

	src, err := ioutil.ReadFile(flag.Arg(0))
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

	err = ioutil.WriteFile(flag.Arg(1), dst, 0644)
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
