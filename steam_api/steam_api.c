#include "steam.h"

CSteamContext ctx;

EXPORT ISteamGameServer *g_pSteamClientGameServer = &ctx.gameServer;

S_CLASSAPI void S_CLASSCALLTYPE traceCall(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
#if defined(_WIN32)
	DebugBreak();
#else
	__builtin_trap();
#endif
}

S_CLASSAPI void S_CLASSCALLTYPE logCall(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

void
initSteamBase(CSteamBase *p)
{
	size_t i;

	p->vptr = p->vtable;
	for (i = 0; i < nelem(p->vtable); i++)
		p->vtable[i] = traceCall;
}

void
initSteamDummy(void)
{
	CSteamBase *p = &ctx.dummy;
	size_t i;

	initSteamBase(p);
	for (i = 0; i < nelem(p->vtable); i++)
		p->vtable[i] = logCall;
}

void
initSteamUtils(void)
{
	CSteamUtils *z = &ctx.utils;
	CSteamBase *p = &z->base;

	initSteamBase(p);
	p->vtable[0] = SteamAPI_ISteamUtils_GetSecondsSinceAppActive;
	p->vtable[1] = SteamAPI_ISteamUtils_GetSecondsSinceComputerActive;
	p->vtable[2] = SteamAPI_ISteamUtils_GetConnectedUniverse;
	p->vtable[3] = SteamAPI_ISteamUtils_GetServerRealTime;
	p->vtable[4] = SteamAPI_ISteamUtils_GetIPCountry;
	p->vtable[5] = SteamAPI_ISteamUtils_GetImageSize;
	p->vtable[6] = SteamAPI_ISteamUtils_GetImageRGBA;
	p->vtable[7] = SteamAPI_ISteamUtils_GetCSERIPPort;
	p->vtable[8] = SteamAPI_ISteamUtils_GetCurrentBatteryPower;
	p->vtable[9] = SteamAPI_ISteamUtils_GetAppID;
	p->vtable[10] = SteamAPI_ISteamUtils_SetOverlayNotificationPosition;
	p->vtable[11] = SteamAPI_ISteamUtils_IsAPICallCompleted;
	p->vtable[12] = SteamAPI_ISteamUtils_GetAPICallFailureReason;
	p->vtable[13] = SteamAPI_ISteamUtils_GetAPICallResult;
	p->vtable[14] = SteamAPI_ISteamUtils_RunFrame;
	p->vtable[15] = SteamAPI_ISteamUtils_GetIPCCallCount;
	p->vtable[16] = SteamAPI_ISteamUtils_SetWarningMessageHook;
	p->vtable[17] = SteamAPI_ISteamUtils_IsOverlayEnabled;
	p->vtable[18] = SteamAPI_ISteamUtils_BOverlayNeedsPresent;
	p->vtable[19] = SteamAPI_ISteamUtils_CheckFileSignature;
	p->vtable[20] = SteamAPI_ISteamUtils_ShowGamepadTextInput;
	p->vtable[21] = SteamAPI_ISteamUtils_GetEnteredGamepadTextLength;
	p->vtable[22] = SteamAPI_ISteamUtils_GetEnteredGamepadTextInput;
	p->vtable[23] = SteamAPI_ISteamUtils_GetSteamUILanguage;
	p->vtable[24] = SteamAPI_ISteamUtils_IsSteamRunningInVR;
	p->vtable[25] = SteamAPI_ISteamUtils_SetOverlayNotificationInset;
	p->vtable[26] = SteamAPI_ISteamUtils_IsSteamInBigPictureMode;
	p->vtable[27] = SteamAPI_ISteamUtils_IsVRHeadsetStreamingEnabled;
	p->vtable[28] = SteamAPI_ISteamUtils_SetVRHeadsetStreamingEnabled;
	p->vtable[29] = SteamAPI_ISteamUtils_StartVRDashboard;
}

void
initSteamApps(void)
{
	CSteamApps *z = &ctx.apps;
	CSteamBase *p = &z->base;

	initSteamBase(p);
	p->vtable[0] = SteamAPI_ISteamApps_BIsSubscribed;
	p->vtable[1] = SteamAPI_ISteamApps_BIsLowViolence;
	p->vtable[2] = SteamAPI_ISteamApps_BIsCybercafe;
	p->vtable[3] = SteamAPI_ISteamApps_BIsVACBanned;
	p->vtable[4] = SteamAPI_ISteamApps_GetCurrentGameLanguage;
	p->vtable[5] = SteamAPI_ISteamApps_GetAvailableGameLanguages;
	p->vtable[6] = SteamAPI_ISteamApps_BIsSubscribedApp;
	p->vtable[7] = SteamAPI_ISteamApps_BIsDlcInstalled;
	p->vtable[8] = SteamAPI_ISteamApps_GetEarliestPurchaseUnixTime;
	p->vtable[9] = SteamAPI_ISteamApps_BIsSubscribedFromFreeWeekend;
	p->vtable[10] = SteamAPI_ISteamApps_GetDLCCount;
	p->vtable[11] = SteamAPI_ISteamApps_BGetDLCDataByIndex;
	p->vtable[12] = SteamAPI_ISteamApps_InstallDLC;
	p->vtable[13] = SteamAPI_ISteamApps_UninstallDLC;
	p->vtable[14] = SteamAPI_ISteamApps_RequestAppProofOfPurchaseKey;
	p->vtable[15] = SteamAPI_ISteamApps_GetCurrentBetaName;
	p->vtable[16] = SteamAPI_ISteamApps_MarkContentCorrupt;
	p->vtable[17] = SteamAPI_ISteamApps_GetInstalledDepots;
	p->vtable[18] = SteamAPI_ISteamApps_GetAppInstallDir;
	p->vtable[19] = SteamAPI_ISteamApps_BIsAppInstalled;
	p->vtable[20] = SteamAPI_ISteamApps_GetAppOwner;
	p->vtable[21] = SteamAPI_ISteamApps_GetLaunchQueryParam;
	p->vtable[22] = SteamAPI_ISteamApps_GetDlcDownloadProgress;
	p->vtable[23] = SteamAPI_ISteamApps_GetAppBuildId;
}

void
initSteamController(void)
{
	CSteamController *z = &ctx.controller;
	CSteamBase *p = &z->base;

	initSteamBase(p);
	p->vtable[0] = SteamAPI_ISteamController_Init;
	p->vtable[1] = SteamAPI_ISteamController_Shutdown;
	p->vtable[2] = SteamAPI_ISteamController_RunFrame;
	p->vtable[3] = SteamAPI_ISteamController_GetConnectedControllers;
	p->vtable[4] = SteamAPI_ISteamController_ShowBindingPanel;
	p->vtable[5] = SteamAPI_ISteamController_GetActionSetHandle;
	p->vtable[6] = SteamAPI_ISteamController_ActivateActionSet;
	p->vtable[7] = SteamAPI_ISteamController_GetCurrentActionSet;
	p->vtable[8] = SteamAPI_ISteamController_GetDigitalActionHandle;
	p->vtable[9] = SteamAPI_ISteamController_GetDigitalActionData;
	p->vtable[10] = SteamAPI_ISteamController_GetDigitalActionOrigins;
	p->vtable[11] = SteamAPI_ISteamController_GetAnalogActionHandle;
	p->vtable[12] = SteamAPI_ISteamController_GetAnalogActionData;
	p->vtable[13] = SteamAPI_ISteamController_GetAnalogActionOrigins;
	p->vtable[14] = SteamAPI_ISteamController_StopAnalogActionMomentum;
	p->vtable[15] = SteamAPI_ISteamController_TriggerHapticPulse;
}

void
initSteamUser(void)
{
	CSteamUser *z = &ctx.user;
	CSteamBase *p = &z->base;

	initSteamBase(p);
	p->vtable[0] = SteamAPI_ISteamUser_GetHSteamUser;
	p->vtable[1] = SteamAPI_ISteamUser_BLoggedOn;
	p->vtable[2] = SteamAPI_ISteamUser_GetSteamID;
	p->vtable[3] = SteamAPI_ISteamUser_InitiateGameConnection;
	p->vtable[4] = SteamAPI_ISteamUser_TerminateGameConnection;
	p->vtable[5] = SteamAPI_ISteamUser_TrackAppUsageEvent;
	p->vtable[6] = SteamAPI_ISteamUser_GetUserDataFolder;
	p->vtable[7] = SteamAPI_ISteamUser_StartVoiceRecording;
	p->vtable[8] = SteamAPI_ISteamUser_StopVoiceRecording;
	p->vtable[9] = SteamAPI_ISteamUser_GetAvailableVoice;
	p->vtable[10] = SteamAPI_ISteamUser_GetVoice;
	p->vtable[11] = SteamAPI_ISteamUser_DecompressVoice;
	p->vtable[12] = SteamAPI_ISteamUser_GetVoiceOptimalSampleRate;
	p->vtable[13] = SteamAPI_ISteamUser_GetAuthSessionTicket;
	p->vtable[14] = SteamAPI_ISteamUser_BeginAuthSession;
	p->vtable[15] = SteamAPI_ISteamUser_EndAuthSession;
	p->vtable[16] = SteamAPI_ISteamUser_CancelAuthTicket;
	p->vtable[17] = SteamAPI_ISteamUser_UserHasLicenseForApp;
	p->vtable[18] = SteamAPI_ISteamUser_BIsBehindNAT;
	p->vtable[19] = SteamAPI_ISteamUser_AdvertiseGame;
	p->vtable[20] = SteamAPI_ISteamUser_RequestEncryptedAppTicket;
	p->vtable[21] = SteamAPI_ISteamUser_GetEncryptedAppTicket;
	p->vtable[22] = SteamAPI_ISteamUser_GetGameBadgeLevel;
	p->vtable[23] = SteamAPI_ISteamUser_GetPlayerSteamLevel;
	p->vtable[24] = SteamAPI_ISteamUser_RequestStoreAuthURL;
}

void
initSteamUserStats(void)
{
	CSteamUserStats *z = &ctx.userStats;
	CSteamBase *p = &z->base;

	initSteamBase(p);
	p->vtable[0] = SteamAPI_ISteamUserStats_RequestCurrentStats;
	p->vtable[1] = SteamAPI_ISteamUserStats_GetStat;
	p->vtable[2] = SteamAPI_ISteamUserStats_GetStat0;
	p->vtable[3] = SteamAPI_ISteamUserStats_SetStat;
	p->vtable[4] = SteamAPI_ISteamUserStats_SetStat0;
	p->vtable[5] = SteamAPI_ISteamUserStats_UpdateAvgRateStat;
	p->vtable[6] = SteamAPI_ISteamUserStats_GetAchievement;
	p->vtable[7] = SteamAPI_ISteamUserStats_SetAchievement;
	p->vtable[8] = SteamAPI_ISteamUserStats_ClearAchievement;
	p->vtable[9] = SteamAPI_ISteamUserStats_GetAchievementAndUnlockTime;
	p->vtable[10] = SteamAPI_ISteamUserStats_StoreStats;
	p->vtable[11] = SteamAPI_ISteamUserStats_GetAchievementIcon;
	p->vtable[12] = SteamAPI_ISteamUserStats_GetAchievementDisplayAttribute;
	p->vtable[13] = SteamAPI_ISteamUserStats_IndicateAchievementProgress;
	p->vtable[14] = SteamAPI_ISteamUserStats_GetNumAchievements;
	p->vtable[15] = SteamAPI_ISteamUserStats_GetAchievementName;
	p->vtable[16] = SteamAPI_ISteamUserStats_RequestUserStats;
	p->vtable[17] = SteamAPI_ISteamUserStats_GetUserStat;
	p->vtable[18] = SteamAPI_ISteamUserStats_GetUserStat0;
	p->vtable[19] = SteamAPI_ISteamUserStats_GetUserAchievement;
	p->vtable[20] = SteamAPI_ISteamUserStats_GetUserAchievementAndUnlockTime;
	p->vtable[21] = SteamAPI_ISteamUserStats_ResetAllStats;
	p->vtable[22] = SteamAPI_ISteamUserStats_FindOrCreateLeaderboard;
	p->vtable[23] = SteamAPI_ISteamUserStats_FindLeaderboard;
	p->vtable[24] = SteamAPI_ISteamUserStats_GetLeaderboardName;
	p->vtable[25] = SteamAPI_ISteamUserStats_GetLeaderboardEntryCount;
	p->vtable[26] = SteamAPI_ISteamUserStats_GetLeaderboardSortMethod;
	p->vtable[27] = SteamAPI_ISteamUserStats_GetLeaderboardDisplayType;
	p->vtable[28] = SteamAPI_ISteamUserStats_DownloadLeaderboardEntries;
	p->vtable[29] = SteamAPI_ISteamUserStats_DownloadLeaderboardEntriesForUsers;
	p->vtable[30] = SteamAPI_ISteamUserStats_GetDownloadedLeaderboardEntry;
	p->vtable[31] = SteamAPI_ISteamUserStats_UploadLeaderboardScore;
	p->vtable[32] = SteamAPI_ISteamUserStats_AttachLeaderboardUGC;
	p->vtable[33] = SteamAPI_ISteamUserStats_GetNumberOfCurrentPlayers;
	p->vtable[34] = SteamAPI_ISteamUserStats_RequestGlobalAchievementPercentages;
	p->vtable[35] = SteamAPI_ISteamUserStats_GetMostAchievedAchievementInfo;
	p->vtable[36] = SteamAPI_ISteamUserStats_GetNextMostAchievedAchievementInfo;
	p->vtable[37] = SteamAPI_ISteamUserStats_GetAchievementAchievedPercent;
	p->vtable[38] = SteamAPI_ISteamUserStats_RequestGlobalStats;
	p->vtable[39] = SteamAPI_ISteamUserStats_GetGlobalStat;
	p->vtable[40] = SteamAPI_ISteamUserStats_GetGlobalStat0;
	p->vtable[41] = SteamAPI_ISteamUserStats_GetGlobalStatHistory;
	p->vtable[42] = SteamAPI_ISteamUserStats_GetGlobalStatHistory0;
}

void
initSteamRemoteStorage(void)
{
	CSteamRemoteStorage *z = &ctx.remoteStorage;
	CSteamBase *p = &z->base;

	initSteamBase(p);
	p->vtable[0] = SteamAPI_ISteamRemoteStorage_FileWrite;
	p->vtable[1] = SteamAPI_ISteamRemoteStorage_FileRead;
	p->vtable[2] = SteamAPI_ISteamRemoteStorage_FileWriteAsync;
	p->vtable[3] = SteamAPI_ISteamRemoteStorage_FileReadAsync;
	p->vtable[4] = SteamAPI_ISteamRemoteStorage_FileReadAsyncComplete;
	p->vtable[5] = SteamAPI_ISteamRemoteStorage_FileForget;
	p->vtable[6] = SteamAPI_ISteamRemoteStorage_FileDelete;
	p->vtable[7] = SteamAPI_ISteamRemoteStorage_FileShare;
	p->vtable[8] = SteamAPI_ISteamRemoteStorage_SetSyncPlatforms;
	p->vtable[9] = SteamAPI_ISteamRemoteStorage_FileWriteStreamOpen;
	p->vtable[10] = SteamAPI_ISteamRemoteStorage_FileWriteStreamWriteChunk;
	p->vtable[11] = SteamAPI_ISteamRemoteStorage_FileWriteStreamClose;
	p->vtable[12] = SteamAPI_ISteamRemoteStorage_FileWriteStreamCancel;
	p->vtable[13] = SteamAPI_ISteamRemoteStorage_FileExists;
	p->vtable[14] = SteamAPI_ISteamRemoteStorage_FilePersisted;
	p->vtable[15] = SteamAPI_ISteamRemoteStorage_GetFileSize;
	p->vtable[16] = SteamAPI_ISteamRemoteStorage_GetFileTimestamp;
	p->vtable[17] = SteamAPI_ISteamRemoteStorage_GetSyncPlatforms;
	p->vtable[18] = SteamAPI_ISteamRemoteStorage_GetFileCount;
	p->vtable[19] = SteamAPI_ISteamRemoteStorage_GetFileNameAndSize;
	p->vtable[20] = SteamAPI_ISteamRemoteStorage_GetQuota;
	p->vtable[21] = SteamAPI_ISteamRemoteStorage_IsCloudEnabledForAccount;
	p->vtable[22] = SteamAPI_ISteamRemoteStorage_IsCloudEnabledForApp;
	p->vtable[23] = SteamAPI_ISteamRemoteStorage_SetCloudEnabledForApp;
	p->vtable[24] = SteamAPI_ISteamRemoteStorage_UGCDownload;
	p->vtable[25] = SteamAPI_ISteamRemoteStorage_GetUGCDownloadProgress;
	p->vtable[26] = SteamAPI_ISteamRemoteStorage_GetUGCDetails;
	p->vtable[27] = SteamAPI_ISteamRemoteStorage_UGCRead;
	p->vtable[28] = SteamAPI_ISteamRemoteStorage_GetCachedUGCCount;
	p->vtable[29] = SteamAPI_ISteamRemoteStorage_GetCachedUGCHandle;
	p->vtable[30] = SteamAPI_ISteamRemoteStorage_PublishWorkshopFile;
	p->vtable[31] = SteamAPI_ISteamRemoteStorage_CreatePublishedFileUpdateRequest;
	p->vtable[32] = SteamAPI_ISteamRemoteStorage_UpdatePublishedFileFile;
	p->vtable[33] = SteamAPI_ISteamRemoteStorage_UpdatePublishedFilePreviewFile;
	p->vtable[34] = SteamAPI_ISteamRemoteStorage_UpdatePublishedFileTitle;
	p->vtable[35] = SteamAPI_ISteamRemoteStorage_UpdatePublishedFileDescription;
	p->vtable[36] = SteamAPI_ISteamRemoteStorage_UpdatePublishedFileVisibility;
	p->vtable[37] = SteamAPI_ISteamRemoteStorage_UpdatePublishedFileTags;
	p->vtable[38] = SteamAPI_ISteamRemoteStorage_CommitPublishedFileUpdate;
	p->vtable[39] = SteamAPI_ISteamRemoteStorage_GetPublishedFileDetails;
	p->vtable[40] = SteamAPI_ISteamRemoteStorage_DeletePublishedFile;
	p->vtable[41] = SteamAPI_ISteamRemoteStorage_EnumerateUserPublishedFiles;
	p->vtable[42] = SteamAPI_ISteamRemoteStorage_SubscribePublishedFile;
	p->vtable[43] = SteamAPI_ISteamRemoteStorage_EnumerateUserSubscribedFiles;
	p->vtable[44] = SteamAPI_ISteamRemoteStorage_UnsubscribePublishedFile;
	p->vtable[45] = SteamAPI_ISteamRemoteStorage_UpdatePublishedFileSetChangeDescription;
	p->vtable[46] = SteamAPI_ISteamRemoteStorage_GetPublishedItemVoteDetails;
	p->vtable[47] = SteamAPI_ISteamRemoteStorage_UpdateUserPublishedItemVote;
	p->vtable[48] = SteamAPI_ISteamRemoteStorage_GetUserPublishedItemVoteDetails;
	p->vtable[49] = SteamAPI_ISteamRemoteStorage_EnumerateUserSharedWorkshopFiles;
	p->vtable[50] = SteamAPI_ISteamRemoteStorage_PublishVideo;
	p->vtable[51] = SteamAPI_ISteamRemoteStorage_SetUserPublishedFileAction;
	p->vtable[52] = SteamAPI_ISteamRemoteStorage_EnumeratePublishedFilesByUserAction;
	p->vtable[53] = SteamAPI_ISteamRemoteStorage_EnumeratePublishedWorkshopFiles;
	p->vtable[54] = SteamAPI_ISteamRemoteStorage_UGCDownloadToLocation;

	if (parseSteamVersion(p->version) != 13)
		memmove(&p->vtable[2], &p->vtable[5], sizeof(p->vtable[0]) * 51);
}

void
initSteamClient(void)
{
	CSteamClient *z = &ctx.client;
	CSteamBase *p = &z->base;

	initSteamBase(p);
	p->vtable[0] = SteamAPI_ISteamClient_CreateSteamPipe;
	p->vtable[1] = SteamAPI_ISteamClient_BReleaseSteamPipe;
	p->vtable[2] = SteamAPI_ISteamClient_ConnectToGlobalUser;
	p->vtable[3] = SteamAPI_ISteamClient_CreateLocalUser;
	p->vtable[4] = SteamAPI_ISteamClient_ReleaseUser;
	p->vtable[5] = SteamAPI_ISteamClient_GetISteamUser;
	p->vtable[6] = SteamAPI_ISteamClient_GetISteamGameServer;
	p->vtable[7] = SteamAPI_ISteamClient_SetLocalIPBinding;
	p->vtable[8] = SteamAPI_ISteamClient_GetISteamFriends;
	p->vtable[9] = SteamAPI_ISteamClient_GetISteamUtils;
	p->vtable[10] = SteamAPI_ISteamClient_GetISteamMatchmaking;
	p->vtable[11] = SteamAPI_ISteamClient_GetISteamMatchmakingServers;
	p->vtable[12] = SteamAPI_ISteamClient_GetISteamGenericInterface;
	p->vtable[13] = SteamAPI_ISteamClient_GetISteamUserStats;
	p->vtable[14] = SteamAPI_ISteamClient_GetISteamGameServerStats;
	p->vtable[15] = SteamAPI_ISteamClient_GetISteamApps;
	p->vtable[16] = SteamAPI_ISteamClient_GetISteamNetworking;
	p->vtable[17] = SteamAPI_ISteamClient_GetISteamRemoteStorage;
	p->vtable[18] = SteamAPI_ISteamClient_GetISteamScreenshots;
	p->vtable[19] = SteamAPI_ISteamClient_RunFrame;
	p->vtable[20] = SteamAPI_ISteamClient_GetIPCCallCount;
	p->vtable[21] = SteamAPI_ISteamClient_SetWarningMessageHook;
	p->vtable[22] = SteamAPI_ISteamClient_BShutdownIfAllPipesClosed;
	p->vtable[23] = SteamAPI_ISteamClient_GetISteamHTTP;
	p->vtable[24] = SteamAPI_ISteamClient_GetISteamUnifiedMessages;
	p->vtable[25] = SteamAPI_ISteamClient_GetISteamController;
	p->vtable[26] = SteamAPI_ISteamClient_GetISteamUGC;
	p->vtable[27] = SteamAPI_ISteamClient_GetISteamAppList;
	p->vtable[28] = SteamAPI_ISteamClient_GetISteamMusic;
	p->vtable[29] = SteamAPI_ISteamClient_GetISteamMusicRemote;
	p->vtable[30] = SteamAPI_ISteamClient_GetISteamHTMLSurface;
	p->vtable[31] = SteamAPI_ISteamClient_Set_SteamAPI_CPostAPIResultInProcess;
	p->vtable[32] = SteamAPI_ISteamClient_Set_SteamAPI_CPostAPIResultInProcess;
	p->vtable[33] = SteamAPI_ISteamClient_Set_SteamAPI_CCheckCallbackRegisteredInProcess;
	p->vtable[34] = SteamAPI_ISteamClient_GetISteamInventory;
	p->vtable[35] = SteamAPI_ISteamClient_GetISteamVideo;
	p->vtable[36] = SteamAPI_ISteamClient_GetISteamParentalSettings;
}

void
initSteamVideo(void)
{
	CSteamVideo *z = &ctx.video;
	CSteamBase *p = &z->base;

	initSteamBase(p);
}

void
initSteamFriends(void)
{
	CSteamFriends *z = &ctx.friends;
	CSteamBase *p = &z->base;

	initSteamBase(p);
	p->vtable[0] = SteamAPI_ISteamFriends_GetPersonaName;
	p->vtable[1] = SteamAPI_ISteamFriends_SetPersonaName;
	p->vtable[2] = SteamAPI_ISteamFriends_GetPersonaState;
	p->vtable[3] = SteamAPI_ISteamFriends_GetFriendCount;
	p->vtable[4] = SteamAPI_ISteamFriends_GetFriendByIndex;
	p->vtable[5] = SteamAPI_ISteamFriends_GetFriendRelationship;
	p->vtable[6] = SteamAPI_ISteamFriends_GetFriendPersonaState;
	p->vtable[7] = SteamAPI_ISteamFriends_GetFriendPersonaName;
	p->vtable[8] = SteamAPI_ISteamFriends_GetFriendGamePlayed;
	p->vtable[9] = SteamAPI_ISteamFriends_GetFriendPersonaNameHistory;
	p->vtable[10] = SteamAPI_ISteamFriends_GetFriendSteamLevel;
	p->vtable[11] = SteamAPI_ISteamFriends_GetPlayerNickname;
	p->vtable[12] = SteamAPI_ISteamFriends_GetFriendsGroupCount;
	p->vtable[13] = SteamAPI_ISteamFriends_GetFriendsGroupIDByIndex;
	p->vtable[14] = SteamAPI_ISteamFriends_GetFriendsGroupName;
	p->vtable[15] = SteamAPI_ISteamFriends_GetFriendsGroupMembersCount;
	p->vtable[16] = SteamAPI_ISteamFriends_GetFriendsGroupMembersList;
	p->vtable[17] = SteamAPI_ISteamFriends_HasFriend;
	p->vtable[18] = SteamAPI_ISteamFriends_GetClanCount;
	p->vtable[19] = SteamAPI_ISteamFriends_GetClanByIndex;
	p->vtable[20] = SteamAPI_ISteamFriends_GetClanName;
	p->vtable[21] = SteamAPI_ISteamFriends_GetClanTag;
	p->vtable[22] = SteamAPI_ISteamFriends_GetClanActivityCounts;
	p->vtable[23] = SteamAPI_ISteamFriends_DownloadClanActivityCounts;
	p->vtable[24] = SteamAPI_ISteamFriends_GetFriendCountFromSource;
	p->vtable[25] = SteamAPI_ISteamFriends_GetFriendFromSourceByIndex;
	p->vtable[26] = SteamAPI_ISteamFriends_IsUserInSource;
	p->vtable[27] = SteamAPI_ISteamFriends_SetInGameVoiceSpeaking;
	p->vtable[28] = SteamAPI_ISteamFriends_ActivateGameOverlay;
	p->vtable[29] = SteamAPI_ISteamFriends_ActivateGameOverlayToUser;
	p->vtable[30] = SteamAPI_ISteamFriends_ActivateGameOverlayToWebPage;
	p->vtable[31] = SteamAPI_ISteamFriends_ActivateGameOverlayToStore;
	p->vtable[32] = SteamAPI_ISteamFriends_SetPlayedWith;
	p->vtable[33] = SteamAPI_ISteamFriends_ActivateGameOverlayInviteDialog;
	p->vtable[34] = SteamAPI_ISteamFriends_GetSmallFriendAvatar;
	p->vtable[35] = SteamAPI_ISteamFriends_GetMediumFriendAvatar;
	p->vtable[36] = SteamAPI_ISteamFriends_GetLargeFriendAvatar;
	p->vtable[37] = SteamAPI_ISteamFriends_RequestUserInformation;
	p->vtable[38] = SteamAPI_ISteamFriends_RequestClanOfficerList;
	p->vtable[39] = SteamAPI_ISteamFriends_GetClanOwner;
	p->vtable[40] = SteamAPI_ISteamFriends_GetClanOfficerCount;
	p->vtable[41] = SteamAPI_ISteamFriends_GetClanOfficerByIndex;
	p->vtable[42] = SteamAPI_ISteamFriends_GetUserRestrictions;
	p->vtable[43] = SteamAPI_ISteamFriends_SetRichPresence;
	p->vtable[44] = SteamAPI_ISteamFriends_ClearRichPresence;
	p->vtable[45] = SteamAPI_ISteamFriends_GetFriendRichPresence;
	p->vtable[46] = SteamAPI_ISteamFriends_GetFriendRichPresenceKeyCount;
	p->vtable[47] = SteamAPI_ISteamFriends_GetFriendRichPresenceKeyByIndex;
	p->vtable[48] = SteamAPI_ISteamFriends_RequestFriendRichPresence;
	p->vtable[49] = SteamAPI_ISteamFriends_InviteUserToGame;
	p->vtable[50] = SteamAPI_ISteamFriends_GetCoplayFriendCount;
	p->vtable[51] = SteamAPI_ISteamFriends_GetCoplayFriend;
	p->vtable[52] = SteamAPI_ISteamFriends_GetFriendCoplayTime;
	p->vtable[53] = SteamAPI_ISteamFriends_GetFriendCoplayGame;
	p->vtable[54] = SteamAPI_ISteamFriends_JoinClanChatRoom;
	p->vtable[55] = SteamAPI_ISteamFriends_LeaveClanChatRoom;
	p->vtable[56] = SteamAPI_ISteamFriends_GetClanChatMemberCount;
	p->vtable[57] = SteamAPI_ISteamFriends_GetChatMemberByIndex;
	p->vtable[58] = SteamAPI_ISteamFriends_SendClanChatMessage;
	p->vtable[59] = SteamAPI_ISteamFriends_GetClanChatMessage;
	p->vtable[60] = SteamAPI_ISteamFriends_IsClanChatAdmin;
	p->vtable[61] = SteamAPI_ISteamFriends_IsClanChatWindowOpenInSteam;
	p->vtable[62] = SteamAPI_ISteamFriends_OpenClanChatWindowInSteam;
	p->vtable[63] = SteamAPI_ISteamFriends_CloseClanChatWindowInSteam;
	p->vtable[64] = SteamAPI_ISteamFriends_SetListenForFriendsMessages;
	p->vtable[65] = SteamAPI_ISteamFriends_ReplyToFriendMessage;
	p->vtable[66] = SteamAPI_ISteamFriends_GetFriendMessage;
	p->vtable[67] = SteamAPI_ISteamFriends_GetFollowerCount;
	p->vtable[68] = SteamAPI_ISteamFriends_IsFollowing;
	p->vtable[69] = SteamAPI_ISteamFriends_EnumerateFollowingList;
	p->vtable[70] = SteamAPI_ISteamFriends_IsClanPublic;
	p->vtable[71] = SteamAPI_ISteamFriends_IsClanOfficialGameGroup;
}

void
initSteamHTMLSurface(void)
{
	CSteamHTMLSurface *z = &ctx.htmlSurface;
	CSteamBase *p = &z->base;

	initSteamBase(p);
	p->vtable[0] = SteamAPI_ISteamHTMLSurface_Init;
	p->vtable[1] = SteamAPI_ISteamHTMLSurface_Shutdown;
	p->vtable[2] = SteamAPI_ISteamHTMLSurface_CreateBrowser;
	p->vtable[3] = SteamAPI_ISteamHTMLSurface_RemoveBrowser;
	p->vtable[4] = SteamAPI_ISteamHTMLSurface_LoadURL;
	p->vtable[5] = SteamAPI_ISteamHTMLSurface_SetSize;
	p->vtable[6] = SteamAPI_ISteamHTMLSurface_StopLoad;
	p->vtable[7] = SteamAPI_ISteamHTMLSurface_Reload;
	p->vtable[8] = SteamAPI_ISteamHTMLSurface_GoBack;
	p->vtable[9] = SteamAPI_ISteamHTMLSurface_GoForward;
	p->vtable[10] = SteamAPI_ISteamHTMLSurface_AddHeader;
	p->vtable[11] = SteamAPI_ISteamHTMLSurface_ExecuteJavascript;
	p->vtable[12] = SteamAPI_ISteamHTMLSurface_MouseUp;
	p->vtable[13] = SteamAPI_ISteamHTMLSurface_MouseDown;
	p->vtable[14] = SteamAPI_ISteamHTMLSurface_MouseDoubleClick;
	p->vtable[15] = SteamAPI_ISteamHTMLSurface_MouseMove;
	p->vtable[16] = SteamAPI_ISteamHTMLSurface_MouseWheel;
	p->vtable[17] = SteamAPI_ISteamHTMLSurface_KeyDown;
	p->vtable[18] = SteamAPI_ISteamHTMLSurface_KeyUp;
	p->vtable[19] = SteamAPI_ISteamHTMLSurface_KeyChar;
	p->vtable[20] = SteamAPI_ISteamHTMLSurface_SetHorizontalScroll;
	p->vtable[21] = SteamAPI_ISteamHTMLSurface_SetVerticalScroll;
	p->vtable[22] = SteamAPI_ISteamHTMLSurface_SetKeyFocus;
	p->vtable[23] = SteamAPI_ISteamHTMLSurface_ViewSource;
	p->vtable[24] = SteamAPI_ISteamHTMLSurface_CopyToClipboard;
	p->vtable[25] = SteamAPI_ISteamHTMLSurface_PasteFromClipboard;
	p->vtable[26] = SteamAPI_ISteamHTMLSurface_Find;
	p->vtable[27] = SteamAPI_ISteamHTMLSurface_StopFind;
	p->vtable[28] = SteamAPI_ISteamHTMLSurface_GetLinkAtPosition;
	p->vtable[29] = SteamAPI_ISteamHTMLSurface_SetCookie;
	p->vtable[30] = SteamAPI_ISteamHTMLSurface_SetPageScaleFactor;
	p->vtable[31] = SteamAPI_ISteamHTMLSurface_SetBackgroundMode;
	p->vtable[32] = SteamAPI_ISteamHTMLSurface_AllowStartRequest;
	p->vtable[33] = SteamAPI_ISteamHTMLSurface_JSDialogResponse;
	p->vtable[34] = SteamAPI_ISteamHTMLSurface_FileLoadDialogResponse;
}

void
initSteamInventory(void)
{
	CSteamInventory *z = &ctx.inventory;
	CSteamBase *p = &z->base;

	initSteamBase(p);
	p->vtable[0] = SteamAPI_ISteamInventory_GetResultStatus;
	p->vtable[1] = SteamAPI_ISteamInventory_GetResultItems;
	p->vtable[2] = SteamAPI_ISteamInventory_GetResultItemProperty;
	p->vtable[3] = SteamAPI_ISteamInventory_GetResultTimestamp;
	p->vtable[4] = SteamAPI_ISteamInventory_CheckResultSteamID;
	p->vtable[5] = SteamAPI_ISteamInventory_DestroyResult;
	p->vtable[6] = SteamAPI_ISteamInventory_GetAllItems;
	p->vtable[7] = SteamAPI_ISteamInventory_GetItemsByID;
	p->vtable[8] = SteamAPI_ISteamInventory_SerializeResult;
	p->vtable[9] = SteamAPI_ISteamInventory_DeserializeResult;
	p->vtable[10] = SteamAPI_ISteamInventory_GenerateItems;
	p->vtable[11] = SteamAPI_ISteamInventory_GrantPromoItems;
	p->vtable[12] = SteamAPI_ISteamInventory_AddPromoItem;
	p->vtable[13] = SteamAPI_ISteamInventory_AddPromoItems;
	p->vtable[14] = SteamAPI_ISteamInventory_ConsumeItem;
	p->vtable[15] = SteamAPI_ISteamInventory_ExchangeItems;
	p->vtable[16] = SteamAPI_ISteamInventory_TransferItemQuantity;
	p->vtable[17] = SteamAPI_ISteamInventory_SendItemDropHeartbeat;
	p->vtable[18] = SteamAPI_ISteamInventory_TriggerItemDrop;
	p->vtable[19] = SteamAPI_ISteamInventory_TradeItems;
	p->vtable[20] = SteamAPI_ISteamInventory_LoadItemDefinitions;
	p->vtable[21] = SteamAPI_ISteamInventory_GetItemDefinitionIDs;
	p->vtable[22] = SteamAPI_ISteamInventory_GetItemDefinitionProperty;
	p->vtable[23] = SteamAPI_ISteamInventory_RequestEligiblePromoItemDefinitionsIDs;
	p->vtable[24] = SteamAPI_ISteamInventory_GetEligiblePromoItemDefinitionIDs;
	p->vtable[25] = SteamAPI_ISteamInventory_StartPurchase;
	p->vtable[26] = SteamAPI_ISteamInventory_RequestPrices;
	p->vtable[27] = SteamAPI_ISteamInventory_GetNumItemsWithPrices;
	p->vtable[28] = SteamAPI_ISteamInventory_GetItemsWithPrices;
	p->vtable[29] = SteamAPI_ISteamInventory_GetItemPrice;
	p->vtable[30] = SteamAPI_ISteamInventory_StartUpdateProperties;
	p->vtable[31] = SteamAPI_ISteamInventory_RemoveProperty;
	p->vtable[32] = SteamAPI_ISteamInventory_SetPropertyString;
	p->vtable[33] = SteamAPI_ISteamInventory_SetPropertyBool;
	p->vtable[34] = SteamAPI_ISteamInventory_SetPropertyInt;
	p->vtable[35] = SteamAPI_ISteamInventory_SetPropertyFloat;
	p->vtable[36] = SteamAPI_ISteamInventory_SubmitUpdateProperties;
}

void
initSteamMusic(void)
{
	CSteamMusic *z = &ctx.music;
	CSteamBase *p = &z->base;

	initSteamBase(p);
	p->vtable[0] = SteamAPI_ISteamMusic_BIsEnabled;
	p->vtable[1] = SteamAPI_ISteamMusic_BIsPlaying;
	p->vtable[2] = SteamAPI_ISteamMusic_GetPlaybackStatus;
	p->vtable[3] = SteamAPI_ISteamMusic_Play;
	p->vtable[4] = SteamAPI_ISteamMusic_Pause;
	p->vtable[5] = SteamAPI_ISteamMusic_PlayPrevious;
	p->vtable[6] = SteamAPI_ISteamMusic_PlayNext;
	p->vtable[7] = SteamAPI_ISteamMusic_SetVolume;
	p->vtable[8] = SteamAPI_ISteamMusic_GetVolume;
}

void
initSteamMusicRemote(void)
{
	CSteamMusicRemote *z = &ctx.musicRemote;
	CSteamBase *p = &z->base;

	initSteamBase(p);
	p->vtable[0] = SteamAPI_ISteamMusicRemote_RegisterSteamMusicRemote;
	p->vtable[1] = SteamAPI_ISteamMusicRemote_DeregisterSteamMusicRemote;
	p->vtable[2] = SteamAPI_ISteamMusicRemote_BIsCurrentMusicRemote;
	p->vtable[3] = SteamAPI_ISteamMusicRemote_BActivationSuccess;
	p->vtable[4] = SteamAPI_ISteamMusicRemote_SetDisplayName;
	p->vtable[5] = SteamAPI_ISteamMusicRemote_SetPNGIcon_64x64;
	p->vtable[6] = SteamAPI_ISteamMusicRemote_EnablePlayPrevious;
	p->vtable[7] = SteamAPI_ISteamMusicRemote_EnablePlayNext;
	p->vtable[8] = SteamAPI_ISteamMusicRemote_EnableShuffled;
	p->vtable[9] = SteamAPI_ISteamMusicRemote_EnableLooped;
	p->vtable[10] = SteamAPI_ISteamMusicRemote_EnableQueue;
	p->vtable[11] = SteamAPI_ISteamMusicRemote_EnablePlaylists;
	p->vtable[12] = SteamAPI_ISteamMusicRemote_UpdatePlaybackStatus;
	p->vtable[13] = SteamAPI_ISteamMusicRemote_UpdateShuffled;
	p->vtable[14] = SteamAPI_ISteamMusicRemote_UpdateLooped;
	p->vtable[15] = SteamAPI_ISteamMusicRemote_UpdateVolume;
	p->vtable[16] = SteamAPI_ISteamMusicRemote_CurrentEntryWillChange;
	p->vtable[17] = SteamAPI_ISteamMusicRemote_CurrentEntryIsAvailable;
	p->vtable[18] = SteamAPI_ISteamMusicRemote_UpdateCurrentEntryText;
	p->vtable[19] = SteamAPI_ISteamMusicRemote_UpdateCurrentEntryElapsedSeconds;
	p->vtable[20] = SteamAPI_ISteamMusicRemote_UpdateCurrentEntryCoverArt;
	p->vtable[21] = SteamAPI_ISteamMusicRemote_CurrentEntryDidChange;
	p->vtable[22] = SteamAPI_ISteamMusicRemote_QueueWillChange;
	p->vtable[23] = SteamAPI_ISteamMusicRemote_ResetQueueEntries;
	p->vtable[24] = SteamAPI_ISteamMusicRemote_SetQueueEntry;
	p->vtable[25] = SteamAPI_ISteamMusicRemote_SetCurrentQueueEntry;
	p->vtable[26] = SteamAPI_ISteamMusicRemote_QueueDidChange;
	p->vtable[27] = SteamAPI_ISteamMusicRemote_PlaylistWillChange;
	p->vtable[28] = SteamAPI_ISteamMusicRemote_ResetPlaylistEntries;
	p->vtable[29] = SteamAPI_ISteamMusicRemote_SetPlaylistEntry;
	p->vtable[30] = SteamAPI_ISteamMusicRemote_SetCurrentPlaylistEntry;
	p->vtable[31] = SteamAPI_ISteamMusicRemote_PlaylistDidChange;
}

void
initSteamAppList(void)
{
	CSteamAppList *z = &ctx.appList;
	CSteamBase *p = &z->base;

	initSteamBase(p);
	p->vtable[0] = SteamAPI_ISteamAppList_GetNumInstalledApps;
	p->vtable[1] = SteamAPI_ISteamAppList_GetInstalledApps;
	p->vtable[2] = SteamAPI_ISteamAppList_GetAppName;
	p->vtable[3] = SteamAPI_ISteamAppList_GetAppInstallDir;
	p->vtable[4] = SteamAPI_ISteamAppList_GetAppBuildId;
}

void
initSteamUGC(void)
{
	CSteamUGC *z = &ctx.ugc;
	CSteamBase *p = &z->base;

	initSteamBase(p);
	p->vtable[0] = SteamAPI_ISteamUGC_CreateQueryUserUGCRequest;
	p->vtable[1] = SteamAPI_ISteamUGC_CreateQueryAllUGCRequest;
	p->vtable[2] = SteamAPI_ISteamUGC_CreateQueryUGCDetailsRequest;
	p->vtable[3] = SteamAPI_ISteamUGC_SendQueryUGCRequest;
	p->vtable[4] = SteamAPI_ISteamUGC_GetQueryUGCResult;
	p->vtable[5] = SteamAPI_ISteamUGC_GetQueryUGCPreviewURL;
	p->vtable[6] = SteamAPI_ISteamUGC_GetQueryUGCMetadata;
	p->vtable[7] = SteamAPI_ISteamUGC_GetQueryUGCChildren;
	p->vtable[8] = SteamAPI_ISteamUGC_GetQueryUGCStatistic;
	p->vtable[9] = SteamAPI_ISteamUGC_GetQueryUGCNumAdditionalPreviews;
	p->vtable[10] = SteamAPI_ISteamUGC_GetQueryUGCAdditionalPreview;
	p->vtable[11] = SteamAPI_ISteamUGC_GetQueryUGCNumKeyValueTags;
	p->vtable[12] = SteamAPI_ISteamUGC_GetQueryUGCKeyValueTag;
	p->vtable[13] = SteamAPI_ISteamUGC_ReleaseQueryUGCRequest;
	p->vtable[14] = SteamAPI_ISteamUGC_AddRequiredTag;
	p->vtable[15] = SteamAPI_ISteamUGC_AddExcludedTag;
	p->vtable[16] = SteamAPI_ISteamUGC_SetReturnKeyValueTags;
	p->vtable[17] = SteamAPI_ISteamUGC_SetReturnLongDescription;
	p->vtable[18] = SteamAPI_ISteamUGC_SetReturnMetadata;
	p->vtable[19] = SteamAPI_ISteamUGC_SetReturnChildren;
	p->vtable[20] = SteamAPI_ISteamUGC_SetReturnAdditionalPreviews;
	p->vtable[21] = SteamAPI_ISteamUGC_SetReturnTotalOnly;
	p->vtable[22] = SteamAPI_ISteamUGC_SetLanguage;
	p->vtable[23] = SteamAPI_ISteamUGC_SetAllowCachedResponse;
	p->vtable[24] = SteamAPI_ISteamUGC_SetCloudFileNameFilter;
	p->vtable[25] = SteamAPI_ISteamUGC_SetMatchAnyTag;
	p->vtable[26] = SteamAPI_ISteamUGC_SetSearchText;
	p->vtable[27] = SteamAPI_ISteamUGC_SetRankedByTrendDays;
	p->vtable[28] = SteamAPI_ISteamUGC_AddRequiredKeyValueTag;
	p->vtable[29] = SteamAPI_ISteamUGC_RequestUGCDetails;
	p->vtable[30] = SteamAPI_ISteamUGC_CreateItem;
	p->vtable[31] = SteamAPI_ISteamUGC_StartItemUpdate;
	p->vtable[32] = SteamAPI_ISteamUGC_SetItemTitle;
	p->vtable[33] = SteamAPI_ISteamUGC_SetItemDescription;
	p->vtable[34] = SteamAPI_ISteamUGC_SetItemUpdateLanguage;
	p->vtable[35] = SteamAPI_ISteamUGC_SetItemMetadata;
	p->vtable[36] = SteamAPI_ISteamUGC_SetItemVisibility;
	p->vtable[37] = SteamAPI_ISteamUGC_SetItemTags;
	p->vtable[38] = SteamAPI_ISteamUGC_SetItemContent;
	p->vtable[39] = SteamAPI_ISteamUGC_SetItemPreview;
	p->vtable[40] = SteamAPI_ISteamUGC_RemoveItemKeyValueTags;
	p->vtable[41] = SteamAPI_ISteamUGC_AddItemKeyValueTag;
	p->vtable[42] = SteamAPI_ISteamUGC_SubmitItemUpdate;
	p->vtable[43] = SteamAPI_ISteamUGC_GetItemUpdateProgress;
	p->vtable[44] = SteamAPI_ISteamUGC_SetUserItemVote;
	p->vtable[45] = SteamAPI_ISteamUGC_GetUserItemVote;
	p->vtable[46] = SteamAPI_ISteamUGC_AddItemToFavorites;
	p->vtable[47] = SteamAPI_ISteamUGC_RemoveItemFromFavorites;
	p->vtable[48] = SteamAPI_ISteamUGC_SubscribeItem;
	p->vtable[49] = SteamAPI_ISteamUGC_UnsubscribeItem;
	p->vtable[50] = SteamAPI_ISteamUGC_GetNumSubscribedItems;
	p->vtable[51] = SteamAPI_ISteamUGC_GetSubscribedItems;
	p->vtable[52] = SteamAPI_ISteamUGC_GetItemState;
	p->vtable[53] = SteamAPI_ISteamUGC_GetItemInstallInfo;
	p->vtable[54] = SteamAPI_ISteamUGC_GetItemDownloadInfo;
	p->vtable[55] = SteamAPI_ISteamUGC_DownloadItem;
	p->vtable[56] = SteamAPI_ISteamUGC_BInitWorkshopForGameServer;
	p->vtable[57] = SteamAPI_ISteamUGC_SuspendDownloads;
	p->vtable[58] = SteamAPI_ISteamUGC_StartPlaytimeTracking;
	p->vtable[59] = SteamAPI_ISteamUGC_StopPlaytimeTracking;
	p->vtable[60] = SteamAPI_ISteamUGC_StopPlaytimeTrackingForAllItems;
}

void
initSteamHTTP(void)
{
	CSteamHTTP *z = &ctx.http;
	CSteamBase *p = &z->base;

	initSteamBase(p);
	p->vtable[0] = SteamAPI_ISteamHTTP_CreateHTTPRequest;
	p->vtable[1] = SteamAPI_ISteamHTTP_SetHTTPRequestContextValue;
	p->vtable[2] = SteamAPI_ISteamHTTP_SetHTTPRequestNetworkActivityTimeout;
	p->vtable[3] = SteamAPI_ISteamHTTP_SetHTTPRequestHeaderValue;
	p->vtable[4] = SteamAPI_ISteamHTTP_SetHTTPRequestGetOrPostParameter;
	p->vtable[5] = SteamAPI_ISteamHTTP_SendHTTPRequest;
	p->vtable[6] = SteamAPI_ISteamHTTP_SendHTTPRequestAndStreamResponse;
	p->vtable[7] = SteamAPI_ISteamHTTP_DeferHTTPRequest;
	p->vtable[8] = SteamAPI_ISteamHTTP_PrioritizeHTTPRequest;
	p->vtable[9] = SteamAPI_ISteamHTTP_GetHTTPResponseHeaderSize;
	p->vtable[10] = SteamAPI_ISteamHTTP_GetHTTPResponseHeaderValue;
	p->vtable[11] = SteamAPI_ISteamHTTP_GetHTTPResponseBodySize;
	p->vtable[12] = SteamAPI_ISteamHTTP_GetHTTPResponseBodyData;
	p->vtable[13] = SteamAPI_ISteamHTTP_GetHTTPStreamingResponseBodyData;
	p->vtable[14] = SteamAPI_ISteamHTTP_ReleaseHTTPRequest;
	p->vtable[15] = SteamAPI_ISteamHTTP_GetHTTPDownloadProgressPct;
	p->vtable[16] = SteamAPI_ISteamHTTP_SetHTTPRequestRawPostBody;
	p->vtable[17] = SteamAPI_ISteamHTTP_CreateCookieContainer;
	p->vtable[18] = SteamAPI_ISteamHTTP_ReleaseCookieContainer;
	p->vtable[19] = SteamAPI_ISteamHTTP_SetCookie;
	p->vtable[20] = SteamAPI_ISteamHTTP_SetHTTPRequestCookieContainer;
	p->vtable[21] = SteamAPI_ISteamHTTP_SetHTTPRequestUserAgentInfo;
	p->vtable[22] = SteamAPI_ISteamHTTP_SetHTTPRequestRequiresVerifiedCertificate;
	p->vtable[23] = SteamAPI_ISteamHTTP_SetHTTPRequestAbsoluteTimeoutMS;
	p->vtable[24] = SteamAPI_ISteamHTTP_GetHTTPRequestWasTimedOut;
}

void
initSteamMatchmaking(void)
{
	CSteamMatchmaking *z = &ctx.matchmaking;
	CSteamBase *p = &z->base;

	initSteamBase(p);
	p->vtable[0] = SteamAPI_ISteamMatchmaking_GetFavoriteGameCount;
	p->vtable[1] = SteamAPI_ISteamMatchmaking_GetFavoriteGame;
	p->vtable[2] = SteamAPI_ISteamMatchmaking_AddFavoriteGame;
	p->vtable[3] = SteamAPI_ISteamMatchmaking_RemoveFavoriteGame;
	p->vtable[4] = SteamAPI_ISteamMatchmaking_RequestLobbyList;
	p->vtable[5] = SteamAPI_ISteamMatchmaking_AddRequestLobbyListStringFilter;
	p->vtable[6] = SteamAPI_ISteamMatchmaking_AddRequestLobbyListNumericalFilter;
	p->vtable[7] = SteamAPI_ISteamMatchmaking_AddRequestLobbyListNearValueFilter;
	p->vtable[8] = SteamAPI_ISteamMatchmaking_AddRequestLobbyListFilterSlotsAvailable;
	p->vtable[9] = SteamAPI_ISteamMatchmaking_AddRequestLobbyListDistanceFilter;
	p->vtable[10] = SteamAPI_ISteamMatchmaking_AddRequestLobbyListResultCountFilter;
	p->vtable[11] = SteamAPI_ISteamMatchmaking_AddRequestLobbyListCompatibleMembersFilter;
	p->vtable[12] = SteamAPI_ISteamMatchmaking_GetLobbyByIndex;
	p->vtable[13] = SteamAPI_ISteamMatchmaking_CreateLobby;
	p->vtable[14] = SteamAPI_ISteamMatchmaking_JoinLobby;
	p->vtable[15] = SteamAPI_ISteamMatchmaking_LeaveLobby;
	p->vtable[16] = SteamAPI_ISteamMatchmaking_InviteUserToLobby;
	p->vtable[17] = SteamAPI_ISteamMatchmaking_GetNumLobbyMembers;
	p->vtable[18] = SteamAPI_ISteamMatchmaking_GetLobbyMemberByIndex;
	p->vtable[19] = SteamAPI_ISteamMatchmaking_GetLobbyData;
	p->vtable[20] = SteamAPI_ISteamMatchmaking_SetLobbyData;
	p->vtable[21] = SteamAPI_ISteamMatchmaking_GetLobbyDataCount;
	p->vtable[22] = SteamAPI_ISteamMatchmaking_GetLobbyDataByIndex;
	p->vtable[23] = SteamAPI_ISteamMatchmaking_DeleteLobbyData;
	p->vtable[24] = SteamAPI_ISteamMatchmaking_GetLobbyMemberData;
	p->vtable[25] = SteamAPI_ISteamMatchmaking_SetLobbyMemberData;
	p->vtable[26] = SteamAPI_ISteamMatchmaking_SendLobbyChatMsg;
	p->vtable[27] = SteamAPI_ISteamMatchmaking_GetLobbyChatEntry;
	p->vtable[28] = SteamAPI_ISteamMatchmaking_RequestLobbyData;
	p->vtable[29] = SteamAPI_ISteamMatchmaking_SetLobbyGameServer;
	p->vtable[30] = SteamAPI_ISteamMatchmaking_GetLobbyGameServer;
	p->vtable[31] = SteamAPI_ISteamMatchmaking_SetLobbyMemberLimit;
	p->vtable[32] = SteamAPI_ISteamMatchmaking_GetLobbyMemberLimit;
	p->vtable[33] = SteamAPI_ISteamMatchmaking_SetLobbyType;
	p->vtable[34] = SteamAPI_ISteamMatchmaking_SetLobbyJoinable;
	p->vtable[35] = SteamAPI_ISteamMatchmaking_GetLobbyOwner;
	p->vtable[36] = SteamAPI_ISteamMatchmaking_SetLobbyOwner;
	p->vtable[37] = SteamAPI_ISteamMatchmaking_SetLinkedLobby;
}

void
initSteamMatchmakingServers(void)
{
	CSteamMatchmakingServers *z = &ctx.matchmakingServers;
	CSteamBase *p = &z->base;

	initSteamBase(p);
	p->vtable[0] = SteamAPI_ISteamMatchmakingServers_RequestInternetServerList;
	p->vtable[1] = SteamAPI_ISteamMatchmakingServers_RequestLANServerList;
	p->vtable[2] = SteamAPI_ISteamMatchmakingServers_RequestFriendsServerList;
	p->vtable[3] = SteamAPI_ISteamMatchmakingServers_RequestFavoritesServerList;
	p->vtable[4] = SteamAPI_ISteamMatchmakingServers_RequestHistoryServerList;
	p->vtable[5] = SteamAPI_ISteamMatchmakingServers_RequestSpectatorServerList;
	p->vtable[6] = SteamAPI_ISteamMatchmakingServers_ReleaseRequest;
	p->vtable[7] = SteamAPI_ISteamMatchmakingServers_GetServerDetails;
	p->vtable[8] = SteamAPI_ISteamMatchmakingServers_CancelQuery;
	p->vtable[9] = SteamAPI_ISteamMatchmakingServers_RefreshQuery;
	p->vtable[10] = SteamAPI_ISteamMatchmakingServers_IsRefreshing;
	p->vtable[11] = SteamAPI_ISteamMatchmakingServers_GetServerCount;
	p->vtable[12] = SteamAPI_ISteamMatchmakingServers_RefreshServer;
	p->vtable[13] = SteamAPI_ISteamMatchmakingServers_PingServer;
	p->vtable[14] = SteamAPI_ISteamMatchmakingServers_PlayerDetails;
	p->vtable[15] = SteamAPI_ISteamMatchmakingServers_ServerRules;
	p->vtable[16] = SteamAPI_ISteamMatchmakingServers_CancelServerQuery;
}

void
initSteamUnifiedMessages(void)
{
	CSteamUnifiedMessages *z = &ctx.unifiedMessages;
	CSteamBase *p = &z->base;

	initSteamBase(p);
	p->vtable[0] = SteamAPI_ISteamUnifiedMessages_SendMethod;
	p->vtable[1] = SteamAPI_ISteamUnifiedMessages_GetMethodResponseInfo;
	p->vtable[2] = SteamAPI_ISteamUnifiedMessages_GetMethodResponseData;
	p->vtable[3] = SteamAPI_ISteamUnifiedMessages_ReleaseMethod;
	p->vtable[4] = SteamAPI_ISteamUnifiedMessages_SendNotification;
}

void
initSteamNetworking(void)
{
	CSteamNetworking *z = &ctx.networking;
	CSteamBase *p = &z->base;

	initSteamBase(p);
	p->vtable[0] = SteamAPI_ISteamNetworking_SendP2PPacket;
	p->vtable[1] = SteamAPI_ISteamNetworking_IsP2PPacketAvailable;
	p->vtable[2] = SteamAPI_ISteamNetworking_ReadP2PPacket;
	p->vtable[3] = SteamAPI_ISteamNetworking_AcceptP2PSessionWithUser;
	p->vtable[4] = SteamAPI_ISteamNetworking_CloseP2PSessionWithUser;
	p->vtable[5] = SteamAPI_ISteamNetworking_CloseP2PChannelWithUser;
	p->vtable[6] = SteamAPI_ISteamNetworking_GetP2PSessionState;
	p->vtable[7] = SteamAPI_ISteamNetworking_AllowP2PPacketRelay;
	p->vtable[8] = SteamAPI_ISteamNetworking_CreateListenSocket;
	p->vtable[9] = SteamAPI_ISteamNetworking_CreateP2PConnectionSocket;
	p->vtable[10] = SteamAPI_ISteamNetworking_CreateConnectionSocket;
	p->vtable[11] = SteamAPI_ISteamNetworking_DestroySocket;
	p->vtable[12] = SteamAPI_ISteamNetworking_DestroyListenSocket;
	p->vtable[13] = SteamAPI_ISteamNetworking_SendDataOnSocket;
	p->vtable[14] = SteamAPI_ISteamNetworking_IsDataAvailableOnSocket;
	p->vtable[15] = SteamAPI_ISteamNetworking_RetrieveDataFromSocket;
	p->vtable[16] = SteamAPI_ISteamNetworking_IsDataAvailable;
	p->vtable[17] = SteamAPI_ISteamNetworking_RetrieveData;
	p->vtable[18] = SteamAPI_ISteamNetworking_GetSocketInfo;
	p->vtable[19] = SteamAPI_ISteamNetworking_GetListenSocketInfo;
	p->vtable[20] = SteamAPI_ISteamNetworking_GetSocketConnectionType;
	p->vtable[21] = SteamAPI_ISteamNetworking_GetMaxPacketSize;
}

void
initSteamParentalSettings(void)
{
	CSteamParentalSettings *z = &ctx.parentalSettings;
	CSteamBase *p = &z->base;

	initSteamBase(p);
	p->vtable[0] = SteamAPI_ISteamParentalSettings_BIsParentalLockEnabled;
	p->vtable[1] = SteamAPI_ISteamParentalSettings_BIsParentalLockLocked;
	p->vtable[2] = SteamAPI_ISteamParentalSettings_BIsAppBlocked;
	p->vtable[3] = SteamAPI_ISteamParentalSettings_BIsAppInBlockList;
	p->vtable[4] = SteamAPI_ISteamParentalSettings_BIsFeatureBlocked;
	p->vtable[5] = SteamAPI_ISteamParentalSettings_BIsFeatureInBlockList;
}

void
initSteamScreenshots(void)
{
	CSteamScreenshots *z = &ctx.screenshots;
	CSteamBase *p = &z->base;

	initSteamBase(p);
	p->vtable[0] = SteamAPI_ISteamScreenshots_WriteScreenshot;
	p->vtable[1] = SteamAPI_ISteamScreenshots_AddScreenshotToLibrary;
	p->vtable[2] = SteamAPI_ISteamScreenshots_TriggerScreenshot;
	p->vtable[3] = SteamAPI_ISteamScreenshots_HookScreenshots;
	p->vtable[4] = SteamAPI_ISteamScreenshots_SetLocation;
	p->vtable[5] = SteamAPI_ISteamScreenshots_TagUser;
	p->vtable[6] = SteamAPI_ISteamScreenshots_TagPublishedFile;
}

void
initSteamGameServer(void)
{
	CSteamGameServer *z = &ctx.gameServer;
	CSteamBase *p = &z->base;

	initSteamBase(p);
}

void
initSteamGameServerApps(void)
{
	CSteamGameServerApps *z = &ctx.gameServerApps;
	CSteamBase *p = &z->base;

	initSteamBase(p);
}

void
initSteamAppTicket(void)
{
	CSteamAppTicket *z = &ctx.appTicket;
	CSteamBase *p = &z->base;

	initSteamBase(p);
	p->vtable[0] = SteamAPI_ISteamAppTicket_GetAppOwnershipTicketData;
}

void
initSteamContext(void)
{
	CSteamContext *p = &ctx;
	char logFileName[PATH_MAX];

	snprintf(p->currentLanguage, sizeof(p->currentLanguage), "english");
	snprintf(p->availableLanguages, sizeof(p->availableLanguages), "english,japanese");
	getEnvStr(p->rootDir, sizeof(p->rootDir), "STEAM_SAVEDIR", "save");
	getEnvStr(p->personaName, sizeof(p->personaName), "STEAM_PERSONA_NAME", "steamer");
	p->steamPipe = 1;
	p->steamID.m_gameID = 123;
	p->ref = 1;

	p->steamUser = getEnvInt("STEAM_USER_ID", 123);
	p->appID = getEnvInt("STEAM_APP_ID", STEAM_APP_ID);
#if defined(_WIN32)
	p->steamPID = getRegDWORD(HKEY_CURRENT_USER, "Software\\Valve\\Steam\\ActiveProcess", "pid", 0);
#endif
	if (p->steamPID == 0)
		p->steamPID = getEnvInt("STEAM_PID", 777777);
	p->logLevel = getEnvInt("STEAM_LOG_LEVEL", 100);
	getEnvStr(logFileName, sizeof(logFileName), "STEAM_LOGFILE", "");
	if (logFileName[0] != '\0')
		p->logFile = fopen(logFileName, "wt");
}

void
initSteamVersion(void)
{
	getEnvStr(ctx.client.base.version, sizeof(ctx.client.base.version), "STEAM_API_CLIENT_VERSION", STEAM_CLIENT_VERSION);
	getEnvStr(ctx.utils.base.version, sizeof(ctx.utils.base.version), "STEAM_API_UTILS_VERSION", STEAM_UTILS_VERSION);
	getEnvStr(ctx.remoteStorage.base.version, sizeof(ctx.remoteStorage.base.version), "STEAM_API_REMOTESTORAGE_VERSION", STEAM_REMOTESTORAGE_VERSION);
	getEnvStr(ctx.userStats.base.version, sizeof(ctx.userStats.base.version), "STEAM_API_USERSTATS_VERSION", STEAM_USERSTATS_VERSION);
	getEnvStr(ctx.user.base.version, sizeof(ctx.user.base.version), "STEAM_API_USER_VERSION", STEAM_USER_VERSION);
	getEnvStr(ctx.controller.base.version, sizeof(ctx.controller.base.version), "STEAM_API_CONTROLLER_VERSION", STEAM_CONTROLLER_VERSION);
	getEnvStr(ctx.apps.base.version, sizeof(ctx.apps.base.version), "STEAM_API_APPS_VERSION", STEAM_APPS_VERSION);
	getEnvStr(ctx.video.base.version, sizeof(ctx.video.base.version), "STEAM_API_VIDEO_VERSION", STEAM_VIDEO_VERSION);
	getEnvStr(ctx.friends.base.version, sizeof(ctx.friends.base.version), "STEAM_API_FRIENDS_VERSION", STEAM_FRIENDS_VERSION);
	getEnvStr(ctx.htmlSurface.base.version, sizeof(ctx.htmlSurface.base.version), "STEAM_API_HTMLSURFACE_VERSION", STEAM_HTMLSURFACE_VERSION);
	getEnvStr(ctx.inventory.base.version, sizeof(ctx.inventory.base.version), "STEAM_API_INVENTORY_VERSION", STEAM_INVENTORY_VERSION);
	getEnvStr(ctx.music.base.version, sizeof(ctx.music.base.version), "STEAM_API_MUSIC_VERSION", STEAM_MUSIC_VERSION);
	getEnvStr(ctx.musicRemote.base.version, sizeof(ctx.musicRemote.base.version), "STEAM_API_MUSICREMOTE_VERSION", STEAM_MUSICREMOTE_VERSION);
	getEnvStr(ctx.appList.base.version, sizeof(ctx.appList.base.version), "STEAM_API_APPLIST_VERSION", STEAM_APPLIST_VERSION);
	getEnvStr(ctx.ugc.base.version, sizeof(ctx.ugc.base.version), "STEAM_API_UGC_VERSION", STEAM_UGC_VERSION);
	getEnvStr(ctx.http.base.version, sizeof(ctx.http.base.version), "STEAM_API_HTTP_VERSION", STEAM_HTTP_VERSION);
	getEnvStr(ctx.matchmaking.base.version, sizeof(ctx.matchmaking.base.version), "STEAM_API_MATCHMAKING_VERSION", STEAM_MATCHMAKING_VERSION);
	getEnvStr(ctx.matchmakingServers.base.version, sizeof(ctx.matchmakingServers.base.version), "STEAM_API_MATCHMAKINGSERVERS_VERSION", STEAM_MATCHMAKINGSERVERS_VERSION);
	getEnvStr(ctx.unifiedMessages.base.version, sizeof(ctx.unifiedMessages.base.version), "STEAM_API_UNIFIEDMESSAGES_VERSION", STEAM_UNIFIEDMESSAGES_VERSION);
	getEnvStr(ctx.networking.base.version, sizeof(ctx.networking.base.version), "STEAM_API_NETWORKING_VERSION", STEAM_NETWORKING_VERSION);
	getEnvStr(ctx.parentalSettings.base.version, sizeof(ctx.parentalSettings.base.version), "STEAM_API_PARENTALSETTINGS_VERSION", STEAM_PARENTALSETTINGS_VERSION);
	getEnvStr(ctx.screenshots.base.version, sizeof(ctx.screenshots.base.version), "STEAM_API_SCREENSHOTS_VERSION", STEAM_SCREENSHOTS_VERSION);
	getEnvStr(ctx.gameServer.base.version, sizeof(ctx.gameServer.base.version), "STEAM_API_GAMESERVER_VERSION", STEAM_GAMESERVER_VERSION);
	getEnvStr(ctx.gameServerApps.base.version, sizeof(ctx.gameServerApps.base.version), "STEAM_API_GAMESERVERAPPS_VERSION", STEAM_GAMESERVERAPPS_VERSION);
	getEnvStr(ctx.appTicket.base.version, sizeof(ctx.appTicket.base.version), "STEAM_API_APP_TICKET_VERSION", STEAM_APP_TICKET_VERSION);
}

void
initSteamInput(void)
{
	CSteamInput *z = &ctx.input;
	CSteamBase *p = &z->base;

	initSteamBase(p);

	p->vtable[0] = SteamAPI_ISteamInput_Init;
	p->vtable[1] = SteamAPI_ISteamInput_Shutdown;
	p->vtable[2] = SteamAPI_ISteamInput_RunFrame;
	p->vtable[3] = SteamAPI_ISteamInput_GetConnectedControllers;
	p->vtable[4] = SteamAPI_ISteamInput_GetActionSetHandle;
	p->vtable[5] = SteamAPI_ISteamInput_ActivateActionSet;
	p->vtable[6] = SteamAPI_ISteamInput_GetCurrentActionSet;
	p->vtable[7] = SteamAPI_ISteamInput_ActivateActionSetLayer;
	p->vtable[8] = SteamAPI_ISteamInput_DeactivateActionSetLayer;
	p->vtable[9] = SteamAPI_ISteamInput_DeactivateAllActionSetLayers;
	p->vtable[10] = SteamAPI_ISteamInput_GetActiveActionSetLayers;
	p->vtable[11] = SteamAPI_ISteamInput_GetDigitalActionHandle;
	p->vtable[12] = SteamAPI_ISteamInput_GetDigitalActionData;
	p->vtable[13] = SteamAPI_ISteamInput_GetDigitalActionOrigins;
	p->vtable[14] = SteamAPI_ISteamInput_GetAnalogActionHandle;
	p->vtable[15] = SteamAPI_ISteamInput_GetAnalogActionData;
	p->vtable[16] = SteamAPI_ISteamInput_GetAnalogActionOrigins;
	p->vtable[17] = SteamAPI_ISteamInput_GetGlyphForActionOrigin;
	p->vtable[18] = SteamAPI_ISteamInput_GetStringForActionOrigin;
	p->vtable[19] = SteamAPI_ISteamInput_StopAnalogActionMomentum;
	p->vtable[20] = SteamAPI_ISteamInput_GetMotionData;
	p->vtable[21] = SteamAPI_ISteamInput_TriggerVibration;
	p->vtable[22] = SteamAPI_ISteamInput_SetLEDColor;
	p->vtable[23] = SteamAPI_ISteamInput_TriggerHapticPulse;
	p->vtable[24] = SteamAPI_ISteamInput_TriggerRepeatedHapticPulse;
	p->vtable[25] = SteamAPI_ISteamInput_ShowBindingPanel;
	p->vtable[26] = SteamAPI_ISteamInput_GetInputTypeForHandle;
	p->vtable[27] = SteamAPI_ISteamInput_GetControllerForGamepadIndex;
	p->vtable[28] = SteamAPI_ISteamInput_GetGamepadIndexForController;
	p->vtable[29] = SteamAPI_ISteamInput_GetStringForXboxOrigin;
	p->vtable[30] = SteamAPI_ISteamInput_GetGlyphForXboxOrigin;
	p->vtable[31] = SteamAPI_ISteamInput_GetActionOriginFromXboxOrigin;
	p->vtable[32] = SteamAPI_ISteamInput_TranslateActionOrigin;
	p->vtable[33] = SteamAPI_ISteamInput_GetDeviceBindingRevision;
	p->vtable[34] = SteamAPI_ISteamInput_GetRemotePlaySessionID;
}

void
initSteamInterface(void)
{
	initSteamDummy();
	initSteamApps();
	initSteamController();
	initSteamUser();
	initSteamUserStats();
	initSteamRemoteStorage();
	initSteamUtils();
	initSteamVideo();
	initSteamFriends();
	initSteamHTMLSurface();
	initSteamInventory();
	initSteamMusic();
	initSteamMusicRemote();
	initSteamAppList();
	initSteamUGC();
	initSteamHTTP();
	initSteamMatchmaking();
	initSteamMatchmakingServers();
	initSteamUnifiedMessages();
	initSteamNetworking();
	initSteamParentalSettings();
	initSteamScreenshots();
	initSteamGameServer();
	initSteamGameServerApps();
	initSteamAppTicket();
	initSteamClient();
	initSteamInput();
}

CONSTRUCTOR void
initSteam(void)
{
#if defined(_WIN32)
	InitializeCriticalSection(&ctx.globalLock);
	InitializeCriticalSection(&ctx.logLock);
#else
	pthread_mutex_init(&ctx.globalLock, NULL);
	pthread_mutex_init(&ctx.logLock, NULL);
#endif
	initSteamContext();
	xlogf("%s()\n", __func__);
	initSteamVersion();
	initSteamInterface();
}

S_API bool S_CALLTYPE
SteamAPI_RestartAppIfNecessary(uint32 unOwnAppID)
{
	xlogf("%s(unOwnAppID = %d)\n", __func__, unOwnAppID);
	return false;
}

S_API ISteamUserStats *S_CALLTYPE
SteamUserStats(void)
{
	ISteamUserStats *userStats = &ctx.userStats;
	xlogf("%s() -> %p\n", __func__, userStats);
	return userStats;
}

S_API ISteamUser *S_CALLTYPE
SteamUser(void)
{
	ISteamUser *user = &ctx.user;
	xlogf("%s() -> %p\n", __func__, user);
	return user;
}

S_API ISteamUtils *S_CALLTYPE
SteamUtils(void)
{
	CSteamUtils *utils = &ctx.utils;
	xlogf("%s() -> %p\n", __func__, utils);
	return utils;
}

S_API ISteamApps *S_CALLTYPE
SteamApps(void)
{
	CSteamApps *apps = &ctx.apps;
	xlogf("%s() -> %p\n", __func__, apps);
	return apps;
}

S_API ISteamRemoteStorage *S_CALLTYPE
SteamRemoteStorage(void)
{
	ISteamRemoteStorage *remoteStorage = &ctx.remoteStorage;
	xlogf("%s() -> %p\n", __func__, remoteStorage);
	return remoteStorage;
}

S_API ISteamController *S_CALLTYPE
SteamController(void)
{
	CSteamController *controller = &ctx.controller;
	xlogf("%s() -> %p\n", __func__, controller);
	return controller;
}

S_API ISteamFriends *S_CALLTYPE
SteamFriends(void)
{
	CSteamFriends *friends = &ctx.friends;
	xlogf("%s() -> %p\n", __func__, friends);
	return friends;
}

S_API ISteamClient *S_CALLTYPE
SteamClient(void)
{
	CSteamClient *client = &ctx.client;
	xlogf("%s() -> %p\n", __func__, client);
	return client;
}

S_API ISteamScreenshots *S_CALLTYPE
SteamScreenshots(void)
{
	CSteamScreenshots *screenshots = &ctx.screenshots;
	xlogf("%s() -> %p\n", __func__, screenshots);
	return screenshots;
}

S_API ISteamMatchmaking *S_CALLTYPE
SteamMatchmaking(void)
{
	CSteamMatchmaking *matchmaking = &ctx.matchmaking;
	xlogf("%s() -> %p\n", __func__, matchmaking);
	return matchmaking;
}

S_API ISteamNetworking *S_CALLTYPE
SteamNetworking(void)
{
	CSteamNetworking *networking = &ctx.networking;
	xlogf("%s() -> %p\n", __func__, networking);
	return networking;
}

S_API ISteamGameServer *S_CALLTYPE
SteamGameServer(void)
{
	ISteamGameServer *gameServer = &ctx.gameServer;
	xlogf("%s() -> %p\n", __func__, gameServer);
	return gameServer;
}

S_API ISteamGameServerApps *S_CALLTYPE
SteamGameServerApps(void)
{
	ISteamGameServerApps *gameServerApps = &ctx.gameServerApps;
	xlogf("%s() -> %p\n", __func__, gameServerApps);
	return gameServerApps;
}

S_API ISteamGameServerHTTP *S_CALLTYPE
SteamGameServerHTTP(void)
{
	ISteamGameServerHTTP *gameServerHTTP = &ctx.gameServerHTTP;
	xlogf("%s() -> %p\n", __func__, gameServerHTTP);
	return gameServerHTTP;
}

S_API ISteamMusic *S_CALLTYPE
SteamMusic(void)
{
	ISteamMusic *music = &ctx.music;
	xlogf("%s() -> %p\n", __func__, music);
	return music;
}

S_API ISteamMusicRemote *S_CALLTYPE
SteamMusicRemote(void)
{
	ISteamMusicRemote *musicRemote = &ctx.musicRemote;
	xlogf("%s() -> %p\n", __func__, musicRemote);
	return musicRemote;
}

S_API ISteamVideo *S_CALLTYPE
SteamVideo(void)
{
	ISteamVideo *video = &ctx.video;
	xlogf("%s() -> %p\n", __func__, video);
	return video;
}

S_API ISteamUGC *S_CALLTYPE
SteamUGC(void)
{
	ISteamUGC *ugc = &ctx.ugc;
	xlogf("%s() -> %p\n", __func__, ugc);
	return ugc;
}

S_API ISteamHTTP *S_CALLTYPE
SteamHTTP(void)
{
	ISteamHTTP *http = &ctx.http;
	xlogf("%s() -> %p\n", __func__, http);
	return http;
}

S_API ISteamHTMLSurface *S_CALLTYPE
SteamHTMLSurface(void)
{
	ISteamHTMLSurface *htmlSurface = &ctx.htmlSurface;
	xlogf("%s() -> %p\n", __func__, htmlSurface);
	return htmlSurface;
}

S_API ISteamInventory *S_CALLTYPE
SteamInventory(void)
{
	ISteamInventory *inventory = &ctx.inventory;
	xlogf("%s() -> %p\n", __func__, inventory);
	return inventory;
}

S_API ISteamMatchmakingServers *S_CALLTYPE
SteamMatchmakingServers(void)
{
	ISteamMatchmakingServers *matchmakingServers = &ctx.matchmakingServers;
	xlogf("%s() -> %p\n", __func__, matchmakingServers);
	return matchmakingServers;
}

S_API ISteamAppList *S_CALLTYPE
SteamAppList(void)
{
	ISteamAppList *appList = &ctx.appList;
	xlogf("%s() -> %p\n", __func__, appList);
	return appList;
}

S_API ISteamUnifiedMessages *S_CALLTYPE
SteamUnifiedMessages(void)
{
	ISteamUnifiedMessages *unifiedMessages = &ctx.unifiedMessages;
	xlogf("%s() -> %p\n", __func__, unifiedMessages);
	return unifiedMessages;
}

S_API HSteamUser S_CALLTYPE
Steam_GetHSteamUserCurrent(void)
{
	xlogf("%s()\n", __func__);
	return SteamAPI_GetHSteamUser();
}

S_API const char *S_CALLTYPE
SteamAPI_GetSteamInstallPath(void)
{
	xlogf("%s() -> %s\n", __func__, ctx.rootDir);
	return ctx.rootDir;
}

S_API bool S_CALLTYPE
SteamAPI_Init(void)
{
	xlogf("%s()\n", __func__);
	ctx.ref++;
	return true;
}

S_API bool S_CALLTYPE
SteamAPI_InitSafe(void)
{
	xlogf("%s()\n", __func__);
	ctx.ref++;
	ctx.safe = true;
	return true;
}

S_API void S_CALLTYPE
Steam_RegisterInterfaceFuncs(void *hModule)
{
	xlogf("%s(hModule = %p)\n", __func__, hModule);
}

S_API void S_CALLTYPE
SteamAPI_WriteMiniDump(uint32 uStructuredExceptionCode, void *pvExceptionInfo, uint32 uBuildID)
{
	xlogf("%s(uStructuredExceptionCode = %d, pvExceptionInfo = %p, uBuildID = %d)\n", __func__, uStructuredExceptionCode, pvExceptionInfo, uBuildID);
}

S_API void S_CALLTYPE
SteamAPI_SetMiniDumpComment(const char *pchMsg)
{
	xlogf("%s(pchMsg = %s)\n", __func__, pchMsg);
}

S_API void S_CALLTYPE
SteamAPI_Shutdown(void)
{
	xlogf("%s()\n", __func__);
	ctx.ref++;
}

S_API void S_CALLTYPE
SteamAPI_RegisterCallback(CCallbackBase *pCallback, int iCallback)
{
	xlogf("%s(pCallback = %p, iCallback = %d) (numCallbacks = %zu)\n", __func__, pCallback, iCallback, ctx.numCallbacks);
	if (ctx.numCallbacks <= nelem(ctx.callbacks))
		ctx.callbacks[ctx.numCallbacks++] = pCallback;
}

S_API void S_CALLTYPE
SteamAPI_UnregisterCallback(CCallbackBase *pCallback)
{
	xlogf("%s(pCallback = %p)\n", __func__, pCallback);
}

S_API void S_CALLTYPE
SteamAPI_RunCallbacks(void)
{
}

S_API void S_CALLTYPE
Steam_RunCallbacks(void)
{
}

S_API void S_CALLTYPE
SteamAPI_SetTryCatchCallbacks(bool enable)
{
	xlogf("%s(enable = %d)\n", __func__, enable);
}

S_API ISteamClient *S_CALLTYPE
SteamInternal_CreateInterface(const char *ver, bool *err)
{
	xlogf("%s(ver = %s, err = %p) -> %p\n", __func__, ver, &ctx.client, err);
	snprintf(ctx.client.base.version, sizeof(ctx.client.base.version), "%s", ver);
	initSteamInterface();
	return &ctx.client;
}

S_API ISteamClient *S_CALLTYPE
CreateInterface(const char *ver, bool *err)
{
	xlogf("%s(ver = %s, err = %p)\n", __func__, ver, err);
	return SteamInternal_CreateInterface(ver, err);
}

S_API void *S_CALLTYPE
SteamInternal_FindOrCreateUserInterface(HSteamUser hSteamUser, const char *pszVersion)
{
	void *ptr;

	ptr = &ctx.dummy;
	if (strstr(pszVersion, "STEAMUSERSTATS"))
		ptr = &ctx.userStats;
	else if (strstr(pszVersion, "SteamUser"))
		ptr = &ctx.user;
	else if (strstr(pszVersion, "STEAMINVENTORY"))
		ptr = &ctx.inventory;
	else if (strstr(pszVersion, "SteamController"))
		ptr = &ctx.controller;
	else if (strstr(pszVersion, "SteamInput"))
		ptr = &ctx.input;
	else if (strstr(pszVersion, "SteamUtils"))
		ptr = &ctx.utils;

	xlogf("%s(hSteamUser = %d, pszVersion = %s) -> %p\n", __func__, hSteamUser, pszVersion, ptr);

	return ptr;
}

S_API void *S_CALLTYPE
SteamInternal_FindOrCreateGameServerInterface(HSteamUser hSteamUser, const char *pszVersion)
{
	xlogf("%s(hSteamUser = %d, pszVersion = %s)\n", __func__, hSteamUser, pszVersion);
	return SteamInternal_FindOrCreateUserInterface(hSteamUser, pszVersion);
}

S_API void *S_CALLTYPE
SteamInternal_ContextInit(SteamInternalContext *self)
{
	xlogf("%s(self = %p) (init = %p, ref = %llu, userdata = %p)\n", __func__, self, self->init, (uvlong)self->iref, self->userdata);
	if (self->iref != ctx.ref) {
		self->init(&self->userdata);
		self->iref = ctx.ref;
	}
	xlogf("\n%s(self = %p) returning -> (ref = %llu, userdata = %p)\n", __func__, self, (uvlong)self->iref, self->userdata);
	return &self->userdata;
}

S_API void S_CALLTYPE
SteamAPI_RegisterCallResult(CCallbackBase *pCallback, SteamAPICall_t hAPICall)
{
	xlogf("%s(pCallback = %p, hAPICall = %llu)\n", __func__, pCallback, hAPICall);
}

S_API void S_CALLTYPE
SteamAPI_UnregisterCallResult(CCallbackBase *pCallback, SteamAPICall_t hAPICall)
{
	xlogf("%s(pCallback = %p, hAPICall = %llu)\n", __func__, pCallback, hAPICall);
}

S_API void S_CALLTYPE
SteamAPI_ReleaseCurrentThreadMemory(void)
{
	xlogf("%s()\n", __func__);
}

S_API bool S_CALLTYPE
SteamAPI_IsSteamRunning(void)
{
	xlogf("%s()\n", __func__);
	return true;
}

S_API void S_CALLTYPE
SteamAPI_UseBreakpadCrashHandler(char const *pchVersion, char const *pchDate, char const *pchTime, bool bFullMemoryDumps, void *pvContext, PFNPreMinidumpCallback m_pfnPreMinidumpCallback)
{
	xlogf("%s(pchVersion = %s, pchDate = %s, pchTime = %s, bFullMemoryDumps = %d, pvContext = %p, m_pfnPreMinidumpCallback = %p)\n", __func__, pchVersion, pchDate, pchTime, bFullMemoryDumps, pvContext, m_pfnPreMinidumpCallback);
}

S_API void S_CALLTYPE
SteamAPI_SetBreakpadAppID(uint32 unAppID)
{
	xlogf("%s(unAppId = %x)\n", __func__, unAppID);
}

#if defined(_WIN32)
void
FormatMbiString(MEMORY_BASIC_INFORMATION *Mbi, char *Buffer)
{
	int n;

	n = sprintf(Buffer, "%016lx-%016lx %-8x ", (unsigned long)(uintptr_t)Mbi->BaseAddress, (unsigned long)((uintptr_t)Mbi->BaseAddress + Mbi->RegionSize), (UINT)Mbi->RegionSize);
	switch (Mbi->Type) {
	case MEM_IMAGE:
		n += sprintf(Buffer + n, "IMAGE   ");
		break;
	case MEM_MAPPED:
		n += sprintf(Buffer + n, "MAPPED  ");
		break;
	case MEM_PRIVATE:
		n += sprintf(Buffer + n, "PRIVATE ");
		break;
	default:
		n += sprintf(Buffer + n, "UNMAPPED");
		break;
	}

	n += sprintf(Buffer + n, " ");
	switch (Mbi->Type) {
	case MEM_COMMIT:
		n += sprintf(Buffer + n, "COMMIT");
		break;
	case MEM_FREE:
		n += sprintf(Buffer + n, "FREE");
		break;
	case MEM_RESERVE:
		n += sprintf(Buffer + n, "RESERVE");
		break;
	default:
		n += sprintf(Buffer + n, "N/A");
		break;
	}

	n += sprintf(Buffer + n, " (%04lx) ", (unsigned long)Mbi->Protect);
	if (Mbi->Protect & 0x80)
		n += sprintf(Buffer + n, "WC");
	if (Mbi->Protect & 0x40)
		n += sprintf(Buffer + n, "RWX");
	if (Mbi->Protect & 0x10)
		n += sprintf(Buffer + n, "R");
	if (Mbi->Protect & 0x20)
		n += sprintf(Buffer + n, "X");
	if (Mbi->Protect & 0x02)
		n += sprintf(Buffer + n, "R");
	if (Mbi->Protect & 0x04)
		n += sprintf(Buffer + n, "RW");
	if (Mbi->Protect & 0x08)
		n += sprintf(Buffer + n, "WC");
	if (Mbi->Protect < 0x2)
		n += sprintf(Buffer + n, "-");
}

void
DumpProcessMemory(void)
{
	char Buffer[1024], Filename[MAX_PATH];
	MEMORY_BASIC_INFORMATION Mbi;
	HANDLE Handle;
	LPVOID Addr;

	Handle = GetCurrentProcess();
	Addr = NULL;
	for (;;) {
		if (!VirtualQueryEx(Handle, Addr, &Mbi, sizeof(Mbi)))
			break;
		if (Mbi.RegionSize > ((uintptr_t)-1) - ((uintptr_t)Mbi.BaseAddress))
			break;

		Filename[0] = '\0';
		K32GetMappedFileNameA(Handle, Addr, Filename, sizeof(Filename));

		FormatMbiString(&Mbi, Buffer);
		xlogf("%s\t%s\n", Buffer, Filename);

		Addr = (LPVOID)((uintptr_t)Mbi.BaseAddress + Mbi.RegionSize);
		if (Addr == NULL)
			break;
	}
}

void
PrintStack(void)
{
	unsigned int i;
	void *stack[1024];
	unsigned short frames;
	SYMBOL_INFO *symbol;
	HANDLE process;

	process = GetCurrentProcess();

	SymInitialize(process, NULL, TRUE);

	frames = CaptureStackBackTrace(0, nelem(stack), stack, NULL);
	symbol = (SYMBOL_INFO *)calloc(sizeof(SYMBOL_INFO) + 256 * sizeof(char), 1);
	symbol->MaxNameLen = 255;
	symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

	xlogf("Thread %lx Stack Dump:\n", GetCurrentThreadId());
	for (i = 0; i < frames; i++) {
		SymFromAddr(process, (uintptr_t)(stack[i]), 0, symbol);
		xlogf("%-2i (%p): %s - 0x%0lX\n", frames - i - 1, stack[i], symbol->Name, (unsigned long)symbol->Address);
	}

	free(symbol);
}

const char *
GetExceptionString(int ExceptionCode)
{
	switch (ExceptionCode) {
	case DBG_PRINTEXCEPTION_C:
		return "DBG_PRINTEXCEPTION_C";
	case EXCEPTION_BREAKPOINT:
		return "EXCEPTION_BREAKPOINT";
	case EXCEPTION_ACCESS_VIOLATION:
		return "EXCEPTION_ACCESS_VIOLATION";
	}
	return "UNKNOWN_EXCEPTION_CODE";
}

LONG WINAPI
ExceptionHandler(PEXCEPTION_POINTERS pExceptionInfo)
{
	xlogf("----------\n");

	xlogf("%s(pExceptionInfo = %p)\n", __func__, (void *)pExceptionInfo);
	xlogf("Exception Record {\n");
	xlogf("\tCode:             %x\n", (UINT)pExceptionInfo->ExceptionRecord->ExceptionCode);
	xlogf("\tCode String:      %s\n", GetExceptionString(pExceptionInfo->ExceptionRecord->ExceptionCode));
	xlogf("\tFlags:            %x\n", (UINT)pExceptionInfo->ExceptionRecord->ExceptionFlags);
	xlogf("\tFlags:            %x\n", (UINT)pExceptionInfo->ExceptionRecord->ExceptionAddress);
	xlogf("\tNumberParameters: %d\n", (INT)pExceptionInfo->ExceptionRecord->NumberParameters);
	xlogf("}\n\n");

#if defined(_WIN64)
	xlogf("Context Record {\n");
	xlogf("\tRAX:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Rax);
	xlogf("\tRCX:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Rcx);
	xlogf("\tRDX:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Rdx);
	xlogf("\tRBX:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Rbx);
	xlogf("\tRBP:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Rbp);
	xlogf("\tRSI:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Rsi);
	xlogf("\tRDI:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Rdi);
	xlogf("\tR8:   %lx\n", (ULONG)pExceptionInfo->ContextRecord->R8);
	xlogf("\tR9:   %lx\n", (ULONG)pExceptionInfo->ContextRecord->R9);
	xlogf("\tR10:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->R10);
	xlogf("\tR11:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->R11);
	xlogf("\tR12:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->R12);
	xlogf("\tR13:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->R13);
	xlogf("\tR14:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->R14);
	xlogf("\tR15:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->R15);
	xlogf("\tRIP:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Rip);
	xlogf("\tRSP:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Rsp);
	xlogf("}\n");
#else
	xlogf("Context Record {\n");
	xlogf("\tEAX:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Eax);
	xlogf("\tECX:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Ecx);
	xlogf("\tEDX:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Edx);
	xlogf("\tEBX:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Ebx);
	xlogf("\tEBP:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Ebp);
	xlogf("\tESI:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Esi);
	xlogf("\tEDI:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Edi);
	xlogf("\tEIP:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Eip);
	xlogf("\tESP:  %lx\n", (ULONG)pExceptionInfo->ContextRecord->Esp);
	xlogf("}\n");
#endif
	acquireLock(&ctx.globalLock);
	DumpProcessMemory();
	PrintStack();
	releaseLock(&ctx.globalLock);
	return EXCEPTION_EXECUTE_HANDLER;
}

BOOL WINAPI
Steam_IsDebuggerPresent(void)
{
	xlogf("%s()\n", __func__);
	return 0;
}

void WINAPI
Steam_OutputDebugStringA(LPCSTR lpOutputString)
{
	xlogf("%s(lpOutputString = (%p) %s)\n", __func__, lpOutputString, lpOutputString);
	acquireLock(&ctx.globalLock);
	DumpProcessMemory();
	PrintStack();
	releaseLock(&ctx.globalLock);
	DebugBreak();
}

#if defined(_MSC_VER) && defined(DETOURS)
#include <detours.h>

BOOL(WINAPI *TrueIsDebuggerPresent)
(void) = IsDebuggerPresent;
HINSTANCE(WINAPI *TrueShellExecuteA)
(HWND, LPCSTR, LPCSTR, LPCSTR, LPCSTR, INT) = ShellExecuteA;
void(WINAPI *TrueOutputDebugStringA)(LPCSTR) = OutputDebugStringA;
FARPROC(WINAPI *TrueGetProcAddress)
(HMODULE, LPCSTR) = GetProcAddress;
HMODULE(WINAPI *TrueLoadLibraryA)
(LPCSTR) = LoadLibraryA;
HMODULE(WINAPI *TrueLoadLibraryExA)
(LPCSTR, HANDLE, DWORD) = LoadLibraryExA;
HMODULE(WINAPI *TrueGetModuleHandleA)
(LPCSTR lpModuleName) = GetModuleHandleA;
DWORD(WINAPI *TrueGetModuleFileNameA)
(HMODULE hModule, LPSTR lpFilename, DWORD nSize) = GetModuleFileNameA;
LPTOP_LEVEL_EXCEPTION_FILTER(WINAPI *TrueSetUnhandledExceptionFilter)
(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter) = SetUnhandledExceptionFilter;
BOOL(WINAPI *TrueSetStdHandle)
(DWORD nStdHandle, HANDLE hHandle) = SetStdHandle;
LPVOID(WINAPI *TrueHeapAlloc)
(HANDLE hHandle, DWORD dwFlags, SIZE_T dwBytes) = HeapAlloc;
LPVOID(WINAPI *TrueVirtualAlloc)
(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect) = VirtualAlloc;
void *(*TrueCalloc)(size_t num, size_t size) = calloc;
LSTATUS(WINAPI *TrueRegOpenKeyExA)
(HKEY hKey, LPCSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult) = RegOpenKeyExA;
LSTATUS(WINAPI *TrueRegCloseKey)
(HKEY hKey) = RegCloseKey;
LSTATUS(WINAPI *TrueRegQueryValueExA)
(HKEY hKey, LPCSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData) = RegQueryValueExA;
HANDLE(WINAPI *TrueOpenProcess)
(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProccessId) = OpenProcess;
BOOL(WINAPI *TrueEnumProcesses)
(DWORD *lpidProcess, DWORD cb, LPDWORD lpCbNeeded) = EnumProcesses;

NTSTATUS WINAPI
Steam_NtSetInformationThread(HANDLE Handle, THREADINFOCLASS Class, LPVOID Data, ULONG Length)
{
	xlogf("%s(Handle = %#x, Class = %#x, Data = %p, Length = %lu)\n", __func__, Handle, Class, Data, Length);
	return 0;
}

HINSTANCE WINAPI
Steam_ShellExecuteA(HWND hwnd, LPCSTR lpOperation, LPCSTR lpFile, LPCSTR lpParameters, LPCSTR lpDirectory, INT nShowCmd)
{
	xlogf("%s(hwnd = %x, lpOperation = %s, lpFile = %s, lpParameters = %s, lpDirectory = %s, nShowCmd = %d)\n", __func__, (UINT)hwnd, lpOperation, lpFile, lpParameters, lpDirectory, nShowCmd);
	return TrueShellExecuteA(hwnd, lpOperation, lpFile, lpParameters, lpDirectory, nShowCmd);
}

LPTOP_LEVEL_EXCEPTION_FILTER WINAPI
Steam_SetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter)
{
	xlogf("%s(lpTopLevelExceptionFilter = %p)\n", __func__, lpTopLevelExceptionFilter);
	return NULL;
}

HMODULE WINAPI
Steam_LoadLibraryA(LPCSTR lpLibFilename)
{
	HMODULE Module = TrueLoadLibraryA(lpLibFilename);
	xlogf("%s(lpLibFilename = %s) -> %p\n", __func__, lpLibFilename, Module);
	return Module;
}

HMODULE WINAPI
Steam_LoadLibraryExA(LPCSTR lpLibFilename, HANDLE hFile, DWORD dwFlags)
{
	HMODULE Module = TrueLoadLibraryExA(lpLibFilename, hFile, dwFlags);
	xlogf("%s(lpLibFilename = %s, hFile = %d, dwFlags = %#lx) -> %p\n", __func__, lpLibFilename, hFile, dwFlags, Module);
	return Module;
}

HMODULE WINAPI
Steam_GetModuleHandleA(LPCSTR lpModuleName)
{
	HMODULE Module = TrueGetModuleHandleA(lpModuleName);
	xlogf("%s(lpModuleName = %s) -> %#x\n", __func__, lpModuleName, Module);
	return Module;
}

DWORD WINAPI
Steam_GetModuleFileNameA(HMODULE hModule, LPSTR lpFilename, DWORD nSize)
{
	DWORD Ret = TrueGetModuleFileNameA(hModule, lpFilename, nSize);
	xlogf("%s(hModule = %#x, lpFilename = %s, nSize = %d) -> %d\n", __func__, hModule, lpFilename, nSize, Ret);
	return Ret;
}

BOOL WINAPI
Steam_SetStdHandle(DWORD nStdHandle, HANDLE hHandle)
{
	xlogf("%s(nStdHandle = %d, hHandle = %#x)\n", __func__, nStdHandle, hHandle);
	return TRUE;
}

LPVOID WINAPI
Steam_HeapAlloc(HANDLE hHandle, DWORD dwFlags, SIZE_T dwBytes)
{
	LPVOID Ptr = TrueHeapAlloc(hHandle, dwFlags, dwBytes);
	//xlogf("%s(hHandle = %#x, dwFlags = %#x, dwBytes = %d) -> %#x\n", __func__, hHandle, dwFlags, dwBytes, Ptr);
	return Ptr;
}

LPVOID WINAPI
Steam_MapViewOfFile(HANDLE hFileMappingObject, DWORD dwDesiredAccess, DWORD dwFileOffsetHigh, DWORD dwFileOffsetLow, SIZE_T dwNumbersOfBytesToMap)
{
	LPVOID Ptr = MapViewOfFile(hFileMappingObject, dwDesiredAccess, dwFileOffsetHigh, dwFileOffsetLow, dwNumbersOfBytesToMap);
	xlogf("%s(hFileMappingObject = %#x, dwDesiredAccess = %#x, dwFileOffsetHigh = %#x, dwFileOffsetLow = %#x, dwNumbersOfBytesToMap = %#x) -> %#x\n",
	      __func__, hFileMappingObject, dwDesiredAccess, dwFileOffsetHigh, dwFileOffsetLow, dwNumbersOfBytesToMap, Ptr);
	return Ptr;
}

LPVOID WINAPI
Steam_VirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect)
{
	LPVOID Ptr = TrueVirtualAlloc(lpAddress, dwSize, flAllocationType, flProtect);
	xlogf("%s(lpAddress = %p, dwSize = %#x, flAllocationType = %#x, flProtect = %#x) -> %p\n",
	      __func__, lpAddress, dwSize, flAllocationType, flProtect, Ptr);
	return Ptr;
}

void *
Steam_Calloc(size_t num, size_t size)
{
	void *Ptr = TrueCalloc(num, size);
	xlogf("%s(num = %lu, size = %lu) -> %p\n", __func__, (unsigned long)num, (unsigned long)size, Ptr);
	return Ptr;
}

LSTATUS WINAPI
Steam_RegOpenKeyExA(HKEY hKey, LPCSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult)
{
	LSTATUS Status = TrueRegOpenKeyExA(hKey, lpSubKey, ulOptions, samDesired, phkResult);
	xlogf("%s(hKey = %#x, lpSubKey = %s, ulOptions = %#x, samDesired = %p, phkResult = %p) -> %#x %ld\n",
	      __func__, hKey, lpSubKey, ulOptions, samDesired, phkResult, phkResult ? *phkResult : 0, Status);
	return Status;
}

LSTATUS WINAPI
Steam_RegCloseKey(HKEY hKey)
{
	LSTATUS Status = TrueRegCloseKey(hKey);
	xlogf("%s(hKey = %#x)\n", __func__, hKey);
	return Status;
}

LSTATUS WINAPI
Steam_RegQueryValueExA(HKEY hKey, LPCSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData)
{
	LSTATUS Status = TrueRegQueryValueExA(hKey, lpValueName, lpReserved, lpType, lpData, lpcbData);
	xlogf("%s(hKey = %#x, lpValueName = %s, lpReserved = %p, lpType = %p, lpData = %p, lpcbData = %p) -> %ld\n",
	      __func__, hKey, lpValueName, lpReserved, lpType, lpData, lpcbData, Status);
	return Status;
}

HANDLE WINAPI
Steam_OpenProcess(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId)
{
	HANDLE Handle;
	if (dwProcessId = ctx.steamPID)
		Handle = GetCurrentProcess();
	else
		Handle = TrueOpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
	xlogf("%s(dwDesiredAccess = %#x, bInheritHandle = %d, dwProcessId = %d) (steamPID = %d) -> %#lx\n",
	      __func__, dwDesiredAccess, bInheritHandle, dwProcessId, ctx.steamPID, Handle);
	return Handle;
}

BOOL WINAPI
Steam_EnumProcesses(DWORD *lpidProcess, DWORD cb, LPDWORD lpcbNeeded)
{
	BOOL Ret = TrueEnumProcesses(lpidProcess, cb, lpcbNeeded);
	xlogf("%s(lpidProcess = %p, cb = %d, lpcbNeeded = %p) -> %d, %d",
	      __func__, cb, lpcbNeeded, (lpcbNeeded) ? *lpcbNeeded : 0, Ret);
	return Ret;
}

FARPROC WINAPI
Steam_GetProcAddress(HMODULE hModule, LPCSTR lpProcName)
{
	FARPROC Proc;
	if (!strcmp(lpProcName, "NtSetInformationThread"))
		Proc = (FARPROC)Steam_NtSetInformationThread;
	else if (!strcmp(lpProcName, "SetUnhandledExceptionFilter"))
		Proc = (FARPROC)Steam_SetUnhandledExceptionFilter;
	else if (!strcmp(lpProcName, "IsDebuggerPresent"))
		Proc = (FARPROC)Steam_IsDebuggerPresent;
	else if (!strcmp(lpProcName, "GetProcAddress"))
		Proc = (FARPROC)Steam_GetProcAddress;
	else if (!strcmp(lpProcName, "SetStdHandle"))
		Proc = (FARPROC)Steam_SetStdHandle;
	else if (!strcmp(lpProcName, "HeapAlloc"))
		Proc = (FARPROC)Steam_HeapAlloc;
	else if (!strcmp(lpProcName, "MapViewOfFile"))
		Proc = (FARPROC)Steam_MapViewOfFile;
	else if (!strcmp(lpProcName, "VirtualAlloc"))
		Proc = (FARPROC)Steam_VirtualAlloc;
	else if (!strcmp(lpProcName, "calloc"))
		Proc = (FARPROC)Steam_Calloc;
	else if (!strcmp(lpProcName, "RegOpenKeyExA"))
		Proc = (FARPROC)Steam_RegOpenKeyExA;
	else if (!strcmp(lpProcName, "RegQueryValueExA"))
		Proc = (FARPROC)Steam_RegQueryValueExA;
	else if (!strcmp(lpProcName, "RegCloseKey"))
		Proc = (FARPROC)Steam_RegCloseKey;
	else if (!strcmp(lpProcName, "OpenProcess"))
		Proc = (FARPROC)Steam_OpenProcess;
	else if (!strcmp(lpProcName, "EnumProcesses"))
		Proc = (FARPROC)Steam_EnumProcesses;
	else if (!strcmp(lpProcName, "CreateInterface"))
		Proc = (FARPROC)SteamInternal_CreateInterface;
	else
		Proc = TrueGetProcAddress(hModule, lpProcName);
	xlogf("%s(hModule = %#x, lpProcName = %s) -> %p\n", __func__, hModule, lpProcName, Proc);
	return Proc;
}

void
attachDetours(void)
{
	xlogf("%s()\n", __func__);
	DetourRestoreAfterWith();
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID)TrueIsDebuggerPresent, Steam_IsDebuggerPresent);
	DetourAttach(&(PVOID)TrueOutputDebugStringA, Steam_OutputDebugStringA);
	DetourAttach(&(PVOID)TrueShellExecuteA, Steam_ShellExecuteA);
	DetourAttach(&(PVOID)TrueGetProcAddress, Steam_GetProcAddress);
	DetourAttach(&(PVOID)TrueLoadLibraryA, Steam_LoadLibraryA);
	DetourAttach(&(PVOID)TrueLoadLibraryExA, Steam_LoadLibraryExA);
	DetourAttach(&(PVOID)TrueGetModuleHandleA, Steam_GetModuleHandleA);
	DetourAttach(&(PVOID)TrueGetModuleFileNameA, Steam_GetModuleFileNameA);
	DetourAttach(&(PVOID)TrueSetUnhandledExceptionFilter, Steam_SetUnhandledExceptionFilter);
	DetourAttach(&(PVOID)TrueSetStdHandle, Steam_SetStdHandle);
	DetourAttach(&(PVOID)TrueRegOpenKeyExA, Steam_RegOpenKeyExA);
	DetourAttach(&(PVOID)TrueRegQueryValueExA, Steam_RegQueryValueExA);
	DetourAttach(&(PVOID)TrueRegCloseKey, Steam_RegCloseKey);
	DetourTransactionCommit();
}

void
detachDetours(void)
{
	xlogf("%s()\n", __func__);
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&(PVOID)TrueIsDebuggerPresent, Steam_IsDebuggerPresent);
	DetourDetach(&(PVOID)TrueOutputDebugStringA, Steam_OutputDebugStringA);
	DetourDetach(&(PVOID)TrueShellExecuteA, Steam_ShellExecuteA);
	DetourDetach(&(PVOID)TrueGetProcAddress, Steam_GetProcAddress);
	DetourDetach(&(PVOID)TrueLoadLibraryA, Steam_LoadLibraryA);
	DetourDetach(&(PVOID)TrueLoadLibraryExA, Steam_LoadLibraryExA);
	DetourDetach(&(PVOID)TrueGetModuleHandleA, Steam_GetModuleHandleA);
	DetourDetach(&(PVOID)TrueGetModuleFileNameA, Steam_GetModuleFileNameA);
	DetourDetach(&(PVOID)TrueSetUnhandledExceptionFilter, Steam_SetUnhandledExceptionFilter);
	DetourDetach(&(PVOID)TrueSetStdHandle, Steam_SetStdHandle);
	DetourDetach(&(PVOID)TrueRegOpenKeyExA, Steam_RegOpenKeyExA);
	DetourDetach(&(PVOID)TrueRegQueryValueExA, Steam_RegQueryValueExA);
	DetourDetach(&(PVOID)TrueRegCloseKey, Steam_RegCloseKey);
	DetourTransactionCommit();
}
#endif

typedef NTSTATUS(NTAPI *NtQuerySystemProcessFunc)(HANDLE, PROCESSINFOCLASS, PVOID, ULONG, PULONG);

PPEB
findPEB(void)
{
	NtQuerySystemProcessFunc Query;
	PROCESS_BASIC_INFORMATION Info;
	HANDLE Process;
	ULONG Length;
	NTSTATUS Status;

	Query = (NtQuerySystemProcessFunc)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtQueryInformationProcess");
	if (!Query)
		return NULL;
	Process = GetCurrentProcess();
	Length = sizeof(Info);
	Status = Query(Process, ProcessBasicInformation, &Info, sizeof(Info), &Length);
	if (Status != 0)
		return NULL;
	return Info.PebBaseAddress;
}

void
writeRegistryValues(void)
{
	const char *SubKey = "Software\\Valve\\Steam\\ActiveProcess";
	HKEY Key;
	DWORD Pid;
	DWORD User;

	if (RegCreateKeyA(HKEY_CURRENT_USER, SubKey, &Key) != ERROR_SUCCESS)
		return;
	Pid = ctx.steamPID;
	User = ctx.steamUser;
	RegSetKeyValueA(HKEY_CURRENT_USER, SubKey, "pid", REG_DWORD, &Pid, sizeof(Pid));
	RegSetKeyValueA(HKEY_CURRENT_USER, SubKey, "ActiveUser", REG_DWORD, &User, sizeof(User));
	RegCloseKey(Key);
}

void
hideDebugger(void)
{
	PPEB Peb;
	Peb = findPEB();
	if (Peb)
		Peb->BeingDebugged = 0;
}

BOOL APIENTRY
DllMain(HANDLE hModule, DWORD reason, LPVOID lpReserved)
{
#if defined(_MSC_VER) && defined(DETOURS)
	if (DetourIsHelperProcess())
		return TRUE;
#endif

	if (reason == DLL_PROCESS_ATTACH) {
		initSteam();
		writeRegistryValues();
		hideDebugger();
#if defined(_MSC_VER) && defined(DETOURS)
		attachDetours();
		//AddVectoredExceptionHandler(1, ExceptionHandler);
#endif
	} else if (reason == DLL_PROCESS_DETACH) {
#if defined(_MSC_VER) && defined(DETOURS)
		detachDetours();
#endif
	}

	xlogf("%s(hModule = %p, reason = %lx, lpReserved = %p)\n", __func__, hModule, reason, lpReserved);

	return TRUE;
}
#endif
