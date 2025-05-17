#include "steam.h"

S_CLASSAPI uint32 S_CLASSCALLTYPE
SteamAPI_ISteamAppList_GetNumInstalledApps(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI uint32 S_CLASSCALLTYPE
SteamAPI_ISteamAppList_GetInstalledApps(SELF, AppId_t *pvecAppID, uint32 unMaxAppIDs)
{
	xlogf("%s(self = %p, pvecAppID = %p, unMaxAppIDs = %d)\n", __func__, self, pvecAppID, unMaxAppIDs);
	return 0;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamAppList_GetAppName(SELF, AppId_t *pvecAppID, uint32 unMaxAppIDs)
{
	xlogf("%s(self = %p, pvecAppID = %p, unMaxAppIDs = %d)\n", __func__, self, pvecAppID, unMaxAppIDs);
	return 0;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamAppList_GetAppInstallDir(SELF, AppId_t nAppID, char *pchDirectory, int cchNameMax)
{
	xlogf("%s(self = %p, nAppID = %d, pchDirectory = %s, cchNameMax = %d)\n", __func__, self, nAppID, pchDirectory, cchNameMax);
	return 0;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamAppList_GetAppBuildId(SELF, AppId_t nAppID)
{
	xlogf("%s(self = %p, nAppID = %d)\n", __func__, self, nAppID);
	return 1;
}
