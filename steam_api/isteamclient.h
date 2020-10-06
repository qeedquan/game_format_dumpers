#pragma once

//-----------------------------------------------------------------------------
// Purpose: Base values for callback identifiers, each callback must
//			have a unique ID.
//-----------------------------------------------------------------------------
enum { k_iSteamUserCallbacks = 100 };
enum { k_iSteamGameServerCallbacks = 200 };
enum { k_iSteamFriendsCallbacks = 300 };
enum { k_iSteamBillingCallbacks = 400 };
enum { k_iSteamMatchmakingCallbacks = 500 };
enum { k_iSteamContentServerCallbacks = 600 };
enum { k_iSteamUtilsCallbacks = 700 };
enum { k_iClientFriendsCallbacks = 800 };
enum { k_iClientUserCallbacks = 900 };
enum { k_iSteamAppsCallbacks = 1000 };
enum { k_iSteamUserStatsCallbacks = 1100 };
enum { k_iSteamNetworkingCallbacks = 1200 };
enum { k_iClientRemoteStorageCallbacks = 1300 };
enum { k_iClientDepotBuilderCallbacks = 1400 };
enum { k_iSteamGameServerItemsCallbacks = 1500 };
enum { k_iClientUtilsCallbacks = 1600 };
enum { k_iSteamGameCoordinatorCallbacks = 1700 };
enum { k_iSteamGameServerStatsCallbacks = 1800 };
enum { k_iSteam2AsyncCallbacks = 1900 };
enum { k_iSteamGameStatsCallbacks = 2000 };
enum { k_iClientHTTPCallbacks = 2100 };
enum { k_iClientScreenshotsCallbacks = 2200 };
enum { k_iSteamScreenshotsCallbacks = 2300 };
enum { k_iClientAudioCallbacks = 2400 };
enum { k_iClientUnifiedMessagesCallbacks = 2500 };
enum { k_iSteamStreamLauncherCallbacks = 2600 };
enum { k_iClientControllerCallbacks = 2700 };
enum { k_iSteamControllerCallbacks = 2800 };
enum { k_iClientParentalSettingsCallbacks = 2900 };
enum { k_iClientDeviceAuthCallbacks = 3000 };
enum { k_iClientNetworkDeviceManagerCallbacks = 3100 };
enum { k_iClientMusicCallbacks = 3200 };
enum { k_iClientRemoteClientManagerCallbacks = 3300 };
enum { k_iClientUGCCallbacks = 3400 };
enum { k_iSteamStreamClientCallbacks = 3500 };
enum { k_IClientProductBuilderCallbacks = 3600 };
enum { k_iClientShortcutsCallbacks = 3700 };
enum { k_iClientRemoteControlManagerCallbacks = 3800 };
enum { k_iSteamAppListCallbacks = 3900 };
enum { k_iSteamMusicCallbacks = 4000 };
enum { k_iSteamMusicRemoteCallbacks = 4100 };
enum { k_iClientVRCallbacks = 4200 };
enum { k_iClientGameNotificationCallbacks = 4300 };
enum { k_iSteamGameNotificationCallbacks = 4400 };
enum { k_iSteamHTMLSurfaceCallbacks = 4500 };
enum { k_iClientVideoCallbacks = 4600 };
enum { k_iClientInventoryCallbacks = 4700 };
enum { k_iClientBluetoothManagerCallbacks = 4800 };
enum { k_iClientSharedConnectionCallbacks = 4900 };
enum { k_ISteamParentalSettingsCallbacks = 5000 };
enum { k_iClientShaderCallbacks = 5100 };

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
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamClient_SetLocalIPBinding(SELF, uint32 unIP, uint16 usPort);
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
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamClient_SetWarningMessageHook(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamClient_BShutdownIfAllPipesClosed(SELF);
S_CLASSAPI ISteamHTTP *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamHTTP(SELF, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamUnifiedMessages *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamUnifiedMessages(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamController *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamController(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamUGC *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamUGC(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamAppList *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamAppList(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamMusic *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamMusic(SELF, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamMusicRemote *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamMusicRemote(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamHTMLSurface *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamHTMLSurface(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamClient_Set_SteamAPI_CPostAPIResultInProcess(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamClient_Set_SteamAPI_CCheckCallbackRegisteredInProcess(SELF);
S_CLASSAPI ISteamInventory *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamInventory(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamVideo *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamVideo(SELF, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);
S_CLASSAPI ISteamParentalSettings *S_CLASSCALLTYPE SteamAPI_ISteamClient_GetISteamParentalSettings(SELF, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char *pchVersion);
