package main

import (
	"bytes"
	"flag"
	"fmt"
	"os"
	"strconv"
	"unicode"
)

var (
	kvdefs = flag.Bool("kv", false, "generate kv definitions")

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
	vers := []struct {
		id    string
		key   string
		value string
	}{
		{"applist", "STEAM_APPLIST_VERSION", "STEAMAPPLIST_INTERFACE_VERSION"},
		{"appticket", "STEAM_APP_TICKET_VERSION", "STEAMAPPTICKET_INTERFACE_VERSION"},
		{"apps", "STEAM_APPS_VERSION", "STEAMAPPS_INTERFACE_VERSION"},
		{"client", "STEAM_CLIENT_VERSION", "SteamClient"},
		{"controller", "STEAM_CONTROLLER_VERSION", "SteamController"},
		{"friends", "STEAM_FRIENDS_VERSION", "SteamFriends"},
		{"gamesearch", "STEAMGAMESEARCH_VERSION", "SteamMatchGameSearch"},
		{"gameserver", "STEAM_GAMESERVER_VERSION", "SteamGameServer"},
		{"gameserverapps", "STEAM_GAMESERVERAPPS_VERSION", "SteamGameServerApps"},
		{"htmlsurface", "STEAM_HTMLSURFACE_VERSION", "STEAMHTMLSURFACE_INTERFACE_VERSION_"},
		{"http", "STEAM_HTTP_VERSION", "STEAMHTTP_INTERFACE_VERSION"},
		{"input", "STEAM_INPUT_VERSION", "SteamInput"},
		{"matchmaking", "STEAM_MATCHMAKING_VERSION", "SteamMatchMaking"},
		{"matchmakingservers", "STEAM_MATCHMAKINGSERVERS_VERSION", "SteamMatchMakingServers"},
		{"music", "STEAM_MUSIC_VERSION", "STEAMMUSIC_INTERFACE_VERSION"},
		{"musicremote", "STEAM_MUSICREMOTE_VERSION", "STEAMMUSICREMOTE_INTERFACE_VERSION"},
		{"networking", "STEAM_NETWORKING_VERSION", "SteamNetworking"},
		{"parentalsettings", "STEAM_PARENTALSETTINGS_VERSION", "STEAMPARENTALSETTINGS_INTERFACE_VERSION"},
		{"parties", "STEAM_PARTIES_VERSION", "SteamParties"},
		{"remoteplay", "STEAM_REMOTEPLAY_VERSION", "STEAMREMOTEPLAY_INTERFACE_VERSION"},
		{"remotestorage", "STEAM_REMOTESTORAGE_VERSION", "STEAMREMOTESTORAGE_INTERFACE_VERSION"},
		{"screenshots", "STEAM_SCREENSHOTS_VERSION", "STEAMSCREENSHOTS_INTERFACE_VERSION"},
		{"ugc", "STEAM_UGC_VERSION", "STEAMUGC_INTERFACE_VERSION"},
		{"unifiedmessages", "STEAM_UNIFIEDMESSAGES_VERSION", "STEAMUNIFIEDMESSAGES_INTERFACE_VERSION"},
		{"user", "STEAM_USER_VERSION", "SteamUser"},
		{"userstats", "STEAM_USERSTATS_VERSION", "STEAMUSERSTATS_INTERFACE_VERSION"},
		{"utils", "STEAM_UTILS_VERSION", "SteamUtils"},
		{"video", "STEAM_VIDEO_VERSION", "STEAMVIDEO_INTERFACE_V"},
		{"tv", "STEAM_TV_VERSION", "STEAMTV_INTERFACE_V"},
	}

	buf, err := os.ReadFile(name)
	if err != nil {
		return err
	}

	for _, v := range vers {
		p := buf
		for len(p) > 0 {
			i := bytes.Index(p, []byte(v.value))
			if i < 0 {
				break
			}

			j := i + len(v.value)
			num := false
			for j < len(p) && (unicode.IsDigit(rune(p[j])) || p[j] == '_') {
				j++
				if unicode.IsDigit(rune(p[j])) {
					num = true
				}
			}

			if num {
				if *kvdefs {
					fmt.Printf("%q: %d,\n", v.id, getnum(string(p[i:j])))
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

func getnum(s string) int {
	for i, r := range s {
		if unicode.IsDigit(r) {
			x, _ := strconv.Atoi(s[i:])
			return x
		}
	}
	return 0
}
