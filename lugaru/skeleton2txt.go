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

	z, err := readskeleton(flag.Arg(0))
	if err != nil {
		log.Fatal(err)
	}

	writeskeleton(os.Stdout, z)
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: [options] <skeleton>")
	flag.PrintDefaults()
	os.Exit(2)
}

type Skeleton struct {
	Joints           []Joint
	Muscles          []Muscle
	ForwardJoints    [3]uint32
	LowForwardJoints [3]uint32
}

type Joint struct {
	X, Y, Z   float32
	Length    float32
	Mass      float32
	HasParent byte
	Locked    byte
	ModelNum  uint32
	Visible   byte
	SameTwist byte
	Label     uint32
	HasGun    uint32
	Lower     byte
	ParentID  uint32
}

type Muscle struct {
	Length       float32
	TargetLength float32
	MinLength    float32
	MaxLength    float32
	Strength     float32
	Type         uint32
	Vertices     []uint32
	Visible      byte
	Parent1      uint32
	Parent2      uint32
}

func readskeleton(name string) (z *Skeleton, err error) {
	fp, err := os.Open(name)
	if err != nil {
		return
	}
	defer fp.Close()

	z = &Skeleton{}
	r := bufio.NewReader(fp)

	var numjoints, nummuscles, numvertices uint32

	binary.Read(r, binary.BigEndian, &numjoints)
	z.Joints = make([]Joint, numjoints)
	for i := range z.Joints {
		binary.Read(r, binary.BigEndian, &z.Joints[i])
	}

	binary.Read(r, binary.BigEndian, &nummuscles)
	z.Muscles = make([]Muscle, nummuscles)
	for i := range z.Muscles {
		m := &z.Muscles[i]

		binary.Read(r, binary.BigEndian, &m.Length)
		binary.Read(r, binary.BigEndian, &m.TargetLength)
		binary.Read(r, binary.BigEndian, &m.MinLength)
		binary.Read(r, binary.BigEndian, &m.MaxLength)
		binary.Read(r, binary.BigEndian, &m.Strength)
		binary.Read(r, binary.BigEndian, &m.Type)

		binary.Read(r, binary.BigEndian, &numvertices)
		m.Vertices = make([]uint32, numvertices)
		binary.Read(r, binary.BigEndian, m.Vertices[:])

		binary.Read(r, binary.BigEndian, &m.Visible)
		binary.Read(r, binary.BigEndian, &m.Parent1)
		binary.Read(r, binary.BigEndian, &m.Parent2)
	}

	binary.Read(r, binary.BigEndian, z.ForwardJoints[:])
	binary.Read(r, binary.BigEndian, z.LowForwardJoints[:])

	return
}

func writeskeleton(w io.Writer, z *Skeleton) {
	fmt.Fprintf(w, "# %d joints\n", len(z.Joints))
	for _, j := range z.Joints {
		fmt.Fprintf(w, "%#v\n", j)
	}
	fmt.Fprintf(w, "\n")
	fmt.Fprintf(w, "# %d muscles\n", len(z.Muscles))
	for _, m := range z.Muscles {
		fmt.Fprintf(w, "%#v\n", m)
	}
}
