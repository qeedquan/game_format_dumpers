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

struct SteamInternalContext {
	void (*init)(void *userdata);
	uintp iref;
	void *userdata;
};

typedef void (*PFNPreMinidumpCallback)(void *context);
