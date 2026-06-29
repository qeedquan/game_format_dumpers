#include "steam.h"

#define vtable_ISteamScreenshots002 vtable_ISteamScreenshots003

static void *vtable_ISteamScreenshots003[] = {
    SteamAPI_ISteamScreenshots_WriteScreenshot,
    SteamAPI_ISteamScreenshots_AddScreenshotToLibrary,
    SteamAPI_ISteamScreenshots_TriggerScreenshot,
    SteamAPI_ISteamScreenshots_HookScreenshots,
    SteamAPI_ISteamScreenshots_SetLocation,
    SteamAPI_ISteamScreenshots_TagUser,
    SteamAPI_ISteamScreenshots_TagPublishedFile,
    SteamAPI_ISteamScreenshots_IsScreenshotsHooked,
    SteamAPI_ISteamScreenshots_AddVRScreenshotToLibrary,
};

VtableEntry vtable_ISteamScreenshot[] = {
    {2, vtable_ISteamScreenshots002, sizeof(vtable_ISteamScreenshots002), 0},
    {3, vtable_ISteamScreenshots003, sizeof(vtable_ISteamScreenshots003), 0},
    {0, NULL, 0, 0},
};
