// dump dragon warrior 1 nes rom
// http://www.romhacking.net/documents/dwbytes.txt
package main

import (
	"bytes"
	"encoding/binary"
	"flag"
	"fmt"
	"image"
	"image/color"
	"image/draw"
	"image/png"
	"log"
	"os"
)

var (
	xmag    = flag.Int("xmag", 1, "x magnification")
	ymag    = flag.Int("ymag", 1, "y magnification")
	palFile = flag.String("pal", "", "use palette colors file")

	status int
)

func main() {
	log.SetPrefix("dw1-nes-dumper: ")
	log.SetFlags(0)
	flag.Parse()
	if flag.NArg() < 1 {
		usage()
	}

	data, err := os.ReadFile(flag.Arg(0))
	ck(err)

	dw, err := NewDW1(data)
	ck(err)

	if *palFile != "" {
		ck(dw.LoadPAL(*palFile))
	}
	dw.Xmag = *xmag
	dw.Ymag = *ymag
	dw.Dump(flag.Arg(1))
	os.Exit(status)
}

func ck(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

func ek(err error) bool {
	if err != nil {
		fmt.Fprintln(os.Stderr, err)
		status = 1
		return true
	}
	return false
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: [options] rom [dir]")
	flag.PrintDefaults()
	os.Exit(2)
}

type DW1 struct {
	ROM     []byte
	PRG     []byte
	CHR     []byte
	PAL     [512]color.RGBA
	Tileset map[int]Tile
	BG      []Sprite
	Char    []Sprite
	Tiles   []Tile
	Xmag    int
	Ymag    int
}

type Tile struct {
	image.Point
	ID  int
	AT  int
	PAL []int
}

type Sprite struct {
	Tile   []Tile
	Width  int
	Height int
}

func NewDW1(rom []byte) (*DW1, error) {
	if len(rom) < 80*1024+16 {
		return nil, fmt.Errorf("invalid rom size of %v bytes", len(rom))
	}

	d := &DW1{
		ROM:     rom,
		PRG:     rom[16:],
		CHR:     rom[16+0x4000*4:],
		PAL:     defaultPAL,
		Tileset: tileset,
		Xmag:    1,
		Ymag:    1,
	}
	for _, b := range bgSprites {
		d.BG = append(d.BG, d.makeMapSprite(b[0], b[1], b[2], b[3]))
	}
	for i := 256; i <= 340; i++ {
		if i == 326 || i == 330 {
			continue
		}
		d.Tiles = append(d.Tiles, d.Tileset[i])
	}

	return d, nil
}

func (d *DW1) LoadPAL(name string) error {
	f, err := os.Open(name)
	if err != nil {
		return err
	}
	defer f.Close()

	i := 0
	for ; i < len(d.PAL); i++ {
		var c [3]byte
		err = binary.Read(f, binary.LittleEndian, &c)
		if err != nil {
			break
		}
		d.PAL[i] = color.RGBA{c[0], c[1], c[2], 255}
	}
	if i < 64 {
		return &os.PathError{Op: "read", Path: name, Err: err}
	}
	if i == 64 {
		for j := 1; j < 8; j++ {
			copy(d.PAL[j*64:], d.PAL[0:64])
		}
	}
	return nil
}

func (d *DW1) Dump(dir string) {
	if dir == "" {
		dir = "dw1"
	}
	os.MkdirAll(dir, 0755)
	os.Chdir(dir)

	d.dumpTiles()
	d.dumpPAL()
	d.dumpMaps()
	d.dumpSprites()
	d.dumpOverworldRaw()
	d.dumpOverworld()
}

func (d *DW1) dumpPAL() {
	n := len(d.PAL) * 32 / 16
	m := image.NewRGBA(image.Rect(0, 0, n, n))
	for i, c := range d.PAL {
		x := i % 16
		y := i / 16
		r := image.Rect(x*32, y*32, (x+1)*32, (y+1)*32)
		draw.Draw(m, r, image.NewUniform(c), image.ZP, draw.Src)
	}
	d.writePNG("palette.png", m)
}

func (d *DW1) writePNG(name string, m image.Image) (err error) {
	defer ek(err)
	f, err := os.Create(name)
	if err != nil {
		return err
	}
	err = png.Encode(f, m)
	xerr := f.Close()
	if err == nil {
		err = xerr
	}
	return err
}

func (d *DW1) dumpTiles() {
	tile := 1024
	xmax := 32
	x, y := 0, 0

	img := image.NewRGBA(image.Rect(0, 0, (xmax+1)*8*d.Xmag, (tile/xmax)*8*d.Ymag))
	for i := 0; i < tile; i++ {
		at := 0x0
		pal := overworldPAL[:]

		if t, found := tileset[i]; found {
			at = t.AT
			pal = t.PAL
		}
		d.dumpTile(img, x*8*d.Xmag, y*8*d.Ymag, d.Xmag, d.Ymag, d.CHR, pal, i, at, 0, false)

		if x == xmax {
			x = 0
			y++
		} else {
			x++
		}
	}

	d.writePNG("tiles.png", img)
}

func (d *DW1) dumpTile(img *image.RGBA, x, y, xmag, ymag int, chr []byte, pal []int, tile, at, emp int, grayscale bool) {
	var buf [8]uint8

	py := y
	for i := 0; i < 8; i++ {
		px := x
		pataddr := tile<<4 | i
		p1, p2 := chr[pataddr], chr[pataddr|8]

		// get palette index
		tcl := rchr[p1]
		tch := rchr[p2]

		for i := range buf {
			buf[i] = uint8(at << 2)
		}

		putorle32(chrlobit[tcl&0xF], buf[0:])
		putorle32(chrlobit[tcl>>4], buf[4:])

		putorle32(chrhibit[tch&0xF], buf[0:])
		putorle32(chrhibit[tch>>4], buf[4:])

		for j := 0; j < 8; j++ {
			p := pal[0]
			tc := buf[j]

			if tc&0x3 != 0 {
				p = pal[tc]
			}

			if grayscale {
				p &= 0x30
			}

			idx := p | emp<<6
			c := d.PAL[idx]
			for iy := 0; iy < ymag; iy++ {
				for ix := 0; ix < xmag; ix++ {
					img.Set(px+ix, py+iy, c)
				}
			}
			px += xmag
		}
		py += ymag
	}
}

func (d *DW1) dumpSprite(img *image.RGBA, spr Sprite, x, y int, xmag, ymag int) {
	for _, p := range spr.Tile {
		px := x + p.X*8*xmag
		py := y + p.Y*8*ymag
		d.dumpTile(img, px, py, xmag, ymag, d.CHR, p.PAL, p.ID, p.AT, 0, false)
	}
}

func (d *DW1) makeMapSprite(i1, i2, i3, i4 int) Sprite {
	s := Sprite{
		Tile: []Tile{
			d.Tileset[i1],
			d.Tileset[i2],
			d.Tileset[i3],
			d.Tileset[i4],
		},
		Width:  16,
		Height: 16,
	}
	s.Tile[1].Point = image.Pt(1, 0)
	s.Tile[2].Point = image.Pt(0, 1)
	s.Tile[3].Point = image.Pt(1, 1)

	return s
}

func (d *DW1) dumpMaps() {
	townTable := d.ROM[0x1a10:0x1b00]
	dungeonTable := d.ROM[0x1a20:0x1a28]
	maps := []struct {
		name   string
		table  []byte
		data   []byte
		width  int
		height int
		mask   byte
	}{
		{"charlock_castle_f1", townTable, d.ROM[0xc0:0x188], 20, 20, 0xf},
		{"hauksness", townTable, d.ROM[0x188:0x250], 20, 20, 0xf},
		{"tantegel_castle", townTable, d.ROM[0x250:0x412], 30, 30, 0xf},
		{"tantegel_castle_throne_room", townTable, d.ROM[0x412:0x444], 10, 10, 0xf},
		{"charlock_castle_b7", townTable, d.ROM[0x444:0x606], 30, 30, 0xf},
		{"kol", townTable, d.ROM[0x606:0x726], 24, 24, 0xf},
		{"brecconary", townTable, d.ROM[0x726:0x8e8], 30, 30, 0xf},
		{"cantlin", townTable, d.ROM[0x8e8:0xaaa], 30, 30, 0xf},
		{"garinham", townTable, d.ROM[0xaaa:0xb72], 20, 20, 0xf},
		{"rimuldar", townTable, d.ROM[0xb72:0xd34], 30, 30, 0xf},
		{"tantegel_castle_sunlight_shrine", townTable, d.ROM[0xd34:0xd66], 10, 10, 0x7},
		{"rain_shrine", townTable, d.ROM[0xd66:0xd98], 10, 10, 0x7},
		{"rainbow_shrine", townTable, d.ROM[0xd98:0xdca], 10, 10, 0x7},
		{"charlock_castle_b1", dungeonTable, d.ROM[0xdca:0xe92], 20, 20, 0x7},
		{"charlock_castle_b2", dungeonTable, d.ROM[0xe92:0xec4], 10, 10, 0x7},
		{"charlock_castle_b3", dungeonTable, d.ROM[0xec4:0xef6], 10, 10, 0x7},
		{"charlock_castle_b4", dungeonTable, d.ROM[0xef6:0xf28], 10, 10, 0x7},
		{"charlock_castle_b5", dungeonTable, d.ROM[0xf28:0xf5a], 10, 10, 0x7},
		{"charlock_castle_b6", dungeonTable, d.ROM[0xf5a:0xf8c], 10, 10, 0x7},
		{"swamp_cave", dungeonTable, d.ROM[0xf8c:0xfe6], 6, 30, 0x7},
		{"rock_mountain_b1", dungeonTable, d.ROM[0xfe6:0x1048], 14, 14, 0x7},
		{"rock_mountain_b2", dungeonTable, d.ROM[0x1048:0x10aa], 14, 14, 0x7},
		{"garinham_grave_b1", dungeonTable, d.ROM[0x10aa:0x1172], 20, 20, 0x7},
		{"garinham_grave_b2", dungeonTable, d.ROM[0x126c:0x12c0], 14, 12, 0x7},
		{"garinham_grave_b3", dungeonTable, d.ROM[0x1172:0x123a], 20, 20, 0x7},
		{"garinham_grave_b4", dungeonTable, d.ROM[0x123a:0x126c], 10, 10, 0x7},
		{"erdricks_cave_b1", dungeonTable, d.ROM[0x12C0:0x12F2], 10, 10, 0x7},
		{"erdricks_cave_b2", dungeonTable, d.ROM[0x12F2:0x1324], 10, 10, 0x7},
	}

	for _, m := range maps {
		img, lay := d.dumpMap(d.BG, m.table, m.data, m.width, m.height, m.mask)
		var b bytes.Buffer
		for i := range lay {
			for j := range lay[i] {
				fmt.Fprintf(&b, "%2d ", lay[i][j])
			}
			fmt.Fprintf(&b, "\n")
		}
		err := os.WriteFile(fmt.Sprintf("%s.txt", m.name), b.Bytes(), 0644)
		ek(err)
		d.writePNG(fmt.Sprintf("%s.png", m.name), img)
	}
}

func (d *DW1) dumpMap(spr []Sprite, table, map_ []byte, width, height int, mask byte) (*image.RGBA, [][]byte) {
	lay := [][]byte{}
	img := image.NewRGBA(image.Rect(0, 0, width*16*d.Xmag, height*16*d.Ymag))
	i := 0
	for y := 0; y < height; y++ {
		lay = append(lay, []byte{})
		for x := 0; x < width; x++ {
			l := (map_[i/2] >> ((1 - uint(i&1)) * 4)) & 0xf
			s := spr[table[l&mask]]
			lay[len(lay)-1] = append(lay[len(lay)-1], table[l&mask])
			if s.Tile != nil {
				d.dumpSprite(img, s, x*s.Width*d.Xmag, y*s.Height*d.Ymag, d.Xmag, d.Ymag)
			} else {
				fmt.Printf("%x\n", table[l])
			}
			i++
		}
	}
	return img, lay
}

func (d *DW1) dumpSprites() {
	width := 32
	height := 32
	img := image.NewRGBA(image.Rect(0, 0, width*16*d.Xmag, height*16*d.Ymag))

	x, y := 0, 0
	i := 0
loop:
	for ; y < height; y++ {
		for x = 0; x < width; x++ {
			if i >= len(d.BG) {
				y++
				break loop
			}
			s := d.BG[i]
			d.dumpSprite(img, s, x*s.Width*d.Xmag, y*s.Height*d.Ymag, d.Xmag, d.Ymag)
			i++
		}
	}

	i = 0
loop1:
	for ; y < height; y++ {
		for x = 0; x < width; x++ {
			if i >= len(d.Tiles) {
				break loop1
			}
			p := d.Tiles[i]
			px := x * 8 * d.Xmag
			py := y * 8 * d.Ymag
			d.dumpTile(img, px, py, d.Xmag, d.Ymag, d.CHR, p.PAL, p.ID, p.AT, 0, false)
			i++
		}
	}

	d.writePNG("sprites.png", img)
}

func (d *DW1) dumpOverworldRaw() {
	width := 120
	height := 120
	img := image.NewRGBA(image.Rect(0, 0, width*16*d.Xmag, height*16*d.Ymag))
	map_ := d.ROM[0x1d55:]
	table := d.ROM[0x19F3:0x1A0F]
	x, y := 0, 0
	i := 0

	lay := make([][]byte, height)
	for i := range lay {
		lay[i] = make([]byte, width)
	}

loop:
	for {
		l := (map_[i] >> 4) & 0xf
		n := map_[i] & 0xf
		s := d.BG[table[l]]
		i++

		switch table[l] {
		case 5:
			for i := range s.Tile {
				s.Tile[i].PAL = overworldPAL
			}
		}

		for j := byte(0); j <= n; j++ {
			if s.Tile != nil {
				d.dumpSprite(img, s, x*s.Width*d.Xmag, y*s.Height*d.Ymag, d.Xmag, d.Ymag)
			} else {
				fmt.Printf("%x\n", table[l])
			}
			lay[y][x] = table[l]

			if x++; x == width {
				x = 0
				if y++; y == height {
					break loop
				}
			}
		}
	}

	var b bytes.Buffer
	for i := range lay {
		for j := range lay[i] {
			fmt.Fprintf(&b, "%x ", lay[i][j])
		}
		fmt.Fprintln(&b)
	}
	err := os.WriteFile("overworld_raw.txt", b.Bytes(), 0644)
	ek(err)
	d.writePNG("overworld_raw.png", img)
}

func (d *DW1) dumpOverworld() {
	img := image.NewRGBA(image.Rect(0, 0, 120*16*d.Xmag, 120*16*d.Ymag))
	map_, off := d.dumpOverworldLine(img, d.ROM[0x1d6d:], 0, 0, 0, 120, 11)
	map_, off = d.dumpOverworldLine(img, map_, off, 2, 11, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 3, 12, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 3, 13, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 3, 14, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 3, 15, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 6, 16, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 6, 17, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 6, 18, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 6, 19, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 6, 20, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 6, 21, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 6, 22, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 6, 23, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 6, 24, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 6, 25, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 6, 26, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 6, 27, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 7, 28, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 9, 29, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 12, 30, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 12, 31, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 12, 32, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 12, 33, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 12, 34, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 14, 35, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 15, 36, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 15, 37, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 16, 38, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 16, 39, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 16, 40, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 16, 41, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 16, 42, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 16, 43, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 16, 44, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 16, 45, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 16, 46, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 17, 47, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 17, 48, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 17, 49, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 17, 50, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 17, 51, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 17, 52, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 17, 53, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 17, 54, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 17, 55, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 17, 56, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 17, 57, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 17, 58, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 17, 59, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 17, 60, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 17, 61, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 17, 62, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 17, 63, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 19, 64, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 20, 65, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 20, 66, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 20, 67, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 20, 68, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 20, 69, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 20, 70, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 20, 71, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 20, 72, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 20, 73, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 20, 74, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 21, 75, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 23, 76, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 25, 77, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 25, 78, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 25, 79, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 25, 80, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 25, 81, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 25, 82, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 25, 83, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 25, 84, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 25, 85, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 27, 86, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 29, 87, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 31, 88, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 31, 89, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 31, 90, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 31, 91, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 34, 92, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 38, 93, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 43, 94, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 47, 95, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 47, 96, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 47, 97, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 47, 98, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 47, 99, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 47, 100, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 47, 101, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 47, 102, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 47, 103, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 47, 104, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 47, 105, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 47, 106, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 49, 107, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 51, 108, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 55, 109, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 55, 110, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 57, 111, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 59, 112, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 62, 113, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 66, 114, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 71, 115, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 71, 116, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 71, 117, 120, 1)
	map_, off = d.dumpOverworldLine(img, map_, off, 71, 118, 120, 1)
	//map_, off = d.dumpOverworldLine(img, map_, off, 83, 119, 120, 1)
	d.writePNG("overworld.png", img)
}

func (d *DW1) dumpOverworldLine(img *image.RGBA, map_ []byte, off byte, x, y, w, h int) ([]byte, byte) {
	table := d.ROM[0x19F3:0x1A0F]

	i := 0
	px, py := x, y
loop:
	for {
		l := (map_[i] >> 4) & 0xf
		n := map_[i] & 0xf
		s := d.BG[table[l]]
		for j := range s.Tile {
			s.Tile[j].PAL = overworldPAL
		}

		for j := off; j <= n; j++ {
			if s.Tile != nil {
				r := img.Bounds()
				_ = r
				d.dumpSprite(img, s, (px*s.Width*d.Xmag)%(r.Dx()), (py)*s.Height*d.Ymag, d.Xmag, d.Ymag)
				//d.dumpSprite(img, s, (px * s.Width * d.Xmag), (py)*s.Height*d.Ymag, d.Xmag, d.Ymag)
			} else {
				fmt.Printf("%x\n", table[l])
			}

			if px++; px >= x+w {
				px = 0
				if py++; py >= y+h {
					off = j + 1
					break loop
				}
			}
		}
		off = 0
		i++
	}
	return map_[i:], off
}

func putorle32(v uint32, b []byte) {
	b[0] |= uint8(v & 0xFF)
	b[1] |= uint8((v >> 8) & 0xFF)
	b[2] |= uint8((v >> 16) & 0xFF)
	b[3] |= uint8((v >> 24) & 0xFF)
}

var bgSprites = [][]int{
	{416, 416, 416, 416}, // grass
	{417, 417, 417, 417}, // sand
	{418, 419, 420, 421}, // mound/hills
	{371, 372, 373, 374}, // stairs up
	{375, 375, 375, 375}, // floor
	{379, 380, 381, 382}, // stairs down
	{385, 385, 385, 385}, // swamp
	{386, 387, 388, 389}, // town
	{390, 391, 392, 393}, // cave
	{394, 395, 396, 397}, // castle
	{411, 412, 413, 414}, // bridge
	{383, 383, 384, 384}, // forest
	{504, 506, 505, 507}, // chest
	{503, 499, 365, 366}, // barrier
	{503, 499, 365, 366}, // desk
	{424, 424, 502, 502}, // water
	{367, 368, 369, 370}, // stone block
	{399, 400, 401, 402}, // locked door
	{422, 423, 500, 501}, // craggy mountains
	{403, 404, 405, 406}, // weapon shop
	{407, 408, 409, 410}, // inn
	{339, 339, 339, 339}, // roof (todo)
	{339, 339, 339, 339}, // black tile
	{425, 427, 426, 428}, // princess
	{339, 339, 339, 339}, // shoreline
	{339, 339, 339, 339}, // shoreline
	{339, 339, 339, 339}, // shoreline
	{339, 339, 339, 339}, // shoreline
	{339, 339, 339, 339}, // shoreline
	{339, 339, 339, 339}, // shoreline
	{339, 339, 339, 339}, // shoreline
	{339, 339, 339, 339}, // shoreline
}

var tileset = map[int]Tile{
	// text title screen
	0: {
		ID:  0,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	1: {
		ID:  1,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	2: {
		ID:  2,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	3: {
		ID:  3,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	4: {
		ID:  4,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	5: {
		ID:  5,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	6: {
		ID:  6,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	7: {
		ID:  7,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	8: {
		ID:  8,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	9: {
		ID:  9,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	10: {
		ID:  10,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	11: {
		ID:  11,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	12: {
		ID:  12,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	13: {
		ID:  13,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	14: {
		ID:  14,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	15: {
		ID:  15,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	16: {
		ID:  16,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	17: {
		ID:  17,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	18: {
		ID:  18,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	19: {
		ID:  19,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	20: {
		ID:  20,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	21: {
		ID:  21,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	22: {
		ID:  22,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	23: {
		ID:  23,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	24: {
		ID:  24,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	25: {
		ID:  25,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	26: {
		ID:  26,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	27: {
		ID:  27,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	28: {
		ID:  28,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	29: {
		ID:  29,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	30: {
		ID:  30,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	31: {
		ID:  31,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	32: {
		ID:  32,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	33: {
		ID:  33,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	34: {
		ID:  34,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	35: {
		ID:  35,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	36: {
		ID:  36,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	37: {
		ID:  37,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	38: {
		ID:  38,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	39: {
		ID:  39,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	40: {
		ID:  40,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	41: {
		ID:  41,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	42: {
		ID:  42,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	43: {
		ID:  43,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	44: {
		ID:  44,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	45: {
		ID:  45,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	46: {
		ID:  46,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	47: {
		ID:  47,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	48: {
		ID:  48,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	49: {
		ID:  49,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	50: {
		ID:  50,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	51: {
		ID:  51,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	52: {
		ID:  52,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	53: {
		ID:  53,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	54: {
		ID:  54,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	55: {
		ID:  55,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	56: {
		ID:  56,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	57: {
		ID:  57,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	58: {
		ID:  58,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	59: {
		ID:  59,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	60: {
		ID:  60,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	61: {
		ID:  61,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	62: {
		ID:  62,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	63: {
		ID:  63,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	64: {
		ID:  64,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	65: {
		ID:  65,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	66: {
		ID:  66,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	67: {
		ID:  67,
		AT:  0x0,
		PAL: titlePAL,
	},

	// text title screen
	68: {
		ID:  68,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	69: {
		ID:  69,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	70: {
		ID:  70,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	71: {
		ID:  71,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	72: {
		ID:  72,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	73: {
		ID:  73,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	74: {
		ID:  66,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	75: {
		ID:  75,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	76: {
		ID:  76,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	77: {
		ID:  77,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	78: {
		ID:  78,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	79: {
		ID:  79,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	80: {
		ID:  80,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	81: {
		ID:  81,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	82: {
		ID:  82,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	83: {
		ID:  83,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	84: {
		ID:  84,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	85: {
		ID:  85,
		AT:  0x3,
		PAL: titlePAL,
	},

	// text title screen
	86: {
		ID:  86,
		AT:  0x3,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	116: {
		ID:  116,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	117: {
		ID:  117,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	118: {
		ID:  118,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	119: {
		ID:  119,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	120: {
		ID:  120,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	121: {
		ID:  121,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	122: {
		ID:  122,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	123: {
		ID:  123,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	124: {
		ID:  124,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	125: {
		ID:  125,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	126: {
		ID:  126,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	127: {
		ID:  127,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	128: {
		ID:  128,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	129: {
		ID:  129,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	130: {
		ID:  130,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	131: {
		ID:  131,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	132: {
		ID:  132,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	133: {
		ID:  133,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	134: {
		ID:  134,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	135: {
		ID:  135,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	136: {
		ID:  136,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	137: {
		ID:  137,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	138: {
		ID:  138,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	139: {
		ID:  139,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	140: {
		ID:  140,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	141: {
		ID:  141,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	142: {
		ID:  142,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	143: {
		ID:  143,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	144: {
		ID:  144,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	145: {
		ID:  145,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	146: {
		ID:  146,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	147: {
		ID:  147,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	148: {
		ID:  148,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	149: {
		ID:  149,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	150: {
		ID:  150,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	151: {
		ID:  151,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	152: {
		ID:  152,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	153: {
		ID:  153,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	154: {
		ID:  154,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	155: {
		ID:  155,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	156: {
		ID:  156,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	157: {
		ID:  157,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	158: {
		ID:  158,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	159: {
		ID:  159,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	160: {
		ID:  160,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	161: {
		ID:  161,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	162: {
		ID:  162,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	163: {
		ID:  163,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	164: {
		ID:  164,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	165: {
		ID:  165,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	166: {
		ID:  166,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	167: {
		ID:  167,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	168: {
		ID:  168,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	169: {
		ID:  169,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	170: {
		ID:  170,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	171: {
		ID:  171,
		AT:  0x0,
		PAL: titlePAL,
	},

	// dragon warrior text title screen
	172: {
		ID:  172,
		AT:  0x0,
		PAL: titlePAL,
	},

	// 0
	256: {
		ID:  256,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// 1
	257: {
		ID:  257,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// 2
	258: {
		ID:  258,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// 3
	259: {
		ID:  259,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// 4
	260: {
		ID:  260,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// 5
	261: {
		ID:  261,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// 6
	262: {
		ID:  262,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// 7
	263: {
		ID:  263,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// 8
	264: {
		ID:  264,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// 9
	265: {
		ID:  265,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// a
	266: {
		ID:  266,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// b
	267: {
		ID:  267,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// c
	268: {
		ID:  268,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// d
	269: {
		ID:  269,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// e
	270: {
		ID:  270,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// f
	271: {
		ID:  271,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// g
	272: {
		ID:  272,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// h
	273: {
		ID:  273,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// i
	274: {
		ID:  274,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// j
	275: {
		ID:  275,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// k
	276: {
		ID:  276,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// l
	277: {
		ID:  277,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// m
	278: {
		ID:  278,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// n
	279: {
		ID:  279,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// o
	280: {
		ID:  280,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// p
	281: {
		ID:  281,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// q
	282: {
		ID:  282,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// r
	283: {
		ID:  283,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// s
	284: {
		ID:  284,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// t
	285: {
		ID:  285,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// u
	286: {
		ID:  286,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// v
	287: {
		ID:  287,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// w
	288: {
		ID:  288,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// x
	289: {
		ID:  289,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// y
	290: {
		ID:  290,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// z
	291: {
		ID:  291,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// A
	292: {
		ID:  292,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// B
	293: {
		ID:  293,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// C
	294: {
		ID:  294,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// D
	295: {
		ID:  295,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// E
	296: {
		ID:  296,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// F
	297: {
		ID:  297,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// G
	298: {
		ID:  298,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// H
	299: {
		ID:  299,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// I
	300: {
		ID:  300,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// J
	301: {
		ID:  301,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// K
	302: {
		ID:  302,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// L
	303: {
		ID:  303,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// M
	304: {
		ID:  304,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// N
	305: {
		ID:  305,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// O
	306: {
		ID:  306,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// P
	307: {
		ID:  307,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// Q
	308: {
		ID:  308,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// R
	309: {
		ID:  309,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// S
	310: {
		ID:  310,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// T
	311: {
		ID:  311,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// U
	312: {
		ID:  312,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// V
	313: {
		ID:  313,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// W
	314: {
		ID:  314,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// X
	315: {
		ID:  315,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// Y
	316: {
		ID:  316,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// Z
	317: {
		ID:  317,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// "
	318: {
		ID:  318,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// '
	319: {
		ID:  319,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// *
	320: {
		ID:  320,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// >
	321: {
		ID:  321,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// bottom arrow
	322: {
		ID:  322,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// :
	323: {
		ID:  323,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// ..
	324: {
		ID:  324,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// .
	325: {
		ID:  325,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// sea border
	326: {
		ID:  326,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// ,
	327: {
		ID:  327,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// _
	328: {
		ID:  328,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// sea border
	329: {
		ID:  329,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// ?
	330: {
		ID:  330,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// !
	331: {
		ID:  331,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// ;
	332: {
		ID:  332,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// )
	333: {
		ID:  333,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// (
	334: {
		ID:  334,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// `
	335: {
		ID:  335,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// '.'
	336: {
		ID:  336,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// sea border
	337: {
		ID:  337,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// '
	338: {
		ID:  338,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// EMPTY
	339: {
		ID:  339,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// '
	340: {
		ID:  340,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// black tile
	341: {
		ID:  341,
		AT:  0x0,
		PAL: overworldPAL,
	},
	342: {
		ID:  342,
		AT:  0x0,
		PAL: overworldPAL,
	},
	343: {
		ID:  343,
		AT:  0x0,
		PAL: overworldPAL,
	},
	344: {
		ID:  344,
		AT:  0x0,
		PAL: overworldPAL,
	},
	345: {
		ID:  345,
		AT:  0x0,
		PAL: overworldPAL,
	},
	346: {
		ID:  346,
		AT:  0x0,
		PAL: overworldPAL,
	},
	347: {
		ID:  347,
		AT:  0x0,
		PAL: overworldPAL,
	},
	348: {
		ID:  348,
		AT:  0x0,
		PAL: overworldPAL,
	},
	349: {
		ID:  349,
		AT:  0x0,
		PAL: overworldPAL,
	},
	350: {
		ID:  350,
		AT:  0x0,
		PAL: overworldPAL,
	},
	351: {
		ID:  351,
		AT:  0x0,
		PAL: overworldPAL,
	},
	352: {
		ID:  352,
		AT:  0x0,
		PAL: overworldPAL,
	},
	353: {
		ID:  353,
		AT:  0x0,
		PAL: overworldPAL,
	},
	354: {
		ID:  354,
		AT:  0x0,
		PAL: overworldPAL,
	},
	355: {
		ID:  355,
		AT:  0x0,
		PAL: overworldPAL,
	},
	356: {
		ID:  356,
		AT:  0x0,
		PAL: overworldPAL,
	},
	357: {
		ID:  357,
		AT:  0x0,
		PAL: overworldPAL,
	},
	358: {
		ID:  358,
		AT:  0x0,
		PAL: overworldPAL,
	},
	359: {
		ID:  359,
		AT:  0x0,
		PAL: overworldPAL,
	},
	360: {
		ID:  360,
		AT:  0x0,
		PAL: overworldPAL,
	},
	361: {
		ID:  361,
		AT:  0x0,
		PAL: overworldPAL,
	},
	362: {
		ID:  362,
		AT:  0x0,
		PAL: overworldPAL,
	},

	363: {
		ID:  363,
		AT:  0x0,
		PAL: overworldPAL,
	},

	364: {
		ID:  364,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// desk bottom left
	365: {
		ID:  365,
		AT:  0x2,
		PAL: townPAL,
	},

	// desk bottom right
	366: {
		ID:  366,
		AT:  0x2,
		PAL: townPAL,
	},

	// rock top left
	367: {
		ID:  367,
		AT:  0x1,
		PAL: townPAL,
	},

	// rock top right
	368: {
		ID:  368,
		AT:  0x1,
		PAL: townPAL,
	},

	// rock bottom left
	369: {
		ID:  369,
		AT:  0x1,
		PAL: townPAL,
	},

	// rock bottom right
	370: {
		ID:  370,
		AT:  0x1,
		PAL: townPAL,
	},

	// stair top left
	371: {
		ID:  371,
		AT:  0x1,
		PAL: townPAL,
	},

	// stair top right
	372: {
		ID:  372,
		AT:  0x1,
		PAL: townPAL,
	},

	// stair bottom left
	373: {
		ID:  373,
		AT:  0x1,
		PAL: townPAL,
	},

	// stair bottom right
	374: {
		ID:  374,
		AT:  0x1,
		PAL: townPAL,
	},

	// red floor
	375: {
		ID:  375,
		AT:  0x1,
		PAL: townPAL,
	},

	// black tile
	376: {
		ID:  376,
		AT:  0x0,
		PAL: townPAL,
	},

	// black tile
	377: {
		ID:  377,
		AT:  0x0,
		PAL: townPAL,
	},

	// black tile
	378: {
		ID:  378,
		AT:  0x0,
		PAL: townPAL,
	},

	// brick road
	379: {
		ID:  379,
		AT:  0x1,
		PAL: townPAL,
	},

	// brick road
	380: {
		ID:  380,
		AT:  0x1,
		PAL: townPAL,
	},

	// brick road
	381: {
		ID:  381,
		AT:  0x1,
		PAL: townPAL,
	},

	// brick road
	382: {
		ID:  382,
		AT:  0x1,
		PAL: townPAL,
	},

	// tree top
	383: {
		ID:  383,
		AT:  0x2,
		PAL: overworldPAL,
	},

	// tree bottom
	384: {
		ID:  384,
		AT:  0x2,
		PAL: overworldPAL,
	},

	// swamp
	385: {
		ID:  385,
		AT:  0x2,
		PAL: overworldPAL,
	},

	// town top left
	386: {
		ID:  386,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// town top right
	387: {
		ID:  387,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// town bottom left
	388: {
		ID:  388,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// town bottom right
	389: {
		ID:  389,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// cave top left
	390: {
		ID:  390,
		AT:  0x1,
		PAL: overworldPAL,
	},

	// cave top right
	391: {
		ID:  391,
		AT:  0x1,
		PAL: overworldPAL,
	},

	// cave bottom left
	392: {
		ID:  392,
		AT:  0x1,
		PAL: overworldPAL,
	},

	// cave bottom right
	393: {
		ID:  393,
		AT:  0x1,
		PAL: overworldPAL,
	},

	// castle top left
	394: {
		ID:  394,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// castle top right
	395: {
		ID:  395,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// castle bottom left
	396: {
		ID:  396,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// castle bottom right
	397: {
		ID:  397,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// locked door top left
	399: {
		ID:  399,
		AT:  0x1,
		PAL: townPAL,
	},

	// locked door top right
	400: {
		ID:  400,
		AT:  0x1,
		PAL: townPAL,
	},

	// locked door bottom left
	401: {
		ID:  401,
		AT:  0x1,
		PAL: townPAL,
	},

	// locked door bottom right
	402: {
		ID:  402,
		AT:  0x1,
		PAL: townPAL,
	},

	// weapon shop sign top left
	403: {
		ID:  403,
		AT:  0x1,
		PAL: townPAL,
	},

	// weapon shop sign top right
	404: {
		ID:  404,
		AT:  0x1,
		PAL: townPAL,
	},

	// weapon shop sign bottom left
	405: {
		ID:  405,
		AT:  0x1,
		PAL: townPAL,
	},

	// weapon shop sign bottom right
	406: {
		ID:  406,
		AT:  0x1,
		PAL: townPAL,
	},

	// inn shop sign top left
	407: {
		ID:  407,
		AT:  0x1,
		PAL: townPAL,
	},

	// inn shop sign top right
	408: {
		ID:  408,
		AT:  0x1,
		PAL: townPAL,
	},

	// inn sign bottom left
	409: {
		ID:  409,
		AT:  0x1,
		PAL: townPAL,
	},

	// inn sign bottom right
	410: {
		ID:  410,
		AT:  0x1,
		PAL: townPAL,
	},

	// bridge top left
	411: {
		ID:  411,
		AT:  0x0,
		PAL: townPAL,
	},

	// bridge top right
	412: {
		ID:  412,
		AT:  0x0,
		PAL: townPAL,
	},

	// bridge bottom left
	413: {
		ID:  413,
		AT:  0x0,
		PAL: townPAL,
	},

	// bridge bottom right
	414: {
		ID:  414,
		AT:  0x0,
		PAL: townPAL,
	},

	// castle bricks
	415: {
		ID:  415,
		AT:  0x1,
		PAL: townPAL,
	},

	// grass 1
	416: {
		ID:  416,
		AT:  0x2,
		PAL: overworldPAL,
	},

	// sand
	417: {
		ID:  417,
		AT:  0x3,
		PAL: overworldPAL,
	},

	// hill top left
	418: {
		ID:  418,
		AT:  0x3,
		PAL: overworldPAL,
	},

	// hill top right
	419: {
		ID:  419,
		AT:  0x3,
		PAL: overworldPAL,
	},

	// hill bottom left
	420: {
		ID:  420,
		AT:  0x3,
		PAL: overworldPAL,
	},

	// hill bottom right
	421: {
		ID:  421,
		AT:  0x3,
		PAL: overworldPAL,
	},

	// mountain top left
	422: {
		ID:  422,
		AT:  0x1,
		PAL: overworldPAL,
	},

	// mountain top right
	423: {
		ID:  423,
		AT:  0x1,
		PAL: overworldPAL,
	},

	// sea bottom left
	424: {
		ID:  424,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// princess dungeon top left
	425: {
		ID:  425,
		AT:  0x1,
		PAL: dungeonPAL,
	},

	// princess dungeon top right
	426: {
		ID:  426,
		AT:  0x1,
		PAL: dungeonPAL,
	},

	// princess dungeon bottom left
	427: {
		ID:  427,
		AT:  0x1,
		PAL: dungeonPAL,
	},

	// princess dungeon bottom right
	428: {
		ID:  428,
		AT:  0x1,
		PAL: dungeonPAL,
	},

	// cloud
	429: {
		ID:  429,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// cloud
	430: {
		ID:  430,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// cloud
	431: {
		ID:  431,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// cloud
	432: {
		ID:  432,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// cloud
	433: {
		ID:  433,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// town
	495: {
		ID:  495,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// town
	496: {
		ID:  496,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// town
	497: {
		ID:  497,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// town
	498: {
		ID:  498,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// desk top right
	499: {
		ID:  499,
		AT:  0x2,
		PAL: townPAL,
	},

	// mountain bottom left
	500: {
		ID:  500,
		AT:  0x1,
		PAL: overworldPAL,
	},

	// mountain bottom right
	501: {
		ID:  501,
		AT:  0x1,
		PAL: overworldPAL,
	},

	// water top
	502: {
		ID:  502,
		AT:  0x0,
		PAL: overworldPAL,
	},

	// desk bottom left
	503: {
		ID:  503,
		AT:  0x2,
		PAL: townPAL,
	},

	// desk bottom left
	504: {
		ID:  504,
		AT:  0x1,
		PAL: townPAL,
	},

	// desk bottom left
	505: {
		ID:  505,
		AT:  0x1,
		PAL: townPAL,
	},

	// desk bottom left
	506: {
		ID:  506,
		AT:  0x1,
		PAL: townPAL,
	},

	// desk bottom left
	507: {
		ID:  507,
		AT:  0x1,
		PAL: townPAL,
	},

	// rock
	508: {
		ID:  508,
		AT:  0x7,
		PAL: overworldPAL,
	},

	// rock
	509: {
		ID:  509,
		AT:  0x7,
		PAL: overworldPAL,
	},

	// rock
	510: {
		ID:  510,
		AT:  0x7,
		PAL: overworldPAL,
	},

	// ???
	511: {
		ID:  511,
		AT:  0x1,
		PAL: townPAL,
	},

	// town guy facing right top left
	512: {
		ID:  512,
		AT:  0x4,
		PAL: townPAL,
	},

	// town guy facing right top left
	513: {
		ID:  513,
		AT:  0x4,
		PAL: townPAL,
	},

	// town guy facing right top left
	514: {
		ID:  514,
		AT:  0x4,
		PAL: townPAL,
	},

	// town guy facing right top left
	515: {
		ID:  515,
		AT:  0x4,
		PAL: townPAL,
	},

	// town guy facing right top left
	516: {
		ID:  516,
		AT:  0x4,
		PAL: townPAL,
	},

	// town guy facing right top left
	517: {
		ID:  517,
		AT:  0x4,
		PAL: townPAL,
	},

	// town guy facing right top left
	518: {
		ID:  518,
		AT:  0x4,
		PAL: townPAL,
	},

	// town guy facing right top right
	519: {
		ID:  519,
		AT:  0x4,
		PAL: townPAL,
	},

	// town guy facing right top left
	520: {
		ID:  520,
		AT:  0x4,
		PAL: townPAL,
	},

	// town guy facing right top right
	521: {
		ID:  521,
		AT:  0x4,
		PAL: townPAL,
	},

	// town guy facing forward top left
	522: {
		ID:  522,
		AT:  0x4,
		PAL: townPAL,
	},

	// town guy facing forward top right
	523: {
		ID:  523,
		AT:  0x4,
		PAL: townPAL,
	},

	// town girl hair
	524: {
		ID:  524,
		AT:  0x4,
		PAL: townPAL,
	},

	// town girl face top left
	525: {
		ID:  525,
		AT:  0x4,
		PAL: townPAL,
	},

	// town girl body left
	526: {
		ID:  526,
		AT:  0x4,
		PAL: townPAL,
	},

	// town girl body right
	527: {
		ID:  527,
		AT:  0x4,
		PAL: townPAL,
	},

	// town girl body left
	528: {
		ID:  528,
		AT:  0x4,
		PAL: townPAL,
	},

	// town girl body right
	529: {
		ID:  529,
		AT:  0x4,
		PAL: townPAL,
	},

	// town girl facing right body left
	530: {
		ID:  530,
		AT:  0x4,
		PAL: townPAL,
	},

	// town girl facing right body right
	531: {
		ID:  531,
		AT:  0x4,
		PAL: townPAL,
	},

	// town girl facing right body left
	532: {
		ID:  532,
		AT:  0x4,
		PAL: townPAL,
	},

	// town girl facing right body right
	533: {
		ID:  533,
		AT:  0x4,
		PAL: townPAL,
	},

	// town girl facing forward body left
	534: {
		ID:  534,
		AT:  0x4,
		PAL: townPAL,
	},

	// town girl facing forward body right
	535: {
		ID:  535,
		AT:  0x4,
		PAL: townPAL,
	},

	// town girl facing forward body left
	536: {
		ID:  536,
		AT:  0x6,
		PAL: townPAL,
	},

	// princess hair left
	537: {
		ID:  537,
		AT:  0x6,
		PAL: townPAL,
	},

	// princess dress left
	538: {
		ID:  538,
		AT:  0x7,
		PAL: townPAL,
	},

	// princess dress right
	539: {
		ID:  539,
		AT:  0x7,
		PAL: townPAL,
	},

	// town fat guy body right
	540: {
		ID:  540,
		AT:  0x5,
		PAL: townPAL,
	},

	// town fat guy face left
	541: {
		ID:  541,
		AT:  0x5,
		PAL: townPAL,
	},

	// town fat guy body right
	542: {
		ID:  542,
		AT:  0x5,
		PAL: townPAL,
	},

	// town fat guy facing forward bottom right
	543: {
		ID:  543,
		AT:  0x5,
		PAL: townPAL,
	},

	// hero facing back top left
	544: {
		ID:  544,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing back top right
	545: {
		ID:  545,
		AT:  0x4,
		PAL: townPAL,
	},

	// town fat guy facing left
	546: {
		ID:  546,
		AT:  0x5,
		PAL: townPAL,
	},

	// town fat guy facing left
	547: {
		ID:  547,
		AT:  0x5,
		PAL: townPAL,
	},

	// hero walking up left feet up bottom left
	548: {
		ID:  548,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero walking up left feet up bottom right
	549: {
		ID:  549,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing left top left
	550: {
		ID:  550,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing left top right
	551: {
		ID:  551,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero walking up right feet up bottom left
	552: {
		ID:  552,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero walking up right feet up bottom right
	553: {
		ID:  553,
		AT:  0x4,
		PAL: townPAL,
	},

	// town fat guy facing forward right feet down bottom left
	554: {
		ID:  554,
		AT:  0x5,
		PAL: townPAL,
	},

	// town fat guy facing forward right feet down bottom right
	555: {
		ID:  555,
		AT:  0x5,
		PAL: townPAL,
	},

	// town fat guy facing right top left
	556: {
		ID:  556,
		AT:  0x5,
		PAL: townPAL,
	},

	// town fat guy facing right top right
	557: {
		ID:  557,
		AT:  0x5,
		PAL: townPAL,
	},

	// town fat guy facing left top left
	558: {
		ID:  558,
		AT:  0x5,
		PAL: townPAL,
	},

	// town fat guy facing left top right
	559: {
		ID:  559,
		AT:  0x5,
		PAL: townPAL,
	},

	// hero facing right top left
	560: {
		ID:  560,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing right
	561: {
		ID:  561,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero left feet
	562: {
		ID:  562,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero right feet
	563: {
		ID:  563,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing forward top left
	564: {
		ID:  564,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing forward top right
	565: {
		ID:  565,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing forward bottom left
	566: {
		ID:  566,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing forward bottom right
	567: {
		ID:  567,
		AT:  0x4,
		PAL: townPAL,
	},

	// princess facing left top left
	568: {
		ID:  568,
		AT:  0x7,
		PAL: townPAL,
	},

	// princess facing left top right
	569: {
		ID:  569,
		AT:  0x7,
		PAL: townPAL,
	},

	// princess facing left bottom left
	570: {
		ID:  570,
		AT:  0x7,
		PAL: townPAL,
	},

	// princess facing left bottom right
	571: {
		ID:  571,
		AT:  0x7,
		PAL: townPAL,
	},

	// princess facing forward bottom left
	572: {
		ID:  572,
		AT:  0x7,
		PAL: townPAL,
	},

	// princess facing forward bottom right
	573: {
		ID:  573,
		AT:  0x7,
		PAL: townPAL,
	},

	// princess facing forward top left
	574: {
		ID:  574,
		AT:  0x7,
		PAL: townPAL,
	},

	// princess facing forward top right
	575: {
		ID:  575,
		AT:  0x7,
		PAL: townPAL,
	},

	// hero facing back top left
	576: {
		ID:  576,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing back top right
	577: {
		ID:  577,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing back bottom left
	578: {
		ID:  578,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing back bottom right
	579: {
		ID:  579,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing back top left
	580: {
		ID:  580,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing back top right
	581: {
		ID:  581,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing back bottom left
	582: {
		ID:  582,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing back bottom right
	583: {
		ID:  583,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing right top left
	584: {
		ID:  584,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing right top right
	585: {
		ID:  585,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing right bottom left
	586: {
		ID:  586,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing right bottom right
	587: {
		ID:  587,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing right bottom left
	588: {
		ID:  588,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing right bottom right
	589: {
		ID:  589,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing right bottom left
	590: {
		ID:  590,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing right bottom right
	591: {
		ID:  591,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing forward top left
	592: {
		ID:  592,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing forward top right
	593: {
		ID:  593,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing forward bottom left
	594: {
		ID:  594,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing forward bottom right
	595: {
		ID:  595,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing forward bottom left
	596: {
		ID:  596,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing forward bottom right
	597: {
		ID:  597,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing forward bottom left
	598: {
		ID:  598,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero facing forward bottom right
	599: {
		ID:  599,
		AT:  0x4,
		PAL: townPAL,
	},

	// soldier facing backward top left
	600: {
		ID:  600,
		AT:  0x6,
		PAL: townPAL,
	},

	// soldier facing backward top right
	601: {
		ID:  601,
		AT:  0x6,
		PAL: townPAL,
	},

	// soldier facing forward bottom left
	602: {
		ID:  602,
		AT:  0x6,
		PAL: townPAL,
	},

	// soldier facing forward bottom right
	603: {
		ID:  603,
		AT:  0x6,
		PAL: townPAL,
	},

	// soldier facing forward bottom right
	604: {
		ID:  604,
		AT:  0x6,
		PAL: townPAL,
	},

	// soldier facing forward bottom right
	605: {
		ID:  605,
		AT:  0x6,
		PAL: townPAL,
	},

	// soldier facing forward bottom right
	606: {
		ID:  606,
		AT:  0x6,
		PAL: townPAL,
	},

	// soldier facing forward bottom right
	607: {
		ID:  607,
		AT:  0x6,
		PAL: townPAL,
	},

	// knight facing forward bottom right
	608: {
		ID:  608,
		AT:  0x7,
		PAL: townPAL,
	},

	// old man body
	609: {
		ID:  609,
		AT:  0x6,
		PAL: townPAL,
	},

	// old man ???
	610: {
		ID:  610,
		AT:  0x6,
		PAL: townPAL,
	},

	// old man hat
	611: {
		ID:  611,
		AT:  0x6,
		PAL: townPAL,
	},

	// knight head
	612: {
		ID:  612,
		AT:  0x7,
		PAL: townPAL,
	},

	// wizard beard left
	613: {
		ID:  613,
		AT:  0x6,
		PAL: townPAL,
	},

	// knight body bottom left
	614: {
		ID:  614,
		AT:  0x7,
		PAL: townPAL,
	},

	// wizard robe bottom right
	615: {
		ID:  615,
		AT:  0x6,
		PAL: townPAL,
	},

	// soldier face right top left
	616: {
		ID:  616,
		AT:  0x6,
		PAL: townPAL,
	},

	// soldier face right top right
	617: {
		ID:  617,
		AT:  0x6,
		PAL: townPAL,
	},

	// soldier face right top right
	618: {
		ID:  618,
		AT:  0x6,
		PAL: townPAL,
	},

	// soldier face right top right
	619: {
		ID:  619,
		AT:  0x6,
		PAL: townPAL,
	},

	// soldier face right top right
	620: {
		ID:  620,
		AT:  0x6,
		PAL: townPAL,
	},

	// soldier face right top right
	621: {
		ID:  621,
		AT:  0x6,
		PAL: townPAL,
	},

	// king facing forward top left
	622: {
		ID:  622,
		AT:  0x6,
		PAL: townPAL,
	},

	// king facing forward top left
	623: {
		ID:  623,
		AT:  0x6,
		PAL: townPAL,
	},

	// king facing forward top left
	624: {
		ID:  624,
		AT:  0x6,
		PAL: townPAL,
	},

	// knight facing forward top right
	625: {
		ID:  625,
		AT:  0x7,
		PAL: townPAL,
	},

	// soldier facing left top right
	626: {
		ID:  626,
		AT:  0x6,
		PAL: townPAL,
	},

	// soldier facing left top right
	627: {
		ID:  627,
		AT:  0x6,
		PAL: townPAL,
	},

	// soldier facing left top right
	628: {
		ID:  628,
		AT:  0x6,
		PAL: townPAL,
	},

	// soldier facing left top right
	629: {
		ID:  629,
		AT:  0x7,
		PAL: townPAL,
	},

	// soldier facing left top right
	630: {
		ID:  630,
		AT:  0x6,
		PAL: townPAL,
	},

	// soldier facing left top right
	631: {
		ID:  631,
		AT:  0x7,
		PAL: townPAL,
	},

	// soldier facing forward top left
	632: {
		ID:  632,
		AT:  0x6,
		PAL: townPAL,
	},

	// soldier facing forward top right
	633: {
		ID:  633,
		AT:  0x6,
		PAL: townPAL,
	},

	// soldier facing forward bottom left
	634: {
		ID:  634,
		AT:  0x6,
		PAL: townPAL,
	},

	// soldier facing forward bottom right
	635: {
		ID:  635,
		AT:  0x6,
		PAL: townPAL,
	},

	// soldier facing forward bottom left
	636: {
		ID:  636,
		AT:  0x6,
		PAL: townPAL,
	},

	// soldier facing forward bottom right
	637: {
		ID:  637,
		AT:  0x6,
		PAL: townPAL,
	},

	// knight facing forward bottom left
	638: {
		ID:  638,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight facing forward bottom right
	639: {
		ID:  639,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight facing forward bottom left
	640: {
		ID:  640,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight facing forward bottom right
	641: {
		ID:  641,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight facing forward bottom left
	642: {
		ID:  642,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight facing forward bottom right
	643: {
		ID:  643,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight facing forward bottom left
	644: {
		ID:  644,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight facing forward bottom right
	645: {
		ID:  645,
		AT:  0x6,
		PAL: townPAL,
	},

	// wizard bottom right
	646: {
		ID:  646,
		AT:  0x7,
		PAL: townPAL,
	},

	// wizard bottom right
	647: {
		ID:  647,
		AT:  0x6,
		PAL: townPAL,
	},

	// king facing forward top left
	648: {
		ID:  648,
		AT:  0x6,
		PAL: townPAL,
	},

	// king facing forward top right
	649: {
		ID:  649,
		AT:  0x6,
		PAL: townPAL,
	},

	// king facing forward bottom left
	650: {
		ID:  650,
		AT:  0x6,
		PAL: townPAL,
	},

	// king facing forward bottom right
	651: {
		ID:  651,
		AT:  0x6,
		PAL: townPAL,
	},

	// soldier facing left top left
	652: {
		ID:  652,
		AT:  0x6,
		PAL: townPAL,
	},

	// soldier facing left top right
	653: {
		ID:  653,
		AT:  0x6,
		PAL: townPAL,
	},

	// fat guy facing left top left
	654: {
		ID:  654,
		AT:  0x5,
		PAL: townPAL,
	},

	// fat guy facing left top right
	655: {
		ID:  655,
		AT:  0x5,
		PAL: townPAL,
	},

	// knight top left
	656: {
		ID:  656,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight top right
	657: {
		ID:  657,
		AT:  0x7,
		PAL: townPAL,
	},

	// charlock robe right
	658: {
		ID:  658,
		AT:  0x4,
		PAL: townPAL,
	},

	// knight shield right
	659: {
		ID:  659,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	660: {
		ID:  660,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	661: {
		ID:  661,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	662: {
		ID:  662,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	663: {
		ID:  663,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	664: {
		ID:  664,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	665: {
		ID:  665,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	666: {
		ID:  666,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	667: {
		ID:  667,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	668: {
		ID:  668,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	669: {
		ID:  669,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	670: {
		ID:  670,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	671: {
		ID:  671,
		AT:  0x7,
		PAL: townPAL,
	},

	// wizard
	672: {
		ID:  672,
		AT:  0x6,
		PAL: townPAL,
	},

	// wizard
	673: {
		ID:  673,
		AT:  0x6,
		PAL: townPAL,
	},

	// knight
	674: {
		ID:  674,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	675: {
		ID:  675,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	676: {
		ID:  676,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	677: {
		ID:  677,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	678: {
		ID:  678,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	679: {
		ID:  679,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	680: {
		ID:  680,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	681: {
		ID:  681,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	682: {
		ID:  682,
		AT:  0x7,
		PAL: townPAL,
	},

	// princess facing back top
	683: {
		ID:  683,
		AT:  0x7,
		PAL: townPAL,
	},

	// princess facing back top
	684: {
		ID:  684,
		AT:  0x7,
		PAL: townPAL,
	},

	// princess facing back top
	685: {
		ID:  685,
		AT:  0x7,
		PAL: townPAL,
	},

	// princess hair right
	686: {
		ID:  686,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	687: {
		ID:  687,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	688: {
		ID:  688,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight left body
	689: {
		ID:  689,
		AT:  0x7,
		PAL: townPAL,
	},

	// princess robe carry left
	690: {
		ID:  690,
		AT:  0x7,
		PAL: townPAL,
	},

	// princess robe carry right
	691: {
		ID:  691,
		AT:  0x7,
		PAL: townPAL,
	},

	// princess face right
	692: {
		ID:  692,
		AT:  0x7,
		PAL: townPAL,
	},

	// hero face right
	693: {
		ID:  693,
		AT:  0x4,
		PAL: townPAL,
	},

	// princess robe carry left
	694: {
		ID:  694,
		AT:  0x7,
		PAL: townPAL,
	},

	// princess robe carry right
	695: {
		ID:  695,
		AT:  0x7,
		PAL: townPAL,
	},

	// princess face
	696: {
		ID:  696,
		AT:  0x7,
		PAL: townPAL,
	},

	// hero face right
	697: {
		ID:  697,
		AT:  0x4,
		PAL: townPAL,
	},

	// princess gown left
	698: {
		ID:  698,
		AT:  0x7,
		PAL: townPAL,
	},

	// princess gown right
	699: {
		ID:  699,
		AT:  0x7,
		PAL: townPAL,
	},

	// princess face
	700: {
		ID:  700,
		AT:  0x7,
		PAL: townPAL,
	},

	// hero face
	701: {
		ID:  701,
		AT:  0x4,
		PAL: townPAL,
	},

	// hero carrying princess carry dress left
	702: {
		ID:  702,
		AT:  0x7,
		PAL: townPAL,
	},

	// hero carrying princess carry dress right
	703: {
		ID:  703,
		AT:  0x7,
		PAL: townPAL,
	},

	// princess facing forward bottom left
	704: {
		ID:  704,
		AT:  0x7,
		PAL: townPAL,
	},

	// princess facing forward bottom right
	705: {
		ID:  705,
		AT:  0x7,
		PAL: townPAL,
	},

	// wizard facing forward bottom left
	706: {
		ID:  706,
		AT:  0x6,
		PAL: townPAL,
	},

	// wizard facing forward bottom right
	707: {
		ID:  707,
		AT:  0x6,
		PAL: townPAL,
	},

	// charlock facing back top left
	708: {
		ID:  708,
		AT:  0x4,
		PAL: townPAL,
	},

	// charlock facing back top right
	709: {
		ID:  709,
		AT:  0x4,
		PAL: townPAL,
	},

	// charlock facing back bottom left
	710: {
		ID:  710,
		AT:  0x4,
		PAL: townPAL,
	},

	// charlock facing back bottom right
	711: {
		ID:  711,
		AT:  0x4,
		PAL: townPAL,
	},

	// charlock facing back bottom left
	712: {
		ID:  712,
		AT:  0x4,
		PAL: townPAL,
	},

	// charlock facing back bottom right
	713: {
		ID:  713,
		AT:  0x4,
		PAL: townPAL,
	},

	// charlock facing back bottom left
	714: {
		ID:  714,
		AT:  0x4,
		PAL: townPAL,
	},

	// charlock facing back bottom right
	715: {
		ID:  715,
		AT:  0x4,
		PAL: townPAL,
	},

	// charlock facing back bottom left
	716: {
		ID:  716,
		AT:  0x4,
		PAL: townPAL,
	},

	// charlock facing back bottom right
	717: {
		ID:  717,
		AT:  0x4,
		PAL: townPAL,
	},

	// charlock facing right top left
	718: {
		ID:  718,
		AT:  0x4,
		PAL: townPAL,
	},

	// charlock facing right top right
	719: {
		ID:  719,
		AT:  0x4,
		PAL: townPAL,
	},

	// charlock facing right bottom left
	720: {
		ID:  720,
		AT:  0x4,
		PAL: townPAL,
	},

	// charlock facing right bottom right
	721: {
		ID:  721,
		AT:  0x4,
		PAL: townPAL,
	},

	// charlock facing forward top left
	722: {
		ID:  722,
		AT:  0x4,
		PAL: townPAL,
	},

	// charlock facing forward top right
	723: {
		ID:  723,
		AT:  0x4,
		PAL: townPAL,
	},

	// charlock facing forward bottom left
	724: {
		ID:  724,
		AT:  0x4,
		PAL: townPAL,
	},

	// charlock facing forward bottom right
	725: {
		ID:  725,
		AT:  0x4,
		PAL: townPAL,
	},

	// charlock facing forward top left
	726: {
		ID:  726,
		AT:  0x4,
		PAL: townPAL,
	},

	// charlock facing forward top left
	727: {
		ID:  727,
		AT:  0x4,
		PAL: townPAL,
	},

	// knight
	728: {
		ID:  728,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	729: {
		ID:  729,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	730: {
		ID:  730,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	731: {
		ID:  731,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	732: {
		ID:  732,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	733: {
		ID:  733,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	734: {
		ID:  734,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	735: {
		ID:  735,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	736: {
		ID:  736,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	737: {
		ID:  737,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	738: {
		ID:  738,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	739: {
		ID:  739,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	740: {
		ID:  740,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	741: {
		ID:  741,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	742: {
		ID:  742,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	743: {
		ID:  743,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	744: {
		ID:  744,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	745: {
		ID:  745,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	746: {
		ID:  746,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	747: {
		ID:  747,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	748: {
		ID:  748,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	749: {
		ID:  749,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	750: {
		ID:  750,
		AT:  0x7,
		PAL: townPAL,
	},

	// knight
	751: {
		ID:  751,
		AT:  0x7,
		PAL: townPAL,
	},

	// wizard
	752: {
		ID:  752,
		AT:  0x6,
		PAL: townPAL,
	},

	// wizard
	753: {
		ID:  753,
		AT:  0x6,
		PAL: townPAL,
	},

	// wizard
	754: {
		ID:  754,
		AT:  0x6,
		PAL: townPAL,
	},

	// wizard
	755: {
		ID:  755,
		AT:  0x6,
		PAL: townPAL,
	},

	// wizard
	756: {
		ID:  756,
		AT:  0x6,
		PAL: townPAL,
	},

	// wizard
	757: {
		ID:  757,
		AT:  0x6,
		PAL: townPAL,
	},

	// wizard
	758: {
		ID:  758,
		AT:  0x6,
		PAL: townPAL,
	},

	// wizard
	759: {
		ID:  759,
		AT:  0x6,
		PAL: townPAL,
	},

	// wizard
	760: {
		ID:  760,
		AT:  0x6,
		PAL: townPAL,
	},

	// wizard
	761: {
		ID:  761,
		AT:  0x6,
		PAL: townPAL,
	},

	// wizard
	762: {
		ID:  762,
		AT:  0x6,
		PAL: townPAL,
	},

	// wizard
	763: {
		ID:  763,
		AT:  0x6,
		PAL: townPAL,
	},

	// wizard
	764: {
		ID:  764,
		AT:  0x6,
		PAL: townPAL,
	},

	// wizard
	765: {
		ID:  765,
		AT:  0x6,
		PAL: townPAL,
	},

	// wizard
	766: {
		ID:  766,
		AT:  0x6,
		PAL: townPAL,
	},

	// wizard
	767: {
		ID:  767,
		AT:  0x6,
		PAL: townPAL,
	},

	// star title screen
	768: {
		ID:  768,
		AT:  0x2,
		PAL: titlePAL,
	},

	// star title screen
	769: {
		ID:  769,
		AT:  0x2,
		PAL: titlePAL,
	},

	// star title screen
	770: {
		ID:  770,
		AT:  0x2,
		PAL: titlePAL,
	},

	// star title screen
	771: {
		ID:  771,
		AT:  0x2,
		PAL: titlePAL,
	},

	// star title screen
	772: {
		ID:  772,
		AT:  0x2,
		PAL: titlePAL,
	},

	// star title screen
	773: {
		ID:  773,
		AT:  0x2,
		PAL: titlePAL,
	},

	// star title screen
	774: {
		ID:  774,
		AT:  0x2,
		PAL: titlePAL,
	},

	// star title screen
	775: {
		ID:  775,
		AT:  0x2,
		PAL: titlePAL,
	},

	// star title screen
	776: {
		ID:  776,
		AT:  0x2,
		PAL: titlePAL,
	},

	// star title screen
	777: {
		ID:  777,
		AT:  0x2,
		PAL: titlePAL,
	},

	// star title screen
	778: {
		ID:  778,
		AT:  0x2,
		PAL: titlePAL,
	},

	// star title screen
	779: {
		ID:  779,
		AT:  0x2,
		PAL: titlePAL,
	},

	// star title screen
	780: {
		ID:  780,
		AT:  0x2,
		PAL: titlePAL,
	},

	// star title screen
	781: {
		ID:  781,
		AT:  0x2,
		PAL: titlePAL,
	},

	// star title screen
	782: {
		ID:  782,
		AT:  0x2,
		PAL: titlePAL,
	},

	// star title screen
	783: {
		ID:  783,
		AT:  0x2,
		PAL: titlePAL,
	},

	// star title screen
	784: {
		ID:  784,
		AT:  0x2,
		PAL: titlePAL,
	},

	// star title screen
	785: {
		ID:  785,
		AT:  0x2,
		PAL: titlePAL,
	},

	// star title screen
	786: {
		ID:  786,
		AT:  0x2,
		PAL: titlePAL,
	},

	// star title screen
	787: {
		ID:  787,
		AT:  0x2,
		PAL: titlePAL,
	},

	// star title screen
	788: {
		ID:  788,
		AT:  0x2,
		PAL: titlePAL,
	},

	// star title screen
	789: {
		ID:  789,
		AT:  0x2,
		PAL: titlePAL,
	},

	// dragon title screen
	790: {
		ID:  790,
		AT:  0x2,
		PAL: titlePAL,
	},

	// dragon title screen
	791: {
		ID:  791,
		AT:  0x1,
		PAL: titlePAL,
	},

	// dragon title screen
	792: {
		ID:  792,
		AT:  0x1,
		PAL: titlePAL,
	},

	// dragon title screen
	793: {
		ID:  793,
		AT:  0x1,
		PAL: titlePAL,
	},

	// dragon title screen
	794: {
		ID:  794,
		AT:  0x1,
		PAL: titlePAL,
	},

	// dragon title screen
	795: {
		ID:  795,
		AT:  0x1,
		PAL: titlePAL,
	},

	// dragon title screen
	796: {
		ID:  796,
		AT:  0x1,
		PAL: titlePAL,
	},

	// dragon title screen
	797: {
		ID:  797,
		AT:  0x1,
		PAL: titlePAL,
	},

	// dragon title screen
	798: {
		ID:  798,
		AT:  0x1,
		PAL: titlePAL,
	},
}

var (
	rchr [256]uint8
)

func init() {
	for i := 0; i < 256; i++ {
		v := uint8(i)
		v = ((v >> 1) & 0x55) | ((v & 0x55) << 1)
		v = ((v >> 2) & 0x33) | ((v & 0x33) << 2)
		v = ((v >> 4) & 0x0F) | ((v & 0x0F) << 4)
		rchr[i] = v
	}
}

var chrlobit = [16]uint32{
	0x00000000, 0x00000001, 0x00000100, 0x00000101, 0x00010000, 0x00010001, 0x00010100, 0x00010101,
	0x01000000, 0x01000001, 0x01000100, 0x01000101, 0x01010000, 0x01010001, 0x01010100, 0x01010101,
}

var chrhibit = [16]uint32{
	0x00000000, 0x00000002, 0x00000200, 0x00000202, 0x00020000, 0x00020002, 0x00020200, 0x00020202,
	0x02000000, 0x02000002, 0x02000200, 0x02000202, 0x02020000, 0x02020002, 0x02020200, 0x02020202,
}

var titlePAL = []int{
	0x0F, 0x30, 0x10, 0x00,
	0x0F, 0x27, 0x37, 0x17,
	0x0F, 0x0F, 0x27, 0x27,
	0x0F, 0x0F, 0x24, 0x24,
	0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x37,
	0x0F, 0x0F, 0x30, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F,
}

var townPAL = []int{
	0x0F, 0x30, 0x10, 0x11,
	0x0F, 0x10, 0x00, 0x16,
	0x0F, 0x29, 0x1A, 0x27,
	0x0F, 0x29, 0x37, 0x11,
	0x0F, 0x35, 0x30, 0x12,
	0x0F, 0x35, 0x27, 0x1A,
	0x0F, 0x35, 0x30, 0x00,
	0x0F, 0x35, 0x30, 0x07,
}

var overworldPAL = []int{
	0x0F, 0x30, 0x10, 0x11,
	0x0F, 0x10, 0x00, 0x29,
	0x0F, 0x29, 0x1A, 0x27,
	0x0F, 0x29, 0x37, 0x11,
	0x0F, 0x35, 0x30, 0x12,
	0x0F, 0x35, 0x27, 0x1A,
	0x0F, 0x35, 0x30, 0x00,
	0x0F, 0x35, 0x30, 0x07,
}

var dungeonPAL = []int{
	0x0F, 0x30, 0x0E, 0x0E,
	0x0F, 0x10, 0x00, 0x16,
	0x0F, 0x0E, 0x0E, 0x0E,
	0x0F, 0x0E, 0x0E, 0x0E,
	0x0F, 0x35, 0x30, 0x12,
	0x0F, 0x35, 0x27, 0x1A,
	0x0F, 0x35, 0x30, 0x00,
	0x0F, 0x35, 0x30, 0x07,
}

var defaultPAL = [512]color.RGBA{
	{116, 116, 116, 255},
	{36, 24, 140, 255},
	{0, 0, 168, 255},
	{68, 0, 156, 255},
	{140, 0, 116, 255},
	{168, 0, 16, 255},
	{164, 0, 0, 255},
	{124, 8, 0, 255},
	{64, 44, 0, 255},
	{0, 68, 0, 255},
	{0, 80, 0, 255},
	{0, 60, 20, 255},
	{24, 60, 92, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{188, 188, 188, 255},
	{0, 112, 236, 255},
	{32, 56, 236, 255},
	{128, 0, 240, 255},
	{188, 0, 188, 255},
	{228, 0, 88, 255},
	{216, 40, 0, 255},
	{200, 76, 12, 255},
	{136, 112, 0, 255},
	{0, 148, 0, 255},
	{0, 168, 0, 255},
	{0, 144, 56, 255},
	{0, 128, 136, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{252, 252, 252, 255},
	{60, 188, 252, 255},
	{92, 148, 252, 255},
	{204, 136, 252, 255},
	{244, 120, 252, 255},
	{252, 116, 180, 255},
	{252, 116, 96, 255},
	{252, 152, 56, 255},
	{240, 188, 60, 255},
	{128, 208, 16, 255},
	{76, 220, 72, 255},
	{88, 248, 152, 255},
	{0, 232, 216, 255},
	{120, 120, 120, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{252, 252, 252, 255},
	{168, 228, 252, 255},
	{196, 212, 252, 255},
	{212, 200, 252, 255},
	{252, 196, 252, 255},
	{252, 196, 216, 255},
	{252, 188, 176, 255},
	{252, 216, 168, 255},
	{252, 228, 160, 255},
	{224, 252, 160, 255},
	{168, 240, 188, 255},
	{176, 252, 204, 255},
	{156, 252, 240, 255},
	{196, 196, 196, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{116, 116, 116, 255},
	{36, 24, 140, 255},
	{0, 0, 168, 255},
	{68, 0, 156, 255},
	{140, 0, 116, 255},
	{168, 0, 16, 255},
	{164, 0, 0, 255},
	{124, 8, 0, 255},
	{64, 44, 0, 255},
	{0, 68, 0, 255},
	{0, 80, 0, 255},
	{0, 60, 20, 255},
	{24, 60, 92, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{188, 188, 188, 255},
	{0, 112, 236, 255},
	{32, 56, 236, 255},
	{128, 0, 240, 255},
	{188, 0, 188, 255},
	{228, 0, 88, 255},
	{216, 40, 0, 255},
	{200, 76, 12, 255},
	{136, 112, 0, 255},
	{0, 148, 0, 255},
	{0, 168, 0, 255},
	{0, 144, 56, 255},
	{0, 128, 136, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{252, 252, 252, 255},
	{60, 188, 252, 255},
	{92, 148, 252, 255},
	{204, 136, 252, 255},
	{244, 120, 252, 255},
	{252, 116, 180, 255},
	{252, 116, 96, 255},
	{252, 152, 56, 255},
	{240, 188, 60, 255},
	{128, 208, 16, 255},
	{76, 220, 72, 255},
	{88, 248, 152, 255},
	{0, 232, 216, 255},
	{120, 120, 120, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{252, 252, 252, 255},
	{168, 228, 252, 255},
	{196, 212, 252, 255},
	{212, 200, 252, 255},
	{252, 196, 252, 255},
	{252, 196, 216, 255},
	{252, 188, 176, 255},
	{252, 216, 168, 255},
	{252, 228, 160, 255},
	{224, 252, 160, 255},
	{168, 240, 188, 255},
	{176, 252, 204, 255},
	{156, 252, 240, 255},
	{196, 196, 196, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{116, 116, 116, 255},
	{36, 24, 140, 255},
	{0, 0, 168, 255},
	{68, 0, 156, 255},
	{140, 0, 116, 255},
	{168, 0, 16, 255},
	{164, 0, 0, 255},
	{124, 8, 0, 255},
	{64, 44, 0, 255},
	{0, 68, 0, 255},
	{0, 80, 0, 255},
	{0, 60, 20, 255},
	{24, 60, 92, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{188, 188, 188, 255},
	{0, 112, 236, 255},
	{32, 56, 236, 255},
	{128, 0, 240, 255},
	{188, 0, 188, 255},
	{228, 0, 88, 255},
	{216, 40, 0, 255},
	{200, 76, 12, 255},
	{136, 112, 0, 255},
	{0, 148, 0, 255},
	{0, 168, 0, 255},
	{0, 144, 56, 255},
	{0, 128, 136, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{252, 252, 252, 255},
	{60, 188, 252, 255},
	{92, 148, 252, 255},
	{204, 136, 252, 255},
	{244, 120, 252, 255},
	{252, 116, 180, 255},
	{252, 116, 96, 255},
	{252, 152, 56, 255},
	{240, 188, 60, 255},
	{128, 208, 16, 255},
	{76, 220, 72, 255},
	{88, 248, 152, 255},
	{0, 232, 216, 255},
	{120, 120, 120, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{252, 252, 252, 255},
	{168, 228, 252, 255},
	{196, 212, 252, 255},
	{212, 200, 252, 255},
	{252, 196, 252, 255},
	{252, 196, 216, 255},
	{252, 188, 176, 255},
	{252, 216, 168, 255},
	{252, 228, 160, 255},
	{224, 252, 160, 255},
	{168, 240, 188, 255},
	{176, 252, 204, 255},
	{156, 252, 240, 255},
	{196, 196, 196, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{116, 116, 116, 255},
	{36, 24, 140, 255},
	{0, 0, 168, 255},
	{68, 0, 156, 255},
	{140, 0, 116, 255},
	{168, 0, 16, 255},
	{164, 0, 0, 255},
	{124, 8, 0, 255},
	{64, 44, 0, 255},
	{0, 68, 0, 255},
	{0, 80, 0, 255},
	{0, 60, 20, 255},
	{24, 60, 92, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{188, 188, 188, 255},
	{0, 112, 236, 255},
	{32, 56, 236, 255},
	{128, 0, 240, 255},
	{188, 0, 188, 255},
	{228, 0, 88, 255},
	{216, 40, 0, 255},
	{200, 76, 12, 255},
	{136, 112, 0, 255},
	{0, 148, 0, 255},
	{0, 168, 0, 255},
	{0, 144, 56, 255},
	{0, 128, 136, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{252, 252, 252, 255},
	{60, 188, 252, 255},
	{92, 148, 252, 255},
	{204, 136, 252, 255},
	{244, 120, 252, 255},
	{252, 116, 180, 255},
	{252, 116, 96, 255},
	{252, 152, 56, 255},
	{240, 188, 60, 255},
	{128, 208, 16, 255},
	{76, 220, 72, 255},
	{88, 248, 152, 255},
	{0, 232, 216, 255},
	{120, 120, 120, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{252, 252, 252, 255},
	{168, 228, 252, 255},
	{196, 212, 252, 255},
	{212, 200, 252, 255},
	{252, 196, 252, 255},
	{252, 196, 216, 255},
	{252, 188, 176, 255},
	{252, 216, 168, 255},
	{252, 228, 160, 255},
	{224, 252, 160, 255},
	{168, 240, 188, 255},
	{176, 252, 204, 255},
	{156, 252, 240, 255},
	{196, 196, 196, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{116, 116, 116, 255},
	{36, 24, 140, 255},
	{0, 0, 168, 255},
	{68, 0, 156, 255},
	{140, 0, 116, 255},
	{168, 0, 16, 255},
	{164, 0, 0, 255},
	{124, 8, 0, 255},
	{64, 44, 0, 255},
	{0, 68, 0, 255},
	{0, 80, 0, 255},
	{0, 60, 20, 255},
	{24, 60, 92, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{188, 188, 188, 255},
	{0, 112, 236, 255},
	{32, 56, 236, 255},
	{128, 0, 240, 255},
	{188, 0, 188, 255},
	{228, 0, 88, 255},
	{216, 40, 0, 255},
	{200, 76, 12, 255},
	{136, 112, 0, 255},
	{0, 148, 0, 255},
	{0, 168, 0, 255},
	{0, 144, 56, 255},
	{0, 128, 136, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{252, 252, 252, 255},
	{60, 188, 252, 255},
	{92, 148, 252, 255},
	{204, 136, 252, 255},
	{244, 120, 252, 255},
	{252, 116, 180, 255},
	{252, 116, 96, 255},
	{252, 152, 56, 255},
	{240, 188, 60, 255},
	{128, 208, 16, 255},
	{76, 220, 72, 255},
	{88, 248, 152, 255},
	{0, 232, 216, 255},
	{120, 120, 120, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{252, 252, 252, 255},
	{168, 228, 252, 255},
	{196, 212, 252, 255},
	{212, 200, 252, 255},
	{252, 196, 252, 255},
	{252, 196, 216, 255},
	{252, 188, 176, 255},
	{252, 216, 168, 255},
	{252, 228, 160, 255},
	{224, 252, 160, 255},
	{168, 240, 188, 255},
	{176, 252, 204, 255},
	{156, 252, 240, 255},
	{196, 196, 196, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{116, 116, 116, 255},
	{36, 24, 140, 255},
	{0, 0, 168, 255},
	{68, 0, 156, 255},
	{140, 0, 116, 255},
	{168, 0, 16, 255},
	{164, 0, 0, 255},
	{124, 8, 0, 255},
	{64, 44, 0, 255},
	{0, 68, 0, 255},
	{0, 80, 0, 255},
	{0, 60, 20, 255},
	{24, 60, 92, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{188, 188, 188, 255},
	{0, 112, 236, 255},
	{32, 56, 236, 255},
	{128, 0, 240, 255},
	{188, 0, 188, 255},
	{228, 0, 88, 255},
	{216, 40, 0, 255},
	{200, 76, 12, 255},
	{136, 112, 0, 255},
	{0, 148, 0, 255},
	{0, 168, 0, 255},
	{0, 144, 56, 255},
	{0, 128, 136, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{252, 252, 252, 255},
	{60, 188, 252, 255},
	{92, 148, 252, 255},
	{204, 136, 252, 255},
	{244, 120, 252, 255},
	{252, 116, 180, 255},
	{252, 116, 96, 255},
	{252, 152, 56, 255},
	{240, 188, 60, 255},
	{128, 208, 16, 255},
	{76, 220, 72, 255},
	{88, 248, 152, 255},
	{0, 232, 216, 255},
	{120, 120, 120, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{252, 252, 252, 255},
	{168, 228, 252, 255},
	{196, 212, 252, 255},
	{212, 200, 252, 255},
	{252, 196, 252, 255},
	{252, 196, 216, 255},
	{252, 188, 176, 255},
	{252, 216, 168, 255},
	{252, 228, 160, 255},
	{224, 252, 160, 255},
	{168, 240, 188, 255},
	{176, 252, 204, 255},
	{156, 252, 240, 255},
	{196, 196, 196, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{116, 116, 116, 255},
	{36, 24, 140, 255},
	{0, 0, 168, 255},
	{68, 0, 156, 255},
	{140, 0, 116, 255},
	{168, 0, 16, 255},
	{164, 0, 0, 255},
	{124, 8, 0, 255},
	{64, 44, 0, 255},
	{0, 68, 0, 255},
	{0, 80, 0, 255},
	{0, 60, 20, 255},
	{24, 60, 92, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{188, 188, 188, 255},
	{0, 112, 236, 255},
	{32, 56, 236, 255},
	{128, 0, 240, 255},
	{188, 0, 188, 255},
	{228, 0, 88, 255},
	{216, 40, 0, 255},
	{200, 76, 12, 255},
	{136, 112, 0, 255},
	{0, 148, 0, 255},
	{0, 168, 0, 255},
	{0, 144, 56, 255},
	{0, 128, 136, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{252, 252, 252, 255},
	{60, 188, 252, 255},
	{92, 148, 252, 255},
	{204, 136, 252, 255},
	{244, 120, 252, 255},
	{252, 116, 180, 255},
	{252, 116, 96, 255},
	{252, 152, 56, 255},
	{240, 188, 60, 255},
	{128, 208, 16, 255},
	{76, 220, 72, 255},
	{88, 248, 152, 255},
	{0, 232, 216, 255},
	{120, 120, 120, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{252, 252, 252, 255},
	{168, 228, 252, 255},
	{196, 212, 252, 255},
	{212, 200, 252, 255},
	{252, 196, 252, 255},
	{252, 196, 216, 255},
	{252, 188, 176, 255},
	{252, 216, 168, 255},
	{252, 228, 160, 255},
	{224, 252, 160, 255},
	{168, 240, 188, 255},
	{176, 252, 204, 255},
	{156, 252, 240, 255},
	{196, 196, 196, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{116, 116, 116, 255},
	{36, 24, 140, 255},
	{0, 0, 168, 255},
	{68, 0, 156, 255},
	{140, 0, 116, 255},
	{168, 0, 16, 255},
	{164, 0, 0, 255},
	{124, 8, 0, 255},
	{64, 44, 0, 255},
	{0, 68, 0, 255},
	{0, 80, 0, 255},
	{0, 60, 20, 255},
	{24, 60, 92, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{188, 188, 188, 255},
	{0, 112, 236, 255},
	{32, 56, 236, 255},
	{128, 0, 240, 255},
	{188, 0, 188, 255},
	{228, 0, 88, 255},
	{216, 40, 0, 255},
	{200, 76, 12, 255},
	{136, 112, 0, 255},
	{0, 148, 0, 255},
	{0, 168, 0, 255},
	{0, 144, 56, 255},
	{0, 128, 136, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{252, 252, 252, 255},
	{60, 188, 252, 255},
	{92, 148, 252, 255},
	{204, 136, 252, 255},
	{244, 120, 252, 255},
	{252, 116, 180, 255},
	{252, 116, 96, 255},
	{252, 152, 56, 255},
	{240, 188, 60, 255},
	{128, 208, 16, 255},
	{76, 220, 72, 255},
	{88, 248, 152, 255},
	{0, 232, 216, 255},
	{120, 120, 120, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
	{252, 252, 252, 255},
	{168, 228, 252, 255},
	{196, 212, 252, 255},
	{212, 200, 252, 255},
	{252, 196, 252, 255},
	{252, 196, 216, 255},
	{252, 188, 176, 255},
	{252, 216, 168, 255},
	{252, 228, 160, 255},
	{224, 252, 160, 255},
	{168, 240, 188, 255},
	{176, 252, 204, 255},
	{156, 252, 240, 255},
	{196, 196, 196, 255},
	{0, 0, 0, 255},
	{0, 0, 0, 255},
}
