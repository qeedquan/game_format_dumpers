// TODO: not done
package main

import (
	"bytes"
	"encoding/binary"
	"flag"
	"fmt"
	"io"
	"log"
	"os"

	"github.com/davecgh/go-spew/spew"
)

var (
	cflag = flag.Bool("c", true, "dump config file")
	vflag = flag.Bool("v", true, "be verbose")
)

func main() {
	log.SetPrefix("dump-pack: ")
	log.SetFlags(0)
	flag.Usage = usage
	flag.Parse()
	if flag.NArg() < 1 {
		usage()
	}

	data, err := os.ReadFile(flag.Arg(0))
	ck(err)

	c := Compress{
		Trace: *vflag,
	}
	data, err = c.Decode(data)
	if err != nil {
		spew.Dump(data)
		ck(err)
	}

	var p interface{}
	if *cflag {
		p = &Config{}
	}

	spew.Dump(data)
	binary.Read(bytes.NewReader(data), binary.LittleEndian, p)
	spew.Dump(p)
}

func ck(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: pshd-dumper [options] file")
	flag.PrintDefaults()
	os.Exit(2)
}

type Config struct {
	// 0 - english
	// 1 - french
	// 2 - german
	// 3 - japanese
	// 4 - spanish
	// 5 - portugese
	Language uint8

	// lxxxrrrr
	// rrrr window resolution
	// windowed, 1920x1080, 1768x992, 1680x1050, 1600x1024, 1600x900, 1366x768
	// 1360x768, 1280x1024, 1280x960, 1280x800, 1280x768, 1280x720, 1176x664
	// 1152x864, 1024x768, 800x600, 720x576, 720x480, 640x480
	// l letterboxing
	Window uint8

	Volume uint16

	_ [0x22]byte

	Buttons [2][9]uint32
}

type Compress struct {
	err   error
	Trace bool
}

func (c *Compress) Encode(src []byte) []byte {
	var dst []byte
	for i := 0; i < len(src); {
		n := len(src) - i
		if n >= 4 {
			n = 3
		}
		dst = append(dst, src[i:i+n]...)
		i += n
	}
	dst = append(dst, 0x11)
	return dst
}

func (c *Compress) disassemble(op int, dst, src []byte, sp, m int) string {
	var args string
	switch {
	case op >= 0x40:
		v := op & 0x1f
		if v < 0xc {
			m = (c.read1(src, sp)>>2 | (op&0x1f)<<6) + 1
		}
		n := (op >> 5) - 1
		args = fmt.Sprintf("dst lookback %#x len %#x", m, n+2)
	case op >= 0x20:
		n, sp := c.runz(src, sp, op&0x1f, 0x1f)
		m := (c.read1(src, sp)<<6 | c.read1(src, sp+1)>>2) + 1
		args = fmt.Sprintf("dst lookback %#x len %#x", m, n+2)
	case op > 0x11:
		n := op - 0x11
		args = fmt.Sprintf("src lookahead len %#x", n)
	case op < 0x10:
		m := c.read1(src, sp)>>2 | op<<6 + 1
		n := c.read1(src, sp) & 3
		if op == 0 {
			n, _ = c.runz(src, sp+1, n, 0xf)
		}
		args = fmt.Sprintf("dst lookback %#x len %#x src lookahead len %#x", m, 2, n)
	}

	return fmt.Sprintf("op %#02x dst %#04x src %#04x sp %#04x %s", op, len(dst), len(src), sp, args)
}

func (c *Compress) Decode(src []byte) ([]byte, error) {
	var (
		dst  []byte
		op   int
		sp   int
		n, m int
	)

	op, sp = c.read1(src, sp), sp+1
loop:
	for {
		if sp >= len(src) || c.err != nil {
			break
		}

		if c.Trace {
			fmt.Println(c.disassemble(op, dst, src, sp, m))
		}

		switch {
		case op >= 0x40:
			if v := op & 0x1f; v < 0xc {
				m, sp = (c.read1(src, sp)>>2|v<<6)+1, sp+1
			}
			n = op>>5 - 1
			dst = c.runb(dst, len(dst)-m, n+2)

			n = c.read1(src, sp-1) & 0x3
			if n == 0 {
				op, sp = c.read1(src, sp), sp+1
			} else if n < 0x4 {
				dst, sp = c.append(dst, src, sp, n), sp+n
				op, sp = c.read1(src, sp), sp+1
			}

		case op >= 0x20:
			n, sp = c.runz(src, sp, op&0x1f, 0x1f)
			m = (c.read1(src, sp)<<6 | c.read1(src, sp+1)>>2) + 1
			dst = c.runb(dst, len(dst)-m, n+2)

			op, sp = c.read1(src, sp+1)&0x3, sp+2
			if op == 0x0 {
				op, sp = c.read1(src, sp), sp+1
			} else if op < 0x4 {
				n = op
				dst, sp = c.append(dst, src, sp, n), sp+n
				op, sp = c.read1(src, sp), sp+1
			}

		case op > 0x11:
			n = op - 0x11
			dst, sp = c.append(dst, src, sp, n), sp+n
			op, sp = c.read1(src, sp), sp+1

		case op == 0x11:
			break loop

		case op < 0x10:
			m = c.read1(src, sp)>>2 | op<<6 + 1
			n = c.read1(src, sp) & 0x3
			sp++
			if op == 0 {
				n, sp = c.runz(src, sp, n, 0xf)
			}
			dst = c.runb(dst, len(dst)-m, 2)
			dst, sp = c.append(dst, src, sp, n), sp+n
			op, sp = c.read1(src, sp), sp+1

		default:
			return dst, fmt.Errorf("unsupported op %#x", op)
		}
	}
	return dst, c.err
}

func (c *Compress) runb(p []byte, m, n int) []byte {
	for i := 0; i < n; i++ {
		if m+i < 0 || m+i >= len(p) {
			c.err = fmt.Errorf("out of bounds")
			return p
		}
		p = append(p, p[m+i])
	}
	return p
}

func (c *Compress) runz(p []byte, i, s, x int) (int, int) {
	if s != 0 {
		return s, i
	}
	v := 0
	for {
		v, i = c.read1(p, i), i+1
		if v != 0x0 || c.err != nil {
			s += v + x
			break
		}
		s += 0xff
	}
	return s, i
}

func (c *Compress) read1(p []byte, i int) int {
	if c.err != nil {
		return 0
	}
	if i >= len(p) {
		c.err = io.ErrUnexpectedEOF
		return 0
	}
	return int(p[i])
}

func (c *Compress) append(dst, src []byte, sp, n int) []byte {
	if c.err != nil {
		return dst
	}
	for i := 0; i < n; i++ {
		if sp+i >= len(src) {
			c.err = io.ErrUnexpectedEOF
			break
		}
		dst = append(dst, src[sp+i])
	}
	return dst
}
