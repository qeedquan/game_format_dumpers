#include "steam.h"

S_CLASSAPI HSteamUser S_CLASSCALLTYPE
SteamAPI_ISteamUser_GetHSteamUser(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return ctx.steamUser;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUser_BLoggedOn(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return true;
}

S_CLASSAPI
R_STRUCT_TYPE(CSteamID)
S_CLASSCALLTYPE
SteamAPI_ISteamUser_GetSteamID(SELF)
{
	xlogf("%s(self = %p) -> %llu\n", __func__, self, ctx.steamID.m_gameID);
	return R_STRUCT_RET(ctx.steamID);
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamUser_InitiateGameConnection(SELF, void *pAuthBlob, int cbMaxAuthBlob, CSteamID steamIDGameServer, uint32 unIPServer, uint16 usPortServer, bool bSecure)
{
	xlogf("%s(self = %p, pAuthBlob = %p, cbMaxAuthBlob = %d, steamIDGameServer = %llu, unIPServer = %x usPortServer = %x, bSecure = %d)\n", __func__, self, pAuthBlob, cbMaxAuthBlob, steamIDGameServer.m_gameID, unIPServer, usPortServer, bSecure);
	return 0;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamUser_TerminateGameConnection(SELF, uint32 unIPServer, uint16 usPortServer)
{
	xlogf("%s(self = %p, unIPServer = %x, usPortServer = %x)\n", __func__, self, unIPServer, usPortServer);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamUser_TrackAppUsageEvent(SELF, CGameID gameID, int eAppUsageEvent, const char *pchExtraInfo)
{
	xlogf("%s(self = %p, gameID = %llu, eAppUsageEvent = %d, pchExtraInfo = %s)\n", __func__, self, gameID.id, eAppUsageEvent, pchExtraInfo);
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUser_GetUserDataFolder(SELF, char *pchBuffer, int cubBuffer)
{
	snprintf(pchBuffer, cubBuffer, "%s", ctx.rootDir);
	xlogf("%s(self = %p, pchBuffer = %s, cubBuffer = %d)\n", __func__, self, pchBuffer, cubBuffer);
	return true;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamUser_StartVoiceRecording(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamUser_StopVoiceRecording(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI EVoiceResult S_CLASSCALLTYPE
SteamAPI_ISteamUser_GetAvailableVoice(SELF, uint32 *pcbCompressed, uint32 *pcbUncompressed, uint32 nUncompressedVoiceDesiredSampleRate)
{
	xlogf("%s(self = %p, pcbCompressed = %p, pcbUncompressed = %p, nUncompressedVoiceDesiredSampleRate = %d)\n", __func__, self, pcbCompressed, pcbUncompressed, nUncompressedVoiceDesiredSampleRate);
	return 0;
}

S_CLASSAPI EVoiceResult S_CLASSCALLTYPE
SteamAPI_ISteamUser_GetVoice(SELF, bool bWantCompressed, void *pDestBuffer, uint32 cbDestBufferSize, uint32 *nBytesWritten, bool bWantUncompressed, void *pUncompressedDestBuffer, uint32 cbUncompressedDestBufferSize, uint32 *nUncompressBytesWritten, uint32 nUncompressedVoiceDesiredSampleRate)
{
	xlogf("%s(self = %p, bWantCompressed = %d, pDestBuffer = %p, cbDestBufferSize = %d, nBytesWritten = %p, bWantUncompressed = %d, pUncompressedDestBuffer = %p, nUncompressBytesWritten = %d, cbUncompressedDestBufferSize = %p, nUncompressedVoiceDesiredSampleRate = %d\n", __func__, self, bWantCompressed, pDestBuffer, cbDestBufferSize, nBytesWritten, bWantUncompressed, pUncompressedDestBuffer, cbUncompressedDestBufferSize, nUncompressBytesWritten, nUncompressedVoiceDesiredSampleRate);
	return 0;
}

S_CLASSAPI EVoiceResult S_CLASSCALLTYPE
SteamAPI_ISteamUser_DecompressVoice(SELF, const void *pCompressed, uint32 cbCompressed, void *pDestBuffer, uint32 cbDestBufferSize, uint32 *nBytesWritten, uint32 nDesiredSampleRate)
{
	xlogf("%s(self = %p, pCompressed = %p, cbCompressed = %d, pDestBuffer = %p, cbDestBufferSize = %d, nBytesWritten = %p, nDesiredSampleRate = %d)", __func__, self, pCompressed, cbCompressed, pDestBuffer, cbDestBufferSize, nBytesWritten, nDesiredSampleRate);
	return 0;
}

S_CLASSAPI uint32 S_CLASSCALLTYPE
SteamAPI_ISteamUser_GetVoiceOptimalSampleRate(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI HAuthTicket S_CLASSCALLTYPE
SteamAPI_ISteamUser_GetAuthSessionTicket(SELF, void *pTicket, int cbMaxTicket, uint32 *pcbTicket)
{
	xlogf("%s(self = %p, pTicket = %p, cbMaxTicket = %d, pcbTicket = %p)\n", __func__, self, pTicket, cbMaxTicket, pcbTicket);
	return 0;
}

S_CLASSAPI EBeginAuthSessionResult S_CLASSCALLTYPE
SteamAPI_ISteamUser_BeginAuthSession(SELF, const void *pAuthTicket, int cbAuthTicket, CSteamID steamID)
{
	xlogf("%s(self = %p, pAuthTicket = %p, cbAuthTicket = %d, steamID = %llu)", __func__, self, pAuthTicket, cbAuthTicket, steamID.m_gameID);
	return 0;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamUser_EndAuthSession(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamUser_CancelAuthTicket(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI EUserHasLicenseForAppResult S_CLASSCALLTYPE
SteamAPI_ISteamUser_UserHasLicenseForApp(SELF, CSteamID steamID, AppId_t appID)
{
	xlogf("%s(self = %p, steamID = %llu, appID = %d)\n", __func__, self, steamID.m_gameID, appID);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUser_BIsBehindNAT(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return false;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamUser_AdvertiseGame(SELF, CSteamID steamIDGameServer, uint32 unIPServer, uint16 usPortServer)
{
	xlogf("%s(self = %p steamIDGameServer = %llu, unIPServer = %x, usPortServer = %x)\n", __func__, self, steamIDGameServer.m_gameID, unIPServer, usPortServer);
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUser_RequestEncryptedAppTicket(SELF, void *pDataToInclude, int cbDataToInclude)
{
	xlogf("%s(self = %p, pDataToInclude = %p, cbDataToInclude = %d)\n", __func__, self, pDataToInclude, cbDataToInclude);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUser_GetEncryptedAppTicket(SELF, void *pTicket, int cbMaxTicket, uint32 *pcbTicket)
{
	xlogf("%s(self = %p, pTicket = %p, cbMaxTicket = %d, pcbTicket = %p)\n", __func__, self, pTicket, cbMaxTicket, pcbTicket);
	return true;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamUser_GetGameBadgeLevel(SELF, int nSeries, bool bFoil)
{
	xlogf("%s(self = %p), nSeries = %d, bFail = %d)\n", __func__, self, nSeries, bFoil);
	return 0;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamUser_GetPlayerSteamLevel(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUser_RequestStoreAuthURL(SELF, const char *pchRedirectURL)
{
	xlogf("%s(self = %p, pchRedirectURL = %s)\n", __func__, self, pchRedirectURL);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUser_BIsPhoneVerified(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUser_BIsTwoFactorEnabled(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUser_BIsPhoneIdentifying(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUser_BIsPhoneRequiringVerification(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return false;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUser_GetMarketEligibility(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUser_GetDurationControl(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUser_BSetDurationControlOnlineState(SELF, EDurationControlOnlineState eNewState)
{
	xlogf("%s(self = %p, eNewState = %d)\n", __func__, self, eNewState);
	return false;
}
