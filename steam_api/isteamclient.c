#include "steam.h"

S_CLASSAPI HSteamPipe S_CLASSCALLTYPE SteamAPI_ISteamClient_CreateSteamPipe(SELF)
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
	CSteamUser *user = &ctx.user;
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, user);
	snprintf(user->base.version, sizeof(user->base.version), "%s", pchVersion);
	return user;
}

S_CLASSAPI ISteamGameServer *S_CLASSCALLTYPE
SteamAPI_ISteamAPI_ISteamClient_GetISteamGameServer(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamGameServer *gameServer = &ctx.gameServer;
	xlogf("%s(self = %p, hSteamUser = %d, hSteamPipe = %d, pchVersion = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, gameServer);
	return gameServer;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamClient_SetLocalIPBinding(SELF, uint32 unIP, uint16 usPort)
{
	xlogf("%s(self = %p, unIP = %x, usPort = %d)\n", __func__, self, unIP, usPort);
}

S_CLASSAPI ISteamFriends *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamFriends(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamFriends *friends = &ctx.friends;

	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, friends);
	snprintf(friends->base.version, sizeof(friends->base.version), "%s", pchVersion);
	return friends;
}

S_CLASSAPI ISteamUtils *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamUtils(SELF, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamUtils *utils = &ctx.utils;
	xlogf("%s(self = %p, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamPipe, pchVersion, utils);
	snprintf(utils->base.version, sizeof(utils->base.version), "%s", pchVersion);
	return utils;
}

S_CLASSAPI ISteamMatchmaking *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamMatchmaking(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamMatchmaking *matchmaking = &ctx.matchmaking;
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, matchmaking);
	snprintf(matchmaking->base.version, sizeof(matchmaking->base.version), "%s", pchVersion);
	return matchmaking;
}

S_CLASSAPI ISteamMatchmakingServers *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamMatchmakingServers(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamMatchmakingServers *matchmakingServers = &ctx.matchmakingServers;
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, matchmakingServers);
	snprintf(matchmakingServers->base.version, sizeof(matchmakingServers->base.version), "%s", pchVersion);
	return matchmakingServers;
}

S_CLASSAPI void *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamGenericInterface(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamAppTicket *appTicket = &ctx.appTicket;
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, appTicket);
	return appTicket;
}

S_CLASSAPI ISteamRemoteStorage *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamRemoteStorage(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamRemoteStorage *remoteStorage = &ctx.remoteStorage;
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, remoteStorage);
	return remoteStorage;
}

S_CLASSAPI ISteamScreenshots *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamScreenshots(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamScreenshots *screenshots = &ctx.screenshots;
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, screenshots);
	snprintf(screenshots->base.version, sizeof(screenshots->base.version), "%s", pchVersion);
	return screenshots;
}

S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamClient_RunFrame(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI uint32 S_CLASSCALLTYPE SteamAPI_ISteamClient_GetIPCCallCount(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamClient_SetWarningMessageHook(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamClient_BShutdownIfAllPipesClosed(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return true;
}

S_CLASSAPI ISteamHTTP *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamHTTP(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamHTTP *http = &ctx.http;
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, http);
	snprintf(http->base.version, sizeof(http->base.version), "%s", pchVersion);
	return http;
}

S_CLASSAPI ISteamUnifiedMessages *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamUnifiedMessages(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamUnifiedMessages *unifiedMessages = &ctx.unifiedMessages;
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, unifiedMessages);
	snprintf(unifiedMessages->base.version, sizeof(unifiedMessages->base.version), "%s", pchVersion);
	return unifiedMessages;
}

S_CLASSAPI ISteamController *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamController(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamController *controller = &ctx.controller;
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, controller);
	snprintf(controller->base.version, sizeof(controller->base.version), "%s", pchVersion);
	return controller;
}

