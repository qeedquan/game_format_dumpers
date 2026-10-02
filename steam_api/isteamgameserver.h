#pragma once

typedef void ISteamGameServer;

typedef struct CSteamGameServer CSteamGameServer;

struct CSteamGameServer {
	CSteamBase base;
};

S_API uint64 S_CALLTYPE SteamGameServer_GetSteamID(void);
S_API HSteamPipe S_CALLTYPE SteamGameServer_GetHSteamPipe(void);
S_API bool S_CALLTYPE SteamGameServer_BSecure(void);
S_API bool S_CALLTYPE SteamGameServer_BSecure(void);
S_API void S_CALLTYPE SteamGameServer_RunCallbacks(void);
S_API void S_CALLTYPE SteamGameServer_Shutdown(void);
S_API bool S_CALLTYPE SteamGameServer_Init(void);
S_API bool S_CALLTYPE SteamGameServer_InitSafe(void);
S_API ISteamUtils *S_CALLTYPE SteamGameServerUtils(void);
S_API ISteamInventory *S_CALLTYPE SteamGameServerInventory(void);
S_API ISteamInventory *S_CALLTYPE SteamGameServerStats(void);
S_API ISteamUGC *S_CALLTYPE SteamGameServerUGC(void);
S_API ISteamNetworking *S_CALLTYPE SteamGameServerNetworking(void);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamGameServer_InitGameServer(SELF, uint32 unIP, uint16 usGamePort, uint16 usQueryPort, uint32 unFlags, AppId_t nGameAppId, const char *pchVersionString);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamGameServer_SetProduct(SELF, const char *pszProduct);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamGameServer_SetGameDescription(SELF, const char *pszGameDescription);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamGameServer_SetModDir(SELF, const char *pszModDir);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamGameServer_SetDedicatedServer(SELF, bool bDedicated);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamGameServer_LogOn(SELF, const char *pszToken);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamGameServer_LogOnAnonymous(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamGameServer_LogOff(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamGameServer_BLoggedOn(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamGameServer_BSecure(SELF);
S_CLASSAPI uint64 S_CLASSCALLTYPE SteamAPI_ISteamGameServer_GetSteamID(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamGameServer_WasRestartRequested(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamGameServer_SetMaxPlayerCount(SELF, int cPlayersMax);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamGameServer_SetBotPlayerCount(SELF, int cBotplayers);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamGameServer_SetServerName(SELF, const char *pszServerName);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamGameServer_SetMapName(SELF, const char *pszMapName);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamGameServer_SetPasswordProtected(SELF, bool bPasswordProtected);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamGameServer_SetSpectatorPort(SELF, uint16 unSpectatorPort);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamGameServer_SetSpectatorServerName(SELF, const char *pszSpectatorServerName);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamGameServer_ClearAllKeyValues(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamGameServer_SetKeyValue(SELF, const char *pKey, const char *pValue);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamGameServer_SetGameTags(SELF, const char *pchGameTags);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamGameServer_SetGameData(SELF, const char *pchGameData);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamGameServer_SetRegion(SELF, const char *pszRegion);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamGameServer_SendUserConnectAndAuthenticate(SELF, uint32 unIPClient, const void *pvAuthBlob, uint32 cubAuthBlobSize, CSteamID *pSteamIDUser);
S_CLASSAPI uint64 S_CLASSCALLTYPE SteamAPI_ISteamGameServer_CreateUnauthenticatedUserConnection(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamGameServer_SendUserDisconnect(SELF, CSteamID steamIDUser);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamGameServer_BUpdateUserData(SELF, CSteamID steamIDUser, const char *pchPlayerName, uint32 uScore);
S_CLASSAPI HAuthTicket S_CLASSCALLTYPE SteamAPI_ISteamGameServer_GetAuthSessionTicket(SELF, void *pTicket, int cbMaxTicket, uint32 *pcbTicket);
S_CLASSAPI EBeginAuthSessionResult S_CLASSCALLTYPE SteamAPI_ISteamGameServer_BeginAuthSession(SELF, const void *pAuthTicket, int cbAuthTicket, CSteamID steamID);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamGameServer_EndAuthSession(SELF, CSteamID steamID);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamGameServer_CancelAuthTicket(SELF, HAuthTicket hAuthTicket);
S_CLASSAPI EUserHasLicenseForAppResult S_CLASSCALLTYPE SteamAPI_ISteamGameServer_UserHasLicenseForApp(SELF, CSteamID steamID, AppId_t appID);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamGameServer_RequestUserGroupStatus(SELF, CSteamID steamIDUser, CSteamID steamIDGroup);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamGameServer_GetGameplayStats(SELF);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamGameServer_GetServerReputation(SELF);
S_CLASSAPI uint32 S_CLASSCALLTYPE SteamAPI_ISteamGameServer_GetPublicIP(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamGameServer_HandleIncomingPacket(SELF, const void *pData, int cbData, uint32 srcIP, uint16 srcPort);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamGameServer_GetNextOutgoingPacket(SELF, void *pOut, int cbMaxOut, uint32 *pNetAdr, uint16 *pPort);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamGameServer_EnableHeartbeats(SELF, bool bActive);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamGameServer_SetHeartbeatInterval(SELF, int iHeartbeatInterval);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamGameServer_ForceHeartbeat(SELF);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamGameServer_AssociateWithClan(SELF, CSteamID steamIDClan);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamGameServer_ComputeNewPlayerCompatibility(SELF, CSteamID steamIDNewPlayer);