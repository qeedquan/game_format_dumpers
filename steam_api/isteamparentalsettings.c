#include "steam.h"

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamParentalSettings_BIsParentalLockEnabled(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamParentalSettings_BIsParentalLockLocked(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamParentalSettings_BIsAppBlocked(SELF, AppId_t nAppID)
{
	xlogf("%s(self = %p, nAppID = %d)\n", __func__, self, nAppID);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamParentalSettings_BIsAppInBlockList(SELF, AppId_t nAppID)
{
	xlogf("%s(self = %p, nAppID = %d)\n", __func__, self, nAppID);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamParentalSettings_BIsFeatureBlocked(SELF, EParentalFeature eFeature)
{
	xlogf("%s(self = %p, eFeature = %d)\n", __func__, self, eFeature);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamParentalSettings_BIsFeatureInBlockList(SELF, EParentalFeature eFeature)
{
	xlogf("%s(self = %p, eFeature = %d)\n", __func__, self, eFeature);
	return false;
}
