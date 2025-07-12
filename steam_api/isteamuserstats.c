#include "steam.h"

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_RequestCurrentStats(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetStatInt32(SELF, const char *pchName, int32 *pData)
{
	KV *kv;

	xlogf("%s(self = %p, pchName = %s, pData = %p)\n", __func__, self, pchName, pData);

	kv = lookupKV(kvUserStats, kvUserStatsLen, pchName);
	if (!kv) {
		*pData = 0;
		return false;
	}

	*pData = atoi(kv->val);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetStatFloat(SELF, const char *pchName, float *pData)
{
	KV *kv;

	xlogf("%s(self = %p, pchName = %s, pData = %p)\n", __func__, self, pchName, pData);

	kv = lookupKV(kvUserStats, kvUserStatsLen, pchName);
	if (!kv) {
		*pData = 0;
		return false;
	}

	*pData = atof(kv->val);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_SetStatInt32(SELF, const char *pchName, int32 nData)
{
	xlogf("%s(self = %p, pchName = %s, nData = %d)\n", __func__, self, pchName, nData);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_SetStatFloat(SELF, const char *pchName, float nData)
{
	xlogf("%s(self = %p, pchName = %s, nData = %f)\n", __func__, self, pchName, nData);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_UpdateAvgRateStat(SELF, const char *pchName, float flCountThisSession, double dSessionLength)
{
	xlogf("%s(self = %p, pchName = %s, flCountThisSession = %f, dSessionLength = %lf)\n", __func__, self, pchName, flCountThisSession, dSessionLength);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetAchievement(SELF, const char *pchName, bool *pbAchieved)
{
	xlogf("%s(self = %p, pchName = %s, pbAchieved = %p)\n", __func__, self, pchName, pbAchieved);
	*pbAchieved = true;
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_SetAchievement(SELF, const char *pchName)
{
	xlogf("%s(self = %p, pchName = %s)\n", __func__, self, pchName);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_ClearAchievement(SELF, const char *pchName)
{
	xlogf("%s(self = %p, pchName = %s)\n", __func__, self, pchName);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetAchievementAndUnlockTime(SELF, const char *pchName, bool *pbAchieved, uint32 *punUnlockTime)
{
	xlogf("%s(self = %p, pchName = %s, pbAchieved = %p, punUnlockTime = %p)\n", __func__, self, pchName, pbAchieved, punUnlockTime);
	*pbAchieved = true;
	*punUnlockTime = 1337;
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_StoreStats(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return true;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetAchievementIcon(SELF, const char *pchName)
{
	xlogf("%s(self = %p, pchName = %s)\n", __func__, self, pchName);
	return 0;
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetAchievementDisplayAttribute(SELF, const char *pchName, const char *pchKey)
{
	xlogf("%s(self = %p, pchName = %s, pchKey = %s)\n", __func__, self, pchName, pchKey);
	return "";
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_IndicateAchievementProgress(SELF, const char *pchName, uint32 nCurProgress, uint32 nMaxProgress)
{
	xlogf("%s(self = %p, pchName = %s, nCurProgress = %d, nMaxProgress = %d)\n", __func__, self, pchName, nCurProgress, nMaxProgress);
	return true;
}

S_CLASSAPI uint32 S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetNumAchievements(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetAchievementName(SELF, uint32 iAchievement)
{
	xlogf("%s(self = %p, iAchievement = %d)\n", __func__, self, iAchievement);
	return "";
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_RequestUserStats(SELF, CSteamID steamIDUser)
{
	xlogf("%s(self = %p, steamIDUser = %llu)\n", __func__, self, steamIDUser.m_gameID);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetUserStat(SELF, CSteamID steamIDUser, const char *pchName, int32 *pData)
{
	xlogf("%s(self = %p, steamIDUser = %llu, pchName = %s, pData = %p)\n", __func__, self, steamIDUser.m_gameID, pchName, pData);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetUserStat0(SELF, CSteamID steamIDUser, const char *pchName, float *pData)
{
	xlogf("%s(self = %p, steamIDUser = %llu, pchName = %s, pData = %p)\n", __func__, self, steamIDUser.m_gameID, pchName, pData);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetUserAchievement(SELF, CSteamID steamIDUser, const char *pchName, bool *pbAchieved)
{
	xlogf("%s(self = %p, steamIDUser = %llu, pchName = %s, pbAchieved = %p)\n", __func__, self, steamIDUser.m_gameID, pchName, pbAchieved);
	*pbAchieved = true;
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetUserAchievementAndUnlockTime(SELF, CSteamID steamIDUser, const char *pchName, bool *pbAchieved, uint32 *punUnlockTime)
{
	xlogf("%s(self = %p, steamIDUser = %llu, pchName = %s, pbAchieved = %p, punUnlockTime = %p)\n", __func__, self, steamIDUser.m_gameID, pchName, pbAchieved, punUnlockTime);
	*pbAchieved = true;
	*punUnlockTime = 1337;
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_ResetAllStats(SELF, bool bAchievementsToo)
{
	xlogf("%s(self = %p, bAchievementsToo = %d)\n", __func__, self, bAchievementsToo);
	return true;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_FindOrCreateLeaderboard(SELF, const char *pchLeaderboardName, ELeaderboardSortMethod eLeaderboardSortMethod, ELeaderboardDisplayType eLeaderboardDisplayType)
{
	xlogf("%s(self = %p, pchLeaderboardName = %s, eLeaderboardSortMethod = %d, eLeaderboardDisplayType = %d)\n", __func__, self, pchLeaderboardName, eLeaderboardSortMethod, eLeaderboardDisplayType);
	return 0;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_FindLeaderboard(SELF, const char *pchLeaderboardName)
{
	xlogf("%s(self = %p, pchLeaderboardName = %s)\n", __func__, self, pchLeaderboardName);
	return 0;
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetLeaderboardName(SELF, SteamLeaderboard_t hSteamLeaderboard)
{
	xlogf("%s(self = %p, hSteamLeaderboard = %llu)\n", __func__, self, hSteamLeaderboard);
	return "";
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetLeaderboardEntryCount(SELF, SteamLeaderboard_t hSteamLeaderboard)
{
	xlogf("%s(self = %p, hSteamLeaderboard = %llu)\n", __func__, self, hSteamLeaderboard);
	return 0;
}

S_CLASSAPI ELeaderboardSortMethod S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetLeaderboardSortMethod(SELF, SteamLeaderboard_t hSteamLeaderboard)
{
	xlogf("%s(self = %p, hSteamLeaderboard = %llu)\n", __func__, self, hSteamLeaderboard);
	return 0;
}

S_CLASSAPI ELeaderboardDisplayType S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetLeaderboardDisplayType(SELF, SteamLeaderboard_t hSteamLeaderboard)
{
	xlogf("%s(self = %p, hSteamLeaderboard = %llu)\n", __func__, self, hSteamLeaderboard);
	return 0;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_DownloadLeaderboardEntries(SELF, SteamLeaderboard_t hSteamLeaderboard, ELeaderboardDataRequest eLeaderboardDataRequest, int nRangeStart, int nRangeEnd)
{
	xlogf("%s(self = %p, hSteamLeaderboard = %llu, eLeaderboardDataRequest = %d, nRangeStart = %d, nRangeEnd = %d)\n", __func__, self, hSteamLeaderboard, eLeaderboardDataRequest, nRangeStart, nRangeEnd);
	return 0;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_DownloadLeaderboardEntriesForUsers(SELF, SteamLeaderboard_t hSteamLeaderboard)
{
	xlogf("%s(self = %p, hSteamLeaderboard = %llu)\n", __func__, self, hSteamLeaderboard);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetDownloadedLeaderboardEntry(SELF, SteamLeaderboardEntries_t hSteamLeaderboardEntries, int index, LeaderboardEntry_t *pLeaderboardEntry, int32 *pDetails, int cDetailsMax)
{
	xlogf("%s(self = %p, hSteamLeaderboardEntries = %llu, index = %d, pLeaderboardEntry = %p, pDetails = %p, cDetailsMax = %d)\n", __func__, self, hSteamLeaderboardEntries, index, pLeaderboardEntry, pDetails, cDetailsMax);
	return true;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_UploadLeaderboardScore(SELF, SteamLeaderboard_t hSteamLeaderboard, ELeaderboardUploadScoreMethod eLeaderboardUploadScoreMethod, int32 nScore, const int32 *pScoreDetails, int cScoreDetailsCount)
{
	xlogf("%s(self = %p, hSteamLeaderboard = %llu, eLeaderboardUploadScoreMethod = %d, nScore = %d, pScoreDetails = %p, cScoreDetailsCount = %d)\n", __func__, self, hSteamLeaderboard, eLeaderboardUploadScoreMethod, nScore, pScoreDetails, cScoreDetailsCount);
	return 0;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_AttachLeaderboardUGC(SELF, SteamLeaderboard_t hSteamLeaderboard, UGCHandle_t hUGC)
{
	xlogf("%s(self = %p, hSteamLeaderboard = %llu, hUGC = %llu)\n", __func__, self, hSteamLeaderboard, hUGC);
	return 0;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetNumberOfCurrentPlayers(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_RequestGlobalAchievementPercentages(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetMostAchievedAchievementInfo(SELF, char *pchName, uint32 unNameBufLen, float *pflPercent, bool *pbAchieved)
{
	xlogf("%s(self = %p, pchName = %s, unNameBufLen = %d, pflPercent = %p, pbAchieved = %p)\n", __func__, self, pchName, unNameBufLen, pflPercent, pbAchieved);
	*pflPercent = 100;
	*pbAchieved = true;
	return 0;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetNextMostAchievedAchievementInfo(SELF, int iIteratorPrevious, char *pchName, uint32 unNameBufLen, float *pflPercent, bool *pbAchieved)
{
	xlogf("%s(self = %p, iIteratorPrevious = %d, pchName = %s, unNameBufLen = %d, pflPercent = %p, pbAchieved = %p)\n", __func__, self, iIteratorPrevious, pchName, unNameBufLen, pflPercent, pbAchieved);
	*pflPercent = 100;
	*pbAchieved = true;
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetAchievementAchievedPercent(SELF, const char *pchName, float *pflPercent)
{
	xlogf("%s(self = %p, pchName = %s, pflPercent = %p)\n", __func__, self, pchName, pflPercent);
	*pflPercent = 100;
	return true;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_RequestGlobalStats(SELF, int nHistoryDays)
{
	xlogf("%s(self = %p, nHistoryDays = %d)\n", __func__, self, nHistoryDays);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetGlobalStat(SELF, const char *pchStatName, int64 *pData)
{
	xlogf("%s(self = %p, pchStatName = %s, pData = %p)\n", __func__, self, pchStatName, pData);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetGlobalStatFloat(SELF, const char *pchStatName, float *pData)
{
	xlogf("%s(self = %p, pchStatName = %s, pData = %p)\n", __func__, self, pchStatName, pData);
	return true;
}

S_CLASSAPI int32 S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetGlobalStatHistory(SELF, const char *pchStatName, int64 *pData, uint32 cubData)
{
	xlogf("%s(self = %p, pchStatName = %s, pData = %p, cubData = %d)\n", __func__, self, pchStatName, pData, cubData);
	return 0;
}

S_CLASSAPI int32 S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetGlobalStatHistoryFloat(SELF, const char *pchStatName, float *pData, uint32 cubData)
{
	xlogf("%s(self = %p, pchStatName = %s, pData = %p, cubData = %d)\n", __func__, self, pchStatName, pData, cubData);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetGlobalStatInt64(SELF, const char *pchStatName, int64 *pData)
{
	xlogf("%s(self = %p, pchStatName = %s, pData = %p)\n", __func__, self, pchStatName, pData);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetGlobalStatDouble(SELF, const char *pchStatName, double *pData)
{
	xlogf("%s(self = %p, pchStatName = %s, pData = %p)\n", __func__, self, pchStatName, pData);
	return false;
}

S_CLASSAPI int32 S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetGlobalStatHistoryInt64(SELF, const char *pchStatName, int64 *pData, uint32 cubData)
{
	xlogf("%s(self = %p, pchStatName = %s, pData = %p, cubData = %d)\n", __func__, self, pchStatName, pData, cubData);
	return 0;
}

S_CLASSAPI int32 S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetGlobalStatHistoryDouble(SELF, const char *pchStatName, double *pData, uint32 cubData)
{
	xlogf("%s(self = %p, pchStatName = %s, pData = %p, cubData = %d)\n", __func__, self, pchStatName, pData, cubData);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetAchievementProgressLimitsInt32(SELF, const char *pchName, int32 *pnMinProgress, int32 *pnMaxProgress)
{
	xlogf("%s(self = %p, pchName = %s, pnMinProgress = %p, pnMaxProgress = %p)\n", __func__, self, pchName, pnMinProgress, pnMaxProgress);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUserStats_GetAchievementProgressLimitsFloat(SELF, const char *pchName, float *pnMinProgress, float *pnMaxProgress)
{
	xlogf("%s(self = %p, pchName = %s, pnMinProgress = %p, pnMaxProgress = %p)\n", __func__, self, pchName, pnMinProgress, pnMaxProgress);
	return false;
}
