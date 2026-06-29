#pragma once

#include "steamtypes.h"

typedef struct SteamTVRegion_t SteamTVRegion_t;

struct SteamTVRegion_t {
	int region;
};

typedef enum {
	ESTEAM_TV_REGION_NONE,
} ESteamTVRegionBehavior;

typedef void ISteamTV;

typedef struct CSteamTV CSteamTV;

struct CSteamTV {
	CSteamBase base;
};

S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamTV_IsBroadcasting(SELF, int *pnNumViewers);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamTV_AddBroadcastGameData(SELF, const char *pchKey, const char *pchValue);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamTV_RemoveBroadcastGameData(SELF, const char *pchKey);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamTV_AddTimelineMarker(SELF, const char *pchTemplateName, bool bPersistent, uint8 nColorR, uint8 nColorG, uint8 nColorB);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamTV_RemoveTimelineMarker(SELF);
S_CLASSAPI uint32 S_CLASSCALLTYPE SteamAPI_ISteamTV_AddRegion(SELF, const char *pchElementName, const char *pchTimelineDataSection, const SteamTVRegion_t *pSteamTVRegion, ESteamTVRegionBehavior eSteamTVRegionBehavior);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamTV_RemoveRegion(SELF, uint32 unRegionHandle);
