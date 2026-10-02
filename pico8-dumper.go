package main

import (
	"bufio"
	"flag"
	"fmt"
	"image"
	"image/color"
	"image/draw"
	"image/png"
	"io"
	"log"
	"os"
	"path/filepath"
	"regexp"
	"strings"
)

var (
	palfile = flag.String("p", "", "use palette file")

	status = 0
)

func main() {
	log.SetFlags(0)
	log.SetPrefix("pico8-dumper: ")
	flag.Usage = usage
	flag.Parse()
	if flag.NArg() < 1 {
		usage()
	}

	dump(flag.Arg(0), flag.Arg(1), *palfile)
	os.Exit(status)
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: [options] file [dumpdir]")
	flag.PrintDefaults()
	os.Exit(2)
}

func ck(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

func ek(err error) {
	if err != nil {
		fmt.Fprintf(os.Stderr, "pico8-dumper: %v\n", err)
		status = 1
	}
}

func dump(name, dumpdir, palfile string) {
	f, err := os.Open(name)
	ck(err)
	defer f.Close()

	c := NewCart()

	if palfile != "" {
		pal, err := loadpal(palfile)
		ck(err)
		copy(c.Pal[:], pal)
	}

	err = c.Load(f)
	ck(err)

	fmt.Printf("version %d\n", c.Version)
	for i, s := range c.Sections {
		fmt.Printf("section #%d name: %-10s size: %d\n", i, s.Name, len(s.Data))
	}
	fmt.Println()

	if dumpdir == "" {
		ext := filepath.Ext(name)
		dumpdir = fmt.Sprintf("%s", name[:len(name)-len(ext)])
	}
	os.MkdirAll(dumpdir, 0755)

	fmt.Println("dumping to", dumpdir)
	for _, s := range c.Sections {
		var err error
		switch s.Name {
		case "__lua__":
			codefile := filepath.Join(dumpdir, "code.lua")
			err = os.WriteFile(codefile, s.Data, 0644)
		case "__gfx__":
			gfxfile := filepath.Join(dumpdir, "gfx.png")
			ascfile := filepath.Join(dumpdir, "gfx.asc")
			err = dumpart(gfxfile, ascfile, c.Gfx, s.Data)
		case "__label__":
			labelfile := filepath.Join(dumpdir, "label.png")
			ascfile := filepath.Join(dumpdir, "label.asc")
			err = dumpart(labelfile, ascfile, c.Label, s.Data)
		case "__map__":
			mapfile := filepath.Join(dumpdir, "map.png")
			ascfile := filepath.Join(dumpdir, "map.asc")
			err = dumpart(mapfile, ascfile, c.Map, s.Data)
		default:
			ascname := strings.TrimPrefix(s.Name, "__")
			ascname = strings.TrimSuffix(ascname, "__")
			ascfile := filepath.Join(dumpdir, ascname+".asc")
			err = os.WriteFile(ascfile, s.Data, 0644)
		}
		ek(err)
	}
}

func loadpal(name string) ([]color.RGBA, error) {
	f, err := os.Open(name)
	if err != nil {
		return nil, err
	}
	defer f.Close()

	var p []color.RGBA
	s := bufio.NewScanner(f)
	for li := 1; s.Scan(); li++ {
		var c color.RGBA

		ln := s.Text()
		ln = strings.TrimSpace(ln)
		if ln == "" || strings.HasPrefix(ln, "#") {
			continue
		}

		_, err := fmt.Sscanf(ln, "%v,%v,%v,%v", &c.R, &c.R, &c.G, &c.A)
		if err != nil {
			c.A = 255
			_, err = fmt.Sscanf(ln, "%v,%v,%v", &c.R, &c.G, &c.B)
		}
		if err != nil {
			_, err = fmt.Sscanf(ln, "#%02x%02x%02x%02x", &c.R, &c.G, &c.B, &c.A)
		}
		if err != nil {
			c.A = 255
			_, err = fmt.Sscanf(ln, "#%02x%02x%02x", &c.R, &c.G, &c.B)
		}

		if err != nil {
			return nil, fmt.Errorf("invalid color format at line %d\n", li)
		}

		p = append(p, c)
	}
	return p, nil
}

func dumpart(imgfile, ascfile string, img *image.RGBA, asc []byte) error {
	w, err := os.Create(imgfile)
	if err != nil {
		return err
	}

	err = png.Encode(w, img)
	xerr := w.Close()
	if err == nil {
		err = xerr
	}
	if err != nil {
		return err
	}

	return os.WriteFile(ascfile, asc, 0644)
}

func hexb(b byte) int {
	switch {
	case '0' <= b && b <= '9':
		return int(b) - '0'
	case 'a' <= b && b <= 'f':
		return 10 + int(b) - 'a'
	case 'A' <= b && b <= 'F':
		return 10 + int(b) - 'A'
	}
	return int(b)
}

type Cart struct {
	Version  int
	Sections []*Section
	Pal      [16]color.RGBA
	Gfx      *image.RGBA
	Label    *image.RGBA
	Map      *image.RGBA
}

type Section struct {
	Name string
	Data []byte
}

var defpal = [16]color.RGBA{
	color.RGBA{0, 0, 0, 255},       // black
	color.RGBA{29, 43, 83, 255},    // dark blue
	color.RGBA{126, 37, 83, 255},   // dark purple
	color.RGBA{0, 135, 81, 255},    // dark green
	color.RGBA{171, 82, 54, 255},   // brown
	color.RGBA{95, 87, 79, 255},    // dark-gray
	color.RGBA{194, 195, 199, 255}, // light-gray
	color.RGBA{255, 241, 232, 255}, // white
	color.RGBA{255, 0, 7, 255},     // red
	color.RGBA{255, 163, 0, 255},   // orange
	color.RGBA{255, 236, 39, 255},  // yellow
	color.RGBA{0, 228, 54, 255},    // green
	color.RGBA{41, 173, 255, 255},  // blue
	color.RGBA{131, 118, 156, 255}, // indigo
	color.RGBA{255, 119, 168, 255}, // pink
	color.RGBA{255, 204, 170, 255}, // peach
}

func NewCart() *Cart {
	return &Cart{
		Pal: defpal,
	}
}

func (c *Cart) Load(r io.Reader) error {
	const sig = "pico-8 cartridge // http://www.pico-8.com\n"

	var sigb [len(sig)]byte
	_, err := io.ReadAtLeast(r, sigb[:], len(sigb))
	if err != nil {
		return err
	}
	if string(sigb[:]) != sig {
		return fmt.Errorf("invalid pico8 header signature")
	}

	n, _ := fmt.Fscanf(r, "version %d\n", &c.Version)
	if n != 1 {
		return fmt.Errorf("no pico8 version found")
	}

	data, err := io.ReadAll(r)
	if err != nil {
		return err
	}

	c.Sections = c.Sections[:0]
	re := regexp.MustCompile("__.*__")
	loc := re.FindAllIndex(data, -1)
	for i := range loc {
		sd := data[loc[i][1]:]
		if i+1 < len(loc) {
			sd = data[loc[i][1]:loc[i+1][0]]
		}
		if len(sd) > 0 && sd[0] == '\n' {
			sd = sd[1:]
		}
		c.Sections = append(c.Sections, &Section{
			Name: string(data[loc[i][0]:loc[i][1]]),
			Data: sd,
		})
	}

	for _, s := range c.Sections {
		var err error
		switch s.Name {
		case "__gfx__":
			c.Gfx, err = c.dumpimg(s.Name, s.Data, 128, 128, c.Pal[:])
		case "__label__":
			c.Label, err = c.dumpimg(s.Name, s.Data, 128, 128, c.Pal[:])
		}
		if err != nil {
			return err
		}
	}

	s := c.Section("__map__")
	if s != nil {
		c.Map, err = c.dumpmap(c.Gfx, s.Data, 128, 32, 8)
		if err != nil {
			return err
		}
	}

	return nil
}

func (c *Cart) Section(name string) *Section {
	for _, s := range c.Sections {
		if s.Name == name {
			return s
		}
	}
	return nil
}

func (c *Cart) dumpimg(sectname string, data []byte, width, height int, pal []color.RGBA) (*image.RGBA, error) {
	r := image.Rect(0, 0, width, height)
	m := image.NewRGBA(r)
	i := 0
	for y := r.Min.Y; y < r.Max.Y; y++ {
		for x := 0; x < r.Max.X; x++ {
			if i < len(data) && data[i] == '\n' {
				i++
			}
			val := 0
			if i < len(data) {
				val = hexb(data[i])
			}
			m.Set(x, y, pal[val%len(pal)])
			i++
		}
	}
	return m, nil
}

func (c *Cart) dumpmap(gfx *image.RGBA, data []byte, width, height, tilesize int) (*image.RGBA, error) {
	g := gfx.Bounds()
	r := image.Rect(0, 0, width*tilesize, height*tilesize)
	m := image.NewRGBA(r)
	i := 0
	for y := 0; y < height; y++ {
		for x := 0; x < width; x++ {
			if i < len(data) && data[i] == '\n' {
				i++
			}

			lo, hi := 0, 0
			if i+2 < len(data) {
				hi = hexb(data[i]) << 4
				lo = hexb(data[i+1])
			}

			tl := hi | lo
			tx := (tl * tilesize) % g.Dx()
			ty := (tl * tilesize) / g.Dx()
			dp := image.Rect(x*tilesize, y*tilesize, (x+1)*tilesize, (y+1)*tilesize)
			sp := image.Pt(tx, ty*tilesize)
			draw.Draw(m, dp, gfx, sp, draw.Over)
			i += 2
		}
	}
	return m, nil
}
