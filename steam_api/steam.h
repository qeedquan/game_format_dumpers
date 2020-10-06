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

#include "isteamapps.h"
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
#include "isteaminput.h"
#include "steam_api.h"
#include "steamtypes.h"
#include "openvr.h"

#define nelem(x) (sizeof(x) / sizeof(x[0]))

#if defined(__GNUC__)
#if defined(_WIN32)
#define PRINTF_LIKE __attribute__((__format__(__MINGW_PRINTF_FORMAT, 1, 2)))
#else
#define PRINTF_LIKE __attribute__((format(printf, 1, 2)))
#endif
#else
#define PRINTF_LIKE
#endif

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
#define STEAM_USER_VERSION "SteamUser018"
#endif

#ifndef STEAM_FRIENDS_VERSION
#define STEAM_FRIENDS_VERSION "SteamFriends015"
#endif

#ifndef STEAM_UTILS_VERSION
#define STEAM_UTILS_VERSION "SteamUtils007"
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
#define STEAM_APPS_VERSION "STEAMAPPS_INTERFACE_VERSION007"
#endif

#ifndef STEAM_REMOTESTORAGE_VERSION
#define STEAM_REMOTESTORAGE_VERSION "STEAMREMOTESTORAGE_INTERFACE_VERSION013"
#endif

#ifndef STEAM_SCREENSHOTS_VERSION
#define STEAM_SCREENSHOTS_VERSION "STEAMSCREENSHOTS_INTERFACE_VERSION002"
#endif

#ifndef STEAM_HTTP_VERSION
#define STEAM_HTTP_VERSION "STEAMHTTP_INTERFACE_VERSION002"
#endif

#ifndef STEAM_UNIFIEDMESSAGES_VERSION
#define STEAM_UNIFIEDMESSAGES_VERSION "STEAMUNIFIEDMESSAGES_INTERFACE_VERSION001"
#endif

#ifndef STEAM_UGC_VERSION
#define STEAM_UGC_VERSION "STEAMUGC_INTERFACE_VERSION007"
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
#define STEAM_HTMLSURFACE_VERSION "STEAMHTMLSURFACE_INTERFACE_VERSION_003"
#endif

#ifndef STEAM_INVENTORY_VERSION
#define STEAM_INVENTORY_VERSION "STEAMINVENTORY_INTERFACE_V001"
#endif

#ifndef STEAM_VIDEO_VERSION
#define STEAM_VIDEO_VERSION "STEAMVIDEO_INTERFACE_V001"
#endif

#ifndef STEAM_CONTROLLER_VERSION
#define STEAM_CONTROLLER_VERSION "STEAMCONTROLLER_INTERFACE_V001"
#endif

#ifndef STEAM_NETWORKING_VERSION
#define STEAM_NETWORKING_VERSION "SteamNetworking005"
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
#define STEAM_CLIENT_VERSION "SteamClient017"
#endif

#ifndef STEAM_APP_TICKET_VERSION
#define STEAM_APP_TICKET_VERSION "STEAMAPPTICKET_INTERFACE_VERSION001"
#endif

#ifndef STEAM_INPUT_VERSION
#define STEAM_INPUT_VERSION "SteamInput001"
#endif

#ifdef WIN32
#define stat _stat
#endif

int xstat(const char *filename, struct stat *st);
FILE *xfopen(const char *filename, const char *mode);
void *xrealloc(void *ptr, size_t size);
void *xreallocarray(void *optr, size_t nmemb, size_t size);
void mkdirp(char *path);

CSteamFile *getAllFileListing(const char *dir, int32 *numFiles);

int parseSteamVersion(const char *s);

void getEnvStr(char *buf, size_t len, const char *env, const char *def);
int getEnvInt(const char *env, int def);

#if defined(_WIN32)
DWORD getRegDWORD(HKEY hkey, const char *subkey, const char *data, DWORD def);
char *basename(char *path);
char *dirname(char *path);
#define acquireLock EnterCriticalSection
#define releaseLock LeaveCriticalSection
#else
#define acquireLock pthread_mutex_lock
#define releaseLock pthread_mutex_unlock
#endif

uint64 msticks(void);

PRINTF_LIKE static inline void
xprintf(const char *fmt, ...)
{
	char str[4096];
	va_list ap;

	va_start(ap, fmt);
	vsnprintf(str, sizeof(str), fmt, ap);
	va_end(ap);

	fprintf(stdout, "%s", str);
	fflush(stdout);
	if (ctx.logFile) {
		fprintf(ctx.logFile, "%s", str);
		fflush(ctx.logFile);
	}
}

PRINTF_LIKE static inline void
xlogf(const char *fmt, ...)
{
	uint64 curtick, maxtick, delta;
	char str[4096];
	bool found;
	va_list ap;
	size_t i, idx;

	va_start(ap, fmt);
	vsnprintf(str, sizeof(str), fmt, ap);
	va_end(ap);

	if (ctx.logLevel >= 10) {
		xprintf("%s", str);
		return;
	}

	curtick = msticks();
	maxtick = 0;

	acquireLock(&ctx.logLock);
	found = false;
	idx = ctx.logSize;
	for (i = 0; i < ctx.logSize;) {
		if (!found && !strcmp(ctx.log[i].message, str)) {
			found = true;
			ctx.log[i].numRepeats++;
		}
		delta = curtick - ctx.log[i].tick;
		if (maxtick < delta) {
			idx = i;
			maxtick = delta;
		}
		if (delta >= 1000 || ctx.log[i].numRepeats >= 1000) {
			if (ctx.log[i].numRepeats > 0)
				xprintf("%s (repeated %llu times)\n", ctx.log[i].message, ctx.log[i].numRepeats);
			ctx.log[i] = ctx.log[--ctx.logSize];
		} else {
			ctx.log[i].tick = curtick;
			i++;
		}
	}
	if (idx >= nelem(ctx.log))
		idx = 0;

	if (!found) {
		if (ctx.logSize < nelem(ctx.log))
			ctx.logSize++;
		else if (ctx.log[idx].numRepeats > 0)
			xprintf("%s (repeated %llu times)\n", ctx.log[idx].message, ctx.log[idx].numRepeats);

		snprintf(ctx.log[idx].message, sizeof(ctx.log[idx].message), "%s", str);
		ctx.log[idx].numRepeats = 0;
		ctx.log[idx].tick = curtick;
		xprintf("%s", str);
	}
	releaseLock(&ctx.logLock);
}
