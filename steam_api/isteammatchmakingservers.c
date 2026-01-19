#include "steam.h"

S_CLASSAPI HServerListRequest S_CLASSCALLTYPE
SteamAPI_ISteamMatchmakingServers_RequestInternetServerList(SELF, AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse)
{
	xlogf("%s(self = %p, iApp = %d, ppchFilters = %p, nFilters = %d, pRequestServersResponse = %p)\n", __func__, self, iApp, ppchFilters, nFilters, pRequestServersResponse);
	return NULL;
}

S_CLASSAPI HServerListRequest S_CLASSCALLTYPE
SteamAPI_ISteamMatchmakingServers_RequestLANServerList(SELF, AppId_t iApp, ISteamMatchmakingServerListResponse *pRequestServersResponse)
{
	xlogf("%s(self = %p, iApp = %d, pRequestServersResponse = %p)\n", __func__, self, iApp, pRequestServersResponse);
	return NULL;
}

S_CLASSAPI HServerListRequest S_CLASSCALLTYPE
SteamAPI_ISteamMatchmakingServers_RequestFriendsServerList(SELF, AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse)
{
	xlogf("%s(self = %p, iApp = %d, ppchFilters = %p, nFilters = %d, pRequestServersResponse = %p)\n", __func__, self, iApp, ppchFilters, nFilters, pRequestServersResponse);
	return NULL;
}

S_CLASSAPI HServerListRequest S_CLASSCALLTYPE
SteamAPI_ISteamMatchmakingServers_RequestFavoritesServerList(SELF, AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse)
{
	xlogf("%s(self = %p, iApp = %d, ppchFilters = %p, nFilters = %d, pRequestServersResponse = %p)\n", __func__, self, iApp, ppchFilters, nFilters, pRequestServersResponse);
	return 0;
}

S_CLASSAPI HServerListRequest S_CLASSCALLTYPE
SteamAPI_ISteamMatchmakingServers_RequestHistoryServerList(SELF, AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse)
{
	xlogf("%s(self = %p, iApp = %d, ppchFilters = %p, nFilters = %d, pRequestServersResponse = %p)\n", __func__, self, iApp, ppchFilters, nFilters, pRequestServersResponse);
	return 0;
}

S_CLASSAPI HServerListRequest S_CLASSCALLTYPE
SteamAPI_ISteamMatchmakingServers_RequestSpectatorServerList(SELF, AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse)
{
	xlogf("%s(self = %p, iApp = %d, ppchFilters = %p, nFilters = %d, pRequestServersResponse = %p)\n", __func__, self, iApp, ppchFilters, nFilters, pRequestServersResponse);
	return NULL;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamMatchmakingServers_ReleaseRequest(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI gameserveritem_t *S_CLASSCALLTYPE
SteamAPI_ISteamMatchmakingServers_GetServerDetails(SELF, HServerListRequest hRequest, int iServer)
{
	xlogf("%s(self = %p, hRequest = %p, iServer = %d)\n", __func__, self, hRequest, iServer);
	return NULL;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamMatchmakingServers_CancelQuery(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamMatchmakingServers_RefreshQuery(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMatchmakingServers_IsRefreshing(SELF, HServerListRequest hRequest)
{
	xlogf("%s(self = %p, hRequest = %p)\n", __func__, self, hRequest);
	return true;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamMatchmakingServers_GetServerCount(SELF, HServerListRequest hRequest)
{
	xlogf("%s(self = %p, hRequest = %p)\n", __func__, self, hRequest);
	return 0;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamMatchmakingServers_RefreshServer(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI HServerQuery S_CLASSCALLTYPE
SteamAPI_ISteamMatchmakingServers_PingServer(SELF, uint32 unIP, uint16 usPort, ISteamMatchmakingPingResponse *pRequestServersResponse)
{
	xlogf("%s(self = %p, unIP = %x, usPort = %x, pRequestServersResponse = %p)\n", __func__, self, unIP, usPort, pRequestServersResponse);
	return 0;
}

S_CLASSAPI HServerQuery S_CLASSCALLTYPE
SteamAPI_ISteamMatchmakingServers_PlayerDetails(SELF, uint32 unIP, uint16 usPort, ISteamMatchmakingPlayersResponse *pRequestServersResponse)
{
	xlogf("%s(self = %p, unIP = %x, usPort = %x, pRequestServersResponse = %p)\n", __func__, self, unIP, usPort, pRequestServersResponse);
	return 0;
}

S_CLASSAPI HServerQuery S_CLASSCALLTYPE
SteamAPI_ISteamMatchmakingServers_ServerRules(SELF, uint32 unIP, uint16 usPort, ISteamMatchmakingRulesResponse *pRequestServersResponse)
{
	xlogf("%s(self = %p, unIP = %x, usPort = %x, pRequestServersResponse = %p)\n", __func__, self, unIP, usPort, pRequestServersResponse);
	return 0;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamMatchmakingServers_CancelServerQuery(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamMatchmakingServerListResponse_RefreshComplete(SELF, HServerListRequest hRequest, EMatchMakingServerResponse response)
{
	xlogf("%s(self = %p, hRequest = %p, response = %d)\n", __func__, self, hRequest, response);
}

S_CLASSAPI void
SteamAPI_ISteamMatchmakingServerListResponse_ServerResponded(SELF, HServerListRequest hRequest, int iServer)
{
	xlogf("%s(self = %p, hRequest = %p, iServer = %d)\n", __func__, self, hRequest, iServer);
}

S_CLASSAPI void
SteamAPI_ISteamMatchmakingServerListResponse_ServerFailedToRespond(SELF, HServerListRequest hRequest, int iServer)
{
	xlogf("%s(self = %p, hRequest = %p, iServer = %d)\n", __func__, self, hRequest, iServer);
}