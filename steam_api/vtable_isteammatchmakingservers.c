#include "steam.h"

static void *vtable_ISteamMatchmakingServers002[] = {
    SteamAPI_ISteamMatchmakingServers_RequestInternetServerList,
    SteamAPI_ISteamMatchmakingServers_RequestLANServerList,
    SteamAPI_ISteamMatchmakingServers_RequestFriendsServerList,
    SteamAPI_ISteamMatchmakingServers_RequestFavoritesServerList,
    SteamAPI_ISteamMatchmakingServers_RequestHistoryServerList,
    SteamAPI_ISteamMatchmakingServers_RequestSpectatorServerList,
    SteamAPI_ISteamMatchmakingServers_ReleaseRequest,
    SteamAPI_ISteamMatchmakingServers_GetServerDetails,
    SteamAPI_ISteamMatchmakingServers_CancelQuery,
    SteamAPI_ISteamMatchmakingServers_RefreshQuery,
    SteamAPI_ISteamMatchmakingServers_IsRefreshing,
    SteamAPI_ISteamMatchmakingServers_GetServerCount,
    SteamAPI_ISteamMatchmakingServers_RefreshServer,
    SteamAPI_ISteamMatchmakingServers_PingServer,
    SteamAPI_ISteamMatchmakingServers_PlayerDetails,
    SteamAPI_ISteamMatchmakingServers_ServerRules,
    SteamAPI_ISteamMatchmakingServers_CancelServerQuery,
};

VtableEntry vtable_ISteamMatchmakingServers[] = {
    {2, vtable_ISteamMatchmakingServers002, sizeof(vtable_ISteamMatchmakingServers002), 0},
    {0, NULL, 0, 0},
};
