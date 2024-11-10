package main

import (
	"bufio"
	"encoding/binary"
	"flag"
	"fmt"
	"io"
	"log"
	"os"
)

func main() {
	flag.Parse()
	if flag.NArg() < 1 {
		usage()
	}

	z, err := readanim(flag.Arg(0))
	if err != nil {
		log.Fatal(err)
	}

	writeanim(os.Stdout, z)
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: [options] <animation>")
	flag.PrintDefaults()
	os.Exit(2)
}

type Animation struct {
	Frames []Frame
}

type Vec3 struct {
	X, Y, Z float32
}

type Frame struct {
	Joints       []Joint
	Speed        float32
	Label        float32
	WeaponTarget Vec3
}

type Joint struct {
	Pos    Vec3
	Twist  float32
	Twist2 float32
	Ground byte
}

func readanim(name string) (z *Animation, err error) {
	fp, err := os.Open(name)
	if err != nil {
		return
	}
	defer fp.Close()

	z = &Animation{}
	r := bufio.NewReader(fp)

	var numframes, numjoints uint32
	binary.Read(r, binary.BigEndian, &numframes)
	binary.Read(r, binary.BigEndian, &numjoints)

	z.Frames = make([]Frame, numframes)
	for i := range z.Frames {
		f := &z.Frames[i]
		f.Joints = make([]Joint, numjoints)
		for j := range f.Joints {
			binary.Read(r, binary.BigEndian, &f.Joints[j].Pos.X)
			binary.Read(r, binary.BigEndian, &f.Joints[j].Pos.Y)
			binary.Read(r, binary.BigEndian, &f.Joints[j].Pos.Z)
		}

		for j := range f.Joints {
			binary.Read(r, binary.BigEndian, &f.Joints[j].Twist)
		}

		for j := range f.Joints {
			binary.Read(r, binary.BigEndian, &f.Joints[j].Ground)
		}

		binary.Read(r, binary.BigEndian, &f.Speed)
	}

	for i := range z.Frames {
		f := &z.Frames[i]
		for j := range f.Joints {
			binary.Read(r, binary.BigEndian, &f.Joints[j].Twist2)
		}
	}

	for i := range z.Frames {
		f := &z.Frames[i]
		binary.Read(r, binary.BigEndian, &f.Label)
	}

	var weapontargetnum uint32
	binary.Read(r, binary.BigEndian, &weapontargetnum)

	for i := range z.Frames {
		f := &z.Frames[i]
		binary.Read(r, binary.BigEndian, &f.WeaponTarget.X)
		binary.Read(r, binary.BigEndian, &f.WeaponTarget.Y)
		binary.Read(r, binary.BigEndian, &f.WeaponTarget.Z)
	}

	return
}

func writeanim(w io.Writer, z *Animation) {
	fmt.Fprintf(w, "# %d frames\n\n", len(z.Frames))
	for i, f := range z.Frames {
		fmt.Fprintf(w, "Frame #%d {\n", i+1)
		fmt.Fprintf(w, "  Label        %f\n", f.Label)
		fmt.Fprintf(w, "  Speed        %f\n", f.Speed)
		fmt.Fprintf(w, "  WeaponTarget (%f %f %f)\n", f.WeaponTarget.X, f.WeaponTarget.Y, f.WeaponTarget.Z)

		fmt.Fprintf(w, "  Joints (%d) {\n", len(f.Joints))
		for _, j := range f.Joints {
			fmt.Fprintf(w, "    xyz=(%f %f %f) twist=%f twist2=%f ground=%d\n",
				j.Pos.X, j.Pos.Y, j.Pos.Z, j.Twist, j.Twist2, j.Ground)
		}
		fmt.Fprintf(w, "  }\n")
		fmt.Fprintf(w, "}\n\n")
	}
}
