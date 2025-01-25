#pragma once

enum {
	VTABLE_HAS_PRIVATE = 1,
};

typedef struct {
	int version;
	void **table;
	size_t tablesize;
	int flags;
} VtableEntry;

typedef struct {
	char prefix[64];
	VtableEntry *entries;
	void *ctx;
	CSteamBase *base;
} Vtable;

extern VtableEntry vtable_ISteamMusic[2];
extern VtableEntry vtable_ISteamInput[3];
extern VtableEntry vtable_ISteamRemoteStorage[6];
extern VtableEntry vtable_ISteamAppTicket[2];
extern VtableEntry vtable_ISteamScreenshot[3];
extern VtableEntry vtable_ISteamUtils[6];
extern VtableEntry vtable_ISteamUser[6];
extern VtableEntry vtable_ISteamUserStats[3];
extern VtableEntry vtable_ISteamInventory[4];
extern VtableEntry vtable_ISteamController[4];
extern VtableEntry vtable_ISteamApps[5];
extern VtableEntry vtable_ISteamClient[4];
extern VtableEntry vtable_ISteamAppList[2];
extern VtableEntry vtable_ISteamParentalSettings[2];
extern VtableEntry vtable_ISteamNetworking[3];
extern VtableEntry vtable_ISteamFriends[6];
extern VtableEntry vtable_ISteamUnifiedMessages[2];
extern VtableEntry vtable_ISteamUGC[6];
extern VtableEntry vtable_ISteamHTMLSurface[5];
extern VtableEntry vtable_ISteamMusicRemote[2];
extern VtableEntry vtable_ISteamMatchmakingServers[2];
extern VtableEntry vtable_ISteamHTTP[3];
extern VtableEntry vtable_ISteamMatchmaking[2];
extern VtableEntry vtable_ISteamTV[2];
