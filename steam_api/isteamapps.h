#pragma once

#include "steamtypes.h"
#include "steamclientpublic.h"

enum {
	k_cubAppProofOfPurchaseKeyMax = 240, // max supported length of a legacy cd key
};

typedef void ISteamApps;

typedef struct CSteamApps CSteamApps;

struct CSteamApps {
	CSteamBase base;
};

S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamApps_BIsSubscribed(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamApps_BIsLowViolence(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamApps_BIsCybercafe(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamApps_BIsVACBanned(SELF);
S_CLASSAPI const char *S_CLASSCALLTYPE SteamAPI_ISteamApps_GetCurrentGameLanguage(SELF);
S_CLASSAPI const char *S_CLASSCALLTYPE SteamAPI_ISteamApps_GetAvailableGameLanguages(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamApps_BGetDLCDataByIndex(SELF, int iDLC, AppId_t *pAppID, bool *pbAvailable, char *pchName, int cchNameBufferSize);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamApps_InstallDLC(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamApps_UninstallDLC(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamApps_BIsSubscribedApp(SELF, AppId_t appID);
S_CLASSAPI uint32 S_CLASSCALLTYPE SteamAPI_ISteamApps_GetEarliestPurchaseUnixTime(SELF, AppId_t nAppID);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamApps_BIsDlcInstalled(SELF, AppId_t appID);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamApps_BIsSubscribedFromFreeWeekend(SELF);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamApps_GetDLCCount(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamApps_RequestAppProofOfPurchaseKey(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamApps_GetCurrentBetaName(SELF, char *pchName, int cchNameBufferSize);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamApps_MarkContentCorrupt(SELF, bool bMissingFilesOnly);
S_CLASSAPI uint32 S_CLASSCALLTYPE SteamAPI_ISteamApps_GetInstalledDepots(SELF, AppId_t appID, DepotId_t *pvecDepots, uint32 cMaxDepots);
S_CLASSAPI uint32 S_CLASSCALLTYPE SteamAPI_ISteamApps_GetAppInstallDir(SELF, AppId_t appID, char *pchFolder, uint32 cchFolderBufferSize);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamApps_BIsAppInstalled(SELF, AppId_t appID);
S_CLASSAPI CSteamID S_CLASSCALLTYPE SteamAPI_ISteamApps_GetAppOwner(SELF);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamApps_GetLaunchCommandLine(SELF, char *pszCommandLine, int cubCommandLine);
S_CLASSAPI const char *S_CLASSCALLTYPE SteamAPI_ISteamApps_GetLaunchQueryParam(SELF, const char *pchKey);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamApps_GetDlcDownloadProgress(SELF, AppId_t nAppID, uint64 *punBytesDownloaded, uint64 *punBytesTotal);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamApps_GetAppBuildId(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamApps_RequestAllProofOfPurchaseKeys(SELF);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamApps_GetFileDetails(SELF, const char *pszFileName);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamApps_BIsSubscribedFromFamilySharing(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamApps_BIsTimedTrial(SELF, uint32 *punSecondsAllowed, uint32 *punSecondsPlayed);
