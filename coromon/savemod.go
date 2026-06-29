package main

import (
	"bytes"
	"database/sql"
	"encoding/base64"
	"encoding/json"
	"flag"
	"fmt"
	"io"
	"log"
	"os"
	stdpath "path"
	"strconv"
	"strings"

	_ "github.com/mattn/go-sqlite3"
)

type Saveslot struct {
	VersionID     string
	EncryptedData string
	Metadata      struct {
		PlaytimeInSeconds int
	}
	DecryptedData map[string]any
}

var (
	seckey = flag.String("key", defkey, "specify encryption key")
	maxout = flag.Bool("maxout", false, "max out")
	xp     = flag.Int("xp", 9999999, "specify xp")
)

func main() {
	log.SetPrefix("coromon-savemod: ")
	log.SetFlags(0)

	flag.Usage = usage
	flag.Parse()
	if flag.NArg() != 1 {
		usage()
	}

	db, err := sql.Open("sqlite3", flag.Arg(0))
	check(err)

	data, err := readdata(db, *seckey)
	check(err)

	if *maxout {
		var sav map[string]any
		err = json.Unmarshal([]byte(data), &sav)
		check(err)

		if *maxout {
			maximize(db, sav, *seckey)
		}
	}

	check(db.Close())
	fmt.Println(data)
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: [options] savefile")
	flag.PrintDefaults()
	os.Exit(2)
}

