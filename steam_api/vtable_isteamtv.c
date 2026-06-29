#include "steam.h"

static void *vtable_ISteamTV001[] = {
    SteamAPI_ISteamTV_IsBroadcasting,
    SteamAPI_ISteamTV_AddBroadcastGameData,
    SteamAPI_ISteamTV_RemoveBroadcastGameData,
    SteamAPI_ISteamTV_AddTimelineMarker,
    SteamAPI_ISteamTV_RemoveTimelineMarker,
    SteamAPI_ISteamTV_AddRegion,
    SteamAPI_ISteamTV_RemoveRegion,
};

VtableEntry vtable_ISteamTV[] = {
    {1, vtable_ISteamTV001, sizeof(vtable_ISteamTV001), 0},
    {0, NULL, 0, 0},
};
