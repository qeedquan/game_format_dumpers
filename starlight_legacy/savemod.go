package main

import (
	"bytes"
	"encoding/json"
	"flag"
	"fmt"
	"log"
	"math"
	"os"
)

type File struct {
	Data map[string]any
}

var (
	maxout = flag.Bool("maxout", false, "max out")
)

func main() {
	flag.Parse()
	if flag.NArg() != 2 {
		usage()
	}

	f, err := decode(flag.Arg(0))
	check(err)

	if *maxout {
		f.MaxOut()
	}

	buf, err := json.MarshalIndent(f.Data, "", "    ")
	check(err)
	buf = append(buf, 0)

	err = os.WriteFile(flag.Arg(1), buf, 0644)
	check(err)
}

func check(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: file.save")
	flag.PrintDefaults()
	os.Exit(2)
}

func decode(name string) (*File, error) {
	buf, err := os.ReadFile(flag.Arg(0))
	if err != nil {
		return nil, err
	}

	buf = bytes.TrimSuffix(buf, []byte{0})

	f := &File{
		Data: make(map[string]any),
	}
	err = json.Unmarshal(buf, &f.Data)
	if err != nil {
		return nil, err
	}

	return f, nil
}

func (f *File) MaxOut() {
	fmt.Println("MAX OUT!")

	data := f.Data["data"].(map[string]any)
	main_sram := data["main_sram"].([]any)
	inventory := data["inventory"].([]any)
	party_stats := data["party_stats"].([]any)

	// money
	main_sram[15] = float64(math.MaxInt32)

	// normal items
	items := inventory[0].([]any)
	for _, item := range items {
		values := item.([]any)
		id := values[0].(float64)
		if id != 0 {
			values[1] = float64(999)
		}
	}

	for _, char := range party_stats {
		values := char.([]any)
		// attack
		values[3] = float64(99999)
		// defense
		values[4] = float64(99999)
		// magic attack
		values[5] = float64(99999)
		// magic defense
		values[6] = float64(99999)
		// speed
		values[7] = float64(99999)
		// hp
		values[8] = float64(99999)
		values[9] = float64(99999)
		// mp
		values[10] = float64(99999)
		values[11] = float64(99999)
	}
}
