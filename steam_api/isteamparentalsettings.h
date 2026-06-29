#pragma once

#include "steamtypes.h"

typedef void ISteamParentalSettings;

typedef struct CSteamParentalSettings CSteamParentalSettings;

struct CSteamParentalSettings {
	CSteamBase base;
};

typedef enum {
	k_EFeatureInvalid = 0,
	k_EFeatureStore = 1,
	k_EFeatureCommunity = 2,
	k_EFeatureProfile = 3,
	k_EFeatureFriends = 4,
	k_EFeatureNews = 5,
	k_EFeatureTrading = 6,
	k_EFeatureSettings = 7,
	k_EFeatureConsole = 8,
	k_EFeatureBrowser = 9,
	k_EFeatureParentalSetup = 10,
	k_EFeatureLibrary = 11,
	k_EFeatureTest = 12,
	k_EFeatureMax
} EParentalFeature;

enum { k_iCallback = k_ISteamParentalSettingsCallbacks + 1 };

S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamParentalSettings_BIsParentalLockEnabled(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamParentalSettings_BIsParentalLockLocked(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamParentalSettings_BIsAppBlocked(SELF, AppId_t nAppID);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamParentalSettings_BIsAppInBlockList(SELF, AppId_t nAppID);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamParentalSettings_BIsFeatureBlocked(SELF, EParentalFeature eFeature);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamParentalSettings_BIsFeatureInBlockList(SELF, EParentalFeature eFeature);
