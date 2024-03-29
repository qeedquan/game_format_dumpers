#pragma once

#include "steamtypes.h"

typedef struct CSteamID CSteamID;

typedef uint64 GameID_t;

struct CSteamID {
	union {
		uint64 m_ulGameID;
		GameID_t m_gameID;
	};
};

//-----------------------------------------------------------------------------
// Purpose: Possible positions to tell the overlay to show notifications in
//-----------------------------------------------------------------------------
typedef enum {
	k_EPositionTopLeft = 0,
	k_EPositionTopRight = 1,
	k_EPositionBottomLeft = 2,
	k_EPositionBottomRight = 3,
} ENotificationPosition;

//-----------------------------------------------------------------------------
// Purpose: Broadcast upload result details
//-----------------------------------------------------------------------------
typedef enum {
	k_EBroadcastUploadResultNone = 0,              // broadcast state unknown
	k_EBroadcastUploadResultOK = 1,                // broadcast was good, no problems
	k_EBroadcastUploadResultInitFailed = 2,        // broadcast init failed
	k_EBroadcastUploadResultFrameFailed = 3,       // broadcast frame upload failed
	k_EBroadcastUploadResultTimeout = 4,           // broadcast upload timed out
	k_EBroadcastUploadResultBandwidthExceeded = 5, // broadcast send too much data
	k_EBroadcastUploadResultLowFPS = 6,            // broadcast FPS too low
	k_EBroadcastUploadResultMissingKeyFrames = 7,  // broadcast sending not enough key frames
	k_EBroadcastUploadResultNoConnection = 8,      // broadcast client failed to connect to relay
	k_EBroadcastUploadResultRelayFailed = 9,       // relay dropped the upload
	k_EBroadcastUploadResultSettingsChanged = 10,  // the client changed broadcast settings
	k_EBroadcastUploadResultMissingAudio = 11,     // client failed to send audio data
	k_EBroadcastUploadResultTooFarBehind = 12,     // clients was too slow uploading
} EBroadcastUploadResult;

