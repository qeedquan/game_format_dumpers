package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/md5"
	"encoding/base64"
	"encoding/binary"
	"encoding/hex"
	"encoding/json"
	"flag"
	"fmt"
	"io"
	"log"
	"os"
	"strings"
)

var (
	doEncrypt  = flag.Bool("e", false, "encrypt the input")
	prettyDump = flag.Bool("d", false, "pretty print dump info")
)

func main() {
	log.SetPrefix("savecrypt: ")
	log.SetFlags(0)
	flag.Usage = usage
	flag.Parse()
	if flag.NArg() < 1 {
		usage()
	}

	s, err := dump(flag.Arg(0))
	ck(err)

	if *doEncrypt {
		encryptSave(s)
	}
	if *prettyDump {
		pretty(s)
	} else {
		j, _ := json.Marshal(s)
		fmt.Printf("%s\n", j)
	}
}

func ck(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: [options] file")
	flag.PrintDefaults()
	os.Exit(2)
}

type Save struct {
	Slots    []string `json:"slots"`
	AutoSlot string   `json:"autoSlot"`
	Globals  string   `json:"globals"`
	LastSlot int      `json:"lastSlot"`

	SlotsSalt    []string `json:"slotsSalt,omitempty"`
	AutoSlotSalt string   `json:"autoSlotSalt,omitempty"`
	GlobalsSalt  string   `json:"globalsSalt,omitempty"`
}

func decodeSalt(str string) string {
	salt, err := hex.DecodeString(str)
	ck(err)
	if len(salt) != 8 {
		return string(make([]byte, 8))
	}
	return string(salt)
}

func encryptSave(s *Save) {
	for i := range s.Slots {
		s.Slots[i] = encrypt(s.Slots[i], decodeSalt(s.SlotsSalt[i]))
	}
	s.AutoSlot = encrypt(s.AutoSlot, decodeSalt(s.AutoSlotSalt))
	s.Globals = encrypt(s.Globals, decodeSalt(s.GlobalsSalt))

	s.SlotsSalt = nil
	s.AutoSlotSalt = ""
	s.GlobalsSalt = ""
}

func dump(name string) (*Save, error) {
	b, err := os.ReadFile(name)
	if err != nil {
		return nil, err
	}

	s := &Save{}
	err = json.Unmarshal(b, &s)
	if err != nil {
		return nil, err
	}
	if len(s.SlotsSalt) != len(s.Slots) {
		s.SlotsSalt = make([]string, len(s.Slots))
	}

	s.Globals, s.GlobalsSalt = decrypt(s.Globals, s.GlobalsSalt)
	s.AutoSlot, s.AutoSlotSalt = decrypt(s.AutoSlot, s.AutoSlotSalt)
	for i := range s.Slots {
		s.Slots[i], s.SlotsSalt[i] = decrypt(s.Slots[i], s.SlotsSalt[i])
	}

	return s, nil
}

func prettyJSON(prefix, str string) string {
	n := len(str) - 1
	for ; n > -1; n-- {
		if str[n] >= aes.BlockSize {
			break
		}
	}
	str = str[:n+1]

	m := make(map[string]interface{})
	err := json.Unmarshal([]byte(str), &m)
	b, xerr := json.MarshalIndent(&m, "", "\t")

	fmt.Fprintf(os.Stdout, "%s\n", prefix)
	if err == nil {
		err = xerr
	}
	if err != nil {
		fmt.Fprintf(os.Stdout, "error: %v\n", err)
	}
	fmt.Fprintf(os.Stdout, "%s\n", b)
	fmt.Fprintf(os.Stdout, "------\n")
	return string(b)
}

func pretty(s *Save) {
	for i := range s.Slots {
		prettyJSON(fmt.Sprintf("Slot %d", i), s.Slots[i])
	}
	prettyJSON("Auto Slot", s.AutoSlot)
	prettyJSON("Globals", s.Globals)
}

var (
	cryptSig  = "[-!_0_!-]"
	cryptPass = ":_.NaN0"
)

func encrypt(str, salt string) string {
	if len(str)%aes.BlockSize != 0 {
		pad := aes.BlockSize - (len(str) % aes.BlockSize)
		str += strings.Repeat(string(pad), pad)
	}

	key, iv := evkdf(cryptPass, salt, 1)
	block, err := aes.NewCipher(key)
	ck(err)

	enc := cipher.NewCBCEncrypter(block, iv)

	dst := make([]byte, len(str))
	enc.CryptBlocks(dst, []byte(str))

	dst = append([]byte(salt), dst...)
	dst = append([]byte{0x65, 0x64, 0x5f, 0x5f}, dst...)
	dst = append([]byte{0x53, 0x61, 0x6c, 0x74}, dst...)

	return cryptSig + base64.StdEncoding.EncodeToString(dst)
}

func decrypt(str, defaultSalt string) (string, string) {
	if !strings.HasPrefix(str, cryptSig) {
		return str, defaultSalt
	}
	str = str[len(cryptSig):]

	dec, err := base64.StdEncoding.DecodeString(str)
	if err != nil || len(dec) < 16 {
		return str, defaultSalt
	}

	salt := ""
	sig1 := binary.BigEndian.Uint32(dec[0:])
	sig2 := binary.BigEndian.Uint32(dec[4:])
	if sig1 == 0x53616c74 && sig2 == 0x65645f5f {
		salt = string(dec[8:16])
		dec = dec[16:]
	}

	key, iv := evkdf(cryptPass, salt, 1)

	block, err := aes.NewCipher(key)
	if err != nil {
		return str, defaultSalt
	}

	text := make([]byte, len(dec))
	cbc := cipher.NewCBCDecrypter(block, iv)
	cbc.CryptBlocks(text, dec)

	return string(text), hex.EncodeToString([]byte(salt))
}

func evkdf(pass, salt string, iterations int) (key, iv []byte) {
	const size = 12 * 3

	h := md5.New()

	var b, d []byte
	for len(d) < size {
		h.Reset()
		if b != nil {
			h.Write(b)
		}
		io.WriteString(h, pass)
		io.WriteString(h, salt)
		b = h.Sum(nil)

		for i := 1; i < iterations; i++ {
			h.Write(b)
			b = h.Sum(nil)
			h.Reset()
		}
		d = append(d, b...)
	}

	return d[:32], d[32:]
}
