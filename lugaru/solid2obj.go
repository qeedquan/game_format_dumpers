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

	m, err := readsolid(flag.Arg(0))
	if err != nil {
		log.Fatal(err)
	}

	writeobj(os.Stdout, m)
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: [options] model.solid")
	flag.PrintDefaults()
	os.Exit(2)
}

type Model struct {
	Vertices  []float32
	Texcoords []float32
	Faces     []uint16
}

func readsolid(name string) (m *Model, err error) {
	f, err := os.Open(name)
	if err != nil {
		return
	}
	defer f.Close()

	r := bufio.NewReader(f)
	m = &Model{}

	var nvert, ntri uint16
	binary.Read(r, binary.BigEndian, &nvert)
	binary.Read(r, binary.BigEndian, &ntri)

	m.Vertices = make([]float32, 3*nvert)
	m.Texcoords = make([]float32, 2*3*ntri)
	m.Faces = make([]uint16, 3*ntri)

	binary.Read(r, binary.BigEndian, m.Vertices)
	for i := 0; i < int(ntri); i++ {
		var f [6]uint16
		var t [6]float32

		binary.Read(r, binary.BigEndian, f[:])
		binary.Read(r, binary.BigEndian, t[:])

		m.Faces[3*i] = f[0]
		m.Faces[3*i+1] = f[2]
		m.Faces[3*i+2] = f[4]

		m.Texcoords[3*i] = t[0]
		m.Texcoords[3*i+1] = t[3]
		m.Texcoords[3*i+2] = t[1]
		m.Texcoords[3*i+3] = t[4]
		m.Texcoords[3*i+4] = t[2]
		m.Texcoords[3*i+5] = t[5]
	}

	return
}

func writeobj(w io.Writer, m *Model) {
	v := m.Vertices
	vt := m.Texcoords
	f := m.Faces

	fmt.Fprintf(w, "# %d vertices %d texcoords %d faces\n", len(v)/3, len(vt)/2, len(f)/3)

	for i := 0; i < len(v); i += 3 {
		fmt.Fprintf(w, "v %f %f %f\n", v[i], v[i+1], v[i+2])
	}

	for i := 0; i < len(vt); i += 2 {
		fmt.Fprintf(w, "vt %f %f\n", vt[i], vt[i+1])
	}

	for i := 0; i < len(f); i += 3 {
		fmt.Fprintf(w, "f %d %d %d\n", f[i]+1, f[i+1]+1, f[i+2]+1)
	}
}
