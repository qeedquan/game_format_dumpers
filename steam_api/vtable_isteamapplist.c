#include "steam.h"

static void *vtable_ISteamAppList001[] = {
    SteamAPI_ISteamAppList_GetNumInstalledApps,
    SteamAPI_ISteamAppList_GetInstalledApps,
    SteamAPI_ISteamAppList_GetAppName,
    SteamAPI_ISteamAppList_GetAppInstallDir,
    SteamAPI_ISteamAppList_GetAppBuildId,
};

VtableEntry vtable_ISteamAppList[] = {
    {1, vtable_ISteamAppList001, sizeof(vtable_ISteamAppList001), 0},
    {0, NULL, 0, 0},
};
