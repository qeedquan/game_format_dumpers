#pragma once

// lobby type description
typedef enum {
	k_ELobbyTypePrivate = 0,     // only way to join the lobby is to invite to someone else
	k_ELobbyTypeFriendsOnly = 1, // shows for friends or invitees, but not in lobby list
	k_ELobbyTypePublic = 2,      // visible for friends and in lobby list
	k_ELobbyTypeInvisible = 3,   // returned by search, but not visible to other friends
	                             //    useful if you want a user in two lobbies, for example matching groups together
	                             //	  a user can be in only one regular lobby, and up to two invisible lobbies
} ELobbyType;

typedef enum {
	k_ESteamPartyBeaconLocationType_Invalid = 0,
	k_ESteamPartyBeaconLocationType_ChatGroup = 1,

	k_ESteamPartyBeaconLocationType_Max,
} ESteamPartyBeaconLocationType;

typedef struct {
	ESteamPartyBeaconLocationType m_eType;
	uint64 m_ulLocationID;
} SteamPartyBeaconLocation_t;

typedef enum {
	k_ESteamPartyBeaconLocationDataInvalid = 0,
	k_ESteamPartyBeaconLocationDataName = 1,
	k_ESteamPartyBeaconLocationDataIconURLSmall = 2,
	k_ESteamPartyBeaconLocationDataIconURLMedium = 3,
	k_ESteamPartyBeaconLocationDataIconURLLarge = 4,
} ESteamPartyBeaconLocationData;

typedef void ISteamGameSearch;
typedef void ISteamParties;
typedef void ISteamMatchmaking;

typedef struct CSteamGameSearch CSteamGameSearch;
typedef struct CSteamParties CSteamParties;
typedef struct CSteamMatchmaking CSteamMatchmaking;

struct CSteamGameSearch {
	CSteamBase base;
};

struct CSteamParties {
	CSteamBase base;
};

struct CSteamMatchmaking {
	CSteamBase base;
};

S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_GetFavoriteGameCount(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_GetFavoriteGame(SELF, int iGame, AppId_t *pnAppID, uint32 *pnIP, uint16 *pnConnPort, uint16 *pnQueryPort, uint32 *punFlags, uint32 *pRTime32LastPlayedOnServer);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_AddFavoriteGame(SELF, AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags, uint32 rTime32LastPlayedOnServer);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_RemoveFavoriteGame(SELF, AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_RequestLobbyList(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_AddRequestLobbyListStringFilter(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_AddRequestLobbyListNumericalFilter(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_AddRequestLobbyListNearValueFilter(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_AddRequestLobbyListFilterSlotsAvailable(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_AddRequestLobbyListDistanceFilter(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_AddRequestLobbyListResultCountFilter(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_AddRequestLobbyListCompatibleMembersFilter(SELF);
S_CLASSAPI CSteamID *S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_GetLobbyByIndex(SELF, int iLobby);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_CreateLobby(SELF, ELobbyType eLobbyType, int cMaxMembers);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_JoinLobby(SELF, CSteamID steamIDLobby);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_LeaveLobby(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_InviteUserToLobby(SELF, CSteamID steamIDLobby, CSteamID steamIDInvitee);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_GetNumLobbyMembers(SELF, CSteamID steamIDLobby);
S_CLASSAPI CSteamID *S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_GetLobbyMemberByIndex(SELF, CSteamID steamIDLobby, int iMember);
S_CLASSAPI const char *S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_GetLobbyData(SELF, CSteamID steamIDLobby, const char *pchKey);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_SetLobbyData(SELF, CSteamID steamIDLobby, const char *pchKey, const char *pchValue);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_GetLobbyDataCount(SELF, CSteamID steamIDLobby);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_GetLobbyDataByIndex(SELF, CSteamID steamIDLobby, int iLobbyData, char *pchKey, int cchKeyBufferSize, char *pchValue, int cchValueBufferSize);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_DeleteLobbyData(SELF, CSteamID steamIDLobby, const char *pchKey);
S_CLASSAPI const char *S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_GetLobbyMemberData(SELF, CSteamID steamIDLobby, CSteamID steamIDUser, const char *pchKey);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_SetLobbyMemberData(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_SendLobbyChatMsg(SELF, CSteamID steamIDLobby, const void *pvMsgBody, int cubMsgBody);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_GetLobbyChatEntry(SELF, CSteamID steamIDLobby, int iChatID, CSteamID *pSteamIDUser, void *pvData, int cubData, EChatEntryType *peChatEntryType);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_RequestLobbyData(SELF, CSteamID steamIDLobby);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_SetLobbyGameServer(SELF, CSteamID steamIDLobby, uint32 unGameServerIP, uint16 unGameServerPort, CSteamID steamIDGameServer);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_GetLobbyGameServer(SELF, CSteamID steamIDLobby, uint32 *punGameServerIP, uint16 *punGameServerPort, CSteamID *psteamIDGameServer);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_SetLobbyMemberLimit(SELF, CSteamID steamIDLobby, int cMaxMembers);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_GetLobbyMemberLimit(SELF, CSteamID steamIDLobby);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_SetLobbyType(SELF, CSteamID steamIDLobby, ELobbyType eLobbyType);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_SetLobbyJoinable(SELF, CSteamID steamIDLobby, bool bLobbyJoinable);
S_CLASSAPI CSteamID *S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_GetLobbyOwner(SELF, CSteamID steamIDLobby);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_SetLobbyOwner(SELF, CSteamID steamIDLobby, CSteamID steamIDNewOwner);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMatchmaking_SetLinkedLobby(SELF, CSteamID steamIDLobby, CSteamID steamIDLobbyDependent);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamMatchmakingPingResponse_ServerFailedToRespond(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamMatchmakingPingResponse_ServerResponded(SELF, gameserveritem_t *server);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamMatchmakingPlayersResponse_AddPlayerToList(SELF, const char *pchName, int nScore, float flTimePlayed);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamMatchmakingPlayersResponse_PlayersFailedToRespond(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamMatchmakingPlayersResponse_PlayersRefreshComplete(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamMatchmakingRulesResponse_RulesResponded(SELF, const char *pchRule, const char *pchValue);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamMatchmakingRulesResponse_RulesFailedToRespond(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamMatchmakingRulesResponse_RulesRefreshComplete(SELF);
