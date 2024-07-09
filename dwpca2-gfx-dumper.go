// dump gfx files for
// http://www.compmike19.com/dwpca2.zip
package main

import (
	"flag"
	"fmt"
	"image"
	"image/color"
	"image/png"
	"log"
	"os"
	"path/filepath"
)

func main() {
	var width, height int

	log.SetFlags(0)
	flag.IntVar(&width, "w", 320, "width")
	flag.Usage = usage
	flag.Parse()
	if flag.NArg() < 1 {
		usage()
	}

	buf, err := os.ReadFile(flag.Arg(0))
	ck(err)

	height = len(buf) / (width * 3)
	rgba := image.NewRGBA(image.Rect(0, 0, width, height))

	i := 0
	for y := 0; y < height; y++ {
		for x := 0; x < width; x++ {
			rgba.Set(x, y, color.RGBA{buf[i], buf[i+1], buf[i+2], 255})
			i += 3
		}
	}

	var output string
	if flag.NArg() < 2 {
		output = flag.Arg(0)
		ext := filepath.Ext(output)
		output = output[:len(output)-len(ext)] + ".png"
	} else {
		output = flag.Arg(1)
	}
	w, err := os.Create(output)
	ck(err)
	ck(png.Encode(w, rgba))
	ck(w.Close())
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: <dat_file> <image_file>")
	flag.PrintDefaults()
	os.Exit(2)
}

func ck(err error) {
	if err != nil {
		log.Fatal(err)
	}
}
