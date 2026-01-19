#pragma once

#include "steamtypes.h"

typedef struct CCallbackBase CCallbackBase;

enum {
	k_ECallbackFlagsRegistered = 0x01,
	k_ECallbackFlagsGameServer = 0x02
};

struct CCallbackBase {
	uint8 m_nCallbackFlags;
	int m_iCallback;
};

typedef struct SteamInternalContext SteamInternalContext;
typedef struct CSteamAPIContext CSteamAPIContext;
typedef struct CSteamGameServerAPIContext CSteamGameServerAPIContext;

struct CSteamAPIContext {
	ISteamClient *steamClient;
	ISteamUser *steamUser;
	ISteamFriends *steamFriends;
	ISteamUtils *steamUtils;
	ISteamMatchmaking *steamMatchmaking;
	ISteamGameSearch *steamGameSearch;
	ISteamUserStats *steamUserStats;
	ISteamApps *steamApps;
	ISteamMatchmakingServers *steamMatchmakingServers;
	ISteamNetworking *steamNetworking;
	ISteamRemoteStorage *steamRemoteStorage;
	ISteamScreenshots *steamScreenshots;
	ISteamHTTP *steamHTTP;
	ISteamController *m_pController;
	ISteamUGC *steamUGC;
	ISteamAppList *steamAppList;
	ISteamMusic *steamMusic;
	ISteamMusicRemote *steamMusicRemote;
	ISteamHTMLSurface *steamHTMLSurface;
	ISteamInventory *steamInventory;
	ISteamVideo *steamVideo;
	ISteamTV *steamTV;
	ISteamParentalSettings *steamParentalSettings;
	ISteamInput *steamInput;
};

struct CSteamGameServerAPIContext {
	ISteamClient *steamClient;
	ISteamGameServer *steamGameServer;
	ISteamUtils *steamGameServerUtils;
	ISteamNetworking *steamGameServerNetworking;
	ISteamGameServerStats *steamGameServerStats;
	ISteamHTTP *steamHTTP;
	ISteamInventory *steamInventory;
	ISteamUGC *steamUGC;
	ISteamApps *steamApps;
};

struct SteamInternalContext {
	void (*init)(void *);
	uintp iref;
	CSteamAPIContext ctx;
};

typedef void (*PFNPreMinidumpCallback)(void *context);

void *createInterface(const char *name);
