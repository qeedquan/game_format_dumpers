package main

import (
	"debug/elf"
	"debug/pe"
	"flag"
	"fmt"
	"log"
	"os"
	"strings"

	"github.com/qeedquan/go-media/debug"
	"github.com/qeedquan/go-media/debug/elfutil"
	"github.com/qeedquan/go-media/debug/peutil"
)

var (
	errUnsupportedArch = fmt.Errorf("unsupported architecture")
	errSectionNotFound = fmt.Errorf("section not found")
	errPatchNotFound   = fmt.Errorf("patch not found")
)

var flags struct {
	Arch    string
	Section string
}

func main() {
	log.SetFlags(0)
	log.SetPrefix("")

	flag.StringVar(&flags.Arch, "a", "", "forcefully specify architecture")
	flag.StringVar(&flags.Section, "s", ".text", "specify section")
	flag.Usage = usage
	flag.Parse()
	if flag.NArg() != 3 {
		usage()
	}

	arch, data, err := readexec(flag.Arg(1), flags.Section)
	ck(err)

	any := true
	if flags.Arch != "" {
		arch = flags.Arch
		any = false
	}

	err = dump(arch, flag.Arg(0), flag.Arg(2), data, any)
	ck(err)
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: [options] function infile outfile")
	flag.PrintDefaults()
	os.Exit(2)
}

func ck(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

func readexec(name, section string) (arch string, data []byte, err error) {
	ef, eferr := elfutil.Open(name)
	pf, peerr := peutil.Open(name)
	switch {
	case eferr == nil:
		defer ef.Close()
		switch ef.Machine {
		case elf.EM_386:
			arch = "linux32"
		case elf.EM_X86_64:
			arch = "linux64"
		default:
			err = errUnsupportedArch
		}
		if err != nil {
			return
		}

		_, s := ef.Section(section)
		if s == nil {
			err = errSectionNotFound
			return
		}

		data = s.Data

	case peerr == nil:
		defer pf.Close()
		switch pf.Machine {
		case pe.IMAGE_FILE_MACHINE_I386:
			arch = "windows32"
		default:
			err = errUnsupportedArch
		}
		if err != nil {
			return
		}

		s := pf.Section(section)
		if s == nil {
			err = errSectionNotFound
			return
		}

		data = s.Data

	default:
		err = fmt.Errorf("unsupported file type")
	}

	return
}

func dump(arch, fun, name string, data []byte, any bool) (err error) {
	var p *debug.Patch
	for _, c := range ctab {
		if c.Func == fun && ((any && strings.HasPrefix(c.Arch, arch)) || (!any && c.Arch == arch)) {
			l := debug.FindPatches(data, c.Header, c.Trailer)
			if len(l) != 1 {
				if !any {
					return errPatchNotFound
				}
			} else {
				fmt.Printf("%s:%s: found signature\n", c.Arch, c.Func)
				p = &l[0]
				break
			}
		}
	}
	if p == nil {
		return errPatchNotFound
	}

	fmt.Printf("writing to %s\n", name)
	return os.WriteFile(name, p.Data, 0644)
}

type Code struct {
	Arch    string
	Func    string
	Header  []byte
	Trailer []byte
}

var ctab = []Code{
	{
		"linux32dbg", "PSIO_Util_Decompress",
		[]byte{0x55, 0x57, 0x56, 0x53, 0x83, 0xec, 0x20, 0x8b, 0x6c, 0x24, 0x34},
		[]byte{0xe9, 0x25, 0xf9, 0xff, 0xff, 0x66, 0x90, 0x66, 0x90},
	},

	{
		"linux64", "PSIO_Util_Decompress",
		[]byte{0x41, 0x57, 0x41, 0x56, 0x41, 0x55, 0x41, 0x54, 0x55, 0x53, 0x0f, 0xb6, 0x2f, 0x40, 0x80, 0xfd, 0x11, 0x0f, 0x86, 0x21, 0x02, 0x00, 0x00},
		[]byte{0x31, 0xc0, 0xe9, 0x76, 0xff, 0xff, 0xff, 0x66, 0x2e, 0x0f, 0x1f, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00},
	},

	{
		"windows32", "PSIO_Util_Decompress",
		[]byte{0x8b, 0x44, 0x24, 0x08, 0x53, 0x55, 0x56, 0x8b, 0x74, 0x24, 0x10, 0x03, 0xc6, 0x89, 0x44, 0x24, 0x10},
		[]byte{0x5f, 0x1b, 0xc0, 0x5e, 0x83, 0xe0, 0xfc, 0x5d, 0x83, 0xc0, 0xfc, 0x5b, 0xc3, 0xcc, 0xcc, 0xcc},
	},

	{
		"windows32dbg", "PSIO_Util_Decompress",
		[]byte{0x83, 0x3d, 0x48, 0x10, 0x5e, 0x00, 0x00, 0x74, 0x04, 0x33, 0xc0, 0xeb, 0x0c, 0xa1, 0x34, 0x81, 0x60, 0x00},
		[]byte{0x5f, 0x1b, 0xc0, 0x5e, 0x83, 0xe0, 0xfc, 0x5d, 0x83, 0xc0, 0xfc, 0x5b, 0xc3, 0xcc, 0xcc, 0xcc},
	},
}
