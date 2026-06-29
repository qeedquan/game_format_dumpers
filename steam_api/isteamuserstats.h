#pragma once

#include "steamclientpublic.h"
#include "steamtypes.h"

typedef uint64 SteamLeaderboard_t;
typedef uint64 SteamLeaderboardEntries_t;

// the sort order of a leaderboard
typedef enum {
	k_ELeaderboardSortMethodNone = 0,
	k_ELeaderboardSortMethodAscending = 1,  // top-score is lowest number
	k_ELeaderboardSortMethodDescending = 2, // top-score is highest number
} ELeaderboardSortMethod;

// the display type (used by the Steam Community web site) for a leaderboard
typedef enum {
	k_ELeaderboardDisplayTypeNone = 0,
	k_ELeaderboardDisplayTypeNumeric = 1,          // simple numerical score
	k_ELeaderboardDisplayTypeTimeSeconds = 2,      // the score represents a time, in seconds
	k_ELeaderboardDisplayTypeTimeMilliSeconds = 3, // the score represents a time, in milliseconds
} ELeaderboardDisplayType;

typedef enum {
	k_ELeaderboardUploadScoreMethodNone = 0,
	k_ELeaderboardUploadScoreMethodKeepBest = 1,    // Leaderboard will keep user's best score
	k_ELeaderboardUploadScoreMethodForceUpdate = 2, // Leaderboard will always replace score with specified
} ELeaderboardUploadScoreMethod;

// type of data request, when downloading leaderboard entries
typedef enum {
	k_ELeaderboardDataRequestGlobal = 0,
	k_ELeaderboardDataRequestGlobalAroundUser = 1,
	k_ELeaderboardDataRequestFriends = 2,
	k_ELeaderboardDataRequestUsers = 3
} ELeaderboardDataRequest;

typedef struct LeaderboardEntry_t LeaderboardEntry_t;

struct LeaderboardEntry_t {
	CSteamID m_steamIDUser; // user with the entry - use SteamFriends()->GetFriendPersonaName() & SteamFriends()->GetFriendAvatar() to get more info
	int32 m_nGlobalRank;    // [1..N], where N is the number of users with an entry in the leaderboard
	int32 m_nScore;         // score as set in the leaderboard
	int32 m_cDetails;       // number of int32 details available for this entry
	UGCHandle_t m_hUGC;     // handle for UGC attached to the entry
};

typedef void ISteamUserStats;

typedef struct CSteamUserStats CSteamUserStats;

struct CSteamUserStats {
	CSteamBase base;
};

