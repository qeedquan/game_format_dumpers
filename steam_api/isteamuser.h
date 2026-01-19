#pragma once

// results from UserHasLicenseForApp

typedef enum {
	k_EUserHasLicenseResultHasLicense = 0,         // User has a license for specified app
	k_EUserHasLicenseResultDoesNotHaveLicense = 1, // User does not have a license for the specified app
	k_EUserHasLicenseResultNoAuth = 2              // User has not been authenticated
} EUserHasLicenseForAppResult;

// Error codes for use with the voice functions
typedef enum {
	k_EVoiceResultOK = 0,
	k_EVoiceResultNotInitialized = 1,
	k_EVoiceResultNotRecording = 2,
	k_EVoiceResultNoData = 3,
	k_EVoiceResultBufferTooSmall = 4,
	k_EVoiceResultDataCorrupted = 5,
	k_EVoiceResultRestricted = 6,
	k_EVoiceResultUnsupportedCodec = 7,
	k_EVoiceResultReceiverOutOfDate = 8,
	k_EVoiceResultReceiverDidNotAnswer = 9,
} EVoiceResult;

// results from BeginAuthSession
typedef enum {
	k_EBeginAuthSessionResultOK = 0,               // Ticket is valid for self game and self steamID.
	k_EBeginAuthSessionResultInvalidTicket = 1,    // Ticket is not valid.
	k_EBeginAuthSessionResultDuplicateRequest = 2, // A ticket has already been submitted for self steamID
	k_EBeginAuthSessionResultInvalidVersion = 3,   // Ticket is from an incompatible interface version
	k_EBeginAuthSessionResultGameMismatch = 4,     // Ticket is not for self game
	k_EBeginAuthSessionResultExpiredTicket = 5,    // Ticket has expired
} EBeginAuthSessionResult;

typedef struct CGameID CGameID;

struct CGameID {
	uint64 id;
};

typedef int32 HSteamUser;

typedef uint32 HAuthTicket;

typedef void ISteamUser;

typedef struct CSteamUser CSteamUser;

struct CSteamUser {
	CSteamBase base;
};

S_CLASSAPI HSteamUser S_CLASSCALLTYPE SteamAPI_ISteamUser_GetHSteamUser(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUser_BLoggedOn(SELF);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamUser_InitiateGameConnection(SELF, void *pAuthBlob, int cbMaxAuthBlob, CSteamID steamIDGameServer, uint32 unIPServer, uint16 usPortServer, bool bSecure);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamUser_TerminateGameConnection(SELF, uint32 unIPServer, uint16 usPortServer);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamUser_TrackAppUsageEvent(SELF, CGameID gameID, int eAppUsageEvent, const char *pchExtraInfo);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUser_GetUserDataFolder(SELF, char *pchBuffer, int cubBuffer);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamUser_StartVoiceRecording(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamUser_StopVoiceRecording(SELF);
S_CLASSAPI EVoiceResult S_CLASSCALLTYPE SteamAPI_ISteamUser_GetAvailableVoice(SELF, uint32 *pcbCompressed, uint32 *pcbUncompressed, uint32 nUncompressedVoiceDesiredSampleRate);
S_CLASSAPI EVoiceResult S_CLASSCALLTYPE SteamAPI_ISteamUser_GetVoice(SELF, bool bWantCompressed, void *pDestBuffer, uint32 cbDestBufferSize, uint32 *nBytesWritten, bool bWantUncompressed, void *pUncompressedDestBuffer, uint32 cbUncompressedDestBufferSize, uint32 *nUncompressBytesWritten, uint32 nUncompressedVoiceDesiredSampleRate);
S_CLASSAPI EVoiceResult S_CLASSCALLTYPE SteamAPI_ISteamUser_DecompressVoice(SELF, const void *pCompressed, uint32 cbCompressed, void *pDestBuffer, uint32 cbDestBufferSize, uint32 *nBytesWritten, uint32 nDesiredSampleRate);
S_CLASSAPI uint32 S_CLASSCALLTYPE SteamAPI_ISteamUser_GetVoiceOptimalSampleRate(SELF);
S_CLASSAPI HAuthTicket S_CLASSCALLTYPE SteamAPI_ISteamUser_GetAuthSessionTicket(SELF, void *pTicket, int cbMaxTicket, uint32 *pcbTicket);
S_CLASSAPI EBeginAuthSessionResult S_CLASSCALLTYPE SteamAPI_ISteamUser_BeginAuthSession(SELF, const void *pAuthTicket, int cbAuthTicket, CSteamID steamID);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamUser_EndAuthSession(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamUser_CancelAuthTicket(SELF);
S_CLASSAPI EUserHasLicenseForAppResult S_CLASSCALLTYPE SteamAPI_ISteamUser_UserHasLicenseForApp(SELF, CSteamID steamID, AppId_t appID);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUser_BIsBehindNAT(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamUser_AdvertiseGame(SELF, CSteamID steamIDGameServer, uint32 unIPServer, uint16 usPortServer);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUser_RequestEncryptedAppTicket(SELF, void *pDataToInclude, int cbDataToInclude);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUser_GetEncryptedAppTicket(SELF, void *pTicket, int cbMaxTicket, uint32 *pcbTicket);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamUser_GetGameBadgeLevel(SELF, int nSeries, bool bFoil);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamUser_GetPlayerSteamLevel(SELF);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUser_RequestStoreAuthURL(SELF, const char *pchRedirectURL);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUser_BIsPhoneVerified(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUser_BIsTwoFactorEnabled(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUser_BIsPhoneIdentifying(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUser_BIsPhoneRequiringVerification(SELF);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUser_GetMarketEligibility(SELF);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUser_GetDurationControl(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUser_BSetDurationControlOnlineState(SELF, EDurationControlOnlineState eNewState);

S_CLASSAPI
R_STRUCT_TYPE(CSteamID)
S_CLASSCALLTYPE SteamAPI_ISteamUser_GetSteamID(SELF);