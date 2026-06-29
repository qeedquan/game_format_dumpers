#include "steam.h"

S_CLASSAPI uint32 S_CLASSCALLTYPE
SteamAPI_ISteamUtils_GetSecondsSinceAppActive(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI uint32 S_CLASSCALLTYPE
SteamAPI_ISteamUtils_GetSecondsSinceComputerActive(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI EUniverse S_CLASSCALLTYPE
SteamAPI_ISteamUtils_GetConnectedUniverse(SELF)
{
	EUniverse ret = k_EUniversePublic;
	xlogf("%s(self = %p) -> %d\n", __func__, self, ret);
	return ret;
}

S_CLASSAPI uint32 S_CLASSCALLTYPE
SteamAPI_ISteamUtils_GetServerRealTime(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamUtils_GetIPCountry(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return "america";
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUtils_GetImageSize(SELF, int iImage, uint32 *pnWidth, uint32 *pnHeight)
{
	xlogf("%s(self = %p, iImage = %d, pnWidth = %p, pnHeight = %p)\n", __func__, self, iImage, pnWidth, pnHeight);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUtils_GetImageRGBA(SELF, int iImage, uint8 *pubDest, int nDestBufferSize)
{
	xlogf("%s(self = %p, iImage = %d, pubDest = %p, nDestBufferSize = %d)\n", __func__, self, iImage, pubDest, nDestBufferSize);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUtils_GetCSERIPPort(SELF, uint32 *unIP, uint16 *usPort)
{
	xlogf("%s(self = %p, unIP = %p, usPort = %p)\n", __func__, self, unIP, usPort);
	return false;
}

S_CLASSAPI uint8 S_CLASSCALLTYPE
SteamAPI_ISteamUtils_GetCurrentBatteryPower(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI uint32 S_CLASSCALLTYPE
SteamAPI_ISteamUtils_GetAppID(SELF)
{
	CSteamContext *p = &ctx;
	xlogf("%s(self = %p) -> %d\n", __func__, self, p->appID);
	return p->appID;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamUtils_SetOverlayNotificationPosition(SELF, ENotificationPosition eNotificationPosition)
{
	xlogf("%s(self = %p, eNotificationPosition = %#x)\n", __func__, self, eNotificationPosition);
}

S_CLASSAPI ESteamAPICallFailure S_CLASSCALLTYPE
SteamAPI_ISteamUtils_GetAPICallFailureReason(SELF, SteamAPICall_t hSteamAPICall)
{
	xlogf("%s(self = %p, hSteamAPICall = %llu)\n", __func__, self, hSteamAPICall);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUtils_GetAPICallResult(SELF, SteamAPICall_t hSteamAPICall, void *pCallback, int cubCallback, int iCallbackExpected, bool *pbFailed)
{
	xlogf("%s(self = %p, hSteamAPICall = %llu, pCallback = %p, cubCallback = %d, iCallbackExpected = %d, pbFailed = %p)\n", __func__, self, hSteamAPICall, pCallback, cubCallback, iCallbackExpected, pbFailed);
	return true;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamUtils_RunFrame(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI uint32 S_CLASSCALLTYPE
SteamAPI_ISteamUtils_GetIPCCallCount(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamUtils_SetWarningMessageHook(SELF, SteamAPIWarningMessageHook_t pFunction)
{
	xlogf("%s(self = %p, pFunction = %p)\n", __func__, self, pFunction);
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUtils_IsOverlayEnabled(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUtils_BOverlayNeedsPresent(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return false;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUtils_CheckFileSignature(SELF, const char *szFileName)
{
	xlogf("%s(self = %p, szFilename = %s)\n", __func__, self, szFileName);
	return 1;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUtils_ShowGamepadTextInput(SELF, EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char *pchDescription, uint32 unCharMax, const char *pchExistingText)
{
	xlogf("%s(self = %p, eInputMode = %d, eLineInputMode = %d, pchDescription = %s, unCharMax = %d, pchExistingText = %s\n", __func__, self, eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText);
	return true;
}

S_CLASSAPI uint32 S_CLASSCALLTYPE
SteamAPI_ISteamUtils_GetEnteredGamepadTextLength(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUtils_GetEnteredGamepadTextInput(SELF, char *pchText, uint32 cchText)
{
	xlogf("%s(self = %p, pchText = %s, cchText = %d)\n", __func__, self, pchText, cchText);
	return true;
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamUtils_GetSteamUILanguage(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return ctx.currentLanguage;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUtils_IsSteamRunningInVR(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return false;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamUtils_SetOverlayNotificationInset(SELF, int nHorizontalInset, int nVerticalInset)
{
	xlogf("%s(self = %p, nHorizontalInset = %d, nVerticalInset = %d)\n", __func__, self, nHorizontalInset, nVerticalInset);
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUtils_IsAPICallCompleted(SELF, SteamAPICall_t hSteamAPICall, bool *pbFailed)
{
	xlogf("%s(self = %p, hSteamAPICall = %llu, pbFailed = %p)\n", __func__, self, hSteamAPICall, pbFailed);
	*pbFailed = false;
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUtils_IsSteamInBigPictureMode(SELF)
{
	bool enabled = false;
	xlogf("%s(self = %p) -> %d\n", __func__, self, enabled);
	return enabled;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUtils_IsVRHeadsetStreamingEnabled(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return false;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamUtils_SetVRHeadsetStreamingEnabled(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamUtils_StartVRDashboard(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUtils_IsSteamChinaLauncher(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUtils_InitFilterText(SELF, uint32 unFilterOptions)
{
	xlogf("%s(self = %p, unFilterOptions = %x)\n", __func__, self, unFilterOptions);
	return false;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamUtils_FilterText(SELF, ETextFilteringContext eContext, CSteamID sourceSteamID, const char *pchInputMessage, char *pchOutFilteredText, uint32 nByteSizeOutFilteredText)
{
	xlogf("%s(self = %p, eContext = %x, sourceSteamID = %llx, pchInputMessage = %s, pchOutFilteredText = %s, nByteSizeOutFilteredText = %d)\n",
	      __func__, self, eContext, sourceSteamID.m_ulGameID, pchInputMessage, pchOutFilteredText, nByteSizeOutFilteredText);
	return 0;
}

S_CLASSAPI ESteamIPv6ConnectivityState S_CLASSCALLTYPE
SteamAPI_ISteamUtils_GetIPv6ConnectivityState(SELF, ESteamIPv6ConnectivityProtocol eProtocol)
{
	xlogf("%s(self = %p, eProtocol = %x)\n", __func__, self, eProtocol);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUtils_IsSteamRunningOnSteamDeck(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUtils_ShowFloatingGamepadTextInput(SELF, EFloatingGamepadTextInputMode eKeyboardMode, int nTextFieldXPosition, int nTextFieldYPosition, int nTextFieldWidth, int nTextFieldHeight)
{
	xlogf("%s(self = %p, eKeyboardMode = %d, nTextFieldXPosition = %d, nTextFieldYPosition = %d, nTextFieldWidth = %d, nTextFieldHeight = %d)\n",
	      __func__, self, eKeyboardMode, nTextFieldXPosition, nTextFieldYPosition, nTextFieldWidth, nTextFieldHeight);
	return false;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamUtils_SetGameLauncherMode(SELF, bool bLauncherMode)
{
	xlogf("%s(self = %p, bLauncherMode = %d)\n", __func__, self, bLauncherMode);
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUtils_DismissFloatingGamepadTextInput(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return false;
}