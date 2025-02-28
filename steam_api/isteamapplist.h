#pragma once

#include "steamtypes.h"

typedef void ISteamAppList;

typedef struct CSteamAppList CSteamAppList;

struct CSteamAppList {
	CSteamBase base;
};

S_CLASSAPI uint32 S_CLASSCALLTYPE SteamAPI_ISteamAppList_GetNumInstalledApps(SELF);
S_CLASSAPI uint32 S_CLASSCALLTYPE SteamAPI_ISteamAppList_GetInstalledApps(SELF, AppId_t *pvecAppID, uint32 unMaxAppIDs);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamAppList_GetAppName(SELF, AppId_t *pvecAppID, uint32 unMaxAppIDs);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamAppList_GetAppInstallDir(SELF, AppId_t nAppID, char *pchDirectory, int cchNameMax);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamAppList_GetAppBuildId(SELF, AppId_t nAppID);