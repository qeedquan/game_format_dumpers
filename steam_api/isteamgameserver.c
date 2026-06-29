#include "steam.h"

S_API uint64 S_CALLTYPE
SteamGameServer_GetSteamID(void)
{
	xlogf("%s()\n", __func__);
	return ctx.steamID.m_gameID;
}

S_API HSteamPipe S_CALLTYPE
SteamGameServer_GetHSteamPipe(void)
{
	xlogf("%s()\n", __func__);
	return SteamAPI_GetHSteamPipe();
}

S_API HSteamUser S_CALLTYPE
SteamGameServer_GetHSteamUser(void)
{
	xlogf("%s()\n", __func__);
	return SteamAPI_GetHSteamUser();
}

S_API bool S_CALLTYPE
SteamGameServer_BSecure(void)
{
	xlogf("%s()\n", __func__);
	return true;
}

S_API void S_CALLTYPE
SteamGameServer_RunCallbacks(void)
{
}

S_API void S_CALLTYPE
SteamGameServer_Shutdown(void)
{
	xlogf("%s\n", __func__);
}

S_API bool S_CALLTYPE
SteamGameServer_Init(void)
{
	xlogf("%s()\n", __func__);
	return true;
}

S_API bool S_CALLTYPE
SteamGameServer_InitSafe(void)
{
	xlogf("%s()\n", __func__);
	return true;
}

S_API ISteamUtils *S_CALLTYPE
SteamGameServerUtils(void)
{
	xlogf("%s()\n", __func__);
	return &ctx.utils;
}

S_API ISteamInventory *S_CALLTYPE
SteamGameServerInventory(void)
{
	xlogf("%s()\n", __func__);
	return &ctx.inventory;
}

S_API ISteamInventory *S_CALLTYPE
SteamGameServerStats(void)
{
	xlogf("%s()\n", __func__);
	return &ctx.gameServerStats;
}

S_API ISteamUGC *S_CALLTYPE
SteamGameServerUGC(void)
{
	xlogf("%s()\n", __func__);
	return &ctx.ugc;
}

S_API ISteamNetworking *S_CALLTYPE
SteamGameServerNetworking(void)
{
	xlogf("%s()\n", __func__);
	return &ctx.networking;
}

