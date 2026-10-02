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

	f, err := decode(flag.Arg(0))
	if err != nil {
		log.Fatal(err)
	}

	for i, a := range f.Accounts {
		fmt.Printf("Account #%d\n", i+1)
		fmt.Printf("\tDifficulty:  %d\n", a.Difficulty)
		fmt.Printf("\tProgress:    %d\n", a.Progress)
	}
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: [options] <users_file>")
	flag.PrintDefaults()
	os.Exit(2)
}

type File struct {
	Active   int
	Accounts []Account
}

type Account struct {
	Difficulty      int
	Progress        int
	Campaigns       []Campaign
	CurrentCampaign string
	Points          float32
	Highscore       []float32
	FastTime        []float32
	Unlocked        []byte
	Name            string
}

type Campaign struct {
	Name      string
	Time      float32
	Score     float32
	FastTime  float32
	Highscore float32
	Choices   []int
}

func decode(name string) (p *File, err error) {
	f, err := os.Open(name)
	if err != nil {
		return
	}
	defer f.Close()

	p = &File{}
	var (
		r            = bufio.NewReader(f)
		numaccounts  int
		numcampaigns int
		numchoices   int
	)

	get(r, &numaccounts, &p.Active)
	for i := 0; i < numaccounts; i++ {
		a := Account{}

		get(r, &a.Difficulty, &a.Progress, &numcampaigns)
		for j := 0; j < numcampaigns; j++ {
			c := Campaign{}

			get(r, &c.Name, &c.Time, &c.Score, &c.FastTime, &c.Highscore, &numchoices)
			for k := 0; k < numchoices; k++ {
				c.Choices = append(c.Choices, get4(r))
			}

			a.Campaigns = append(a.Campaigns, c)
		}

		get(r, &a.CurrentCampaign, &a.Points)
		for i := 0; i < 50; i++ {
			a.Highscore = append(a.Highscore, getflt(r))
			a.FastTime = append(a.FastTime, getflt(r))
		}
		a.Unlocked = make([]byte, 60)
		get(r, &a.Unlocked, &a.Name)

		p.Accounts = append(p.Accounts, a)
	}

	return
}

func get(r io.Reader, args ...any) {
	for _, arg := range args {
		switch x := arg.(type) {
		case *int:
			*x = get4(r)
		case *float32:
			*x = getflt(r)
		case *string:
			*x = getstr(r)
		case *[]byte:
			binary.Read(r, binary.BigEndian, x)
		default:
			panic("unknown type")
		}
	}
}

func get4(r io.Reader) int {
	var i int32

	err := binary.Read(r, binary.BigEndian, &i)
	if err != nil {
		panic(err)
	}

	return int(i)
}

func getflt(r io.Reader) float32 {
	var f float32

	err := binary.Read(r, binary.BigEndian, &f)
	if err != nil {
		panic(err)
	}

	return f
}

func getstr(r io.Reader) string {
	var n int32
	var b []byte

	err := binary.Read(r, binary.BigEndian, &n)

	b = make([]byte, n)
	xerr := binary.Read(r, binary.BigEndian, b)

	if err == nil {
		err = xerr
	}

	if err != nil {
		panic(err)
	}

	return string(b)
}
