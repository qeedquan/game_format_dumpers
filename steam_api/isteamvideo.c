#include "steam.h"

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamVideo_GetVideoURL(SELF, AppId_t unVideoAppID)
{
	xlogf("%s(self = %p, unVideoAppID = %d)\n", __func__, self, unVideoAppID);
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamVideo_IsBroadcasting(SELF, int *pnNumViewers)
{
	xlogf("%s(self = %p, pnNumViewers = %p)\n", __func__, self, pnNumViewers);
	return false;
}