S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUserStats_RequestCurrentStats(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetStatInt32(SELF, const char *pchName, int32 *pData);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetStatFloat(SELF, const char *pchName, float *pData);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUserStats_SetStatInt32(SELF, const char *pchName, int32 nData);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUserStats_SetStatFloat(SELF, const char *pchName, float nData);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUserStats_UpdateAvgRateStat(SELF, const char *pchName, float flCountThisSession, double dSessionLength);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetAchievement(SELF, const char *pchName, bool *pbAchieved);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUserStats_SetAchievement(SELF, const char *pchName);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUserStats_ClearAchievement(SELF, const char *pchName);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetAchievementAndUnlockTime(SELF, const char *pchName, bool *pbAchieved, uint32 *punUnlockTime);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUserStats_StoreStats(SELF);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetAchievementIcon(SELF, const char *pchName);
S_CLASSAPI const char *S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetAchievementDisplayAttribute(SELF, const char *pchName, const char *pchKey);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUserStats_IndicateAchievementProgress(SELF, const char *pchName, uint32 nCurProgress, uint32 nMaxProgress);
S_CLASSAPI uint32 S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetNumAchievements(SELF);
S_CLASSAPI const char *S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetAchievementName(SELF, uint32 iAchievement);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUserStats_RequestUserStats(SELF, CSteamID steamIDUser);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetUserStat(SELF, CSteamID steamIDUser, const char *pchName, int32 *pData);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetUserStat0(SELF, CSteamID steamIDUser, const char *pchName, float *pData);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetUserAchievement(SELF, CSteamID steamIDUser, const char *pchName, bool *pbAchieved);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetUserAchievementAndUnlockTime(SELF, CSteamID steamIDUser, const char *pchName, bool *pbAchieved, uint32 *punUnlockTime);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUserStats_ResetAllStats(SELF, bool bAchievementsToo);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUserStats_FindOrCreateLeaderboard(SELF, const char *pchLeaderboardName, ELeaderboardSortMethod eLeaderboardSortMethod, ELeaderboardDisplayType eLeaderboardDisplayType);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUserStats_FindLeaderboard(SELF, const char *pchLeaderboardName);
S_CLASSAPI const char *S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetLeaderboardName(SELF, SteamLeaderboard_t hSteamLeaderboard);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetLeaderboardEntryCount(SELF, SteamLeaderboard_t hSteamLeaderboard);
S_CLASSAPI ELeaderboardSortMethod S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetLeaderboardSortMethod(SELF, SteamLeaderboard_t hSteamLeaderboard);
S_CLASSAPI ELeaderboardDisplayType S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetLeaderboardDisplayType(SELF, SteamLeaderboard_t hSteamLeaderboard);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUserStats_DownloadLeaderboardEntries(SELF, SteamLeaderboard_t hSteamLeaderboard, ELeaderboardDataRequest eLeaderboardDataRequest, int nRangeStart, int nRangeEnd);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUserStats_DownloadLeaderboardEntriesForUsers(SELF, SteamLeaderboard_t hSteamLeaderboard);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetDownloadedLeaderboardEntry(SELF, SteamLeaderboardEntries_t hSteamLeaderboardEntries, int index, LeaderboardEntry_t *pLeaderboardEntry, int32 *pDetails, int cDetailsMax);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUserStats_UploadLeaderboardScore(SELF, SteamLeaderboard_t hSteamLeaderboard, ELeaderboardUploadScoreMethod eLeaderboardUploadScoreMethod, int32 nScore, const int32 *pScoreDetails, int cScoreDetailsCount);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUserStats_AttachLeaderboardUGC(SELF, SteamLeaderboard_t hSteamLeaderboard, UGCHandle_t hUGC);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetNumberOfCurrentPlayers(SELF);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUserStats_RequestGlobalAchievementPercentages(SELF);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetMostAchievedAchievementInfo(SELF, char *pchName, uint32 unNameBufLen, float *pflPercent, bool *pbAchieved);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetNextMostAchievedAchievementInfo(SELF, int iIteratorPrevious, char *pchName, uint32 unNameBufLen, float *pflPercent, bool *pbAchieved);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetAchievementAchievedPercent(SELF, const char *pchName, float *pflPercent);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUserStats_RequestGlobalStats(SELF, int nHistoryDays);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetGlobalStat(SELF, const char *pchStatName, int64 *pData);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetGlobalStat0(SELF, const char *pchStatName, float *pData);
S_CLASSAPI int32 S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetGlobalStatHistory(SELF, const char *pchStatName, int64 *pData, uint32 cubData);
S_CLASSAPI int32 S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetGlobalStatHistory0(SELF, const char *pchStatName, float *pData, uint32 cubData);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetGlobalStatInt64(SELF, const char *pchStatName, int64 *pData);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetGlobalStatDouble(SELF, const char *pchStatName, double *pData);
S_CLASSAPI int32 S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetGlobalStatHistoryInt64(SELF, const char *pchStatName, int64 *pData, uint32 cubData);
S_CLASSAPI int32 S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetGlobalStatHistoryDouble(SELF, const char *pchStatName, double *pData, uint32 cubData);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetAchievementProgressLimitsInt32(SELF, const char *pchName, int32 *pnMinProgress, int32 *pnMaxProgress);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUserStats_GetAchievementProgressLimitsFloat(SELF, const char *pchName, float *pnMinProgress, float *pnMaxProgress);
