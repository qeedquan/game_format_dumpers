#include "steam.h"

S_CLASSAPI uint32 S_CLASSCALLTYPE
SteamAPI_ISteamAppTicket_GetAppOwnershipTicketData(SELF, uint32 nAppID, void *pvBuffer, uint32 cbBufferLength, uint32 *piAppId, uint32 *piSteamId, uint32 *piSignature, uint32 *pcbSignature)
{
	uint8 sig[] = {0x7, 0x7, 0x7, 0x7};
	uint8 *ptr;
	size_t off;

	xlogf("%s(self = %p, nAppID = %d, pvBuffer = %p, cbBufferLength = %u, piAppId = %p, piSteamId = %p, piSignature = %p, pcbSignature = %p)\n",
	      __func__, self, nAppID, pvBuffer, cbBufferLength, piAppId, piSteamId, piSignature, pcbSignature);

	if (cbBufferLength < 32)
		return 0;

	ptr = pvBuffer;
	off = 4;
	if (piAppId) {
		memmove(ptr + off, &nAppID, sizeof(nAppID));
		*piAppId = off;
	}
	off += sizeof(nAppID);

	if (piSteamId) {
		memmove(ptr + off, &ctx.steamID, sizeof(ctx.steamID));
		*piSteamId = off;
	}
	off += sizeof(ctx.steamID);

	if (piSignature) {
		memmove(ptr + off, sig, sizeof(sig));
		*piSignature = off;
	}
	off += sizeof(sig);

	if (pcbSignature) {
		memmove(ptr + off, sig, sizeof(sig));
		*pcbSignature = off;
	}
	off += sizeof(sig);

	return cbBufferLength;
}