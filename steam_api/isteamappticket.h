#pragma once

#include "steamtypes.h"

typedef void ISteamAppTicket;

typedef struct CSteamAppTicket CSteamAppTicket;

struct CSteamAppTicket {
	CSteamBase base;
};

S_CLASSAPI uint32 S_CLASSCALLTYPE SteamAPI_ISteamAppTicket_GetAppOwnershipTicketData(SELF, uint32 nAppID, void *pvBuffer, uint32 cbBufferLength, uint32 *piAppId, uint32 *piSteamId, uint32 *piSignature, uint32 *pcbSignature);