// General result codes
typedef enum {
	k_EResultOK = 1,           // success
	k_EResultFail = 2,         // generic failure
	k_EResultNoConnection = 3, // no/failed network connection
	//	k_EResultNoConnectionRetry = 4,						// OBSOLETE - removed
	k_EResultInvalidPassword = 5,        // password/ticket is invalid
	k_EResultLoggedInElsewhere = 6,      // same user logged in elsewhere
	k_EResultInvalidProtocolVer = 7,     // protocol version is incorrect
	k_EResultInvalidParam = 8,           // a parameter is incorrect
	k_EResultFileNotFound = 9,           // file was not found
	k_EResultBusy = 10,                  // called method busy - action not taken
	k_EResultInvalidState = 11,          // called object was in an invalid state
	k_EResultInvalidName = 12,           // name is invalid
	k_EResultInvalidEmail = 13,          // email is invalid
	k_EResultDuplicateName = 14,         // name is not unique
	k_EResultAccessDenied = 15,          // access is denied
	k_EResultTimeout = 16,               // operation timed out
	k_EResultBanned = 17,                // VAC2 banned
	k_EResultAccountNotFound = 18,       // account not found
	k_EResultInvalidSteamID = 19,        // steamID is invalid
	k_EResultServiceUnavailable = 20,    // The requested service is currently unavailable
	k_EResultNotLoggedOn = 21,           // The user is not logged on
	k_EResultPending = 22,               // Request is pending (may be in process, or waiting on third party)
	k_EResultEncryptionFailure = 23,     // Encryption or Decryption failed
	k_EResultInsufficientPrivilege = 24, // Insufficient privilege
	k_EResultLimitExceeded = 25,         // Too much of a good thing
	k_EResultRevoked = 26,               // Access has been revoked (used for revoked guest passes)
	k_EResultExpired = 27,               // License/Guest pass the user is trying to access is expired
	k_EResultAlreadyRedeemed = 28,       // Guest pass has already been redeemed by account, cannot be acked again
	k_EResultDuplicateRequest = 29,      // The request is a duplicate and the action has already occurred in the past, ignored this time
	k_EResultAlreadyOwned = 30,          // All the games in this guest pass redemption request are already owned by the user
	k_EResultIPNotFound = 31,            // IP address not found
	k_EResultPersistFailed = 32,         // failed to write change to the data store
	k_EResultLockingFailed = 33,         // failed to acquire access lock for this operation
	k_EResultLogonSessionReplaced = 34,
	k_EResultConnectFailed = 35,
	k_EResultHandshakeFailed = 36,
	k_EResultIOFailure = 37,
	k_EResultRemoteDisconnect = 38,
	k_EResultShoppingCartNotFound = 39, // failed to find the shopping cart requested
	k_EResultBlocked = 40,              // a user didn't allow it
	k_EResultIgnored = 41,              // target is ignoring sender
	k_EResultNoMatch = 42,              // nothing matching the request found
	k_EResultAccountDisabled = 43,
	k_EResultServiceReadOnly = 44,                         // this service is not accepting content changes right now
	k_EResultAccountNotFeatured = 45,                      // account doesn't have value, so this feature isn't available
	k_EResultAdministratorOK = 46,                         // allowed to take this action, but only because requester is admin
	k_EResultContentVersion = 47,                          // A Version mismatch in content transmitted within the Steam protocol.
	k_EResultTryAnotherCM = 48,                            // The current CM can't service the user making a request, user should try another.
	k_EResultPasswordRequiredToKickSession = 49,           // You are already logged in elsewhere, this cached credential login has failed.
	k_EResultAlreadyLoggedInElsewhere = 50,                // You are already logged in elsewhere, you must wait
	k_EResultSuspended = 51,                               // Long running operation (content download) suspended/paused
	k_EResultCancelled = 52,                               // Operation canceled (typically by user: content download)
	k_EResultDataCorruption = 53,                          // Operation canceled because data is ill formed or unrecoverable
	k_EResultDiskFull = 54,                                // Operation canceled - not enough disk space.
	k_EResultRemoteCallFailed = 55,                        // an remote call or IPC call failed
	k_EResultPasswordUnset = 56,                           // Password could not be verified as it's unset server side
	k_EResultPSNAccountUnlinked = 57,                      // Attempt to logon from a PS3 failed because the PSN online id is not linked to a Steam account
	k_EResultPSNTicketInvalid = 58,                        // PSN ticket was invalid
	k_EResultPSNAccountAlreadyLinked = 59,                 // PSN account is already linked to some other account, must explicitly request to replace/delete the link first
	k_EResultRemoteFileConflict = 60,                      // The sync cannot resume due to a conflict between the local and remote files
	k_EResultIllegalPassword = 61,                         // The requested new password is not legal
	k_EResultSameAsPreviousValue = 62,                     // new value is the same as the old one ( secret question and answer )
	k_EResultAccountLogonDenied = 63,                      // account login denied due to 2nd factor authentication failure
	k_EResultCannotUseOldPassword = 64,                    // The requested new password is not legal
	k_EResultInvalidLoginAuthCode = 65,                    // account login denied due to auth code invalid
	k_EResultAccountLogonDeniedNoMail = 66,                // account login denied due to 2nd factor auth failure - and no mail has been sent
	k_EResultHardwareNotCapableOfIPT = 67,                 //
	k_EResultIPTInitError = 68,                            //
	k_EResultParentalControlRestrictions = 69,             // Operation failed due to parental control restrictions for current user
	k_EResultFacebookQueryError = 70,                      // Facebook query returned an error
	k_EResultExpiredLoginAuthCode = 71,                    // Expired Login Auth Code
	k_EResultIPLoginRestrictionFailed = 72,                // IP Login Restriction Failed
	k_EResultAccountLockedDown = 73,                       // Account Locked Down
	k_EResultAccountLogonDeniedVerifiedEmailRequired = 74, // Account Logon Denied Verified Email Required
	k_EResultNoMatchingURL = 75,                           // No matching URL
	k_EResultBadResponse = 76,                             // parse failure, missing field, etc.
	k_EResultRequirePasswordReEntry = 77,                  // The user cannot complete the action until they re-enter their password
	k_EResultValueOutOfRange = 78,                         // the value entered is outside the acceptable range
	k_EResultUnexpectedError = 79,                         //
	k_EResultFeatureDisabled = 80,                         //
	k_EResultInvalidCEGSubmission = 81,                    //
	k_EResultRestrictedDevice = 82,                        //
	k_EResultRegionLocked = 83,                            //
	k_EResultRateLimitExceeded = 84,                       //
} EResult;

typedef enum {
	k_ESteamIPv6ConnectivityProtocol_Invalid = 0,
	k_ESteamIPv6ConnectivityProtocol_HTTP = 1, // because a proxy may make this different than other protocols
	k_ESteamIPv6ConnectivityProtocol_UDP = 2,  // test UDP connectivity. Uses a port that is commonly needed for other Steam stuff. If UDP works, TCP probably works.
} ESteamIPv6ConnectivityProtocol;

typedef enum {
	k_ESteamIPv6ConnectivityState_Unknown = 0, // We haven't run a test yet
	k_ESteamIPv6ConnectivityState_Good = 1,    // We have recently been able to make a request on ipv6 for the given protocol
	k_ESteamIPv6ConnectivityState_Bad = 2,     // We failed to make a request, either because this machine has no ipv6 address assigned, or it has no upstream connectivity
} ESteamIPv6ConnectivityState;

typedef enum {
	k_EDurationControlOnlineState_Invalid = 0,       // nil value
	k_EDurationControlOnlineState_Offline = 1,       // currently in offline play - single-player, offline co-op, etc.
	k_EDurationControlOnlineState_Online = 2,        // currently in online play
	k_EDurationControlOnlineState_OnlineHighPri = 3, // currently in online play and requests not to be interrupted
} EDurationControlOnlineState;
