#include "steam.h"

static void *vtable_ISteamParentalSettings001[] = {
    SteamAPI_ISteamParentalSettings_BIsParentalLockEnabled,
    SteamAPI_ISteamParentalSettings_BIsParentalLockLocked,
    SteamAPI_ISteamParentalSettings_BIsAppBlocked,
    SteamAPI_ISteamParentalSettings_BIsAppInBlockList,
    SteamAPI_ISteamParentalSettings_BIsFeatureBlocked,
    SteamAPI_ISteamParentalSettings_BIsFeatureInBlockList,
};

VtableEntry vtable_ISteamParentalSettings[] = {
    {1, vtable_ISteamParentalSettings001, sizeof(vtable_ISteamParentalSettings001), 0},
    {0, NULL, 0, 0},
};
