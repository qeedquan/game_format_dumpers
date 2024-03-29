#include "steam.h"

static void *vtable_ISteamUserStats011[] = {
    SteamAPI_ISteamUserStats_RequestCurrentStats,
    SteamAPI_ISteamUserStats_GetStatInt32,
    SteamAPI_ISteamUserStats_GetStatFloat,
    SteamAPI_ISteamUserStats_SetStatInt32,
    SteamAPI_ISteamUserStats_SetStatFloat,
    SteamAPI_ISteamUserStats_UpdateAvgRateStat,
    SteamAPI_ISteamUserStats_GetAchievement,
    SteamAPI_ISteamUserStats_SetAchievement,
    SteamAPI_ISteamUserStats_ClearAchievement,
    SteamAPI_ISteamUserStats_GetAchievementAndUnlockTime,
    SteamAPI_ISteamUserStats_StoreStats,
    SteamAPI_ISteamUserStats_GetAchievementIcon,
    SteamAPI_ISteamUserStats_GetAchievementDisplayAttribute,
    SteamAPI_ISteamUserStats_IndicateAchievementProgress,
    SteamAPI_ISteamUserStats_GetNumAchievements,
    SteamAPI_ISteamUserStats_GetAchievementName,
    SteamAPI_ISteamUserStats_RequestUserStats,
    SteamAPI_ISteamUserStats_GetUserStat,
    SteamAPI_ISteamUserStats_GetUserStat,
    SteamAPI_ISteamUserStats_GetUserAchievement,
    SteamAPI_ISteamUserStats_GetUserAchievementAndUnlockTime,
    SteamAPI_ISteamUserStats_ResetAllStats,
    SteamAPI_ISteamUserStats_FindOrCreateLeaderboard,
    SteamAPI_ISteamUserStats_FindLeaderboard,
    SteamAPI_ISteamUserStats_GetLeaderboardName,
    SteamAPI_ISteamUserStats_GetLeaderboardEntryCount,
    SteamAPI_ISteamUserStats_GetLeaderboardSortMethod,
    SteamAPI_ISteamUserStats_GetLeaderboardDisplayType,
    SteamAPI_ISteamUserStats_DownloadLeaderboardEntries,
    SteamAPI_ISteamUserStats_DownloadLeaderboardEntriesForUsers,
    SteamAPI_ISteamUserStats_GetDownloadedLeaderboardEntry,
    SteamAPI_ISteamUserStats_UploadLeaderboardScore,
    SteamAPI_ISteamUserStats_AttachLeaderboardUGC,
    SteamAPI_ISteamUserStats_GetNumberOfCurrentPlayers,
    SteamAPI_ISteamUserStats_RequestGlobalAchievementPercentages,
    SteamAPI_ISteamUserStats_GetMostAchievedAchievementInfo,
    SteamAPI_ISteamUserStats_GetNextMostAchievedAchievementInfo,
    SteamAPI_ISteamUserStats_GetAchievementAchievedPercent,
    SteamAPI_ISteamUserStats_RequestGlobalStats,
    SteamAPI_ISteamUserStats_GetGlobalStatInt64,
    SteamAPI_ISteamUserStats_GetGlobalStatDouble,
    SteamAPI_ISteamUserStats_GetGlobalStatHistoryInt64,
    SteamAPI_ISteamUserStats_GetGlobalStatHistoryDouble,
};

static void *vtable_ISteamUserStats012[] = {
    SteamAPI_ISteamUserStats_RequestCurrentStats,
    SteamAPI_ISteamUserStats_GetStatInt32,
    SteamAPI_ISteamUserStats_GetStatFloat,
    SteamAPI_ISteamUserStats_SetStatInt32,
    SteamAPI_ISteamUserStats_SetStatFloat,
    SteamAPI_ISteamUserStats_UpdateAvgRateStat,
    SteamAPI_ISteamUserStats_GetAchievement,
    SteamAPI_ISteamUserStats_SetAchievement,
    SteamAPI_ISteamUserStats_ClearAchievement,
    SteamAPI_ISteamUserStats_GetAchievementAndUnlockTime,
    SteamAPI_ISteamUserStats_StoreStats,
    SteamAPI_ISteamUserStats_GetAchievementIcon,
    SteamAPI_ISteamUserStats_GetAchievementDisplayAttribute,
    SteamAPI_ISteamUserStats_IndicateAchievementProgress,
    SteamAPI_ISteamUserStats_GetNumAchievements,
    SteamAPI_ISteamUserStats_GetAchievementName,
    SteamAPI_ISteamUserStats_RequestUserStats,
    SteamAPI_ISteamUserStats_GetUserStat,
    SteamAPI_ISteamUserStats_GetUserStat,
    SteamAPI_ISteamUserStats_GetUserAchievement,
    SteamAPI_ISteamUserStats_GetUserAchievementAndUnlockTime,
    SteamAPI_ISteamUserStats_ResetAllStats,
    SteamAPI_ISteamUserStats_FindOrCreateLeaderboard,
    SteamAPI_ISteamUserStats_FindLeaderboard,
    SteamAPI_ISteamUserStats_GetLeaderboardName,
    SteamAPI_ISteamUserStats_GetLeaderboardEntryCount,
    SteamAPI_ISteamUserStats_GetLeaderboardSortMethod,
    SteamAPI_ISteamUserStats_GetLeaderboardDisplayType,
    SteamAPI_ISteamUserStats_DownloadLeaderboardEntries,
    SteamAPI_ISteamUserStats_DownloadLeaderboardEntriesForUsers,
    SteamAPI_ISteamUserStats_GetDownloadedLeaderboardEntry,
    SteamAPI_ISteamUserStats_UploadLeaderboardScore,
    SteamAPI_ISteamUserStats_AttachLeaderboardUGC,
    SteamAPI_ISteamUserStats_GetNumberOfCurrentPlayers,
    SteamAPI_ISteamUserStats_RequestGlobalAchievementPercentages,
    SteamAPI_ISteamUserStats_GetMostAchievedAchievementInfo,
    SteamAPI_ISteamUserStats_GetNextMostAchievedAchievementInfo,
    SteamAPI_ISteamUserStats_GetAchievementAchievedPercent,
    SteamAPI_ISteamUserStats_RequestGlobalStats,
    SteamAPI_ISteamUserStats_GetGlobalStatInt64,
    SteamAPI_ISteamUserStats_GetGlobalStatDouble,
    SteamAPI_ISteamUserStats_GetGlobalStatHistoryInt64,
    SteamAPI_ISteamUserStats_GetGlobalStatHistoryDouble,
    SteamAPI_ISteamUserStats_GetAchievementProgressLimitsInt32,
    SteamAPI_ISteamUserStats_GetAchievementProgressLimitsFloat,
};

VtableEntry vtable_ISteamUserStats[] = {
    {11, vtable_ISteamUserStats011, sizeof(vtable_ISteamUserStats011), 0},
    {12, vtable_ISteamUserStats012, sizeof(vtable_ISteamUserStats012), 0},
    {0, NULL, 0, 0},
};