S_CLASSAPI ISteamUGC *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamUGC(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamUGC *ugc = &ctx.ugc;
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, ugc);
	snprintf(ugc->base.version, sizeof(ugc->base.version), "%s", pchVersion);
	return ugc;
}

S_CLASSAPI ISteamAppList *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamAppList(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamAppList *appList = &ctx.appList;
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, appList);
	snprintf(appList->base.version, sizeof(appList->base.version), "%s", pchVersion);
	return appList;
}

S_CLASSAPI ISteamMusic *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamMusic(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamMusic *music = &ctx.music;
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, music);
	snprintf(music->base.version, sizeof(music->base.version), "%s", pchVersion);
	return music;
}

S_CLASSAPI ISteamMusicRemote *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamMusicRemote(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamMusicRemote *musicRemote = &ctx.musicRemote;
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, musicRemote);
	snprintf(musicRemote->base.version, sizeof(musicRemote->base.version), "%s", pchVersion);
	return musicRemote;
}

S_CLASSAPI ISteamHTMLSurface *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamHTMLSurface(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamHTMLSurface *htmlSurface = &ctx.htmlSurface;
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, htmlSurface);
	snprintf(htmlSurface->base.version, sizeof(htmlSurface->base.version), "%s", pchVersion);
	return htmlSurface;
}

S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamClient_Set_SteamAPI_CPostAPIResultInProcess(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamClient_Set_SteamAPI_CCheckCallbackRegisteredInProcess(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI ISteamInventory *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamInventory(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamInventory *inventory = &ctx.inventory;
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, inventory);
	snprintf(inventory->base.version, sizeof(inventory->base.version), "%s", pchVersion);
	return inventory;
}

S_CLASSAPI ISteamVideo *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamVideo(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamVideo *video = &ctx.video;
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, video);
	snprintf(video->base.version, sizeof(video->base.version), "%s", pchVersion);
	return video;
}

S_CLASSAPI ISteamParentalSettings *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamParentalSettings(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamParentalSettings *parentalSettings = &ctx.parentalSettings;
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, parentalSettings);
	snprintf(parentalSettings->base.version, sizeof(parentalSettings->base.version), "%s", pchVersion);
	return parentalSettings;
}

S_CLASSAPI ISteamGameServerStats *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamGameServerStats(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamGameServerStats *gameServerStats = &ctx.gameServerStats;
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, gameServerStats);
	snprintf(gameServerStats->base.version, sizeof(gameServerStats->base.version), "%s", pchVersion);
	return gameServerStats;
}

S_CLASSAPI ISteamUserStats *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamUserStats(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamUserStats *userStats = &ctx.userStats;
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, userStats);
	snprintf(userStats->base.version, sizeof(userStats->base.version), "%s", pchVersion);
	return userStats;
}

S_CLASSAPI ISteamNetworking *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamNetworking(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamNetworking *networking = &ctx.networking;
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, networking);
	snprintf(networking->base.version, sizeof(networking->base.version), "%s", pchVersion);
	return networking;
}

S_CLASSAPI ISteamGameServer *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamGameServer(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamGameServer *gameServer = &ctx.gameServer;
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, gameServer);
	snprintf(gameServer->base.version, sizeof(gameServer->base.version), "%s", pchVersion);
	return gameServer;
}

S_CLASSAPI ISteamApps *S_CLASSCALLTYPE
SteamAPI_ISteamClient_GetISteamApps(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
{
	CSteamApps *apps = &ctx.apps;
	xlogf("%s(self = %p, user = %d, pipe = %d, ver = %s) -> %p\n", __func__, self, hSteamUser, hSteamPipe, pchVersion, apps);
	snprintf(apps->base.version, sizeof(apps->base.version), "%s", pchVersion);
	return apps;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamClient_Remove_SteamAPI_CPostAPIResultInProcess(SELF, SteamAPI_PostAPIResultInProcess_t func)
{
	xlogf("%s(self = %p, func = %p)\n", __func__, self, func);
}