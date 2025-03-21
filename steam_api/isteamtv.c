#include "steam.h"

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamTV_IsBroadcasting(SELF, int *pnNumViewers)
{
	xlogf("%s(self = %p, pnNumViewers = %p)\n", __func__, self, pnNumViewers);
	return false;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamTV_AddBroadcastGameData(SELF, const char *pchKey, const char *pchValue)
{
	xlogf("%s(self = %p, pchKey = %s, pchValue = %s)\n", __func__, self, pchKey, pchValue);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamTV_RemoveBroadcastGameData(SELF, const char *pchKey)
{
	xlogf("%s(self = %p, pchKey = %s)\n", __func__, self, pchKey);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamTV_AddTimelineMarker(SELF, const char *pchTemplateName, bool bPersistent, uint8 nColorR, uint8 nColorG, uint8 nColorB)
{
	xlogf("%s(self = %p, pchTemplateName = %s, bPersistent = %d, nColorR = %d, nColorG = %d, nColorB = %d)\n",
	      __func__, self, pchTemplateName, bPersistent, nColorR, nColorG, nColorB);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamTV_RemoveTimelineMarker(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI uint32 S_CLASSCALLTYPE
SteamAPI_ISteamTV_AddRegion(SELF, const char *pchElementName, const char *pchTimelineDataSection, const SteamTVRegion_t *pSteamTVRegion, ESteamTVRegionBehavior eSteamTVRegionBehavior)
{
	xlogf("%s(self = %p, pchElementName = %s, pchTimelineDataSection = %s, pSteamTVRegion = %p, eSteamTVRegionBehavior %d)\n",
	      __func__, self, pchElementName, pchTimelineDataSection, pSteamTVRegion, eSteamTVRegionBehavior);
	return 0;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamTV_RemoveRegion(SELF, uint32 unRegionHandle)
{
	xlogf("%s(self = %p, unRegionHandle = %d)\n", __func__, self, unRegionHandle);
}
