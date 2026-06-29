#pragma once

#if defined(_MSC_VER)
#pragma comment(lib, "dbghelp.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "Advapi32.lib")
#endif

#if defined(__GNUC__) && defined(_WIN32)
#define __USE_MINGW_ANSI_STDIO 1
#endif

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

#if defined(_WIN32)
#include <direct.h>
#include <windows.h>
#include <psapi.h>
#include <dbghelp.h>
#include <winternl.h>
#include <winnt.h>
#if !defined(PATH_MAX)
#define PATH_MAX MAX_PATH
#endif
#else
#include <libgen.h>
#include <dirent.h>
#include <unistd.h>
#include <pthread.h>
#endif

#include "steamtypes.h"
#include "isteamapps.h"
#include "isteaminput.h"
#include "isteamcontroller.h"
#include "isteamremotestorage.h"
#include "isteamuser.h"
#include "isteamuserstats.h"
#include "isteamutils.h"
#include "isteaminventory.h"
#include "isteamhtmlsurface.h"
#include "isteamugc.h"
#include "isteamnetworking.h"
#include "isteamgameserver.h"
#include "isteamgameserverapps.h"
#include "isteamgameserverhttp.h"
#include "isteamgameserverstats.h"
#include "isteamfriends.h"
#include "isteammatchmakingservers.h"
#include "isteammatchmaking.h"
#include "isteamclient.h"
#include "isteamscreenshots.h"
#include "isteamvr.h"
#include "isteamappticket.h"
#include "isteamremoteplay.h"
#include "isteamtv.h"
#include "steam_api.h"
#include "openvr.h"
#include "vtable.h"

typedef struct LogMessage LogMessage;

struct LogMessage {
	char message[4096];
	uint64 tick;
	uint64 numRepeats;
};

typedef struct CSteamFile CSteamFile;

struct CSteamFile {
	char path[PATH_MAX];
	bool isDir;
	int32 size;
};

typedef struct CSteamContext CSteamContext;

struct CSteamContext {
	CSteamBase dummy;
	CSteamApps apps;
	CSteamController controller;
	CSteamUserStats userStats;
	CSteamUser user;
	CSteamUtils utils;
	CSteamRemoteStorage remoteStorage;
	CSteamGameServer gameServer;
	CSteamGameServerApps gameServerApps;
	CSteamGameServerHTTP gameServerHTTP;
	CSteamFriends friends;
	CSteamMatchmaking matchmaking;
	CSteamMatchmakingServers matchmakingServers;
	CSteamScreenshots screenshots;
	CSteamHTTP http;
	CSteamUnifiedMessages unifiedMessages;
	CSteamUGC ugc;
	CSteamAppList appList;
	CSteamMusic music;
	CSteamMusicRemote musicRemote;
	CSteamHTMLSurface htmlSurface;
	CSteamInventory inventory;
	CSteamVideo video;
	CSteamParentalSettings parentalSettings;
	CSteamGameServerStats gameServerStats;
	CSteamNetworking networking;
	CSteamAppTicket appTicket;
	CSteamClient client;
	CSteamInput input;
	CSteamGameSearch gameSearch;
	CSteamParties parties;
	CSteamRemotePlay remotePlay;
	CSteamTV tv;

	uint32 appID;
	uint64 steamPID;
	char currentLanguage[32];
	char availableLanguages[128];

	bool safe;

	HSteamPipe steamPipe;
	HSteamUser steamUser;
	CSteamID steamID;

	uintp ref;

	char rootDir[PATH_MAX];
	char personaName[256];

	CSteamFile *files;
	size_t numFiles;

	void *callbacks[128];
	size_t numCallbacks;

	uint64 ticks;
	int logLevel;
	FILE *logFile;
	LogMessage log[32];
	size_t logSize;

#if defined(_WIN32)
	CRITICAL_SECTION globalLock, logLock;
#else
	pthread_mutex_t globalLock, logLock;
#endif
};

extern CSteamContext ctx;

#ifndef STEAM_APP_ID
#define STEAM_APP_ID 888888
#endif

#ifndef STEAM_USER_VERSION
#define STEAM_USER_VERSION "SteamUser021"
#endif

#ifndef STEAM_FRIENDS_VERSION
#define STEAM_FRIENDS_VERSION "SteamFriends017"
#endif

#ifndef STEAM_UTILS_VERSION
#define STEAM_UTILS_VERSION "SteamUtils010"
#endif