S_API uint32 S_CALLTYPE
SteamGameServer_GetIPCCallCount(void)
{
	xlogf("%s()\n", __func__);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_InitGameServer(SELF, uint32 unIP, uint16 usGamePort, uint16 usQueryPort, uint32 unFlags, AppId_t nGameAppId, const char *pchVersionString)
{
	xlogf("%s(self = %p, unIP = %d, usGamePort = %d, usQueryPort = %d, unFlags = %#x, nGameAppId = %#x, pchVersionString = %s)\n", __func__, self, unIP, usGamePort, usQueryPort, unFlags, nGameAppId, pchVersionString);
	return true;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_SetProduct(SELF, const char *pszProduct)
{
	xlogf("%s(self = %p, pszProduct = %s)\n", __func__, self, pszProduct);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_SetGameDescription(SELF, const char *pszGameDescription)
{
	xlogf("%s(self = %p, pszGameDescription = %s)\n", __func__, self, pszGameDescription);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_SetModDir(SELF, const char *pszModDir)
{
	xlogf("%s(self = %p, pszModDir = %s)\n", __func__, self, pszModDir);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_SetDedicatedServer(SELF, bool bDedicated)
{
	xlogf("%s(self = %p, bDedicated = %d)\n", __func__, self, bDedicated);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_LogOn(SELF, const char *pszToken)
{
	xlogf("%s(self = %p, pszToken = %s)\n", __func__, self, pszToken);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_LogOnAnonymous(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_LogOff(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_BLoggedOn(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_BSecure(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return true;
}

S_CLASSAPI uint64 S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_GetSteamID(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_WasRestartRequested(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return false;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_SetMaxPlayerCount(SELF, int cPlayersMax)
{
	xlogf("%s(self = %p, cPlayersMax = %d)\n", __func__, self, cPlayersMax);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_SetBotPlayerCount(SELF, int cBotplayers)
{
	xlogf("%s(self = %p, cBotplayers = %d)\n", __func__, self, cBotplayers);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_SetServerName(SELF, const char *pszServerName)
{
	xlogf("%s(self = %p, pszServerName = %s)\n", __func__, self, pszServerName);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_SetMapName(SELF, const char *pszMapName)
{
	xlogf("%s(self = %p, pszMapName = %s)\n", __func__, self, pszMapName);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_SetPasswordProtected(SELF, bool bPasswordProtected)
{
	xlogf("%s(self = %p, bPasswordProtected = %d)\n", __func__, self, bPasswordProtected);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_SetSpectatorPort(SELF, uint16 unSpectatorPort)
{
	xlogf("%s(self = %p, unSpectatorPort = %d)\n", __func__, self, unSpectatorPort);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_SetSpectatorServerName(SELF, const char *pszSpectatorServerName)
{
	xlogf("%s(self = %p, pszSpectatorServerName = %s)\n", __func__, self, pszSpectatorServerName);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_ClearAllKeyValues(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_SetKeyValue(SELF, const char *pKey, const char *pValue)
{
	xlogf("%s(self = %p, pKey = %s, pValue = %s)\n", __func__, self, pKey, pValue);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_SetGameTags(SELF, const char *pchGameTags)
{
	xlogf("%s(self = %p, pchGameTags = %s)\n", __func__, self, pchGameTags);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_SetGameData(SELF, const char *pchGameData)
{
	xlogf("%s(self = %p, pchGameData = %s)\n", __func__, self, pchGameData);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_SetRegion(SELF, const char *pszRegion)
{
	xlogf("%s(self = %p, pszRegion = %s)\n", __func__, self, pszRegion);
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_SendUserConnectAndAuthenticate(SELF, uint32 unIPClient, const void *pvAuthBlob, uint32 cubAuthBlobSize, CSteamID *pSteamIDUser)
{
	xlogf("%s(self = %p, unIPClient = %#x, pvAuthBlob = %p, cubAuthBlobSize = %d, pSteamIDUser = %p)\n", __func__, self, unIPClient, pvAuthBlob, cubAuthBlobSize, pSteamIDUser);
	return true;
}

S_CLASSAPI uint64 S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_CreateUnauthenticatedUserConnection(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_SendUserDisconnect(SELF, CSteamID steamIDUser)
{
	xlogf("%s(self = %p, steamIDUser = %llu)\n", __func__, self, steamIDUser.m_gameID);
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_BUpdateUserData(SELF, CSteamID steamIDUser, const char *pchPlayerName, uint32 uScore)
{
	xlogf("%s(self = %p, steamIDUser = %llu, pchPlayerName = %s, uScore = %d)\n", __func__, self, steamIDUser.m_gameID, pchPlayerName, uScore);
	return true;
}

S_CLASSAPI HAuthTicket S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_GetAuthSessionTicket(SELF, void *pTicket, int cbMaxTicket, uint32 *pcbTicket)
{
	xlogf("%s(self = %p, pTicket = %p, cbMaxTicket = %d, pcbTicket = %p)\n", __func__, self, pTicket, cbMaxTicket, pcbTicket);
	return 0;
}

S_CLASSAPI EBeginAuthSessionResult S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_BeginAuthSession(SELF, const void *pAuthTicket, int cbAuthTicket, CSteamID steamID)
{
	xlogf("%s(self = %p, pAuthTicket = %p, cbAuthTicket = %d, steamID = %llu)\n", __func__, self, pAuthTicket, cbAuthTicket, steamID.m_gameID);
	return 0;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_EndAuthSession(SELF, CSteamID steamID)
{
	xlogf("%s(self = %p, steamID = %llu)\n", __func__, self, steamID.m_gameID);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_CancelAuthTicket(SELF, HAuthTicket hAuthTicket)
{
	xlogf("%s(self = %p, hAuthTicket = %d)\n", __func__, self, hAuthTicket);
}

S_CLASSAPI EUserHasLicenseForAppResult S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_UserHasLicenseForApp(SELF, CSteamID steamID, AppId_t appID)
{
	xlogf("%s(self = %p, steamID = %llu, appID = %d)\n", __func__, self, steamID.m_gameID, appID);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_RequestUserGroupStatus(SELF, CSteamID steamIDUser, CSteamID steamIDGroup)
{
	xlogf("%s(self = %p, steamIDUser = %llu, steamIDGroup = %llu)\n", __func__, self, steamIDUser.m_gameID, steamIDGroup.m_gameID);
	return true;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_GetGameplayStats(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_GetServerReputation(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI uint32 S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_GetPublicIP(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_HandleIncomingPacket(SELF, const void *pData, int cbData, uint32 srcIP, uint16 srcPort)
{
	xlogf("%s(self = %p, pData = %p, cbData = %d, srcIP = %#x, srcPort = %d)\n", __func__, self, pData, cbData, srcIP, srcPort);
	return true;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_GetNextOutgoingPacket(SELF, void *pOut, int cbMaxOut, uint32 *pNetAdr, uint16 *pPort)
{
	xlogf("%s(self = %p, pOut = %p, cbMaxOut = %d, pNetAdr = %p, pPort = %p)\n", __func__, self, pOut, cbMaxOut, pNetAdr, pPort);
	return 0;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_EnableHeartbeats(SELF, bool bActive)
{
	xlogf("%s(self = %p, bActive = %d)\n", __func__, self, bActive);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_SetHeartbeatInterval(SELF, int iHeartbeatInterval)
{
	xlogf("%s(self = %p, iHeartbeatInterval = %d)\n", __func__, self, iHeartbeatInterval);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_ForceHeartbeat(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_AssociateWithClan(SELF, CSteamID steamIDClan)
{
	xlogf("%s(self = %p, steamIDClan = %llu)\n", __func__, self, steamIDClan.m_gameID);
	return 0;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamGameServer_ComputeNewPlayerCompatibility(SELF, CSteamID steamIDNewPlayer)
{
	xlogf("%s(self = %p, steamIDNewPlayer = %llu)\n", __func__, self, steamIDNewPlayer.m_gameID);
	return 0;
}