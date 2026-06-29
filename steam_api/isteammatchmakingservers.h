#pragma once

#include "steamtypes.h"

typedef void ISteamMatchmakingServerListResponse;
typedef void ISteamMatchmakingPingResponse;
typedef void ISteamMatchmakingPlayersResponse;
typedef void ISteamMatchmakingRulesResponse;

typedef int HServerQuery;

/// Store key/value pair used in matchmaking queries.
///
/// Actually, the name Key/Value is a bit misleading.  The "key" is better
/// understood as "filter operation code" and the "value" is the operand to this
/// filter operation.  The meaning of the operand depends upon the filter.
typedef struct {
	char m_szKey[256];
	char m_szValue[256];
} MatchMakingKeyValuePair_t;

//
// Max size (in bytes of UTF-8 data, not in characters) of server fields, including null terminator.
// WARNING: These cannot be changed easily, without breaking clients using old interfaces.
//
enum {
	k_cbMaxGameServerGameDir = 32,
	k_cbMaxGameServerMapName = 32,
	k_cbMaxGameServerGameDescription = 64,
	k_cbMaxGameServerName = 64,
	k_cbMaxGameServerTags = 128,
	k_cbMaxGameServerGameData = 2048
};

typedef enum EMatchMakingServerResponse {
	eServerResponded = 0,
	eServerFailedToRespond,
	eNoServersListedOnMasterServer // for the Internet query type, returned in response callback if no servers of this type match
} EMatchMakingServerResponse;

typedef struct {
	uint16 m_usConnectionPort; // (in HOST byte order)
	uint16 m_usQueryPort;
	uint32 m_unIP;
} servernetadr_t;

typedef struct {
	servernetadr_t m_NetAdr;                                    ///< IP/Query Port/Connection Port for this server
	int m_nPing;                                                ///< current ping time in milliseconds
	bool m_bHadSuccessfulResponse;                              ///< server has responded successfully in the past
	bool m_bDoNotRefresh;                                       ///< server is marked as not responding and should no longer be refreshed
	char m_szGameDir[k_cbMaxGameServerGameDir];                 ///< current game directory
	char m_szMap[k_cbMaxGameServerMapName];                     ///< current map
	char m_szGameDescription[k_cbMaxGameServerGameDescription]; ///< game description
	uint32 m_nAppID;                                            ///< Steam App ID of this server
	int m_nPlayers;                                             ///< total number of players currently on the server.  INCLUDES BOTS!!
	int m_nMaxPlayers;                                          ///< Maximum players that can join this server
	int m_nBotPlayers;                                          ///< Number of bots (i.e simulated players) on this server
	bool m_bPassword;                                           ///< true if this server needs a password to join
	bool m_bSecure;                                             ///< Is this server protected by VAC
	uint32 m_ulTimeLastPlayed;                                  ///< time (in unix time) when this server was last played on (for favorite/history servers)
	int m_nServerVersion;                                       ///< server version as reported to Steam

	/// Game server name
	char m_szServerName[k_cbMaxGameServerName];

	// For data added after SteamMatchMaking001 add it here

	/// the tags this server exposes
	char m_szGameTags[k_cbMaxGameServerTags];

	/// steamID of the game server - invalid if it's doesn't have one (old server, or not connected to Steam)
	CSteamID m_steamID;
} gameserveritem_t;

typedef void *HServerListRequest;

typedef void ISteamMatchmakingServers;

typedef struct CSteamMatchmakingServers CSteamMatchmakingServers;

struct CSteamMatchmakingServers {
	CSteamBase base;
};

S_CLASSAPI HServerListRequest S_CLASSCALLTYPE SteamAPI_ISteamMatchmakingServers_RequestInternetServerList(SELF, AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse);
S_CLASSAPI HServerListRequest S_CLASSCALLTYPE SteamAPI_ISteamMatchmakingServers_RequestLANServerList(SELF, AppId_t iApp, ISteamMatchmakingServerListResponse *pRequestServersResponse);
S_CLASSAPI HServerListRequest S_CLASSCALLTYPE SteamAPI_ISteamMatchmakingServers_RequestFriendsServerList(SELF, AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse);
S_CLASSAPI HServerListRequest S_CLASSCALLTYPE SteamAPI_ISteamMatchmakingServers_RequestFavoritesServerList(SELF, AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse);
S_CLASSAPI HServerListRequest S_CLASSCALLTYPE SteamAPI_ISteamMatchmakingServers_RequestHistoryServerList(SELF, AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse);
S_CLASSAPI HServerListRequest S_CLASSCALLTYPE SteamAPI_ISteamMatchmakingServers_RequestSpectatorServerList(SELF, AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamMatchmakingServers_ReleaseRequest(SELF);
S_CLASSAPI gameserveritem_t *S_CLASSCALLTYPE SteamAPI_ISteamMatchmakingServers_GetServerDetails(SELF, HServerListRequest hRequest, int iServer);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamMatchmakingServers_CancelQuery(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamMatchmakingServers_RefreshQuery(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMatchmakingServers_IsRefreshing(SELF, HServerListRequest hRequest);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamMatchmakingServers_GetServerCount(SELF, HServerListRequest hRequest);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamMatchmakingServers_RefreshServer(SELF);
S_CLASSAPI HServerQuery S_CLASSCALLTYPE SteamAPI_ISteamMatchmakingServers_PingServer(SELF, uint32 unIP, uint16 usPort, ISteamMatchmakingPingResponse *pRequestServersResponse);
S_CLASSAPI HServerQuery S_CLASSCALLTYPE SteamAPI_ISteamMatchmakingServers_PlayerDetails(SELF, uint32 unIP, uint16 usPort, ISteamMatchmakingPlayersResponse *pRequestServersResponse);
S_CLASSAPI HServerQuery S_CLASSCALLTYPE SteamAPI_ISteamMatchmakingServers_ServerRules(SELF, uint32 unIP, uint16 usPort, ISteamMatchmakingRulesResponse *pRequestServersResponse);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamMatchmakingServers_CancelServerQuery(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamMatchmakingServerListResponse_RefreshComplete(SELF, HServerListRequest hRequest, EMatchMakingServerResponse response);
S_CLASSAPI void SteamAPI_ISteamMatchmakingServerListResponse_ServerResponded(SELF, HServerListRequest hRequest, int iServer);
S_CLASSAPI void SteamAPI_ISteamMatchmakingServerListResponse_ServerFailedToRespond(SELF, HServerListRequest hRequest, int iServer);