#pragma once

#include "steamtypes.h"

typedef uint64 ClientUnifiedMessageHandle;

typedef void ISteamUnifiedMessages;

typedef struct CSteamUnifiedMessages CSteamUnifiedMessages;

struct CSteamUnifiedMessages {
	CSteamBase base;
};

S_CLASSAPI ClientUnifiedMessageHandle S_CLASSCALLTYPE SteamAPI_ISteamUnifiedMessages_SendMethod(SELF, const char *pchServiceMethod, const void *pRequestBuffer, uint32 unRequestBufferSize, uint64 unContext);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUnifiedMessages_GetMethodResponseInfo(SELF, ClientUnifiedMessageHandle hHandle, uint32 *punResponseSize, EResult *peResult);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUnifiedMessages_GetMethodResponseData(SELF, ClientUnifiedMessageHandle hHandle, void *pResponseBuffer, uint32 unResponseBufferSize, bool bAutoRelease);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUnifiedMessages_ReleaseMethod(SELF, ClientUnifiedMessageHandle hHandle);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUnifiedMessages_SendNotification(SELF, const char *pchServiceNotification, const void *pNotificationBuffer, uint32 unNotificationBufferSize);