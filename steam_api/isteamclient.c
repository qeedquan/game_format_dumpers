#include "steam.h"

S_CLASSAPI HSteamPipe S_CLASSCALLTYPE
SteamAPI_ISteamClient_CreateSteamPipe(SELF)
{
	ctx.steamPipe++;
	xlogf("%s(self = %p) -> %d\n", __func__, self, ctx.steamPipe);
	return ctx.steamPipe;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamClient_BReleaseSteamPipe(SELF, HSteamPipe hSteamPipe)
{
	xlogf("%s(self = %p, hSteamPipe = %d)\n", __func__, self, hSteamPipe);
	return true;
}

S_CLASSAPI HSteamUser S_CLASSCALLTYPE
SteamAPI_ISteamClient_ConnectToGlobalUser(SELF, HSteamPipe hSteamPipe)
{
	xlogf("%s(self = %p, hSteamPipe = %d) -> %d\n", __func__, self, hSteamPipe, ctx.steamUser);
	return ctx.steamUser;
}

S_CLASSAPI HSteamUser S_CLASSCALLTYPE
SteamAPI_ISteamClient_CreateLocalUser(SELF, HSteamPipe *phSteamPipe, EAccountType eAccountType)
{
	xlogf("%s(self = %p, phSteamPipe = %p, eAccountType = %d) -> %d\n", __func__, self, phSteamPipe, eAccountType, ctx.steamUser);
	return ctx.steamUser;
}

S_CLASSAPI HSteamPipe S_CLASSCALLTYPE
SteamAPI_GetHSteamPipe(void)
{
	xlogf("%s() -> %d\n", __func__, ctx.steamPipe);
	return ctx.steamPipe;
}

S_CLASSAPI HSteamUser S_CLASSCALLTYPE
SteamAPI_GetHSteamUser(void)
{
	xlogf("%s() -> %d\n", __func__, ctx.steamUser);
	return ctx.steamUser;
}

S_CLASSAPI HSteamPipe S_CLASSCALLTYPE
GetHSteamPipe(void)
{
	xlogf("%s() -> %d\n", __func__, ctx.steamPipe);
	return ctx.steamPipe;
}

S_CLASSAPI HSteamUser S_CLASSCALLTYPE
GetHSteamUser(void)
{
	xlogf("%s() -> %d\n", __func__, ctx.steamUser);
	return ctx.steamUser;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamClient_ReleaseUser(SELF, HSteamPipe hSteamPipe, HSteamUser hUser)
{
	xlogf("%s(self = %p, hSteamPipe = %d, hSteamUser = %d)\n", __func__, self, hSteamPipe, hUser);
}

S_CLASSAPI ISteamUser *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamUser(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamUser *user = createInterface(pchVersion);
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, user);
	return user;
}

S_CLASSAPI ISteamGameServer *S_CLASSCALLTYPE
SteamAPI_ISteamAPI_ISteamClient_GetISteamGameServer(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamGameServer *gameServer = createInterface(pchVersion);
	xlogf("%s(self = %p, hSteamUser = %d, hSteamPipe = %d, pchVersion = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, gameServer);
	return gameServer;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamClient_SetLocalIPBindingUint32(SELF, uint32 unIP, uint16 usPort)
{
	xlogf("%s(self = %p, unIP = %x, usPort = %d)\n", __func__, self, unIP, usPort);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamClient_SetLocalIPBinding(SELF, SteamIPAddress_t *unIP, uint16 usPort)
{
	xlogf("%s(self = %p, unIP = %p, usPort = %d)\n", __func__, self, unIP, usPort);
}

S_CLASSAPI ISteamFriends *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamFriends(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamFriends *friends = createInterface(pchVersion);
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, friends);
	return friends;
}

S_CLASSAPI ISteamUtils *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamUtils(SELF, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamUtils *utils = createInterface(pchVersion);
	xlogf("%s(self = %p, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamPipe, pchVersion, utils);
	return utils;
}

S_CLASSAPI ISteamMatchmaking *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamMatchmaking(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamMatchmaking *matchmaking = createInterface(pchVersion);
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, matchmaking);
	return matchmaking;
}

S_CLASSAPI ISteamMatchmakingServers *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamMatchmakingServers(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamMatchmakingServers *matchmakingServers = createInterface(pchVersion);
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, matchmakingServers);
	return matchmakingServers;
}

S_CLASSAPI void *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamGenericInterface(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamAppTicket *appTicket = createInterface(pchVersion);
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, appTicket);
	return appTicket;
}

S_CLASSAPI ISteamRemoteStorage *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamRemoteStorage(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamRemoteStorage *remoteStorage = createInterface(pchVersion);
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, remoteStorage);
	return remoteStorage;
}

