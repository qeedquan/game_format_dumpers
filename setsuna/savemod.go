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
}

type State struct {
	Version uint32

	PlayTime         int64
	Money            uint32
	EventProgression int32

	EventFlag     [2500]int32
	EventVariable [2500]float32

	CookingItemID       int32
	ContinuationCount   int32
	SaveFloor           [10]byte
	SavePosition        [3]float32
	SaveForward         [3]float32
	AirshipPosition     [3]float32
	AirshipForward      [3]float32
	OptionData          uint32
	MilitaryServiceData MilitaryServiceData

	ShopSellData     [16][512]uint32
	BraveStoryData   int32
	ShiningPointData [300][3]int32

	HaveItemInfo [4096]HaveItemInfo

	ConsumeItemSortData   [256]int16
	AccessoryItemSortData [512]int16
	MateriaItemSortData   [512]int16
	EventItemSortData     [256]int16

	WeaponItemSortData_PLAYER     [32]int16
	WeaponItemSortData_SETSUNA    [32]int16
	WeaponItemSortData_TSUKUSHI   [32]int16
	WeaponItemSortData_YOMI       [32]int16
	WeaponItemSortData_KISHIL     [32]int16
	WeaponItemSortData_SION       [32]int16
	WeaponItemSortData_GRIMREAPER [32]int16

	Skip [13420]byte

	CharacterStatus [7]CharacterStatus

	PartyMember [7]int32
	FieldMember [3]int32
	Debuff      [7]int32

	CharacterName [7][32]byte
	AirshipName   [32]byte
}

type BraveStoryData struct {
	GetAccessory    [150]BraveStorySaveData
	ArriveGeography [80]BraveStorySaveData
	GetItem         [500]BraveStorySaveData
	GetMateria      [300]BraveStorySaveData
	GetWeapon       [20]BraveStorySaveData
	TalkShop        [130]BraveStorySaveData
	EncountMonster  [130]EncountMonsterSaveData
	Person          [50]BraveStorySaveData
	Memo            [100]BraveStorySaveData
	Note            [100]BraveStorySaveData
	Coop            [200]BraveStorySaveData
	Sublimation     [40]BraveStorySaveData
	SetsunaSystem   [300]BraveStorySaveData
}

type EncountMonsterSaveData struct {
	DropFlag int32
	BraveStorySaveData
}

type BraveStorySaveData struct {
	IsOpen uint8
	IsNew  uint8
}

type MilitaryServiceData struct {
	BattleCount            uint32
	MaxDamage              uint32
	SetsunaCount           uint32
	SublimationCount       uint32
	SearchPointCount       uint32
	MealCount              uint32
	SaveCount              uint32
	CommandSublimateCount  int32
	PassiveSublimateCount  int32
	CoopSetsunaSystemCount int32
	JustKillCount          int32
	OverKillCount          int32
	KillFlag               int32
	GetItemBoxCount        uint32
	Reserve                [10]uint32
}

type HaveItemInfo struct {
	UniqueId int16
	HaveNum  uint16
	ItemId   int32
	Values   [10]int32
	ItemName [48]byte
	IsNew    uint8
}

type MaterialSlot struct {
	SlotType     int16
	UniqueItemID int16
}

type CharacterEquip struct {
	WeaponUniqueItemId    int16
	AccessoryUniqueItemId int16
}

type CharacterMateria struct {
	MaterialSlot [12]MaterialSlot
}

type CharacterStatus struct {
	BaseStatus  CharacterLvParameter
	FluStatus   FluctuateStatus
	Equip       CharacterEquip
	Materia     CharacterMateria
	MemberState int32
	Exp         int32
}

type CharacterLvParameter struct {
	Id      int32
	NeedExp int32
	MaxHp   int32
	Lv      int16
	MaxMp   int16
	Power   int16
	Magic   int16
}

type FluctuateStatus struct {
	Hp int32
	Mp int16
}

const (
	SIG = 20160322
	HDR = 0xc0
)

var flags struct {
	key     string
	iv      string
	maxout  bool
	decrypt bool
}

func main() {
	log.SetFlags(0)
	log.SetPrefix("setsuna: ")

	flag.StringVar(&flags.key, "key", "Ao2gH1hHIZo29kid", "specify key")
	flag.StringVar(&flags.iv, "iv", "w6S7PEvZBz7kxOYv", "specify iv")
	flag.BoolVar(&flags.maxout, "maxout", false, "maxout")
	flag.BoolVar(&flags.decrypt, "decrypt", false, "output decrypted version")
	flag.Usage = usage
	flag.Parse()
	if flag.NArg() != 2 {
		usage()
	}

	f, err := decode(flag.Arg(0), []byte(flags.key), []byte(flags.iv))
	if err != nil {
		log.Fatal(err)
	}

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
		fmt.Printf("%d\n", f.Version)
		return nil, fmt.Errorf("invalid signature")
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

	f.Money = math.MaxUint32
	for i := range f.CharacterStatus {
		f.CharacterStatus[i].BaseStatus.Lv = 99
		f.CharacterStatus[i].BaseStatus.MaxHp = 999
		f.CharacterStatus[i].BaseStatus.MaxMp = 999
		f.CharacterStatus[i].BaseStatus.Power = 9999
		f.CharacterStatus[i].BaseStatus.Magic = 9999

		f.CharacterStatus[i].FluStatus.Hp = 999
		f.CharacterStatus[i].FluStatus.Mp = 999
	}

	binary.Write(binWriter(f.Data), binary.LittleEndian, &f.State)
}

type binWriter []byte

func (b binWriter) Write(p []byte) (int, error) {
	copy(b[:], p)
	return len(p), nil
}
