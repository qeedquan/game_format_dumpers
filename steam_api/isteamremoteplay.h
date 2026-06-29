#pragma once

#include "steamtypes.h"
#include "steamclientpublic.h"

typedef enum {
	k_ESteamDeviceFormFactorUnknown = 0,
	k_ESteamDeviceFormFactorPhone = 1,
	k_ESteamDeviceFormFactorTablet = 2,
	k_ESteamDeviceFormFactorComputer = 3,
	k_ESteamDeviceFormFactorTV = 4,
} ESteamDeviceFormFactor;

typedef uint32 RemotePlaySessionID_t;

typedef void ISteamRemotePlay;

typedef struct CSteamRemotePlay CSteamRemotePlay;

struct CSteamRemotePlay {
	CSteamBase base;
};

S_CLASSAPI uint32 S_CLASSCALLTYPE SteamAPI_ISteamRemotePlay_GetSessionCount(SELF);
S_CLASSAPI RemotePlaySessionID_t S_CLASSCALLTYPE SteamAPI_ISteamRemotePlay_GetSessionID(SELF, int iSessionIndex);
S_CLASSAPI CSteamID S_CLASSCALLTYPE SteamAPI_ISteamRemotePlay_GetSessionSteamID(SELF, RemotePlaySessionID_t unSessionID);
S_CLASSAPI const char *S_CLASSCALLTYPE SteamAPI_ISteamRemotePlay_GetSessionClientName(SELF, RemotePlaySessionID_t unSessionID);
S_CLASSAPI ESteamDeviceFormFactor S_CLASSCALLTYPE SteamAPI_ISteamRemotePlay_GetSessionClientFormFactor(SELF, RemotePlaySessionID_t unSessionID);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamRemotePlay_BGetSessionClientResolution(SELF, RemotePlaySessionID_t unSessionID, int *pnResolutionX, int *pnResolutionY);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamRemotePlay_BSendRemotePlayTogetherInvite(SELF, CSteamID steamIDFriend);
