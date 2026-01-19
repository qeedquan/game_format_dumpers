#include "steam.h"

CSteamContext ctx;
EXPORT ISteamGameServer *g_pSteamClientGameServer = &ctx.gameServer;

KV kvUserStats[128];
size_t kvUserStatsLen;

S_CLASSAPI void S_CLASSCALLTYPE
logCall(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
traceCall(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
#if defined(_WIN32)
	DebugBreak();
#else
	__builtin_trap();
#endif
}

void
initSteamBase(CSteamBase *p)
{
	size_t i;

	p->vptr = p->vtable;
	for (i = 0; i < nelem(p->vtable); i++)
		p->vtable[i] = traceCall;
}

void *
createInterface(const char *name)
{
	static const Vtable vtables[] = {
	    {"STEAMAPPS", vtable_ISteamApps, &ctx.apps, &ctx.apps.base},
	    {"SteamInput", vtable_ISteamInput, &ctx.input, &ctx.input.base},
	    {"STEAMMUSIC", vtable_ISteamMusic, &ctx.music, &ctx.music.base},
	    {"STEAMREMOTESTORAGE", vtable_ISteamRemoteStorage, &ctx.remoteStorage, &ctx.remoteStorage.base},
	    {"STEAMAPPTICKET", vtable_ISteamAppTicket, &ctx.appTicket, &ctx.appTicket.base},
	    {"STEAMSCREENSHOTS", vtable_ISteamScreenshot, &ctx.screenshots, &ctx.screenshots.base},
	    {"SteamUtils", vtable_ISteamUtils, &ctx.utils, &ctx.utils.base},
	    {"STEAMUSERSTATS", vtable_ISteamUserStats, &ctx.userStats, &ctx.userStats.base},
	    {"SteamUser", vtable_ISteamUser, &ctx.user, &ctx.user.base},
	    {"STEAMINVENTORY", vtable_ISteamInventory, &ctx.inventory, &ctx.inventory.base},
	    {"SteamController", vtable_ISteamController, &ctx.controller, &ctx.controller.base},
	    {"STEAMCONTROLLER_INTERFACE_VERSION", vtable_ISteamController, &ctx.controller, &ctx.controller.base},
	    {"SteamFriends", vtable_ISteamFriends, &ctx.friends, &ctx.friends.base},
	    {"SteamMatchMakingServers", vtable_ISteamMatchmakingServers, &ctx.matchmaking, &ctx.matchmaking.base},
	    {"SteamMatchMaking", vtable_ISteamMatchmaking, &ctx.matchmaking, &ctx.matchmaking.base},
	    {"SteamNetworking", vtable_ISteamNetworking, &ctx.networking, &ctx.networking.base},
	    {"STEAMHTTP", vtable_ISteamHTTP, &ctx.http, &ctx.http.base},
	    {"STEAMUNIFIEDMESSAGES", vtable_ISteamUnifiedMessages, &ctx.unifiedMessages, &ctx.unifiedMessages.base},
	    {"STEAMUGC", vtable_ISteamUGC, &ctx.ugc, &ctx.ugc.base},
	    {"STEAMAPPLIST", vtable_ISteamAppList, &ctx.appList, &ctx.appList.base},
	    {"STEAMHTMLSURFACE", vtable_ISteamHTMLSurface, &ctx.htmlSurface, &ctx.htmlSurface.base},
	    {"STEAMVIDEO", NULL, &ctx.video, &ctx.video.base},
	    {"SteamClient", vtable_ISteamClient, &ctx.client, &ctx.client.base},
	    {"SteamMatchGameSearch", NULL, &ctx.gameSearch, &ctx.gameSearch.base},
	    {"SteamParties", NULL, &ctx.parties, &ctx.parties.base},
	    {"STEAMREMOTEPLAY", NULL, &ctx.remotePlay, &ctx.remotePlay.base},
	    {"STEAMPARENTALSETTINGS", vtable_ISteamParentalSettings, &ctx.parentalSettings, &ctx.parentalSettings.base},
	    {"STEAMMUSICREMOTE", vtable_ISteamMusicRemote, &ctx.musicRemote, &ctx.musicRemote.base},
	    {"STEAMTV", vtable_ISteamTV, &ctx.tv, &ctx.tv.base},
	};

	VtableEntry *entry, *result;
	CSteamBase *base;
	int version;
	size_t i;

	for (i = 0; i < nelem(vtables); i++) {
		if (!strstr(name, vtables[i].prefix))
			continue;

		entry = vtables[i].entries;
		base = vtables[i].base;

		if (entry == NULL) {
			xlogf("WARNING: UNHANDLED INTERFACE CREATION FOR '%s'\n", name);
			return vtables[i].ctx;
		}

		version = parseSteamVersion(name);
		if (name != base->version)
			snprintf(base->version, sizeof(base->version), "%s", name);
		initSteamBase(base);

		do {
			result = entry;
			if (entry->version == version)
				break;

			entry++;
		} while (entry->table != NULL);
		memcpy(base->vtable, result->table, result->tablesize);

		if (entry->table == NULL)
			xlogf("WARNING: MISMATCH VERSION USED FOR '%s'\n", name);

		return vtables[i].ctx;
	}

	xlogf("FAILED TO FIND INTERFACE '%s'\n", name);
	return &ctx.dummy;
}

void
initSteamDummy(void)
{
	CSteamBase *p = &ctx.dummy;
	size_t i;

	for (i = 0; i < nelem(p->vtable); i++)
		p->vtable[i] = logCall;
}

void
initSteamContext(void)
{
	CSteamContext *p = &ctx;
	char logFileName[PATH_MAX];

	snprintf(p->currentLanguage, sizeof(p->currentLanguage), "english");
	snprintf(p->availableLanguages, sizeof(p->availableLanguages), "english,japanese");
	getEnvStr(p->rootDir, sizeof(p->rootDir), "STEAM_SAVEDIR", "save");
	getEnvStr(p->personaName, sizeof(p->personaName), "STEAM_PERSONA_NAME", "steamer");
	p->steamPipe = 1;
	p->steamID.m_gameID = 123;
	p->ref = 1;

	p->steamUser = getEnvInt("STEAM_USER_ID", 123);
	p->appID = getEnvInt("STEAM_APP_ID", STEAM_APP_ID);
#if defined(_WIN32)
	p->steamPID = getRegDWORD(HKEY_CURRENT_USER, "Software\\Valve\\Steam\\ActiveProcess", "pid", 0);
#endif
	if (p->steamPID == 0)
		p->steamPID = getEnvInt("STEAM_PID", 777777);
	p->logLevel = getEnvInt("STEAM_LOG_LEVEL", 100);
	getEnvStr(logFileName, sizeof(logFileName), "STEAM_LOGFILE", "");
	if (logFileName[0] != '\0')
		p->logFile = fopen(logFileName, "wt");
}

void
initSteamVersion(void)
{
	getEnvStr(ctx.client.base.version, sizeof(ctx.client.base.version), "STEAM_CLIENT_VERSION", STEAM_CLIENT_VERSION);
	getEnvStr(ctx.utils.base.version, sizeof(ctx.utils.base.version), "STEAM_UTILS_VERSION", STEAM_UTILS_VERSION);
	getEnvStr(ctx.remoteStorage.base.version, sizeof(ctx.remoteStorage.base.version), "STEAM_REMOTESTORAGE_VERSION", STEAM_REMOTESTORAGE_VERSION);
	getEnvStr(ctx.userStats.base.version, sizeof(ctx.userStats.base.version), "STEAM_USERSTATS_VERSION", STEAM_USERSTATS_VERSION);
	getEnvStr(ctx.user.base.version, sizeof(ctx.user.base.version), "STEAM_USER_VERSION", STEAM_USER_VERSION);
	getEnvStr(ctx.controller.base.version, sizeof(ctx.controller.base.version), "STEAM_CONTROLLER_VERSION", STEAM_CONTROLLER_VERSION);
	getEnvStr(ctx.apps.base.version, sizeof(ctx.apps.base.version), "STEAM_APPS_VERSION", STEAM_APPS_VERSION);
	getEnvStr(ctx.video.base.version, sizeof(ctx.video.base.version), "STEAM_VIDEO_VERSION", STEAM_VIDEO_VERSION);
	getEnvStr(ctx.friends.base.version, sizeof(ctx.friends.base.version), "STEAM_FRIENDS_VERSION", STEAM_FRIENDS_VERSION);
	getEnvStr(ctx.htmlSurface.base.version, sizeof(ctx.htmlSurface.base.version), "STEAM_HTMLSURFACE_VERSION", STEAM_HTMLSURFACE_VERSION);
	getEnvStr(ctx.inventory.base.version, sizeof(ctx.inventory.base.version), "STEAM_INVENTORY_VERSION", STEAM_INVENTORY_VERSION);
	getEnvStr(ctx.music.base.version, sizeof(ctx.music.base.version), "STEAM_MUSIC_VERSION", STEAM_MUSIC_VERSION);
	getEnvStr(ctx.musicRemote.base.version, sizeof(ctx.musicRemote.base.version), "STEAM_MUSICREMOTE_VERSION", STEAM_MUSICREMOTE_VERSION);
	getEnvStr(ctx.appList.base.version, sizeof(ctx.appList.base.version), "STEAM_APPLIST_VERSION", STEAM_APPLIST_VERSION);
	getEnvStr(ctx.ugc.base.version, sizeof(ctx.ugc.base.version), "STEAM_UGC_VERSION", STEAM_UGC_VERSION);
	getEnvStr(ctx.http.base.version, sizeof(ctx.http.base.version), "STEAM_HTTP_VERSION", STEAM_HTTP_VERSION);
	getEnvStr(ctx.matchmaking.base.version, sizeof(ctx.matchmaking.base.version), "STEAM_MATCHMAKING_VERSION", STEAM_MATCHMAKING_VERSION);
	getEnvStr(ctx.matchmakingServers.base.version, sizeof(ctx.matchmakingServers.base.version), "STEAM_MATCHMAKINGSERVERS_VERSION", STEAM_MATCHMAKINGSERVERS_VERSION);
	getEnvStr(ctx.unifiedMessages.base.version, sizeof(ctx.unifiedMessages.base.version), "STEAM_UNIFIEDMESSAGES_VERSION", STEAM_UNIFIEDMESSAGES_VERSION);
	getEnvStr(ctx.networking.base.version, sizeof(ctx.networking.base.version), "STEAM_NETWORKING_VERSION", STEAM_NETWORKING_VERSION);
	getEnvStr(ctx.parentalSettings.base.version, sizeof(ctx.parentalSettings.base.version), "STEAM_PARENTALSETTINGS_VERSION", STEAM_PARENTALSETTINGS_VERSION);
	getEnvStr(ctx.screenshots.base.version, sizeof(ctx.screenshots.base.version), "STEAM_SCREENSHOTS_VERSION", STEAM_SCREENSHOTS_VERSION);
	getEnvStr(ctx.gameServer.base.version, sizeof(ctx.gameServer.base.version), "STEAM_GAMESERVER_VERSION", STEAM_GAMESERVER_VERSION);
	getEnvStr(ctx.gameServerApps.base.version, sizeof(ctx.gameServerApps.base.version), "STEAM_GAMESERVERAPPS_VERSION", STEAM_GAMESERVERAPPS_VERSION);
	getEnvStr(ctx.appTicket.base.version, sizeof(ctx.appTicket.base.version), "STEAM_APP_TICKET_VERSION", STEAM_APP_TICKET_VERSION);
	getEnvStr(ctx.input.base.version, sizeof(ctx.input.base.version), "STEAM_INPUT_VERSION", STEAM_INPUT_VERSION);
	getEnvStr(ctx.gameSearch.base.version, sizeof(ctx.gameSearch.base.version), "STEAM_GAMESEARCH_VERSION", STEAM_GAMESEARCH_VERSION);
	getEnvStr(ctx.parties.base.version, sizeof(ctx.parties.base.version), "STEAM_PARTIES_VERSION", STEAM_PARTIES_VERSION);
	getEnvStr(ctx.remotePlay.base.version, sizeof(ctx.remotePlay.base.version), "STEAM_REMOTEPLAY_VERSION", STEAM_REMOTEPLAY_VERSION);
}

void
initSteamInterface(void)
{
	initSteamDummy();

	initSteamBase(&ctx.gameSearch.base);
	initSteamBase(&ctx.parties.base);
	initSteamBase(&ctx.gameSearch.base);
	initSteamBase(&ctx.remotePlay.base);
	initSteamBase(&ctx.gameServer.base);
	initSteamBase(&ctx.gameServerApps.base);
	initSteamBase(&ctx.video.base);

	createInterface(ctx.apps.base.version);
	createInterface(ctx.remoteStorage.base.version);
	createInterface(ctx.music.base.version);
	createInterface(ctx.input.base.version);
	createInterface(ctx.appTicket.base.version);
	createInterface(ctx.screenshots.base.version);
	createInterface(ctx.utils.base.version);
	createInterface(ctx.user.base.version);
	createInterface(ctx.userStats.base.version);
	createInterface(ctx.inventory.base.version);
	createInterface(ctx.controller.base.version);
	createInterface(ctx.client.base.version);
	createInterface(ctx.appList.base.version);
	createInterface(ctx.parentalSettings.base.version);
	createInterface(ctx.networking.base.version);
	createInterface(ctx.friends.base.version);
	createInterface(ctx.unifiedMessages.base.version);
	createInterface(ctx.ugc.base.version);
	createInterface(ctx.htmlSurface.base.version);
	createInterface(ctx.musicRemote.base.version);
	createInterface(ctx.matchmakingServers.base.version);
	createInterface(ctx.http.base.version);
}

CONSTRUCTOR void
initSteam(void)
{
	char str[128];

#if defined(_WIN32)
	InitializeCriticalSection(&ctx.globalLock);
	InitializeCriticalSection(&ctx.logLock);
#else
	pthread_mutex_init(&ctx.globalLock, NULL);
	pthread_mutex_init(&ctx.logLock, NULL);
#endif
	initSteamContext();
	xlogf("%s()\n", __func__);
	initSteamVersion();
	initSteamInterface();

	getEnvStr(str, sizeof(str), "STEAM_USER_STATS_FILE", "userstats.txt");
	loadKV(str, kvUserStats, nelem(kvUserStats), &kvUserStatsLen);
}

S_API bool S_CALLTYPE
SteamAPI_RestartAppIfNecessary(uint32 unOwnAppID)
{
	xlogf("%s(unOwnAppID = %d)\n", __func__, unOwnAppID);
	return false;
}

S_API ISteamUserStats *S_CALLTYPE
SteamUserStats(void)
{
	ISteamUserStats *userStats = &ctx.userStats;
	xlogf("%s() -> %p\n", __func__, userStats);
	return userStats;
}

S_API ISteamUser *S_CALLTYPE
SteamUser(void)
{
	ISteamUser *user = &ctx.user;
	xlogf("%s() -> %p\n", __func__, user);
	return user;
}

S_API ISteamUtils *S_CALLTYPE
SteamUtils(void)
{
	CSteamUtils *utils = &ctx.utils;
	xlogf("%s() -> %p\n", __func__, utils);
	return utils;
}

S_API ISteamApps *S_CALLTYPE
SteamApps(void)
{
	CSteamApps *apps = &ctx.apps;
	xlogf("%s() -> %p\n", __func__, apps);
	return apps;
}

S_API ISteamRemoteStorage *S_CALLTYPE
SteamRemoteStorage(void)
{
	ISteamRemoteStorage *remoteStorage = &ctx.remoteStorage;
	xlogf("%s() -> %p\n", __func__, remoteStorage);
	return remoteStorage;
}

S_API ISteamController *S_CALLTYPE
SteamController(void)
{
	CSteamController *controller = &ctx.controller;
	xlogf("%s() -> %p\n", __func__, controller);
	return controller;
}

S_API ISteamFriends *S_CALLTYPE
SteamFriends(void)
{
	CSteamFriends *friends = &ctx.friends;
	xlogf("%s() -> %p\n", __func__, friends);
	return friends;
}

S_API ISteamClient *S_CALLTYPE
SteamClient(void)
{
	CSteamClient *client = &ctx.client;
	xlogf("%s() -> %p\n", __func__, client);
	return client;
}

S_API ISteamScreenshots *S_CALLTYPE
SteamScreenshots(void)
{
	CSteamScreenshots *screenshots = &ctx.screenshots;
	xlogf("%s() -> %p\n", __func__, screenshots);
	return screenshots;
}

S_API ISteamMatchmaking *S_CALLTYPE
SteamMatchmaking(void)
{
	CSteamMatchmaking *matchmaking = &ctx.matchmaking;
	xlogf("%s() -> %p\n", __func__, matchmaking);
	return matchmaking;
}

S_API ISteamNetworking *S_CALLTYPE
SteamNetworking(void)
{
	CSteamNetworking *networking = &ctx.networking;
	xlogf("%s() -> %p\n", __func__, networking);
	return networking;
}

S_API ISteamGameServer *S_CALLTYPE
SteamGameServer(void)
{
	ISteamGameServer *gameServer = &ctx.gameServer;
	xlogf("%s() -> %p\n", __func__, gameServer);
	return gameServer;
}

S_API ISteamGameServerApps *S_CALLTYPE
SteamGameServerApps(void)
{
	ISteamGameServerApps *gameServerApps = &ctx.gameServerApps;
	xlogf("%s() -> %p\n", __func__, gameServerApps);
	return gameServerApps;
}

S_API ISteamGameServerHTTP *S_CALLTYPE
SteamGameServerHTTP(void)
{
	ISteamGameServerHTTP *gameServerHTTP = &ctx.gameServerHTTP;
	xlogf("%s() -> %p\n", __func__, gameServerHTTP);
	return gameServerHTTP;
}

S_API ISteamMusic *S_CALLTYPE
SteamMusic(void)
{
	ISteamMusic *music = &ctx.music;
	xlogf("%s() -> %p\n", __func__, music);
	return music;
}

S_API ISteamMusicRemote *S_CALLTYPE
SteamMusicRemote(void)
{
	ISteamMusicRemote *musicRemote = &ctx.musicRemote;
	xlogf("%s() -> %p\n", __func__, musicRemote);
	return musicRemote;
}

S_API ISteamVideo *S_CALLTYPE
SteamVideo(void)
{
	ISteamVideo *video = &ctx.video;
	xlogf("%s() -> %p\n", __func__, video);
	return video;
}

S_API ISteamUGC *S_CALLTYPE
SteamUGC(void)
{
	ISteamUGC *ugc = &ctx.ugc;
	xlogf("%s() -> %p\n", __func__, ugc);
	return ugc;
}

S_API ISteamHTTP *S_CALLTYPE
SteamHTTP(void)
{
	ISteamHTTP *http = &ctx.http;
	xlogf("%s() -> %p\n", __func__, http);
	return http;
}

S_API ISteamHTMLSurface *S_CALLTYPE
SteamHTMLSurface(void)
{
	ISteamHTMLSurface *htmlSurface = &ctx.htmlSurface;
	xlogf("%s() -> %p\n", __func__, htmlSurface);
	return htmlSurface;
}

S_API ISteamInventory *S_CALLTYPE
SteamInventory(void)
{
	ISteamInventory *inventory = &ctx.inventory;
	xlogf("%s() -> %p\n", __func__, inventory);
	return inventory;
}

S_API ISteamMatchmakingServers *S_CALLTYPE
SteamMatchmakingServers(void)
{
	ISteamMatchmakingServers *matchmakingServers = &ctx.matchmakingServers;
	xlogf("%s() -> %p\n", __func__, matchmakingServers);
	return matchmakingServers;
}

S_API ISteamAppList *S_CALLTYPE
SteamAppList(void)
{
	ISteamAppList *appList = &ctx.appList;
	xlogf("%s() -> %p\n", __func__, appList);
	return appList;
}

S_API ISteamUnifiedMessages *S_CALLTYPE
SteamUnifiedMessages(void)
{
	ISteamUnifiedMessages *unifiedMessages = &ctx.unifiedMessages;
	xlogf("%s() -> %p\n", __func__, unifiedMessages);
	return unifiedMessages;
}

S_API HSteamUser S_CALLTYPE
Steam_GetHSteamUserCurrent(void)
{
	xlogf("%s()\n", __func__);
	return SteamAPI_GetHSteamUser();
}

S_API const char *S_CALLTYPE
SteamAPI_GetSteamInstallPath(void)
{
	xlogf("%s() -> %s\n", __func__, ctx.rootDir);
	return ctx.rootDir;
}

S_API bool S_CALLTYPE
SteamAPI_Init(void)
{
	xlogf("%s()\n", __func__);
	ctx.ref++;
	return true;
}

S_API bool S_CALLTYPE
SteamAPI_InitSafe(void)
{
	xlogf("%s()\n", __func__);
	ctx.ref++;
	ctx.safe = true;
	return true;
}

S_API int S_CALLTYPE
SteamInternal_SteamAPI_Init(const char *pszVersion, int arg)
{
	xlogf("%s(pszVersion=%s, arg=%d)\n", __func__, pszVersion, arg);
	createInterface(pszVersion);
	return 0;
}

S_API void S_CALLTYPE
Steam_RegisterInterfaceFuncs(void *hModule)
{
	xlogf("%s(hModule = %p)\n", __func__, hModule);
}

S_API void S_CALLTYPE
SteamAPI_WriteMiniDump(uint32 uStructuredExceptionCode, void *pvExceptionInfo, uint32 uBuildID)
{
	xlogf("%s(uStructuredExceptionCode = %d, pvExceptionInfo = %p, uBuildID = %d)\n", __func__, uStructuredExceptionCode, pvExceptionInfo, uBuildID);
}

S_API void S_CALLTYPE
SteamAPI_SetMiniDumpComment(const char *pchMsg)
{
	xlogf("%s(pchMsg = %s)\n", __func__, pchMsg);
}

S_API void S_CALLTYPE
SteamAPI_Shutdown(void)
{
	xlogf("%s()\n", __func__);
	ctx.ref++;
}

S_API void S_CALLTYPE
SteamAPI_RegisterCallback(CCallbackBase *pCallback, int iCallback)
{
	xlogf("%s(pCallback = %p, iCallback = %d) (numCallbacks = %zu)\n", __func__, pCallback, iCallback, ctx.numCallbacks + 1);
	if (ctx.numCallbacks < nelem(ctx.callbacks))
		ctx.callbacks[ctx.numCallbacks++] = pCallback;
}

S_API void S_CALLTYPE
SteamAPI_UnregisterCallback(CCallbackBase *pCallback)
{
	xlogf("%s(pCallback = %p)\n", __func__, pCallback);
}

S_API void S_CALLTYPE
SteamAPI_RunCallbacks(void)
{
	if (!getEnvInt("STEAM_API_RUN_CALLBACKS", 1))
		return;
}

S_API void S_CALLTYPE
Steam_RunCallbacks(void)
{
	SteamAPI_RunCallbacks();
}

S_API void S_CALLTYPE
SteamAPI_SetTryCatchCallbacks(bool enable)
{
	xlogf("%s(enable = %d)\n", __func__, enable);
}

S_API ISteamClient *S_CALLTYPE
SteamInternal_CreateInterface(const char *ver, bool *err)
{
	xlogf("%s(ver = %s, err = %p) -> %p\n", __func__, ver, &ctx.client, err);
	initSteamVersion();
	snprintf(ctx.client.base.version, sizeof(ctx.client.base.version), "%s", ver);
	initSteamInterface();
	return &ctx.client;
}

S_API ISteamClient *S_CALLTYPE
CreateInterface(const char *ver, bool *err)
{
	xlogf("%s(ver = %s, err = %p)\n", __func__, ver, err);
	return SteamInternal_CreateInterface(ver, err);
}

S_API void *S_CALLTYPE
SteamInternal_FindOrCreateUserInterface(HSteamUser hSteamUser, const char *pszVersion)
{
	void *ptr;

	ptr = createInterface(pszVersion);
	if (ptr == &ctx.dummy)
		xlogf("%s(hSteamUser = %d, pszVersion = %s) -> %p (DUMMY)\n", __func__, hSteamUser, pszVersion, ptr);
	else
		xlogf("%s(hSteamUser = %d, pszVersion = %s) -> %p\n", __func__, hSteamUser, pszVersion, ptr);

	return ptr;
}

S_API void *S_CALLTYPE
SteamInternal_FindOrCreateGameServerInterface(HSteamUser hSteamUser, const char *pszVersion)
{
	xlogf("%s(hSteamUser = %d, pszVersion = %s)\n", __func__, hSteamUser, pszVersion);
	return SteamInternal_FindOrCreateUserInterface(hSteamUser, pszVersion);
}

S_API void *S_CALLTYPE
SteamInternal_ContextInit(SteamInternalContext *self)
{
	xlogf("%s(self = %p) (init = %p, ref = %llu [%llu], ctx = %p)\n", __func__,
	      self, self->init, (uvlong)self->iref, (uvlong)ctx.ref, &self->ctx);
	if (self->iref != ctx.ref) {
		self->init(&self->ctx);
		self->iref = ctx.ref;
	}
	xlogf("\n%s(self = %p) returning -> (ref = %llu, ctx = %p)\n", __func__, self, (uvlong)self->iref, &self->ctx);
	return &self->ctx;
}

S_API void S_CALLTYPE
SteamAPI_RegisterCallResult(CCallbackBase *pCallback, SteamAPICall_t hAPICall)
{
	xlogf("%s(pCallback = %p, hAPICall = %llu)\n", __func__, pCallback, hAPICall);
}

S_API void S_CALLTYPE
SteamAPI_UnregisterCallResult(CCallbackBase *pCallback, SteamAPICall_t hAPICall)
{
	xlogf("%s(pCallback = %p, hAPICall = %llu)\n", __func__, pCallback, hAPICall);
}

S_API void S_CALLTYPE
SteamAPI_ReleaseCurrentThreadMemory(void)
{
	xlogf("%s()\n", __func__);
}

S_API bool S_CALLTYPE
SteamAPI_IsSteamRunning(void)
{
	xlogf("%s()\n", __func__);
	return true;
}

S_API void S_CALLTYPE
SteamAPI_UseBreakpadCrashHandler(char const *pchVersion, char const *pchDate, char const *pchTime, bool bFullMemoryDumps, void *pvContext, PFNPreMinidumpCallback m_pfnPreMinidumpCallback)
{
	xlogf("%s(pchVersion = %s, pchDate = %s, pchTime = %s, bFullMemoryDumps = %d, pvContext = %p, m_pfnPreMinidumpCallback = %p)\n", __func__, pchVersion, pchDate, pchTime, bFullMemoryDumps, pvContext, m_pfnPreMinidumpCallback);
}

S_API void S_CALLTYPE
SteamAPI_SetBreakpadAppID(uint32 unAppID)
{
	xlogf("%s(unAppId = %x)\n", __func__, unAppID);
}

#if defined(_WIN32)

S_API void
MbiWindowsString(MEMORY_BASIC_INFORMATION *Mbi, char *Buffer)
{
	int n;

	n = sprintf(Buffer, "%016lx-%016lx %-8x ",
	            (unsigned long)(uintptr_t)Mbi->BaseAddress,
	            (unsigned long)((uintptr_t)Mbi->BaseAddress + Mbi->RegionSize),
	            (UINT)Mbi->RegionSize);

	switch (Mbi->Type) {
	case MEM_IMAGE:
		n += sprintf(Buffer + n, "IMAGE   ");
		break;
	case MEM_MAPPED:
		n += sprintf(Buffer + n, "MAPPED  ");
		break;
	case MEM_PRIVATE:
		n += sprintf(Buffer + n, "PRIVATE ");
		break;
	default:
		n += sprintf(Buffer + n, "UNMAPPED");
		break;
	}

	n += sprintf(Buffer + n, " ");
	switch (Mbi->Type) {
	case MEM_COMMIT:
		n += sprintf(Buffer + n, "COMMIT");
		break;
	case MEM_FREE:
		n += sprintf(Buffer + n, "FREE");
		break;
	case MEM_RESERVE:
		n += sprintf(Buffer + n, "RESERVE");
		break;
	default:
		n += sprintf(Buffer + n, "N/A");
		break;
	}

	n += sprintf(Buffer + n, " (%04lx) ", (unsigned long)Mbi->Protect);
	if (Mbi->Protect & 0x80)
		n += sprintf(Buffer + n, "WC");
	if (Mbi->Protect & 0x40)
		n += sprintf(Buffer + n, "RWX");
	if (Mbi->Protect & 0x10)
		n += sprintf(Buffer + n, "R");
	if (Mbi->Protect & 0x20)
		n += sprintf(Buffer + n, "X");
	if (Mbi->Protect & 0x02)
		n += sprintf(Buffer + n, "R");
	if (Mbi->Protect & 0x04)
		n += sprintf(Buffer + n, "RW");
	if (Mbi->Protect & 0x08)
		n += sprintf(Buffer + n, "WC");
	if (Mbi->Protect < 0x2)
		n += sprintf(Buffer + n, "-");
}

S_API void
MbiPosixString(MEMORY_BASIC_INFORMATION *Mbi, char *Buffer)
{
	char perms[8];

	sprintf(perms, "----");
	if (Mbi->Protect & (0x40 | 0x10 | 0x2 | 0x4))
		perms[0] = 'r';
	if (Mbi->Protect & (0x80 | 0x40 | 0x4 | 0x8))
		perms[1] = 'w';
	if (Mbi->Protect & (0x40 | 0x20))
		perms[2] = 'x';

	sprintf(Buffer, "%#lx %#lx %#x %#lx %s",
	        (unsigned long)(uintptr_t)Mbi->BaseAddress,
	        (unsigned long)((uintptr_t)Mbi->BaseAddress + Mbi->RegionSize),
	        (UINT)Mbi->RegionSize, 0UL, perms);
}

S_API uintptr_t
FindExecutableBase(void)
{
	char Filename[MAX_PATH];
	MEMORY_BASIC_INFORMATION Mbi;
	HANDLE Handle;
	LPVOID Addr;
	uintptr_t Base;

	Handle = GetCurrentProcess();
	Addr = NULL;
	Base = 0;
	for (;;) {
		if (!VirtualQueryEx(Handle, Addr, &Mbi, sizeof(Mbi)))
			break;
		if (Mbi.RegionSize > ((uintptr_t)-1) - ((uintptr_t)Mbi.BaseAddress))
			break;

		Filename[0] = '\0';
		K32GetMappedFileNameA(Handle, Addr, Filename, sizeof(Filename));
		if (strstr(Filename, ".exe") || strstr(Filename, ".EXE")) {
			Base = (uintptr_t)Mbi.BaseAddress;
			break;
		}

		Addr = (LPVOID)((uintptr_t)Mbi.BaseAddress + Mbi.RegionSize);
		if (Addr == NULL)
			break;
	}
	return Base;
}

static FILE *
CreateOutputFile(const char *output, const char *mode)
{
	FILE *stream;

	if (!output)
		return stdout;

	stream = fopen(output, mode);
	if (!stream) {
		xlogf("Failed to open file '%s': %s\n", output, strerror(errno));
		return stdout;
	}
	return stream;
}

S_API LONGLONG
GetFileOffsetFromHandle(HANDLE hFile)
{
	LARGE_INTEGER liOfs = {0};
	LARGE_INTEGER liNew = {0};
	SetFilePointerEx(hFile, liOfs, &liNew, FILE_CURRENT);
	return liNew.QuadPart;
}

S_API void
PrintHandlePath(HANDLE handle, const char *output, const char *mode)
{
	FILE *stream;
	char path[PATH_MAX];

	stream = CreateOutputFile(output, mode);
	GetFinalPathNameByHandleA(handle, path, sizeof(path), 0);
	fprintf(stream, "Handle: %#lx Path: %s Offset: %lld\n", (ULONG)(uintptr_t)handle, path, GetFileOffsetFromHandle(handle));
	if (stream != stdout)
		fclose(stream);
}

S_API void
DumpProcessMap(const char *format, const char *output, const char *mode)
{
	char buffer[1024], filename[MAX_PATH];
	MEMORY_BASIC_INFORMATION mbi;
	HANDLE handle;
	LPVOID addr;
	FILE *stream;

	stream = CreateOutputFile(output, mode);
	handle = GetCurrentProcess();
	addr = NULL;
	for (;;) {
		if (!VirtualQueryEx(handle, addr, &mbi, sizeof(mbi)))
			break;
		if (mbi.RegionSize > ((uintptr_t)-1) - ((uintptr_t)mbi.BaseAddress))
			break;

		filename[0] = '\0';
		K32GetMappedFileNameA(handle, addr, filename, sizeof(filename));

		if (format && !strcmp(format, "windows"))
			MbiWindowsString(&mbi, buffer);
		else
			MbiPosixString(&mbi, buffer);

		fprintf(stream, "%s %s\n", buffer, filename);

		addr = (LPVOID)((uintptr_t)mbi.BaseAddress + mbi.RegionSize);
		if (addr == NULL)
			break;
	}
	fprintf(stream, "\n");

	if (stream != stdout)
		fclose(stream);
}

S_API void
PrintStack(const char *output, const char *mode)
{
	unsigned int i;
	void *stack[1024];
	unsigned short frames;
	SYMBOL_INFO *symbol;
	HANDLE process;
	FILE *stream;

	stream = CreateOutputFile(output, mode);
	process = GetCurrentProcess();

	SymInitialize(process, NULL, TRUE);

	frames = CaptureStackBackTrace(0, nelem(stack), stack, NULL);
	symbol = (SYMBOL_INFO *)calloc(sizeof(SYMBOL_INFO) + 256 * sizeof(char), 1);
	symbol->MaxNameLen = 255;
	symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

	xlogf("Thread %lx Stack Dump:\n", GetCurrentThreadId());
	for (i = 0; i < frames; i++) {
		SymFromAddr(process, (uintptr_t)(stack[i]), 0, symbol);
		fprintf(stream, "%-2i (%p): %s - 0x%0lX\n", frames - i - 1, stack[i], symbol->Name, (unsigned long)symbol->Address);
	}
	fprintf(stream, "\n");

	free(symbol);
	if (stream != stdout)
		fclose(stream);
}

const char *
GetExceptionString(int ExceptionCode)
{
	switch (ExceptionCode) {
	case DBG_PRINTEXCEPTION_C:
		return "DBG_PRINTEXCEPTION_C";
	case EXCEPTION_BREAKPOINT:
		return "EXCEPTION_BREAKPOINT";
	case EXCEPTION_ACCESS_VIOLATION:
		return "EXCEPTION_ACCESS_VIOLATION";
	}
	return "UNKNOWN_EXCEPTION_CODE";
}

LONG WINAPI
ExceptionHandler(PEXCEPTION_POINTERS pExceptionInfo)
{
	xlogf("----------\n");

	xlogf("%s(pExceptionInfo = %p)\n", __func__, (void *)pExceptionInfo);
	xlogf("Exception Record {\n");
	xlogf("\tCode:             %x\n", (UINT)pExceptionInfo->ExceptionRecord->ExceptionCode);
	xlogf("\tCode String:      %s\n", GetExceptionString(pExceptionInfo->ExceptionRecord->ExceptionCode));
	xlogf("\tFlags:            %x\n", (UINT)pExceptionInfo->ExceptionRecord->ExceptionFlags);
	xlogf("\tFlags:            %llx\n", (ULONGLONG)(uintptr_t)pExceptionInfo->ExceptionRecord->ExceptionAddress);
	xlogf("\tNumberParameters: %d\n", (INT)pExceptionInfo->ExceptionRecord->NumberParameters);
	xlogf("}\n\n");

#if defined(_WIN64)
	xlogf("Context Record {\n");
	xlogf("\tRAX:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Rax);
	xlogf("\tRCX:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Rcx);
	xlogf("\tRDX:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Rdx);
	xlogf("\tRBX:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Rbx);
	xlogf("\tRBP:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Rbp);
	xlogf("\tRSI:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Rsi);
	xlogf("\tRDI:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Rdi);
	xlogf("\tR8:   %lx\n", (ULONG)pExceptionInfo->ContextRecord->R8);
	xlogf("\tR9:   %lx\n", (ULONG)pExceptionInfo->ContextRecord->R9);
	xlogf("\tR10:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->R10);
	xlogf("\tR11:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->R11);
	xlogf("\tR12:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->R12);
	xlogf("\tR13:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->R13);
	xlogf("\tR14:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->R14);
	xlogf("\tR15:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->R15);
	xlogf("\tRIP:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Rip);
	xlogf("\tRSP:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Rsp);
	xlogf("}\n");
#else
	xlogf("Context Record {\n");
	xlogf("\tEAX:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Eax);
	xlogf("\tECX:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Ecx);
	xlogf("\tEDX:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Edx);
	xlogf("\tEBX:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Ebx);
	xlogf("\tEBP:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Ebp);
	xlogf("\tESI:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Esi);
	xlogf("\tEDI:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Edi);
	xlogf("\tEIP:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Eip);
	xlogf("\tESP:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Esp);
	xlogf("}\n");
#endif
	acquireLock(&ctx.globalLock);
	DumpProcessMap(NULL, NULL, NULL);
	PrintStack(NULL, NULL);
	releaseLock(&ctx.globalLock);
	return EXCEPTION_EXECUTE_HANDLER;
}

BOOL WINAPI
Steam_IsDebuggerPresent(void)
{
	xlogf("%s()\n", __func__);
	return 0;
}

void WINAPI
Steam_OutputDebugStringA(LPCSTR lpOutputString)
{
	xlogf("%s(lpOutputString = (%p) %s)\n", __func__, lpOutputString, lpOutputString);
	acquireLock(&ctx.globalLock);
	DumpProcessMap(NULL, NULL, NULL);
	PrintStack(NULL, NULL);
	releaseLock(&ctx.globalLock);
	DebugBreak();
}

#if defined(_MSC_VER) && defined(DETOURS)
#include <detours.h>

// clang-format off
HANDLE (WINAPI *TrueCreateFileA)(LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE) = CreateFileA;
BOOL (WINAPI *TrueIsDebuggerPresent)(void) = IsDebuggerPresent;
HINSTANCE (WINAPI *TrueShellExecuteA)(HWND, LPCSTR, LPCSTR, LPCSTR, LPCSTR, INT) = ShellExecuteA;
void (WINAPI *TrueOutputDebugStringA)(LPCSTR) = OutputDebugStringA;
FARPROC (WINAPI *TrueGetProcAddress)(HMODULE, LPCSTR) = GetProcAddress;
HMODULE (WINAPI *TrueLoadLibraryA)(LPCSTR) = LoadLibraryA;
HMODULE (WINAPI *TrueLoadLibraryExA)(LPCSTR, HANDLE, DWORD) = LoadLibraryExA;
HMODULE (WINAPI *TrueLoadLibraryW)(LPCWSTR) = LoadLibraryW;
HMODULE(WINAPI *TrueGetModuleHandleA)(LPCSTR) = GetModuleHandleA;
DWORD (WINAPI *TrueGetModuleFileNameA)(HMODULE, LPSTR, DWORD) = GetModuleFileNameA;
LPTOP_LEVEL_EXCEPTION_FILTER (WINAPI *TrueSetUnhandledExceptionFilter)(LPTOP_LEVEL_EXCEPTION_FILTER) = SetUnhandledExceptionFilter;
BOOL (WINAPI *TrueSetStdHandle)(DWORD, HANDLE) = SetStdHandle;
LPVOID (WINAPI *TrueHeapAlloc)(HANDLE, DWORD, SIZE_T) = HeapAlloc;
LPVOID (WINAPI *TrueVirtualAlloc)(LPVOID, SIZE_T, DWORD, DWORD) = VirtualAlloc;
void *(*TrueCalloc)(size_t, size_t) = calloc;
LSTATUS (WINAPI *TrueRegOpenKeyExA)(HKEY, LPCSTR, DWORD, REGSAM, PHKEY) = RegOpenKeyExA;
LSTATUS (WINAPI *TrueRegCreateKeyExA)(HKEY, LPCSTR, DWORD, LPSTR, DWORD, REGSAM, const LPSECURITY_ATTRIBUTES, PHKEY, LPDWORD) = RegCreateKeyExA;
LSTATUS (WINAPI *TrueRegCloseKey)(HKEY) = RegCloseKey;
LSTATUS (WINAPI *TrueRegQueryValueExA)(HKEY, LPCSTR, LPDWORD, LPDWORD, LPBYTE, LPDWORD) = RegQueryValueExA;
HANDLE (WINAPI *TrueOpenProcess)(DWORD, BOOL, DWORD) = OpenProcess;
BOOL (WINAPI *TrueEnumProcesses)(DWORD *, DWORD, LPDWORD) = EnumProcesses;
BOOL (WINAPI *TrueSetEnvironmentVariableA)(LPCSTR, LPCSTR) = SetEnvironmentVariableA;
DWORD (WINAPI *TrueGetEnvironmentVariableA)(LPCSTR, LPSTR, DWORD) = GetEnvironmentVariableA;
// clang-format on

NTSTATUS WINAPI
Steam_NtSetInformationThread(HANDLE Handle, THREADINFOCLASS Class, LPVOID Data, ULONG Length)
{
	xlogf("%s(Handle = %#x, Class = %#x, Data = %p, Length = %lu)\n", __func__, Handle, Class, Data, Length);
	return 0;
}

HINSTANCE WINAPI
Steam_ShellExecuteA(HWND hwnd, LPCSTR lpOperation, LPCSTR lpFile, LPCSTR lpParameters, LPCSTR lpDirectory, INT nShowCmd)
{
	xlogf("%s(hwnd = %llx, lpOperation = %s, lpFile = %s, lpParameters = %s, lpDirectory = %s, nShowCmd = %d)\n", __func__, (ULONGLONG)hwnd, lpOperation, lpFile, lpParameters, lpDirectory, nShowCmd);
	return TrueShellExecuteA(hwnd, lpOperation, lpFile, lpParameters, lpDirectory, nShowCmd);
}

LPTOP_LEVEL_EXCEPTION_FILTER WINAPI
Steam_SetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter)
{
	xlogf("%s(lpTopLevelExceptionFilter = %p)\n", __func__, lpTopLevelExceptionFilter);
	return TrueSetUnhandledExceptionFilter(lpTopLevelExceptionFilter);
}

HMODULE WINAPI
Steam_LoadLibraryA(LPCSTR lpLibFilename)
{
	HMODULE Module = TrueLoadLibraryA(lpLibFilename);
	xlogf("%s(lpLibFilename = %s) -> %p\n", __func__, lpLibFilename, Module);
	return Module;
}

HMODULE WINAPI
Steam_LoadLibraryExA(LPCSTR lpLibFilename, HANDLE hFile, DWORD dwFlags)
{
	HMODULE Module = TrueLoadLibraryExA(lpLibFilename, hFile, dwFlags);
	xlogf("%s(lpLibFilename = %s, hFile = %d, dwFlags = %#lx) -> %p\n", __func__, lpLibFilename, hFile, dwFlags, Module);
	return Module;
}

HMODULE WINAPI
Steam_LoadLibraryW(LPCWSTR lpLibFilename)
{
	HMODULE Module = TrueLoadLibraryW(lpLibFilename);
	xlogf("%s(lpLibFilename = %ls) -> %p\n", __func__, lpLibFilename, Module);
	return Module;
}

HMODULE WINAPI
Steam_GetModuleHandleA(LPCSTR lpModuleName)
{
	HMODULE Module = TrueGetModuleHandleA(lpModuleName);
	xlogf("%s(lpModuleName = %s) -> %#x\n", __func__, lpModuleName, Module);
	return Module;
}

DWORD WINAPI
Steam_GetModuleFileNameA(HMODULE hModule, LPSTR lpFilename, DWORD nSize)
{
	DWORD Ret = TrueGetModuleFileNameA(hModule, lpFilename, nSize);
	xlogf("%s(hModule = %#x, lpFilename = %s, nSize = %d) -> %d\n", __func__, hModule, lpFilename, nSize, Ret);
	return Ret;
}

BOOL WINAPI
Steam_SetStdHandle(DWORD nStdHandle, HANDLE hHandle)
{
	xlogf("%s(nStdHandle = %d, hHandle = %#x)\n", __func__, nStdHandle, hHandle);
	return TRUE;
}

LPVOID WINAPI
Steam_HeapAlloc(HANDLE hHandle, DWORD dwFlags, SIZE_T dwBytes)
{
	LPVOID Ptr = TrueHeapAlloc(hHandle, dwFlags, dwBytes);
	// xlogf("%s(hHandle = %#x, dwFlags = %#x, dwBytes = %d) -> %#x\n", __func__, hHandle, dwFlags, dwBytes, Ptr);
	return Ptr;
}

LPVOID WINAPI
Steam_MapViewOfFile(HANDLE hFileMappingObject, DWORD dwDesiredAccess, DWORD dwFileOffsetHigh, DWORD dwFileOffsetLow, SIZE_T dwNumbersOfBytesToMap)
{
	LPVOID Ptr = MapViewOfFile(hFileMappingObject, dwDesiredAccess, dwFileOffsetHigh, dwFileOffsetLow, dwNumbersOfBytesToMap);
	xlogf("%s(hFileMappingObject = %#x, dwDesiredAccess = %#x, dwFileOffsetHigh = %#x, dwFileOffsetLow = %#x, dwNumbersOfBytesToMap = %#x) -> %#x\n",
	      __func__, hFileMappingObject, dwDesiredAccess, dwFileOffsetHigh, dwFileOffsetLow, dwNumbersOfBytesToMap, Ptr);
	return Ptr;
}

LPVOID WINAPI
Steam_VirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect)
{
	LPVOID Ptr = TrueVirtualAlloc(lpAddress, dwSize, flAllocationType, flProtect);
	xlogf("%s(lpAddress = %p, dwSize = %#x, flAllocationType = %#x, flProtect = %#x) -> %p\n",
	      __func__, lpAddress, dwSize, flAllocationType, flProtect, Ptr);
	return Ptr;
}

void *
Steam_Calloc(size_t num, size_t size)
{
	void *Ptr = TrueCalloc(num, size);
	xlogf("%s(num = %lu, size = %lu) -> %p\n", __func__, (unsigned long)num, (unsigned long)size, Ptr);
	return Ptr;
}

LSTATUS WINAPI
Steam_RegCreateKeyExA(HKEY hKey, LPCSTR lpSubKey, DWORD Reserved, LPSTR lpClass, DWORD dwOptions, REGSAM samDesired, const LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult, LPDWORD lpdwDisposition)
{
	LSTATUS Status = TrueRegCreateKeyExA(hKey, lpSubKey, Reserved, lpClass, dwOptions, samDesired, lpSecurityAttributes, phkResult, lpdwDisposition);
	xlogf("%s(hKey = %#x, lpSubKey = %s, Reserved = %#lx, lpClass = %s, dwOptions = %#x, samDesired = %p, phkResult = %p, lpdwDisposition = %p) -> %#x %ld\n",
	      __func__, hKey, lpSubKey, Reserved, lpClass, dwOptions, samDesired, lpSecurityAttributes, phkResult, lpdwDisposition, phkResult ? *phkResult : 0, Status);
	return Status;
}

LSTATUS WINAPI
Steam_RegOpenKeyExA(HKEY hKey, LPCSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult)
{
	LSTATUS Status = TrueRegOpenKeyExA(hKey, lpSubKey, ulOptions, samDesired, phkResult);
	xlogf("%s(hKey = %#x, lpSubKey = %s, ulOptions = %#x, samDesired = %p, phkResult = %p) -> %#x %ld\n",
	      __func__, hKey, lpSubKey, ulOptions, samDesired, phkResult, phkResult ? *phkResult : 0, Status);
	return Status;
}

LSTATUS WINAPI
Steam_RegCloseKey(HKEY hKey)
{
	LSTATUS Status = TrueRegCloseKey(hKey);
	xlogf("%s(hKey = %#x)\n", __func__, hKey);
	return Status;
}

LSTATUS WINAPI
Steam_RegQueryValueExA(HKEY hKey, LPCSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData)
{
	LSTATUS Status = TrueRegQueryValueExA(hKey, lpValueName, lpReserved, lpType, lpData, lpcbData);
	xlogf("%s(hKey = %#x, lpValueName = %s, lpReserved = %p, lpType = %p, lpData = %p, lpcbData = %p) -> %ld\n",
	      __func__, hKey, lpValueName, lpReserved, lpType, lpData, lpcbData, Status);
	return Status;
}

HANDLE WINAPI
Steam_OpenProcess(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId)
{
	HANDLE Handle;
	if (dwProcessId = ctx.steamPID)
		Handle = GetCurrentProcess();
	else
		Handle = TrueOpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
	xlogf("%s(dwDesiredAccess = %#x, bInheritHandle = %d, dwProcessId = %d) (steamPID = %d) -> %#lx\n",
	      __func__, dwDesiredAccess, bInheritHandle, dwProcessId, ctx.steamPID, Handle);
	return Handle;
}

BOOL WINAPI
Steam_EnumProcesses(DWORD *lpidProcess, DWORD cb, LPDWORD lpcbNeeded)
{
	BOOL Ret = TrueEnumProcesses(lpidProcess, cb, lpcbNeeded);
	xlogf("%s(lpidProcess = %p, cb = %d, lpcbNeeded = %p) -> %d, %d\n",
	      __func__, cb, lpcbNeeded, (lpcbNeeded) ? *lpcbNeeded : 0, Ret);
	return Ret;
}

BOOL WINAPI
Steam_SetEnvironmentVariableA(LPCSTR lpName, LPCSTR lpValue)
{
	BOOL Ret = TrueSetEnvironmentVariableA(lpName, lpValue);
	xlogf("%s(lpName = %s, lpValue = %s) -> %d\n",
	      __func__, lpName, lpValue, Ret);
	return Ret;
}

DWORD WINAPI
Steam_GetEnvironmentVariableA(LPCSTR lpName, LPSTR lpBuffer, DWORD nSize)
{
	DWORD Ret = TrueGetEnvironmentVariableA(lpName, lpBuffer, nSize);
	xlogf("%s(lpName = %s, lpBuffer = %p, nSize = %lu) -> %lu\n",
	      __func__, lpName, lpBuffer, nSize, Ret);
	return Ret;
}

HANDLE WINAPI
Steam_CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
	HANDLE Ret = TrueCreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
	return Ret;
}

FARPROC WINAPI
Steam_GetProcAddress(HMODULE hModule, LPCSTR lpProcName)
{
	ULONG_PTR Function;
	FARPROC Proc;
	const char *Name;

	Function = (ULONG_PTR)lpProcName >> 16;
	Proc = TrueGetProcAddress(hModule, lpProcName);
	if (!Proc || Function == 0) {
		if (Function == 0)
			xlogf("%s(hModule = %#x, lpProcName = %p) -> NULL\n", __func__, hModule, lpProcName);
		else
			xlogf("%s(hModule = %#x, lpProcName = %s) -> NULL\n", __func__, hModule, lpProcName);
		return NULL;
	}

	if (!strcmp(lpProcName, "SetUnhandledExceptionFilter"))
		Proc = (FARPROC)Steam_SetUnhandledExceptionFilter;
	else if (!strcmp(lpProcName, "NtSetInformationThread"))
		Proc = (FARPROC)Steam_NtSetInformationThread;
	else if (!strcmp(lpProcName, "IsDebuggerPresent"))
		Proc = (FARPROC)Steam_IsDebuggerPresent;
	else if (!strcmp(lpProcName, "GetProcAddress"))
		Proc = (FARPROC)Steam_GetProcAddress;
	else if (!strcmp(lpProcName, "SetStdHandle"))
		Proc = (FARPROC)Steam_SetStdHandle;
	else if (!strcmp(lpProcName, "HeapAlloc"))
		Proc = (FARPROC)Steam_HeapAlloc;
	else if (!strcmp(lpProcName, "MapViewOfFile"))
		Proc = (FARPROC)Steam_MapViewOfFile;
	else if (!strcmp(lpProcName, "VirtualAlloc"))
		Proc = (FARPROC)Steam_VirtualAlloc;
	else if (!strcmp(lpProcName, "calloc"))
		Proc = (FARPROC)Steam_Calloc;
	else if (!strcmp(lpProcName, "RegCreateKeyExA"))
		Proc = (FARPROC)Steam_RegCreateKeyExA;
	else if (!strcmp(lpProcName, "RegOpenKeyExA"))
		Proc = (FARPROC)Steam_RegOpenKeyExA;
	else if (!strcmp(lpProcName, "RegQueryValueExA"))
		Proc = (FARPROC)Steam_RegQueryValueExA;
	else if (!strcmp(lpProcName, "RegCloseKey"))
		Proc = (FARPROC)Steam_RegCloseKey;
	else if (!strcmp(lpProcName, "OpenProcess"))
		Proc = (FARPROC)Steam_OpenProcess;
	else if (!strcmp(lpProcName, "EnumProcesses"))
		Proc = (FARPROC)Steam_EnumProcesses;
	else if (!strcmp(lpProcName, "CreateInterface"))
		Proc = (FARPROC)SteamInternal_CreateInterface;
	else if (!strcmp(lpProcName, "SetEnvironmentVariableA"))
		Proc = (FARPROC)Steam_SetEnvironmentVariableA;
	else if (!strcmp(lpProcName, "GetEnvironmentVariableA"))
		Proc = (FARPROC)Steam_GetEnvironmentVariableA;

	xlogf("%s(hModule = %#x, lpProcName = %s) -> %p\n", __func__, hModule, lpProcName, Proc);
	return Proc;
}

S_API void
attachDetours(void)
{
	xlogf("%s()\n", __func__);
	DetourRestoreAfterWith();
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID)TrueCreateFileA, Steam_CreateFileA);
	DetourAttach(&(PVOID)TrueIsDebuggerPresent, Steam_IsDebuggerPresent);
	DetourAttach(&(PVOID)TrueOutputDebugStringA, Steam_OutputDebugStringA);
	DetourAttach(&(PVOID)TrueShellExecuteA, Steam_ShellExecuteA);
	DetourAttach(&(PVOID)TrueGetProcAddress, Steam_GetProcAddress);
	DetourAttach(&(PVOID)TrueLoadLibraryA, Steam_LoadLibraryA);
	DetourAttach(&(PVOID)TrueLoadLibraryExA, Steam_LoadLibraryExA);
	DetourAttach(&(PVOID)TrueLoadLibraryW, Steam_LoadLibraryW);
	DetourAttach(&(PVOID)TrueGetModuleHandleA, Steam_GetModuleHandleA);
	DetourAttach(&(PVOID)TrueGetModuleFileNameA, Steam_GetModuleFileNameA);
	DetourAttach(&(PVOID)TrueSetUnhandledExceptionFilter, Steam_SetUnhandledExceptionFilter);
	DetourAttach(&(PVOID)TrueSetStdHandle, Steam_SetStdHandle);
	DetourAttach(&(PVOID)TrueRegCreateKeyExA, Steam_RegCreateKeyExA);
	DetourAttach(&(PVOID)TrueRegOpenKeyExA, Steam_RegOpenKeyExA);
	DetourAttach(&(PVOID)TrueRegQueryValueExA, Steam_RegQueryValueExA);
	DetourAttach(&(PVOID)TrueRegCloseKey, Steam_RegCloseKey);
	DetourAttach(&(PVOID)TrueSetEnvironmentVariableA, Steam_SetEnvironmentVariableA);
	DetourAttach(&(PVOID)TrueGetEnvironmentVariableA, Steam_GetEnvironmentVariableA);
	DetourTransactionCommit();
}

S_API void
detachDetours(void)
{
	xlogf("%s()\n", __func__);
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&(PVOID)TrueCreateFileA, Steam_CreateFileA);
	DetourDetach(&(PVOID)TrueIsDebuggerPresent, Steam_IsDebuggerPresent);
	DetourDetach(&(PVOID)TrueOutputDebugStringA, Steam_OutputDebugStringA);
	DetourDetach(&(PVOID)TrueShellExecuteA, Steam_ShellExecuteA);
	DetourDetach(&(PVOID)TrueGetProcAddress, Steam_GetProcAddress);
	DetourDetach(&(PVOID)TrueLoadLibraryA, Steam_LoadLibraryA);
	DetourDetach(&(PVOID)TrueLoadLibraryExA, Steam_LoadLibraryExA);
	DetourDetach(&(PVOID)TrueLoadLibraryW, Steam_LoadLibraryW);
	DetourDetach(&(PVOID)TrueGetModuleHandleA, Steam_GetModuleHandleA);
	DetourDetach(&(PVOID)TrueGetModuleFileNameA, Steam_GetModuleFileNameA);
	DetourDetach(&(PVOID)TrueSetUnhandledExceptionFilter, Steam_SetUnhandledExceptionFilter);
	DetourDetach(&(PVOID)TrueSetStdHandle, Steam_SetStdHandle);
	DetourDetach(&(PVOID)TrueRegCreateKeyExA, Steam_RegCreateKeyExA);
	DetourDetach(&(PVOID)TrueRegOpenKeyExA, Steam_RegOpenKeyExA);
	DetourDetach(&(PVOID)TrueRegQueryValueExA, Steam_RegQueryValueExA);
	DetourDetach(&(PVOID)TrueRegCloseKey, Steam_RegCloseKey);
	DetourDetach(&(PVOID)TrueSetEnvironmentVariableA, Steam_SetEnvironmentVariableA);
	DetourDetach(&(PVOID)TrueGetEnvironmentVariableA, Steam_GetEnvironmentVariableA);
	DetourTransactionCommit();
}
#endif

typedef NTSTATUS(NTAPI *NtQuerySystemProcessFunc)(HANDLE, PROCESSINFOCLASS, PVOID, ULONG, PULONG);

PPEB
findPEB(void)
{
	NtQuerySystemProcessFunc Query;
	PROCESS_BASIC_INFORMATION Info;
	HANDLE Process;
	ULONG Length;
	NTSTATUS Status;

	Query = (NtQuerySystemProcessFunc)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtQueryInformationProcess");
	if (!Query)
		return NULL;
	Process = GetCurrentProcess();
	Length = sizeof(Info);
	Status = Query(Process, ProcessBasicInformation, &Info, sizeof(Info), &Length);
	if (Status != 0)
		return NULL;
	return Info.PebBaseAddress;
}

void
writeRegistryValues(void)
{
	const char *SubKey = "Software\\Valve\\Steam\\ActiveProcess";
	HKEY Key;
	DWORD Pid;
	DWORD User;

	if (RegCreateKeyA(HKEY_CURRENT_USER, SubKey, &Key) != ERROR_SUCCESS)
		return;
	Pid = ctx.steamPID;
	User = ctx.steamUser;
	RegSetKeyValueA(HKEY_CURRENT_USER, SubKey, "pid", REG_DWORD, &Pid, sizeof(Pid));
	RegSetKeyValueA(HKEY_CURRENT_USER, SubKey, "ActiveUser", REG_DWORD, &User, sizeof(User));
	RegCloseKey(Key);
}

void
hideDebugger(void)
{
	PPEB Peb;
	Peb = findPEB();
	if (Peb)
		Peb->BeingDebugged = 0;
}

BOOL APIENTRY
DllMain(HANDLE hModule, DWORD reason, LPVOID lpReserved)
{
#if defined(_MSC_VER) && defined(DETOURS)
	if (DetourIsHelperProcess())
		return TRUE;
#endif

	if (reason == DLL_PROCESS_ATTACH) {
		initSteam();
		writeRegistryValues();
		hideDebugger();
#if defined(_MSC_VER) && defined(DETOURS)
		attachDetours();
		// AddVectoredExceptionHandler(1, ExceptionHandler);
#endif
	} else if (reason == DLL_PROCESS_DETACH) {
#if defined(_MSC_VER) && defined(DETOURS)
		detachDetours();
#endif
	}

	xlogf("%s(hModule = %p, reason = %lx, lpReserved = %p)\n", __func__, hModule, reason, lpReserved);

	return TRUE;
}
#endif
