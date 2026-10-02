package main

import (
	"bytes"
	"database/sql"
	"encoding/json"
	"flag"
	"fmt"
	"log"
	"os"
	"strings"

	_ "github.com/mattn/go-sqlite3"
)

var (
	maxOut = flag.Bool("m", false, "max out")
)

func main() {
	log.SetPrefix("savemod: ")
	log.SetFlags(0)
	flag.Usage = usage
	flag.Parse()

	if flag.NArg() < 1 {
		usage()
	}

	save, err := NewSave(flag.Arg(0))
	ck(err)
	defer save.Close()

	if *maxOut {
		ck(save.MaxOut())
	}
	save.Dump()
}

type Save struct {
	db *sql.DB
}

func NewSave(name string) (*Save, error) {
	db, err := sql.Open("sqlite3", name)
	if err != nil {
		return nil, err
	}
	return &Save{
		db: db,
	}, nil
}

func (s *Save) Close() error {
	return s.db.Close()
}

func (s *Save) Dump() error {
	rows, err := s.db.Query("SELECT * FROM ItemTable")
	if err != nil {
		return err
	}

	defer rows.Close()
	for rows.Next() {
		var key, val string
		err := rows.Scan(&key, &val)
		if err != nil {
			return err
		}

		val = strings.Replace(val, "\x00", "", -1)
		buf := new(bytes.Buffer)
		err = json.Indent(buf, []byte(val), "", "\t")
		if err != nil {
			return err
		}

		fmt.Printf("%s = %s\n\n", key, buf)
	}
	return nil
}

type Heroes struct {
	List []Stat
}

type Amount struct {
	Name   string
	Amount int
}

type StatBoosts struct {
	Hp           int
	Attack       int
	Defense      int
	Magic        int
	Speed        int
	MagicDefense int
	Luck         int
}

type Stat struct {
	Level       int
	Experience  int
	InParty     bool
	WeaponID    interface{}
	ArmorID     interface{}
	AccessoryID interface{}
	Hp          int
	HpMax       int
	OldHpMax    int
	Bp          int
	BpMax       int
	Name        string
	Sprite      string
	StatBoosts  StatBoosts
	Immunity    []Amount
	Weakness    []Amount
	Resistance  []Amount
}

func (s *Save) MaxOut() error {
	_, err := s.db.Exec("UPDATE ItemTable SET value='99999999' where key='gold_0'")
	if err != nil {
		return err
	}

	var heroes Heroes
	rows, err := s.db.Query("SELECT value FROM ItemTable where key='heroes_0'")
	if err != nil {
		return err
	}

	var val string
	rows.Next()
	rows.Scan(&val)
	val = strings.Replace(val, "\x00", "", -1)
	err = json.Unmarshal([]byte(val), &heroes)
	if err != nil {
		return err
	}
	rows.Close()

	for i := range heroes.List {
		p := &heroes.List[i]
		s := &p.StatBoosts
		s.Attack = 9999
		s.Defense = 9999
		s.Magic = 9999
		s.Speed = 9999
		s.Luck = 9999
		s.MagicDefense = 9999
	}

	buf := new(bytes.Buffer)

	printAmount := func(name string, amount []Amount) {
		fmt.Fprintf(buf, `%q:[`, name)
		for n, m := range amount {
			fmt.Fprintf(buf, `{`)
			fmt.Fprintf(buf, `"name":%q`, m.Name)
			fmt.Fprintf(buf, `"amount":%d`, m.Amount)
			fmt.Fprintf(buf, `}`)
			if n+1 < len(amount) {
				fmt.Fprintf(buf, `,`)
			}
		}
		fmt.Fprintf(buf, `],`)
	}

	printID := func(name string, v interface{}) {
		if _, ok := v.(string); ok {
			fmt.Fprintf(buf, "%q:%q,", name, v)
		} else {
			fmt.Fprintf(buf, "%q:%v,", name, v)
		}
	}

	fmt.Fprintf(buf, `{"list":[`)
	for i, p := range heroes.List {
		fmt.Fprintf(buf, `{`)
		fmt.Fprintf(buf, `"level":%d,`, p.Level)
		fmt.Fprintf(buf, `"experience":%d,`, p.Experience)
		fmt.Fprintf(buf, `"inParty":%v,`, p.InParty)
		printID("weaponID", p.WeaponID)
		printID("armorID", p.ArmorID)
		printID("accessoryID", p.AccessoryID)
		fmt.Fprintf(buf, `"hp":%d,`, p.Hp)
		fmt.Fprintf(buf, `"hpMax":%d,`, p.HpMax)
		fmt.Fprintf(buf, `"bp":%d,`, p.Bp)
		fmt.Fprintf(buf, `"bpMax":%d,`, p.BpMax)
		fmt.Fprintf(buf, `"name":%q,`, p.Name)
		fmt.Fprintf(buf, `"sprite":%q,`, p.Sprite)

		printAmount("immunity", p.Immunity)
		printAmount("weakness", p.Weakness)
		printAmount("resistance", p.Resistance)
		fmt.Fprintf(buf, `"oldHpMax":%d,`, p.OldHpMax)

		fmt.Fprintf(buf, `"statBoosts":{`)
		m := &p.StatBoosts
		fmt.Fprintf(buf, `"attack":%d,`, m.Attack)
		fmt.Fprintf(buf, `"defense":%d,`, m.Defense)
		fmt.Fprintf(buf, `"magic":%d,`, m.Magic)
		fmt.Fprintf(buf, `"speed":%d,`, m.Speed)
		fmt.Fprintf(buf, `"hp":%d,`, m.Hp)
		fmt.Fprintf(buf, `"luck":%d`, m.Luck)
		fmt.Fprintf(buf, `}`)

		fmt.Fprintf(buf, `}`)
		if i+1 < len(heroes.List) {
			fmt.Fprintf(buf, ",")
		}
	}
	fmt.Fprintf(buf, `]}`)

	mp := make(map[string]interface{})
	err = json.Unmarshal(buf.Bytes(), &mp)
	if err != nil {
		fmt.Printf("%s\n", buf)
		return err
	}

	_, err = s.db.Exec("UPDATE ItemTable SET value=? where key='heroes_0'", buf.String())
	if err != nil {
		return err
	}

	return nil
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: savemod [options] file")
	flag.PrintDefaults()
	os.Exit(2)
}

func ck(err error) {
	if err != nil {
		log.Fatal(err)
	}
}
