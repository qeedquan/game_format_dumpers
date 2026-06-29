#include "steam.h"

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_GetFavoriteGameCount(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_GetFavoriteGame(SELF, int iGame, AppId_t *pnAppID, uint32 *pnIP, uint16 *pnConnPort, uint16 *pnQueryPort, uint32 *punFlags, uint32 *pRTime32LastPlayedOnServer)
{
	xlogf("%s(self = %p, iGame = %d, pnAppID = %p, pnIP = %p, pnConnPort = %p, pnQueryPort = %p, punFlags = %p, pRTime32LastPlayedOnServer = %p)\n", __func__, self, iGame, pnAppID, pnIP, pnConnPort, pnQueryPort, punFlags, pRTime32LastPlayedOnServer);
	return true;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_AddFavoriteGame(SELF, AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags, uint32 rTime32LastPlayedOnServer)
{
	xlogf("%s(self = %p, nAppID = %d, nIP = %d, nConnPort = %d, nQueryPort = %d, unFlags = %d, rTime32LastPlayedOnServer = %x)\n", __func__, self, nAppID, nIP, nConnPort, nQueryPort, unFlags, rTime32LastPlayedOnServer);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_RemoveFavoriteGame(SELF, AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags)
{
	xlogf("%s(self = %p, nAppID = %d, nIP = %d, nConnPort = %d, nQueryPort = %d, unFlags = %d)\n", __func__, self, nAppID, nIP, nConnPort, nQueryPort, unFlags);
	return true;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_RequestLobbyList(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 1;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_AddRequestLobbyListStringFilter(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_AddRequestLobbyListNumericalFilter(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_AddRequestLobbyListNearValueFilter(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_AddRequestLobbyListFilterSlotsAvailable(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_AddRequestLobbyListDistanceFilter(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_AddRequestLobbyListResultCountFilter(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_AddRequestLobbyListCompatibleMembersFilter(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI CSteamID *S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_GetLobbyByIndex(SELF, int iLobby)
{
	xlogf("%s(self = %p, iLobby = %d)\n", __func__, self, iLobby);
	return NULL;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_CreateLobby(SELF, ELobbyType eLobbyType, int cMaxMembers)
{
	xlogf("%s(self = %p, eLobbyType = %d, cMaxMembers = %d)\n", __func__, self, eLobbyType, cMaxMembers);
	return 1;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_JoinLobby(SELF, CSteamID steamIDLobby)
{
	xlogf("%s(self = %p, steamIDLobby = %llu)\n", __func__, self, steamIDLobby.m_gameID);
	return 1;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_LeaveLobby(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_InviteUserToLobby(SELF, CSteamID steamIDLobby, CSteamID steamIDInvitee)
{
	xlogf("%s(self = %p, steamIDLobby = %llu, steamIDInvitee = %llu)\n", __func__, self, steamIDLobby.m_gameID, steamIDInvitee.m_gameID);
	return true;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_GetNumLobbyMembers(SELF, CSteamID steamIDLobby)
{
	xlogf("%s(self = %p, steamIDLobby = %llu)\n", __func__, self, steamIDLobby.m_gameID);
	return 0;
}

S_CLASSAPI CSteamID *S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_GetLobbyMemberByIndex(SELF, CSteamID steamIDLobby, int iMember)
{
	xlogf("%s(self = %p, steamIDLobby = %llu, iMember = %d)\n", __func__, self, steamIDLobby.m_gameID, iMember);
	return NULL;
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_GetLobbyData(SELF, CSteamID steamIDLobby, const char *pchKey)
{
	xlogf("%s(self = %p, steamIDLobby = %llu, pchKey = %s)\n", __func__, self, steamIDLobby.m_gameID, pchKey);
	return "";
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_SetLobbyData(SELF, CSteamID steamIDLobby, const char *pchKey, const char *pchValue)
{
	xlogf("%s(self = %p, steamIDLobby = %llu, pchKey = %s, pchValue = %s)\n", __func__, self, steamIDLobby.m_gameID, pchKey, pchValue);
	return true;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_GetLobbyDataCount(SELF, CSteamID steamIDLobby)
{
	xlogf("%s(self = %p, steamIDLobby = %llu)\n", __func__, self, steamIDLobby.m_gameID);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_GetLobbyDataByIndex(SELF, CSteamID steamIDLobby, int iLobbyData, char *pchKey, int cchKeyBufferSize, char *pchValue, int cchValueBufferSize)
{
	xlogf("%s(self = %p, steamIDLobby = %llu, iLobbyData = %d, pchKey = %s, cchKeyBufferSize = %d, pchValue = %s, cchValueBufferSize = %d)\n", __func__, self, steamIDLobby.m_gameID, iLobbyData, pchKey, cchKeyBufferSize, pchValue, cchValueBufferSize);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_DeleteLobbyData(SELF, CSteamID steamIDLobby, const char *pchKey)
{
	xlogf("%s(self = %p, steamIDLobby = %llu, pchKey = %s)\n", __func__, self, steamIDLobby.m_gameID, pchKey);
	return true;
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_GetLobbyMemberData(SELF, CSteamID steamIDLobby, CSteamID steamIDUser, const char *pchKey)
{
	xlogf("%s(self = %p, steamIDLobby = %llu, steamIDUser = %llu, pchKey = %s)\n", __func__, self, steamIDLobby.m_gameID, steamIDUser.m_gameID, pchKey);
	return "";
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_SetLobbyMemberData(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_SendLobbyChatMsg(SELF, CSteamID steamIDLobby, const void *pvMsgBody, int cubMsgBody)
{
	xlogf("%s(self = %p, steamIDLobby = %llu, pvMsgBody = %p, cubMsgBody = %d)\n", __func__, self, steamIDLobby.m_gameID, pvMsgBody, cubMsgBody);
	return true;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_GetLobbyChatEntry(SELF, CSteamID steamIDLobby, int iChatID, CSteamID *pSteamIDUser, void *pvData, int cubData, EChatEntryType *peChatEntryType)
{
	xlogf("%s(self = %p, steamIDLobby = %llu, iChatID = %d, pSteamIDUser = %p, pvData = %p, cubData = %d, peChatEntryType = %p)\n", __func__, self, steamIDLobby.m_gameID, iChatID, pSteamIDUser, pvData, cubData, peChatEntryType);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_RequestLobbyData(SELF, CSteamID steamIDLobby)
{
	xlogf("%s(self = %p, steamIDLobby = %llu)\n", __func__, self, steamIDLobby.m_gameID);
	return true;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_SetLobbyGameServer(SELF, CSteamID steamIDLobby, uint32 unGameServerIP, uint16 unGameServerPort, CSteamID steamIDGameServer)
{
	xlogf("%s(self = %p, steamIDLobby = %llu, unGameServerIP = %d, unGameServerPort = %d, steamIDGameServer = %llu)\n", __func__, self, steamIDLobby.m_gameID, unGameServerIP, unGameServerPort, steamIDGameServer.m_gameID);
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_GetLobbyGameServer(SELF, CSteamID steamIDLobby, uint32 *punGameServerIP, uint16 *punGameServerPort, CSteamID *psteamIDGameServer)
{
	xlogf("%s(self = %p, steamIDLobby = %llu, punGameServerIP = %p, punGameServerPort = %p, psteamIDGameServer = %p)\n", __func__, self, steamIDLobby.m_gameID, punGameServerIP, punGameServerPort, psteamIDGameServer);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_SetLobbyMemberLimit(SELF, CSteamID steamIDLobby, int cMaxMembers)
{
	xlogf("%s(self = %p, steamIDLobby = %llu, cMaxMembers = %d)\n", __func__, self, steamIDLobby.m_gameID, cMaxMembers);
	return true;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_GetLobbyMemberLimit(SELF, CSteamID steamIDLobby)
{
	xlogf("%s(self = %p, steamIDLobby = %llu)\n", __func__, self, steamIDLobby.m_gameID);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_SetLobbyType(SELF, CSteamID steamIDLobby, ELobbyType eLobbyType)
{
	xlogf("%s(self = %p, steamIDLobby = %llu, eLobbyType = %d)\n", __func__, self, steamIDLobby.m_gameID, eLobbyType);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_SetLobbyJoinable(SELF, CSteamID steamIDLobby, bool bLobbyJoinable)
{
	xlogf("%s(self = %p, steamIDLobby = %llu, bLobbyJoinable = %d)\n", __func__, self, steamIDLobby.m_gameID, bLobbyJoinable);
	return false;
}

S_CLASSAPI CSteamID *S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_GetLobbyOwner(SELF, CSteamID steamIDLobby)
{
	xlogf("%s(self = %p, steamIDLobby = %llu)\n", __func__, self, steamIDLobby.m_gameID);
	return NULL;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_SetLobbyOwner(SELF, CSteamID steamIDLobby, CSteamID steamIDNewOwner)
{
	xlogf("%s(self = %p, steamIDLobby = %llu, steamIDNewOwner = %llu)\n", __func__, self, steamIDLobby.m_gameID, steamIDNewOwner.m_gameID);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMatchmaking_SetLinkedLobby(SELF, CSteamID steamIDLobby, CSteamID steamIDLobbyDependent)
{
	xlogf("%s(self = %p, steamIDLobby = %llu, steamIDLobbyDependent = %llu)\n", __func__, self, steamIDLobby.m_gameID, steamIDLobbyDependent.m_gameID);
	return true;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamMatchmakingPingResponse_ServerFailedToRespond(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamMatchmakingPingResponse_ServerResponded(SELF, gameserveritem_t *server)
{
	xlogf("%s(self = %p, server = %p)\n", __func__, self, server);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamMatchmakingPlayersResponse_AddPlayerToList(SELF, const char *pchName, int nScore, float flTimePlayed)
{
	xlogf("%s(self = %p, pchName = %s, nScore = %d, flTimePlayed = %f)\n", __func__, self, pchName, nScore, flTimePlayed);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamMatchmakingPlayersResponse_PlayersFailedToRespond(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamMatchmakingPlayersResponse_PlayersRefreshComplete(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamMatchmakingRulesResponse_RulesResponded(SELF, const char *pchRule, const char *pchValue)
{
	xlogf("%s(self = %p, pchRule = %s, pchValue = %s)\n", __func__, self, pchRule, pchValue);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamMatchmakingRulesResponse_RulesFailedToRespond(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamMatchmakingRulesResponse_RulesRefreshComplete(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}
