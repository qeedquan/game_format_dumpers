#include "steam.h"

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamApps_BIsSubscribed(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamApps_BIsLowViolence(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamApps_BIsCybercafe(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamApps_BIsVACBanned(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return false;
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamApps_GetCurrentGameLanguage(SELF)
{
	CSteamContext *p = &ctx;
	xlogf("%s(self = %p) -> %s\n", __func__, self, p->currentLanguage);
	return p->currentLanguage;
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamApps_GetAvailableGameLanguages(SELF)
{
	CSteamContext *p = &ctx;
	xlogf("%s(self = %p) -> %s\n", __func__, self, p->availableLanguages);
	return p->availableLanguages;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamApps_BIsSubscribedApp(SELF, AppId_t appID)
{
	xlogf("%s(self = %p, appID = %d)\n", __func__, self, appID);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamApps_BIsDlcInstalled(SELF, AppId_t appID)
{
	xlogf("%s(self = %p, appID = %d)\n", __func__, self, appID);
	return true;
}

S_CLASSAPI uint32 S_CLASSCALLTYPE
SteamAPI_ISteamApps_GetEarliestPurchaseUnixTime(SELF, AppId_t nAppID)
{
	xlogf("%s(self = %p, appID = %d)\n", __func__, self, nAppID);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamApps_BIsSubscribedFromFreeWeekend(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return true;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamApps_GetDLCCount(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamApps_BGetDLCDataByIndex(SELF, int iDLC, AppId_t *pAppID, bool *pbAvailable, char *pchName, int cchNameBufferSize)
{
	xlogf("%s(self = %p, iDLC = %d, pAppID = %p, pbAvailable = %p, pchName = %s, cchNameBufferSize = %d)\n", __func__, self, iDLC, pAppID, pbAvailable, pchName, cchNameBufferSize);
	return true;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamApps_InstallDLC(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamApps_UninstallDLC(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamApps_RequestAppProofOfPurchaseKey(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamApps_GetCurrentBetaName(SELF, char *pchName, int cchNameBufferSize)
{
	xlogf("%s(self = %p, pchName = %s, cchNameBufferSize = %d)\n", __func__, self, pchName, cchNameBufferSize);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamApps_MarkContentCorrupt(SELF, bool bMissingFilesOnly)
{
	xlogf("%s(self = %p, bMissingFilesOnly = %d)\n", __func__, self, bMissingFilesOnly);
	return true;
}

S_CLASSAPI uint32 S_CLASSCALLTYPE
SteamAPI_ISteamApps_GetInstalledDepots(SELF, AppId_t appID, DepotId_t *pvecDepots, uint32 cMaxDepots)
{
	xlogf("%s(self = %p, appID = %d, pvecDepots = %p, cMaxDepots = %d)\n", __func__, self, appID, pvecDepots, cMaxDepots);
	return 0;
}

S_CLASSAPI uint32 S_CLASSCALLTYPE
SteamAPI_ISteamApps_GetAppInstallDir(SELF, AppId_t appID, char *pchFolder, uint32 cchFolderBufferSize)
{
	xlogf("%s(self = %p, appID = %d, pchFolder = %s, cchFolderBufferSize = %d)\n", __func__, self, appID, pchFolder, cchFolderBufferSize);
	return 1;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamApps_BIsAppInstalled(SELF, AppId_t appID)
{
	xlogf("%s(self = %p, appID = %d)\n", __func__, self, appID);
	return true;
}

S_CLASSAPI CSteamID S_CLASSCALLTYPE
SteamAPI_ISteamApps_GetAppOwner(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	CSteamID id = {0};
	return id;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamApps_GetLaunchCommandLine(SELF, char *pszCommandLine, int cubCommandLine)
{
	xlogf("%s(self = %p, pszCommandLine = %s, cubCommandLine = %d)\n", __func__, self, pszCommandLine, cubCommandLine);
	return 0;
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamApps_GetLaunchQueryParam(SELF, const char *pchKey)
{
	xlogf("%s(self = %p, pchKey = %s)\n", __func__, self, pchKey);
	return "";
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamApps_GetDlcDownloadProgress(SELF, AppId_t nAppID, uint64 *punBytesDownloaded, uint64 *punBytesTotal)
{
	xlogf("%s(self = %p, nAppID = %d, punBytesDownloaded = %p, punBytesTotal = %p)\n", __func__, self, nAppID, punBytesDownloaded, punBytesTotal);
	return true;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamApps_GetAppBuildId(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamApps_RequestAllProofOfPurchaseKeys(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamApps_GetFileDetails(SELF, const char *pszFileName)
{
	xlogf("%s(self = %p, pszFileName = %s)\n", __func__, self, pszFileName);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamApps_BIsSubscribedFromFamilySharing(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamApps_BIsTimedTrial(SELF, uint32 *punSecondsAllowed, uint32 *punSecondsPlayed)
{
	xlogf("%s(self = %p, punSecondsAllowed = %p, punSecondsPlayed = %p)\n",
	      __func__, self, punSecondsAllowed, punSecondsPlayed);
	return false;
}
