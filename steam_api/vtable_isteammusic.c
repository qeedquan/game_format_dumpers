#include "steam.h"

static void *vtable_ISteamMusic001[] = {
    SteamAPI_ISteamMusic_BIsEnabled,
    SteamAPI_ISteamMusic_BIsPlaying,
    SteamAPI_ISteamMusic_GetPlaybackStatus,
    SteamAPI_ISteamMusic_Play,
    SteamAPI_ISteamMusic_Pause,
    SteamAPI_ISteamMusic_PlayPrevious,
    SteamAPI_ISteamMusic_PlayNext,
    SteamAPI_ISteamMusic_SetVolume,
    SteamAPI_ISteamMusic_GetVolume,
};

VtableEntry vtable_ISteamMusic[] = {
    {1, vtable_ISteamMusic001, sizeof(vtable_ISteamMusic001), 0},
    {0, NULL, 0, 0},
};