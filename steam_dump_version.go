package main

import (
	"bytes"
	"flag"
	"fmt"
	"io/ioutil"
	"os"
	"unicode"
)

var (
	cdefs = flag.Bool("c", false, "generate cdefs")

	status = 0
)

func main() {
	flag.Usage = usage
	flag.Parse()
	if flag.NArg() < 1 {
		usage()
	}

	for _, name := range flag.Args() {
		ek(dump(name))
	}
	os.Exit(status)
}

func ek(err error) {
	if err != nil {
		fmt.Fprintln(os.Stderr, "steam_dump_version:", err)
		status = 1
	}
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: [options] file ...")
	flag.PrintDefaults()
	os.Exit(2)
}

func dump(name string) error {
	defs := []string{
		"STEAM_APPLIST_VERSION",
		"STEAM_APPS_VERSION",
		"STEAM_CLIENT_VERSION",
		"STEAM_CONTROLLER_VERSION",
		"STEAM_FRIENDS_VERSION",
		"STEAM_GAMESERVER_VERSION",
		"STEAM_HTMLSURFACE_VERSION",
		"STEAM_HTTP_VERSION",
		"STEAM_INVENTORY_VERSION",
		"STEAM_MATCHMAKINGSERVERS_VERSION",
		"STEAM_MATCHMAKING_VERSION",
		"STEAM_MUSICREMOTE_VERSION",
		"STEAM_MUSIC_VERSION",
		"STEAM_NETWORKING_VERSION",
		"STEAM_PARENTALSETTINGS_VERSION",
		"STEAM_REMOTESTORAGE_VERSION",
		"STEAM_SCREENSHOTS_VERSION",
		"STEAM_UGC_VERSION",
		"STEAM_UNIFIEDMESSAGES_VERSION",
		"STEAM_USERSTATS_VERSION",
		"STEAM_USER_VERSION",
		"STEAM_UTILS_VERSION",
		"STEAM_VIDEO_VERSION",
		"STEAM_APPTICKET_VERSION",
	}
	vers := []string{
		"STEAMAPPLIST_INTERFACE_VERSION",
		"STEAMAPPS_INTERFACE_VERSION",
		"SteamClient",
		"SteamController",
		"SteamFriends",
		"STEAMGAMESERVER_INTERFACE_VERSION",
		"STEAMHTMLSURFACE_INTERFACE_VERSION",
		"STEAMHTTP_INTERFACE_VERSION",
		"STEAMINVENTORY_INTERFACE_V",
		"SteamMatchMakingServers",
		"SteamMatchMaking",
		"STEAMMUSICREMOTE_INTERFACE_VERSION",
		"STEAMMUSIC_INTERFACE_VERSION",
		"SteamNetworking",
		"STEAMPARENTALSETTINGS_INTERFACE_VERSION",
		"STEAMREMOTESTORAGE_INTERFACE_VERSION",
		"STEAMSCREENSHOTS_INTERFACE_VERSION",
		"STEAMUGC_INTERFACE_VERSION",
		"STEAMUNIFIEDMESSAGES_INTERFACE_VERSION",
		"STEAMUSERSTATS_INTERFACE_VERSION",
		"SteamUser",
		"SteamUtils",
		"STEAMVIDEO_INTERFACE_V",
		"STEAMAPPTICKET_INTERFACE_VERSION",
	}

	buf, err := ioutil.ReadFile(name)
	if err != nil {
		return err
	}

	for n, ver := range vers {
		p := buf
		for len(p) > 0 {
			i := bytes.Index(p, []byte(ver))
			if i < 0 {
				if !*cdefs {
					fmt.Printf("%s not found\n", ver)
				}
				break
			}

			j := i + len(ver)
			num := false
			for j < len(p) && (unicode.IsDigit(rune(p[j])) || p[j] == '_') {
				j++
				if unicode.IsDigit(rune(p[j])) {
					num = true
				}
			}
			if num {
				if *cdefs {
					fmt.Printf("DEFS += -D %s='\"%s\"'\n", defs[n], p[i:j])
				} else {
					fmt.Printf("%s\n", p[i:j])
				}
				break
			}

			p = p[j:]
		}
	}

	return nil
}