func check(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

func maximize(db *sql.DB, sav map[string]any, sec string) {
	rows, err := db.Query("SELECT * FROM preference")
	if err != nil {
		return
	}
	defer rows.Close()

	var store [][2]string
	for rows.Next() {
		var key, val string

		err = rows.Scan(&key, &val)
		if err != nil {
			return
		}

		if !strings.HasPrefix(key, "saveslot_self_") || val == "null" {
			continue
		}

		root := pathto(sav[key], "decryptedData")
		if root == nil {
			continue
		}

		setfield(root, "gold", 9999999)
		for _, fld := range []string{"squad", "monsterStorage"} {
			node := pathto(root, fld)
			if coromons, ok := node.([]any); ok {
				for i := range coromons {
					p, ok := coromons[i].(map[string]any)
					if !ok {
						continue
					}
					p["potential"] = 21
					p["xp"] = *xp
					p["health"] = 999
					p["energy"] = 999
				}
			}
		}
		node := pathto(root, "items")
		if items, ok := node.(map[string]any); ok {
			for p, _ := range items {
				items[p] = 99
			}
		}

		buf, err := json.Marshal(root)
		if err != nil {
			continue
		}

		enc := encrypt(string(buf), sec)
		i, j := getlocation(val, "encryptedData")
		if i < 0 || j < 0 {
			continue
		}

		val = strings.Replace(val, val[i:j], enc, 1)
		store = append(store, [2]string{key, val})
	}

	for _, kv := range store {
		res, err := db.Exec("UPDATE preference SET value=? where key=?", kv[1], kv[0])
		if err != nil {
			fmt.Println("Failed to update store: ", res, err)
		}
	}
}

func getlocation(str, fld string) (i, j int) {
	fld = fmt.Sprintf(`"%s":"`, fld)
	i = strings.Index(str, fld)
	if i < 0 {
		return
	}
	j = strings.Index(str[i+len(fld):], `"`)
	if j < 0 {
		return
	}
	i += len(fld)
	j += i
	return
}

func setfield(root any, fld string, val any) bool {
	dir, base := stdpath.Split(fld)
	node := pathto(root, dir)
	if node == nil {
		return false
	}

	store, ok := node.(map[string]any)
	if !ok {
		return false
	}

	store[base] = val
	return true
}

func pathto(root any, path string) any {
	node, ok := root.(map[string]any)
	if !ok {
		return nil
	}

	res := any(node)
	path = stdpath.Clean(path)
	toks := strings.Split(path, "/")
	for i, tok := range toks {
		if tok == "." || tok == "" {
			continue
		}

		switch xnode := node[tok].(type) {
		case map[string]any:
			node = xnode
			res = xnode
		default:
			if i+1 < len(toks) {
				return nil
			}
			res = xnode
		}
	}
	return res
}

func readdata(db *sql.DB, sec string) (data string, err error) {
	store, err := readpref(db, sec)
	if err != nil {
		return
	}
	return jsonify(store)
}

func readpref(db *sql.DB, sec string) (store [][2]string, err error) {
	rows, err := db.Query("SELECT * FROM preference ORDER BY key")
	if err != nil {
		return
	}
	defer rows.Close()

	for rows.Next() {
		var key, val string
		err = rows.Scan(&key, &val)
		if err != nil {
			return
		}

		if sec == "" {
			goto next
		}

		switch {
		case key == "globalSettings":
			data, xerr := decrypt(val, sec)
			if xerr == nil {
				val = data
			}

		case strings.HasPrefix(key, "saveslot_self_") && val != "null":
			var slot Saveslot
			xerr := json.Unmarshal([]byte(val), &slot)
			if xerr != nil {
				break
			}

			data, xerr := decrypt(slot.EncryptedData, sec)
			if xerr != nil {
				break
			}

			if strings.HasPrefix(data, "{") {
				data = data[1:]
			}

			if strings.HasSuffix(data, "}") {
				data = data[:len(data)-1]
			}

			if strings.HasSuffix(val, "}") {
				val = val[:len(val)-1]
			}

			val += "," + `"decryptedData":{` + data + "}}"
		}

	next:
		_, xerr := strconv.Atoi(val)
		if xerr != nil && !strings.HasPrefix(val, "{") {
			val = `"` + val + `"`
		}
		store = append(store, [2]string{key, val})
	}

	return
}

func jsonify(store [][2]string) (js string, err error) {
	w := new(bytes.Buffer)
	b := new(bytes.Buffer)

	fmt.Fprintf(w, "{")
	for i, p := range store {
		if i > 0 {
			fmt.Fprintf(w, ",\n")
		}
		fmt.Fprintf(w, "\t%q: %s", p[0], p[1])
	}
	fmt.Fprintf(w, "}")

	err = json.Indent(b, w.Bytes(), "", "\t")
	if err != nil {
		err = fmt.Errorf("failed to jsonify: %v\n\n%s\n", err, w)
		return
	}

	js = string(b.String())
	return
}

func encrypt(str, key string) string {
	return base64enc(xorcrypt(str, key))
}

func decrypt(str, key string) (string, error) {
	data, err := base64dec(str)
	if err != nil {
		return data, err
	}
	return xorcrypt(data, key), nil
}

func xorcrypt(buf, key string) string {
	res := make([]byte, len(buf))
	for i := range buf {
		res[i] = buf[i] ^ key[i%len(key)]
	}
	return string(res)
}

func base64enc(str string) string {
	w := new(bytes.Buffer)
	enc := base64.NewEncoder(base64.StdEncoding, w)
	fmt.Fprint(enc, str)
	enc.Close()
	return w.String()
}

func base64dec(str string) (string, error) {
	dec := base64.NewDecoder(base64.StdEncoding, strings.NewReader(str))
	buf, err := io.ReadAll(dec)
	return string(buf), err
}

const defkey = "Yp=Tk8Of3JaxE\\s@Wn;Ri6Md1H_vCZq>Ul9Pg4KbyF]tAXo<Sj7Ne2I`wD[r?Vm:Qh5Lc0G^uBYp=Tk8Of3JaxE\\s@Wn;Ri6Md1H_vCZq>Ul9Pg4KbyF]tAXo<Sj7Ne2I`wD[r?Vm:Qh5Lc0G^uBYp=Tk8Of3JaxE\\s@Wn;Ri6Md1H_vCZq>Ul9Pg4KbyF]tAXo<Sj7Ne2I`wD[r?Vm:Qh5Lc0G^uBYp=Tk8Of3JaxE\\s@Wn;Ri6Md1H_vCZq>Ul9Pg4KbyF]tAXo<Sj7Ne2I`wD[r?Vm:Qh5Lc0G^uBYp=Tk8Of3JaxE\\s@Wn;Ri6Md1H_vCZq>Ul9P"
