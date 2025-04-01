#pragma once

#include "steamtypes.h"
#include "isteamuser.h"
#include "isteamnetworking.h"
#include "isteamscreenshots.h"
#include "isteamhttp.h"
#include "isteamunifiedmessages.h"
#include "isteamugc.h"
#include "isteamapplist.h"
#include "isteammusic.h"
#include "isteammusicremote.h"
#include "isteaminventory.h"
#include "isteamvideo.h"
#include "isteamparentalsettings.h"
#include "isteamremoteplay.h"
#include "steam_api_common.h"

// Steam account types
typedef enum {
	k_EAccountTypeInvalid = 0,
	k_EAccountTypeIndividual = 1,     // single user account
	k_EAccountTypeMultiseat = 2,      // multiseat (e.g. cybercafe) account
	k_EAccountTypeGameServer = 3,     // game server account
	k_EAccountTypeAnonGameServer = 4, // anonymous game server account
	k_EAccountTypePending = 5,        // pending
	k_EAccountTypeContentServer = 6,  // content server
	k_EAccountTypeClan = 7,
	k_EAccountTypeChat = 8,
	k_EAccountTypeConsoleUser = 9, // Fake SteamID for local PSN account on PS3 or Live account on 360, etc.
	k_EAccountTypeAnonUser = 10,

	// Max of 16 items in self field
	k_EAccountTypeMax
} EAccountType;

typedef void ISteamClient;

typedef struct CSteamClient CSteamClient;

struct CSteamClient {
	CSteamBase base;
};

typedef void (*SteamAPI_PostAPIResultInProcess_t)(SteamAPICall_t callHandle, void *, uint32 unCallbackSize, int iCallbackNum);

S_CLASSAPI HSteamPipe S_CLASSCALLTYPE SteamAPI_ISteamClient_CreateSteamPipe(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamClient_BReleaseSteamPipe(SELF, HSteamPipe hSteamPipe);
S_CLASSAPI HSteamUser S_CLASSCALLTYPE SteamAPI_ISteamClient_ConnectToGlobalUser(SELF, HSteamPipe hSteamPipe);
S_CLASSAPI HSteamUser S_CLASSCALLTYPE SteamAPI_ISteamClient_CreateLocalUser(SELF, HSteamPipe *phSteamPipe, EAccountType eAccountType);
S_CLASSAPI HSteamPipe S_CLASSCALLTYPE SteamAPI_GetHSteamPipe(void);
S_CLASSAPI HSteamUser S_CLASSCALLTYPE SteamAPI_GetHSteamUser(void);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamClient_ReleaseUser(SELF, HSteamPipe hSteamPipe, HSteamUser hUser);
S_CLASSAPI ISteamUser *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamUser(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamGameServer *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamGameServer(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamClient_SetLocalIPBindingUint32(SELF, uint32 unIP, uint16 usPort);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamClient_SetLocalIPBinding(SELF, SteamIPAddress_t *unIP, uint16 usPort);
S_CLASSAPI ISteamFriends *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamFriends(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamUtils *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamUtils(SELF, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamMatchmaking *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamMatchmaking(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamMatchmakingServers *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamMatchmakingServers(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI void *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamGenericInterface(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamUserStats *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamUserStats(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamGameServerStats *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamGameServerStats(SELF, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamApps *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamApps(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamNetworking *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamNetworking(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamRemoteStorage *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamRemoteStorage(SELF, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamScreenshots *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamScreenshots(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamClient_RunFrame(SELF);
S_CLASSAPI uint32 S_CLASSCALLTYPE SteamAPI_ISteamClient_GetIPCCallCount(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamClient_SetWarningMessageHook(SELF, SteamAPIWarningMessageHook_t pFunction);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamClient_BShutdownIfAllPipesClosed(SELF);
S_CLASSAPI ISteamHTTP *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamHTTP(SELF, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamUnifiedMessages *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamUnifiedMessages(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamController *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamController(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamUGC *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamUGC(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamAppList *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamAppList(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamMusic *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamMusic(SELF, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamMusicRemote *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamMusicRemote(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamHTMLSurface *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamHTMLSurface(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamClient_Set_SteamAPI_CPostAPIResultInProcess(SELF, void (*func)());
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamClient_Remove_SteamAPI_CPostAPIResultInProcess(SELF, void (*func)());
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamClient_Set_SteamAPI_CCheckCallbackRegisteredInProcess(SELF, SteamAPI_CheckCallbackRegistered_t func);
S_CLASSAPI ISteamInventory *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamInventory(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamVideo *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamVideo(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamParentalSettings *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamParentalSettings(SELF, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamGameSearch *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamGameSearch(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamInput *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamInput(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamParties *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamParties(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamRemotePlay *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamRemotePlay(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamClient_DestroyAllInterfaces(SELF);
