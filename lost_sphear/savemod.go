package main

import (
	"bytes"
	"crypto/aes"
	"crypto/cipher"
	"crypto/md5"
	"encoding/binary"
	"flag"
	"fmt"
	"log"
	"math"
	"os"

	"github.com/davecgh/go-spew/spew"
)

type File struct {
	Data   []byte
	Header []byte
	State
	Items  [8][]Item
	Player []Player
}

type State struct {
	Version uint32

	PlayTime int64
	GameTime float32
	Scenario int32
	Money    int32
	FloorID  [16]byte
	AreaID   int32

	PlayerName  [9][32]byte
	PlayerLevel [9]int32
	PlayerParam [9]int32

	Clear               uint8
	MainSceneState      int32
	MiniMapState        int32
	CameraLockAreaIndex int32
	FloorPassiveIndex   int32
	ItemSort            int32

	MachineryState       int32
	MachineryEnergy      int32
	MachineryEnergyMax   int32
	MachineryBoostTime   float32
	MachineryBoostEnable uint8
	MachineryScanTime    int32
	MachineryScanEnable  uint8

	PlayerPosition [3]float32
	PlayerRotY     float32

	TotalExperience int32
	TotalMoney      int32

	BattleCount                int32
	HumanBattleActionCount     int32
	MachineryBattleActionCount int32
	MachineryKillCount         int32
	SetsunaKillCount           int32
	MaxHitCount                int32
	MaxSimultaneousAttackCount int32
	MaxDamage                  int32
	WeakAttackCount            int32
	CriticalCount              int32
	AvoidCount                 int32
	SpritniteCreateCount       int32
	SublimationCount           int32
	SetsunaSystemCount         int32
	CounterCount               int32
	FishingCount               int32
	ShiningPointCount          int32
	ArtifactCreateCount        int32
	MachineryMenuCount         int32
	FoodCount                  int32
	ScanKillCount              int32

	ShopBuyMoney  int32
	ShopSellMoney int32

	FieldMoveDistance      float32
	BattleMoveDistance     float32
	RecoveryHpMoveDistance float32
	RecoveryMpMoveDistance float32
	DebuffSlipMoveDistance float32
	GroundDamageDistance   float32
	GroundDamageTime       float32
}

type Player struct {
	CharacterID      [8]byte
	Index            int32
	TrueName         [32]byte
	InParty          uint8
	FixedPartyMember uint8
	HaveMachinery    uint8
	Machinery        uint8
	MachinerySave    uint8
	FoodCorrectHP    int32
	FoodCorrectMP    int32
	NowHitPoint      int32
	NowMagicPoint    int32
	BuffDebuff       [][16]byte
	Equipment        []int32
}

type Machinery struct {
	ID          int32
	Index       int32
	Name        [32]byte
	NowHitPoint int32
}

type Item struct {
	ID              [14]byte
	UID             int32
	PosessionNumber int32
	SortIndex       int32
	IsBrowsed       uint8
	GetTime         int64
}

const (
	SIG = 20170721
	HDR = 0x510
)

var flags struct {
	key     string
	iv      string
	maxout  bool
	decrypt bool
}

func main() {
	log.SetFlags(0)
	log.SetPrefix("lost-sphear: ")

	flag.StringVar(&flags.key, "key", "G3giuyVjh8F3KZTM", "specify key")
	flag.StringVar(&flags.iv, "iv", "v6LVsqPyB4jm6bgw", "specify iv")
	flag.BoolVar(&flags.maxout, "maxout", false, "maxout")
	flag.BoolVar(&flags.decrypt, "decrypt", false, "output decrypted version")
	flag.Usage = usage
	flag.Parse()
	if flag.NArg() != 2 {
		usage()
	}

	f, err := decode(flag.Arg(0), []byte(flags.key), []byte(flags.iv))
	check(err)

	if flags.maxout {
		maxout(f)
	}

	spew.Dump(f.State)

	var buf []byte
	if flags.decrypt {
		buf = append(buf, f.Header...)
		buf = append(buf, f.Data...)
	} else {
		buf, err = encode(f, []byte(flags.key), []byte(flags.iv))
		check(err)
	}

	err = os.WriteFile(flag.Arg(1), buf, 0644)
	check(err)
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: [options] file")
	flag.PrintDefaults()
	os.Exit(2)
}

func check(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

func decode(name string, key, iv []byte) (*File, error) {
	buf, err := os.ReadFile(name)
	if err != nil {
		return nil, err
	}

	if len(buf) < HDR {
		return nil, fmt.Errorf("file too small")
	}

	f := &File{
		Header: buf[:HDR],
		Data:   buf[HDR:],
	}

	if len(key) > 0 {
		block, err := aes.NewCipher(key)
		if err != nil {
			return nil, err
		}

		dec := make([]byte, len(f.Data))
		if len(dec)%block.BlockSize() != 0 {
			return nil, fmt.Errorf("encrypted file size not aligned")
		}

		cbc := cipher.NewCBCDecrypter(block, iv)
		cbc.CryptBlocks(dec, f.Data)
		copy(f.Data, dec)
	}

	r := bytes.NewReader(f.Data)
	err = binary.Read(r, binary.LittleEndian, &f.State)
	if err != nil {
		return nil, err
	}

	if f.Version != SIG {
		return nil, fmt.Errorf("invalid signature")
	}

	for kind := range f.Items {
		var (
			capacity int32
			item     Item
		)

		binary.Read(r, binary.LittleEndian, &capacity)
		for range capacity {
			binary.Read(r, binary.LittleEndian, &item)
			f.Items[kind] = append(f.Items[kind], item)
		}
	}

	return f, nil
}

func encode(f *File, key, iv []byte) ([]byte, error) {
	block, err := aes.NewCipher(key)
	if err != nil {
		return nil, err
	}

	data := append([]byte{}, f.Data...)
	off := len(data) - 1
	for ; off >= 0; off-- {
		if data[off] != data[off-1] {
			break
		}
	}

	clear(data[off-md5.Size : off])
	sum := md5.Sum(data[:off])
	copy(data[off-md5.Size:], sum[:])

	buf := make([]byte, len(f.Header)+len(data))
	copy(buf, f.Header)

	cbc := cipher.NewCBCEncrypter(block, iv)
	cbc.CryptBlocks(buf[len(f.Header):], data)
	return buf, nil
}

func maxout(f *File) {
	fmt.Println("MAX OUT!")

	f.Money = math.MaxInt32
	f.TotalMoney = math.MaxInt32

	binary.Write(binWriter(f.Data), binary.LittleEndian, &f.State)
}

type binWriter []byte

func (b binWriter) Write(p []byte) (int, error) {
	copy(b[:], p)
	return len(p), nil
}
