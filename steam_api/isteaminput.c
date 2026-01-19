#include "steam.h"

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInput_Init(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInput_Shutdown(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return true;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamInput_RunFrame(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamInput_GetConnectedControllers(SELF, InputHandle_t *handlesOut)
{
	xlogf("%s(self = %p, handlesOut = %p)\n", __func__, self, handlesOut);
	return 0;
}

S_CLASSAPI InputActionSetHandle_t S_CLASSCALLTYPE
SteamAPI_ISteamInput_GetActionSetHandle(SELF, const char *pszActionSetName)
{
	xlogf("%s(self = %p, pszActionSetName = %s)\n", __func__, self, pszActionSetName);
	return 0;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamInput_ActivateActionSet(SELF, InputHandle_t inputHandle, InputActionSetHandle_t actionSetHandle)
{
	xlogf("%s(self = %p, inputHandle = %llu, actionSetHandle = %llu)\n", __func__, self, inputHandle, actionSetHandle);
}

S_CLASSAPI InputActionSetHandle_t S_CLASSCALLTYPE
SteamAPI_ISteamInput_GetCurrentActionSet(SELF, InputHandle_t inputHandle)
{
	xlogf("%s(self = %p, inputHandle = %llu)\n", __func__, self, inputHandle);
	return 0;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamInput_ActivateActionSetLayer(SELF, InputHandle_t inputHandle, InputActionSetHandle_t actionSetLayerHandle)
{
	xlogf("%s(self = %p, inputHandle = %llu, actionSetHandle = %llu)\n", __func__, self, inputHandle, actionSetLayerHandle);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamInput_DeactivateActionSetLayer(SELF, InputHandle_t inputHandle, InputActionSetHandle_t actionSetLayerHandle)
{
	xlogf("%s(self = %p, inputHandle = %llu, actionSetHandle = %llu)\n", __func__, self, inputHandle, actionSetLayerHandle);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamInput_DeactivateAllActionSetLayers(SELF, InputHandle_t inputHandle)
{
	xlogf("%s(self = %p, inputHandle = %llu)\n", __func__, self, inputHandle);
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamInput_GetActiveActionSetLayers(SELF, InputHandle_t inputHandle, InputActionSetHandle_t *handlesOut)
{
	xlogf("%s(self = %p, inputHandle = %llu, handlesOut = %p)\n", __func__, self, inputHandle, handlesOut);
	return 0;
}

S_CLASSAPI InputDigitalActionHandle_t S_CLASSCALLTYPE
SteamAPI_ISteamInput_GetDigitalActionHandle(SELF, const char *pszActionName)
{
	xlogf("%s(self = %p, pszActionName = %s)\n", __func__, self, pszActionName);
	return 0;
}

S_CLASSAPI InputDigitalActionData_t S_CLASSCALLTYPE
SteamAPI_ISteamInput_GetDigitalActionData(SELF, InputHandle_t inputHandle, InputDigitalActionHandle_t digitalActionHandle)
{
	InputDigitalActionData_t data = {0};
	xlogf("%s(self = %p, inputHandle = %llu, digitalActionHandle = %llu)\n", __func__, self, inputHandle, digitalActionHandle);
	return data;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamInput_GetDigitalActionOrigins(SELF, InputHandle_t inputHandle, InputActionSetHandle_t actionSetHandle, InputDigitalActionHandle_t digitalActionHandle, EInputActionOrigin *originsOut)
{
	xlogf("%s(self = %p, inputHandle = %llu, actionSetHandle = %llu, digitalActionHandle = %llu, originsOut = %p)\n", __func__, self, inputHandle, actionSetHandle, digitalActionHandle, originsOut);
	return 0;
}

S_CLASSAPI InputAnalogActionHandle_t S_CLASSCALLTYPE
SteamAPI_ISteamInput_GetAnalogActionHandle(SELF, const char *pszActionName)
{
	xlogf("%s(self = %p, pszActionName = %s)\n", __func__, self, pszActionName);
	return 0;
}

S_CLASSAPI InputAnalogActionData_t S_CLASSCALLTYPE
SteamAPI_ISteamInput_GetAnalogActionData(SELF, InputHandle_t inputHandle, InputAnalogActionHandle_t analogActionHandle)
{
	InputAnalogActionData_t data = {0};
	xlogf("%s(self = %p, inputHandle = %llu, analogActionHandle = %llu)\n", __func__, self, inputHandle, analogActionHandle);
	return data;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamInput_GetAnalogActionOrigins(SELF, InputHandle_t inputHandle, InputActionSetHandle_t actionSetHandle, InputAnalogActionHandle_t analogActionHandle, EInputActionOrigin *originsOut)
{
	xlogf("%s(self = %p, inputHandle = %llu, actionSetHandle = %llu, analogActionHandle = %llu, EInputActionOrigin = %p)\n",
	      __func__, self, inputHandle, actionSetHandle, analogActionHandle, originsOut);
	return 0;
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamInput_GetGlyphForActionOrigin(SELF, EInputActionOrigin eOrigin)
{
	xlogf("%s(self = %p, eOrigin = %d)\n", __func__, self, eOrigin);
	return "";
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamInput_GetStringForActionOrigin(SELF, EInputActionOrigin eOrigin)
{
	xlogf("%s(self = %p, eOrigin = %d)\n", __func__, self, eOrigin);
	return "";
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamInput_StopAnalogActionMomentum(SELF, InputHandle_t inputHandle, InputAnalogActionHandle_t eAction)
{
	xlogf("%s(self = %p, inputHandle = %llu, eAction = %llu)\n", __func__, self, inputHandle, eAction);
}

S_CLASSAPI InputMotionData_t S_CLASSCALLTYPE
SteamAPI_ISteamInput_GetMotionData(SELF, InputHandle_t inputHandle)
{
	InputMotionData_t data = {0};
	xlogf("%s(self = %p, inputHandle = %llu)\n", __func__, self, inputHandle);
	return data;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamInput_TriggerVibration(SELF, InputHandle_t inputHandle, unsigned short usLeftSpeed, unsigned short usRightSpeed)
{
	xlogf("%s(self = %p, inputHandle = %llu, usLeftSpeed = %d, usRightSpeed = %d)\n",
	      __func__, self, inputHandle, usLeftSpeed, usRightSpeed);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamInput_SetLEDColor(SELF, InputHandle_t inputHandle, uint8 nColorR, uint8 nColorG, uint8 nColorB, unsigned int nFlags)
{
	xlogf("%s(self = %p, inputHandle = %llu, nColorR = %d, nColorG = %d, nColorB = %d, nFlags = %x)\n",
	      __func__, self, inputHandle, nColorR, nColorG, nColorB, nFlags);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamInput_TriggerHapticPulse(SELF, InputHandle_t inputHandle, ESteamControllerPad eTargetPad, unsigned short usDurationMicroSec)
{
	xlogf("%s(self = %p, inputHandle = %llu, eTargetPad = %d, usDurationMicroSec = %d)\n",
	      __func__, self, inputHandle, eTargetPad, usDurationMicroSec);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamInput_TriggerRepeatedHapticPulse(SELF, InputHandle_t inputHandle, ESteamControllerPad eTargetPad, unsigned short usDurationMicroSec, unsigned short usOffMicroSec, unsigned short unRepeat, unsigned int nFlags)
{
	xlogf("%s(self = %p, inputHandle = %llu, eTargetPad = %d, usDurationMicroSec = %d, usOffMicroSec = %d, unRepeat = %d, nFlags = %x)\n",
	      __func__, self, inputHandle, eTargetPad, usDurationMicroSec, usOffMicroSec, unRepeat, nFlags);
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInput_ShowBindingPanel(SELF, InputHandle_t inputHandle)
{
	xlogf("%s(self = %p, inputHandle = %llu)\n", __func__, self, inputHandle);
	return false;
}

S_CLASSAPI ESteamInputType S_CLASSCALLTYPE
SteamAPI_ISteamInput_GetInputTypeForHandle(SELF, InputHandle_t inputHandle)
{
	xlogf("%s(self = %p, inputHandle = %llu)\n", __func__, self, inputHandle);
	return 0;
}

S_CLASSAPI InputHandle_t S_CLASSCALLTYPE
SteamAPI_ISteamInput_GetControllerForGamepadIndex(SELF, int nIndex)
{
	xlogf("%s(self = %p, nIndex = %d)\n", __func__, self, nIndex);
	return 0;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamInput_GetGamepadIndexForController(SELF, InputHandle_t ulControllerHandle)
{
	xlogf("%s(self = %p, ulControllerHandle = %llu)\n", __func__, self, ulControllerHandle);
	return 0;
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamInput_GetStringForXboxOrigin(SELF, EInputActionOrigin eOrigin)
{
	xlogf("%s(self = %p, eOrigin = %d)\n", __func__, self, eOrigin);
	return "";
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamInput_GetGlyphForXboxOrigin(SELF, EInputActionOrigin eOrigin)
{
	xlogf("%s(self = %p, eOrigin = %d)\n", __func__, self, eOrigin);
	return "";
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamInput_GetActionOriginFromXboxOrigin(SELF, EInputActionOrigin eOrigin)
{
	xlogf("%s(self = %p, eOrigin = %d)\n", __func__, self, eOrigin);
	return 0;
}

S_CLASSAPI EInputActionOrigin S_CLASSCALLTYPE
SteamAPI_ISteamInput_TranslateActionOrigin(SELF, ESteamInputType eDestinationInputType, EInputActionOrigin eSourceOrigin)
{
	xlogf("%s(self = %p, eDestinationInputType = %d, eSourceOrigin = %d)\n",
	      __func__, self, eDestinationInputType, eSourceOrigin);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInput_GetDeviceBindingRevision(SELF, InputHandle_t inputHandle, int *pMajor, int *pMinor)
{
	xlogf("%s(self = %p, inputHandle = %llu, pMajor = %p, pMinor = %p)\n", __func__, self, inputHandle, pMajor, pMinor);
	*pMajor = 1;
	*pMinor = 0;
	return true;
}

S_CLASSAPI uint32 S_CLASSCALLTYPE
SteamAPI_ISteamInput_GetRemotePlaySessionID(SELF, InputHandle_t inputHandle)
{
	xlogf("%s(self = %p, inputHandle = %llu)\n", __func__, self, inputHandle);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInput_SetInputActionManifestFilePath(SELF, const char *pchInputActionManifestAbsolutePath)
{
	xlogf("%s(self = %p, inputHandle = %s)\n", __func__, self, pchInputActionManifestAbsolutePath);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInput_BWaitForData(SELF, bool bWaitForever, uint32 unTimeout)
{
	xlogf("%s(self = %p, bWaitForever = %d, unTimeout = %d)\n", __func__, self, bWaitForever, unTimeout);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInput_BNewDataAvailable(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return false;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamInput_EnableDeviceCallbacks(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamInput_EnableActionEventCallbacks(SELF, SteamInputActionEventCallbackPointer pCallback)
{
	xlogf("%s(self = %p, pCallback = %p)\n", __func__, self, pCallback);
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamInput_GetStringForDigitalActionName(SELF, InputDigitalActionHandle_t eActionHandle)
{
	xlogf("%s(self = %p, eActionHandle = %lld)\n", __func__, self, eActionHandle);
	return "Unknown";
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamInput_GetGlyphPNGForActionOrigin(SELF, EInputActionOrigin eOrigin, ESteamInputGlyphSize eSize, uint32 unFlags)
{
	xlogf("%s(self = %p, eOrigin = %d, eSize = %d, unFlags = %#x)\n", __func__, self, eOrigin, eSize, unFlags);
	return "Unknown";
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamInput_GetGlyphSVGForActionOrigin(SELF, EInputActionOrigin eOrigin, uint32 unFlags)
{
	xlogf("%s(self = %p, eOrigin = %d, unFlags = %#x)\n", __func__, self, eOrigin, unFlags);
	return "Unknown";
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamInput_GetGlyphForActionOrigin_Legacy(SELF, EInputActionOrigin eOrigin)
{
	xlogf("%s(self = %p, eOrigin = %d)\n", __func__, self, eOrigin);
	return "Unknown";
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamInput_GetStringForAnalogActionName(SELF, InputAnalogActionHandle_t eActionHandle)
{
	xlogf("%s(self = %p, eActionHandle = %lld)\n", __func__, self, eActionHandle);
	return "Unknown";
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamInput_TriggerVibrationExtended(SELF, InputHandle_t inputHandle, unsigned short usLeftSpeed, unsigned short usRightSpeed, unsigned short usLeftTriggerSpeed, unsigned short usRightTriggerSpeed)
{
	xlogf("%s(self = %p, inputHandle = %lld, usLeftSpeed = %d, usRightSpeed = %d,usLeftTriggerSpeed = %d, usRightTriggerSpeed = %d)\n",
	      __func__, self, inputHandle, usLeftSpeed, usRightSpeed, usLeftTriggerSpeed, usRightTriggerSpeed);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamInput_TriggerSimpleHapticEvent(SELF, InputHandle_t inputHandle, EControllerHapticLocation eHapticLocation, uint8 nIntensity, char nGainDB, uint8 nOtherIntensity, char nOtherGainDB)
{
	xlogf("%s(self = %p, inputHandle = %lld, eHapticLocation = %d, nIntensity = %d, nGainDB = %d, nOtherIntensity = %d, nOtherGainDB=%d)\n",
	      __func__, self, inputHandle, eHapticLocation, nIntensity, nGainDB, nOtherIntensity, nOtherGainDB);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamInput_Legacy_TriggerHapticPulse(SELF, InputHandle_t inputHandle, ESteamControllerPad eTargetPad, unsigned short usDurationMicroSec)
{
	xlogf("%s(self = %p, inputHandle = %lld, eTargetPad = %d, usDurationMicroSec = %d)\n",
	      __func__, self, inputHandle, eTargetPad, usDurationMicroSec);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamInput_Legacy_TriggerRepeatedHapticPulse(SELF, InputHandle_t inputHandle, ESteamControllerPad eTargetPad, unsigned short usDurationMicroSec, unsigned short usOffMicroSec, unsigned short unRepeat, unsigned int nFlags)
{
	xlogf("%s(self = %p, inputHandle = %lld, eTargetPad = %d, usDurationMicroSec = %d, usOffMicroSec = %d, unRepeat = %d, nFlags = %#x)\n",
	      __func__, self, inputHandle, eTargetPad, usDurationMicroSec, usOffMicroSec, unRepeat, nFlags);
}

S_CLASSAPI uint16 S_CLASSCALLTYPE
SteamAPI_ISteamInput_GetSessionInputConfigurationSettings(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}