S_CLASSAPI ISteamScreenshots *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamScreenshots(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamScreenshots *screenshots = createInterface(pchVersion);
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, screenshots);
	return screenshots;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamClient_RunFrame(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI uint32 S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetIPCCallCount(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamClient_SetWarningMessageHook(SELF, SteamAPIWarningMessageHook_t pFunction)
{
	xlogf("%s(self = %p, pFunction = %p)\n", __func__, self, pFunction);
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamClient_BShutdownIfAllPipesClosed(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return true;
}

S_CLASSAPI ISteamHTTP *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamHTTP(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamHTTP *http = createInterface(pchVersion);
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, http);
	return http;
}

S_CLASSAPI ISteamUnifiedMessages *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamUnifiedMessages(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamUnifiedMessages *unifiedMessages = createInterface(pchVersion);
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, unifiedMessages);
	return unifiedMessages;
}

S_CLASSAPI ISteamController *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamController(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamController *controller = createInterface(pchVersion);
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, controller);
	return controller;
}

S_CLASSAPI ISteamUGC *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamUGC(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamUGC *ugc = createInterface(pchVersion);
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, ugc);
	return ugc;
}

S_CLASSAPI ISteamAppList *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamAppList(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamAppList *appList = createInterface(pchVersion);
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, appList);
	return appList;
}

S_CLASSAPI ISteamMusic *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamMusic(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamMusic *music = createInterface(pchVersion);
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, music);
	return music;
}

S_CLASSAPI ISteamMusicRemote *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamMusicRemote(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamMusicRemote *musicRemote = createInterface(pchVersion);
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, musicRemote);
	return musicRemote;
}

S_CLASSAPI ISteamHTMLSurface *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamHTMLSurface(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamHTMLSurface *htmlSurface = createInterface(pchVersion);
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, htmlSurface);
	return htmlSurface;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamClient_Set_SteamAPI_CPostAPIResultInProcess(SELF, void (*func)())
{
	xlogf("%s(self = %p, func = %p)\n", __func__, self, func);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamClient_Remove_SteamAPI_CPostAPIResultInProcess(SELF, void (*func)())
{
	xlogf("%s(self = %p, func = %p)\n", __func__, self, func);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamClient_Set_SteamAPI_CCheckCallbackRegisteredInProcess(SELF, SteamAPI_CheckCallbackRegistered_t func)
{
	xlogf("%s(self = %p, func = %p)\n", __func__, self, func);
}

S_CLASSAPI ISteamInventory *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamInventory(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamInventory *inventory = createInterface(pchVersion);
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, inventory);
	return inventory;
}

S_CLASSAPI ISteamVideo *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamVideo(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamVideo *video = createInterface(pchVersion);
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, video);
	return video;
}

S_CLASSAPI ISteamParentalSettings *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamParentalSettings(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamParentalSettings *parentalSettings = createInterface(pchVersion);
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, parentalSettings);
	return parentalSettings;
}

S_CLASSAPI ISteamGameServerStats *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamGameServerStats(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamGameServerStats *gameServerStats = createInterface(pchVersion);
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, gameServerStats);
	return gameServerStats;
}

S_CLASSAPI ISteamUserStats *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamUserStats(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamUserStats *userStats = createInterface(pchVersion);
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, userStats);
	return userStats;
}

S_CLASSAPI ISteamNetworking *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamNetworking(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamNetworking *networking = createInterface(pchVersion);
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, networking);
	return networking;
}

S_CLASSAPI ISteamGameServer *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamGameServer(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamGameServer *gameServer = createInterface(pchVersion);
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, gameServer);
	return gameServer;
}

S_CLASSAPI ISteamApps *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamApps(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamApps *apps = createInterface(pchVersion);
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, apps);
	return apps;
}

S_CLASSAPI ISteamGameSearch *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamGameSearch(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamGameSearch *gameSearch = createInterface(pchVersion);
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, gameSearch);
	return gameSearch;
}

S_CLASSAPI ISteamInput *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamInput(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamInput *input = createInterface(pchVersion);
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, input);
	return input;
}

S_CLASSAPI ISteamParties *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamParties(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamParties *parties = createInterface(pchVersion);
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, parties);
	return parties;
}

S_CLASSAPI ISteamParties *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamRemotePlay(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamRemotePlay *remotePlay = createInterface(pchVersion);
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, remotePlay);
	return remotePlay;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamClient_DestroyAllInterfaces(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}
