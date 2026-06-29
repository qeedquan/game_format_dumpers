#pragma once

#include "steamtypes.h"

typedef void ISteamVideo;

typedef struct CSteamVideo CSteamVideo;

struct CSteamVideo {
	CSteamBase base;
};

S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamVideo_GetVideoURL(SELF, AppId_t unVideoAppID);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamVideo_IsBroadcasting(SELF, int *pnNumViewers);