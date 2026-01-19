#include "steam.h"

static void *vtable_ISteamUnifiedMessages001[] = {
    SteamAPI_ISteamUnifiedMessages_SendMethod,
    SteamAPI_ISteamUnifiedMessages_GetMethodResponseInfo,
    SteamAPI_ISteamUnifiedMessages_GetMethodResponseData,
    SteamAPI_ISteamUnifiedMessages_ReleaseMethod,
    SteamAPI_ISteamUnifiedMessages_SendNotification,
};

VtableEntry vtable_ISteamUnifiedMessages[] = {
    {1, vtable_ISteamUnifiedMessages001, sizeof(vtable_ISteamUnifiedMessages001), 0},
    {0, NULL, 0, 0},
};
