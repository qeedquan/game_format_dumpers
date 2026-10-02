#include "steam.h"

static void *vtable_ISteamAppTicket001[] = {
    SteamAPI_ISteamAppTicket_GetAppOwnershipTicketData,
};

VtableEntry vtable_ISteamAppTicket[] = {
    {1, vtable_ISteamAppTicket001, sizeof(vtable_ISteamAppTicket001), 0},
    {0, NULL, 0, 0},
};