package main

import (
	"bytes"
	"flag"
	"fmt"
	"image/png"
	"log"
	"os"

	"github.com/qeedquan/go-media/archive/nipponichi/tx2"
	"github.com/qeedquan/go-media/image/dds"
)

func main() {
	flag.Usage = usage
	flag.Parse()
	if flag.NArg() != 2 {
		usage()
	}

	img, err := readimage(flag.Arg(0))
	check(err)

	err = writeimage(flag.Arg(1), img)
	check(err)
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: tx2-dumper [options] input.tx2 output")
	flag.PrintDefaults()
	os.Exit(2)
}

func check(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

func readimage(name string) (*tx2.Image, error) {
	fd, err := os.Open(name)
	if err != nil {
		return nil, err
	}
	defer fd.Close()

	img, err := tx2.Decode(fd)
	if err != nil {
		return nil, err
	}
	return img, nil
}

func writeimage(name string, img *tx2.Image) error {
	buf := new(bytes.Buffer)
	switch img.Type {
	case tx2.TYPE_DXT1, tx2.TYPE_DXT4, tx2.TYPE_DXT5:
		dxt := &dds.Image{
			Header: dds.Header{
				Size:              dds.HEADER_SIZE,
				Flags:             dds.DDSD_CAPS | dds.DDSD_HEIGHT | dds.DDSD_WIDTH | dds.DDSD_PIXELFORMAT,
				Height:            uint32(img.Height),
				Width:             uint32(img.Width),
				PitchOrLinearSize: uint32(img.Width * img.Height),
				Spf: dds.PixelFormat{
					Size:   dds.PIXELFORMAT_SIZE,
					Flags:  dds.DDPF_FOURCC,
					FourCC: dxttype(img.Type),
				},
				Caps: dds.DDSCAPS_TEXTURE,
			},
			Pix: img.Pix,
		}
		dds.Encode(buf, dxt)
		name += ".dds"

	default:
		rgba, err := img.ToRGBA()
		if err != nil {
			return err
		}
		png.Encode(buf, rgba)
		name += ".png"
	}

	return os.WriteFile(name, buf.Bytes(), 0644)
}

func dxttype(typ uint16) uint32 {
	switch typ {
	case tx2.TYPE_DXT1:
		return dds.FOURCC_DXT1
	case tx2.TYPE_DXT4:
		return dds.FOURCC_DXT4
	case tx2.TYPE_DXT5:
		return dds.FOURCC_DXT5
	default:
		panic("unreachable")
	}
}
