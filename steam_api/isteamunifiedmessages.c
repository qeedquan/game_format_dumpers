#include "steam.h"

S_CLASSAPI ClientUnifiedMessageHandle S_CLASSCALLTYPE
SteamAPI_ISteamUnifiedMessages_SendMethod(SELF, const char *pchServiceMethod, const void *pRequestBuffer, uint32 unRequestBufferSize, uint64 unContext)
{
	xlogf("%s(self = %p, pchServiceMethod = %s, pRequestBuffer = %p, unRequestBufferSize = %d, unContext = %llu)\n", __func__, self, pchServiceMethod, pRequestBuffer, unRequestBufferSize, unContext);
	return 1;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUnifiedMessages_GetMethodResponseInfo(SELF, ClientUnifiedMessageHandle hHandle, uint32 *punResponseSize, EResult *peResult)
{
	xlogf("%s(self = %p, hHandle = %llu, punResponseSize = %p, peResult = %p)\n", __func__, self, hHandle, punResponseSize, peResult);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUnifiedMessages_GetMethodResponseData(SELF, ClientUnifiedMessageHandle hHandle, void *pResponseBuffer, uint32 unResponseBufferSize, bool bAutoRelease)
{
	xlogf("%s(self = %p, hHandle = %llu, pResponseBuffer = %p, unResponseBufferSize = %d, bAutoRelease = %d)\n", __func__, self, hHandle, pResponseBuffer, unResponseBufferSize, bAutoRelease);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUnifiedMessages_ReleaseMethod(SELF, ClientUnifiedMessageHandle hHandle)
{
	xlogf("%s(self = %p, hHandle = %llu)\n", __func__, self, hHandle);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUnifiedMessages_SendNotification(SELF, const char *pchServiceNotification, const void *pNotificationBuffer, uint32 unNotificationBufferSize)
{
	xlogf("%s(self = %p, pchServiceNotification = %s, pNotificationBuffer = %p, unNotificationBufferSize = %d)\n", __func__, self, pchServiceNotification, pNotificationBuffer, unNotificationBufferSize);
	return true;
}