#ifndef STEAM_MATCHMAKING_VERSION
#define STEAM_MATCHMAKING_VERSION "SteamMatchMaking009"
#endif

#ifndef STEAM_MATCHMAKINGSERVERS_VERSION
#define STEAM_MATCHMAKINGSERVERS_VERSION "SteamMatchMakingServers002"
#endif

#ifndef STEAM_USERSTATS_VERSION
#define STEAM_USERSTATS_VERSION "STEAMUSERSTATS_INTERFACE_VERSION011"
#endif

#ifndef STEAM_APPS_VERSION
#define STEAM_APPS_VERSION "STEAMAPPS_INTERFACE_VERSION008"
#endif

#ifndef STEAM_REMOTESTORAGE_VERSION
#define STEAM_REMOTESTORAGE_VERSION "STEAMREMOTESTORAGE_INTERFACE_VERSION014"
#endif

#ifndef STEAM_SCREENSHOTS_VERSION
#define STEAM_SCREENSHOTS_VERSION "STEAMSCREENSHOTS_INTERFACE_VERSION003"
#endif

#ifndef STEAM_HTTP_VERSION
#define STEAM_HTTP_VERSION "STEAMHTTP_INTERFACE_VERSION003"
#endif

#ifndef STEAM_UNIFIEDMESSAGES_VERSION
#define STEAM_UNIFIEDMESSAGES_VERSION "STEAMUNIFIEDMESSAGES_INTERFACE_VERSION001"
#endif

#ifndef STEAM_UGC_VERSION
#define STEAM_UGC_VERSION "STEAMUGC_INTERFACE_VERSION016"
#endif

#ifndef STEAM_APPLIST_VERSION
#define STEAM_APPLIST_VERSION "STEAMAPPLIST_INTERFACE_VERSION001"
#endif

#ifndef STEAM_MUSIC_VERSION
#define STEAM_MUSIC_VERSION "STEAMMUSIC_INTERFACE_VERSION001"
#endif

#ifndef STEAM_MUSICREMOTE_VERSION
#define STEAM_MUSICREMOTE_VERSION "STEAMMUSICREMOTE_INTERFACE_VERSION001"
#endif

#ifndef STEAM_HTMLSURFACE_VERSION
#define STEAM_HTMLSURFACE_VERSION "STEAMHTMLSURFACE_INTERFACE_VERSION_005"
#endif

#ifndef STEAM_INVENTORY_VERSION
#define STEAM_INVENTORY_VERSION "STEAMINVENTORY_INTERFACE_V003"
#endif

#ifndef STEAM_VIDEO_VERSION
#define STEAM_VIDEO_VERSION "STEAMVIDEO_INTERFACE_V001"
#endif

#ifndef STEAM_CONTROLLER_VERSION
#define STEAM_CONTROLLER_VERSION "SteamController008"
#endif

#ifndef STEAM_NETWORKING_VERSION
#define STEAM_NETWORKING_VERSION "SteamNetworking006"
#endif

#ifndef STEAM_PARENTALSETTINGS_VERSION
#define STEAM_PARENTALSETTINGS_VERSION "STEAMPARENTALSETTINGS_INTERFACE_VERSION001"
#endif

#ifndef STEAM_GAMESERVER_VERSION
#define STEAM_GAMESERVER_VERSION "SteamGameServer001"
#endif

#ifndef STEAM_GAMESERVERAPPS_VERSION
#define STEAM_GAMESERVERAPPS_VERSION "SteamGameServerApps001"
#endif

#ifndef STEAM_CLIENT_VERSION
#define STEAM_CLIENT_VERSION "SteamClient020"
#endif

#ifndef STEAM_APP_TICKET_VERSION
#define STEAM_APP_TICKET_VERSION "STEAMAPPTICKET_INTERFACE_VERSION001"
#endif

#ifndef STEAM_INPUT_VERSION
#define STEAM_INPUT_VERSION "SteamInput005"
#endif

#ifndef STEAM_GAMESEARCH_VERSION
#define STEAM_GAMESEARCH_VERSION "SteamMatchGameSearch001"
#endif

#ifndef STEAM_PARTIES_VERSION
#define STEAM_PARTIES_VERSION "SteamParties002"
#endif

#ifndef STEAM_REMOTEPLAY_VERSION
#define STEAM_REMOTEPLAY_VERSION "STEAMREMOTEPLAY_INTERFACE_VERSION001"
#endif

#include "util.h"

extern KV kvUserStats[128];
extern size_t kvUserStatsLen;
