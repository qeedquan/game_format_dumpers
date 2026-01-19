#pragma once

#include "steamuniverse.h"

// Input modes for the Big Picture gamepad text entry
typedef enum {
	k_EGamepadTextInputModeNormal = 0,
	k_EGamepadTextInputModePassword = 1
} EGamepadTextInputMode;

// Controls number of allowed lines for the Big Picture gamepad text entry
typedef enum {
	k_EGamepadTextInputLineModeSingleLine = 0,
	k_EGamepadTextInputLineModeMultipleLines = 1
} EGamepadTextInputLineMode;

// Steam API call failure results
typedef enum {
	k_ESteamAPICallFailureNone = -1,          // no failure
	k_ESteamAPICallFailureSteamGone = 0,      // the local Steam process has gone away
	k_ESteamAPICallFailureNetworkFailure = 1, // the network connection to Steam has been broken, or was already broken
	// SteamServersDisconnected_t callback will be sent around the same time
	// SteamServersConnected_t will be sent when the client is able to talk to the Steam servers again
	k_ESteamAPICallFailureInvalidHandle = 2,      // the SteamAPICall_t handle passed in no longer exists
	k_ESteamAPICallFailureMismatchedCallback = 3, // GetAPICallResult() was called with the wrong callback type for this API call
} ESteamAPICallFailure;

typedef enum {
	k_ETextFilteringContextUnknown = 0,     // Unknown context
	k_ETextFilteringContextGameContent = 1, // Game content, only legally required filtering is performed
	k_ETextFilteringContextChat = 2,        // Chat from another player
	k_ETextFilteringContextName = 3,        // Character or item name
} ETextFilteringContext;

typedef enum {
	k_EFloatingGamepadTextInputModeModeSingleLine = 0,    // Enter dismisses the keyboard
	k_EFloatingGamepadTextInputModeModeMultipleLines = 1, // User needs to explictly close the keyboard
	k_EFloatingGamepadTextInputModeModeEmail = 2,
	k_EFloatingGamepadTextInputModeModeNumeric = 3,
} EFloatingGamepadTextInputMode;

typedef void (*SteamAPIWarningMessageHook_t)(int, const char *);

typedef void ISteamUtils;

typedef struct CSteamUtils CSteamUtils;

struct CSteamUtils {
	CSteamBase base;
};

S_CLASSAPI uint32 S_CLASSCALLTYPE SteamAPI_ISteamUtils_GetSecondsSinceAppActive(SELF);
S_CLASSAPI uint32 S_CLASSCALLTYPE SteamAPI_ISteamUtils_GetSecondsSinceComputerActive(SELF);
S_CLASSAPI EUniverse S_CLASSCALLTYPE SteamAPI_ISteamUtils_GetConnectedUniverse(SELF);
S_CLASSAPI uint32 S_CLASSCALLTYPE SteamAPI_ISteamUtils_GetServerRealTime(SELF);
S_CLASSAPI const char *S_CLASSCALLTYPE SteamAPI_ISteamUtils_GetIPCountry(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUtils_GetImageSize(SELF, int iImage, uint32 *pnWidth, uint32 *pnHeight);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUtils_GetImageRGBA(SELF, int iImage, uint8 *pubDest, int nDestBufferSize);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUtils_GetCSERIPPort(SELF, uint32 *unIP, uint16 *usPort);
S_CLASSAPI uint8 S_CLASSCALLTYPE SteamAPI_ISteamUtils_GetCurrentBatteryPower(SELF);
S_CLASSAPI uint32 S_CLASSCALLTYPE SteamAPI_ISteamUtils_GetAppID(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamUtils_SetOverlayNotificationPosition(SELF, ENotificationPosition eNotificationPosition);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUtils_IsAPICallCompleted(SELF, SteamAPICall_t hSteamAPICall, bool *pbFailed);
S_CLASSAPI ESteamAPICallFailure S_CLASSCALLTYPE SteamAPI_ISteamUtils_GetAPICallFailureReason(SELF, SteamAPICall_t hSteamAPICall);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUtils_GetAPICallResult(SELF, SteamAPICall_t hSteamAPICall, void *pCallback, int cubCallback, int iCallbackExpected, bool *pbFailed);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamUtils_RunFrame(SELF);
S_CLASSAPI uint32 S_CLASSCALLTYPE SteamAPI_ISteamUtils_GetIPCCallCount(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamUtils_SetWarningMessageHook(SELF, SteamAPIWarningMessageHook_t pFunction);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUtils_IsOverlayEnabled(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUtils_BOverlayNeedsPresent(SELF);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUtils_CheckFileSignature(SELF, const char *szFileName);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUtils_ShowGamepadTextInput(SELF, EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char *pchDescription, uint32 unCharMax, const char *pchExistingText);
S_CLASSAPI uint32 S_CLASSCALLTYPE SteamAPI_ISteamUtils_GetEnteredGamepadTextLength(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUtils_GetEnteredGamepadTextInput(SELF, char *pchText, uint32 cchText);
S_CLASSAPI const char *S_CLASSCALLTYPE SteamAPI_ISteamUtils_GetSteamUILanguage(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUtils_IsSteamRunningInVR(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamUtils_SetOverlayNotificationInset(SELF, int nHorizontalInset, int nVerticalInset);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUtils_IsSteamInBigPictureMode(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUtils_IsVRHeadsetStreamingEnabled(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamUtils_SetVRHeadsetStreamingEnabled(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamUtils_StartVRDashboard(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUtils_IsSteamChinaLauncher(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUtils_InitFilterText(SELF, uint32 unFilterOptions);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamUtils_FilterText(SELF, ETextFilteringContext eContext, CSteamID sourceSteamID, const char *pchInputMessage, char *pchOutFilteredText, uint32 nByteSizeOutFilteredText);
S_CLASSAPI ESteamIPv6ConnectivityState S_CLASSCALLTYPE SteamAPI_ISteamUtils_GetIPv6ConnectivityState(SELF, ESteamIPv6ConnectivityProtocol eProtocol);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUtils_IsSteamRunningOnSteamDeck(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUtils_ShowFloatingGamepadTextInput(SELF, EFloatingGamepadTextInputMode eKeyboardMode, int nTextFieldXPosition, int nTextFieldYPosition, int nTextFieldWidth, int nTextFieldHeight);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamUtils_SetGameLauncherMode(SELF, bool bLauncherMode);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUtils_DismissFloatingGamepadTextInput(SELF);