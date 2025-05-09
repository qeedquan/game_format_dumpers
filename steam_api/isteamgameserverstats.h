#pragma once

#include "steamtypes.h"

typedef void ISteamGameServerStats;

typedef struct CSteamGameServerStats CSteamGameServerStats;

struct CSteamGameServerStats {
	CSteamBase base;
};

S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamGameServerStats_ClearUserAchievement(SELF, CSteamID steamIDUser, const char *pchName);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamGameServerStats_GetUserAchievement(SELF, CSteamID steamIDUser, const char *pchName, bool *pbAchieved);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamGameServerStats_GetUserStat(SELF, CSteamID steamIDUser, const char *pchName, int32 *pData);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamGameServerStats_GetUserStat0(SELF, CSteamID steamIDUser, const char *pchName, float *pData);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamGameServerStats_SetUserStat(SELF, CSteamID steamIDUser, const char *pchName, int32 nData);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamGameServerStats_SetUserStat0(SELF, CSteamID steamIDUser, const char *pchName, float fData);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamGameServerStats_UpdateUserAvgRateStat(SELF, CSteamID steamIDUser, const char *pchName, float flCountThisSession, double dSessionLength);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamGameServerStats_SetUserAchievement(SELF, CSteamID steamIDUser, const char *pchName);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamGameServerStats_StoreUserStats(SELF, CSteamID steamIDUser);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamGameServerStats_RequestUserStats(SELF, CSteamID steamIDUser);