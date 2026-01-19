#include "steam.h"

bool
SteamController_Init(void)
{
	xlogf("%s()\n", __func__);
	return true;
}

bool
SteamController_Shutdown(void)
{
	xlogf("%s()\n", __func__);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamController_Init(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamController_Shutdown(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return true;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamController_RunFrame(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI int32 S_CLASSCALLTYPE
SteamAPI_ISteamController_GetConnectedControllers(SELF, ControllerHandle_t *handleOut)
{
	xlogf("%s(self = %p, handleOut = %p)\n", __func__, self, handleOut);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamController_ShowBindingPanel(SELF, ControllerHandle_t controllerHandle)
{
	xlogf("%s(self = %p, controllerHandle = %llu)\n", __func__, self, controllerHandle);
	return true;
}

S_CLASSAPI ControllerActionSetHandle_t S_CLASSCALLTYPE
SteamAPI_ISteamController_GetActionSetHandle(SELF, const char *pszActionSetName)
{
	xlogf("%s(self = %p, pszActionSetName = %s)\n", __func__, self, pszActionSetName);
	return 0;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamController_ActivateActionSet(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI ControllerActionSetHandle_t S_CLASSCALLTYPE
SteamAPI_ISteamController_GetCurrentActionSet(SELF, ControllerHandle_t controllerHandle)
{
	xlogf("%s(self = %p, controllerHandle = %llu)\n", __func__, self, controllerHandle);
	return 0;
}

S_CLASSAPI ControllerActionSetHandle_t S_CLASSCALLTYPE
SteamAPI_ISteamController_GetDigitalActionHandle(SELF, const char *pszActionSetName)
{
	xlogf("%s(self = %p, pszActionSetName = %s)\n", __func__, self, pszActionSetName);
	return 0;
}

S_CLASSAPI ControllerDigitalActionData_t S_CLASSCALLTYPE
SteamAPI_ISteamController_GetDigitalActionData(SELF, ControllerHandle_t controllerHandle, ControllerDigitalActionHandle_t digitalActionHandle)
{
	ControllerDigitalActionData_t c = {0};

	xlogf("%s(self = %p, controllerHandle = %llu, digitalActionHandle = %llu)\n", __func__, self, controllerHandle, digitalActionHandle);
	return c;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamController_GetDigitalActionOrigins(SELF, ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetHandle, ControllerDigitalActionHandle_t digitalActionHandle, EControllerActionOrigin *originsOut)
{
	xlogf("%s(self = %p, controllerHandle = %llu, actionSetHandle = %llu, digitalActionHandle = %llu, originsOut = %p)\n", __func__, self, controllerHandle, actionSetHandle, digitalActionHandle, originsOut);
	return 0;
}

S_CLASSAPI ControllerAnalogActionHandle_t S_CLASSCALLTYPE
SteamAPI_ISteamController_GetAnalogActionHandle(SELF, const char *pszActionName)
{
	ControllerAnalogActionHandle_t c = {0};
	xlogf("%s(self = %p, pszActionSetName = %s)\n", __func__, self, pszActionName);
	return c;
}

S_CLASSAPI ControllerAnalogActionData_t S_CLASSCALLTYPE
SteamAPI_ISteamController_GetAnalogActionData(SELF, ControllerHandle_t controllerHandle, ControllerAnalogActionHandle_t analogActionHandle)
{
	ControllerAnalogActionData_t c = {0};
	xlogf("%s(self = %p, controllerHandle = %llu, analogActionHandle = %llu)\n", __func__, self, controllerHandle, analogActionHandle);
	return c;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamController_GetAnalogActionOrigins(SELF, ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetHandle, ControllerAnalogActionHandle_t analogActionHandle, EControllerActionOrigin *originsOut)
{
	xlogf("%s(self = %p, controllerHandle = %llu, actionSetHandle = %llu, analogActionHandle = %llu, originsOut = %p)\n", __func__, self, controllerHandle, actionSetHandle, analogActionHandle, originsOut);
	return 0;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamController_StopAnalogActionMomentum(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamController_TriggerHapticPulse(SELF, ControllerHandle_t controllerHandle, ESteamControllerPad eTargetPad, unsigned short usDurationMicroSec)
{
	xlogf("%s(self = %p, controllerHandle = %llu, eTargetPad = %d, usDurationMicroSec = %d)\n", __func__, self, controllerHandle, eTargetPad, usDurationMicroSec);
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamController_GetControllerState(SELF, uint32_t index, void *state)
{
	xlogf("%s(self = %p, index = %d, state = %p)\n", __func__, self, index, state);
	return false;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamController_SetOverrideMode(SELF, const char *pchMode)
{
	xlogf("%s(self = %p, pchMode = %s)\n", __func__, self, pchMode);
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamController_GetControllerState(SELF, uint32_t index, void *state)
{
	xlogf("%s(self = %p, index = %d, state = %p)\n", __func__, self, index, state);
	return false;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamController_SetOverrideMode(SELF, const char *pchMode)
{
	xlogf("%s(self = %p, pchMode = %s)\n", __func__, self, pchMode);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamController_TriggerHapticPulse(SELF, ControllerHandle_t controllerHandle, ESteamControllerPad eTargetPad, unsigned short usDurationMicroSec)
{
	xlogf("%s(self = %p, controllerHandle = %llu, eTargetPad = %d, usDurationMicroSec = %d)\n",
	      __func__, self, controllerHandle, eTargetPad, usDurationMicroSec);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamController_ActivateActionSetLayer(SELF, ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetLayerHandle)
{
	xlogf("%s(self = %p, controllerHandle = %llu, actionSetLayerHandle = %llx)\n",
	      __func__, self, controllerHandle, actionSetLayerHandle);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamController_DeactivateActionSetLayer(SELF, ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetLayerHandle)
{
	xlogf("%s(self = %p, controllerHandle = %llu, actionSetLayerHandle = %llx)\n",
	      __func__, self, controllerHandle, actionSetLayerHandle);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamController_DeactivateAllActionSetLayers(SELF, ControllerHandle_t controllerHandle)
{
	xlogf("%s(self = %p, controllerHandle = %llu)\n",
	      __func__, self, controllerHandle);
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamController_GetActiveActionSetLayers(SELF, ControllerHandle_t controllerHandle, ControllerActionSetHandle_t *handlesOut)
{
	xlogf("%s(self = %p, controllerHandle = %llu, handlesOut = %p)\n",
	      __func__, self, controllerHandle, handlesOut);
	return 0;
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamController_GetGlyphForActionOrigin(SELF, EControllerActionOrigin eOrigin)
{
	xlogf("%s(self = %p, eOrigin = %d)\n", __func__, self, eOrigin);
	return "?";
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamController_GetStringForActionOrigin(SELF, EControllerActionOrigin eOrigin)
{
	xlogf("%s(self = %p, eOrigin = %d)\n", __func__, self, eOrigin);
	return "?";
}

S_CLASSAPI ControllerMotionData_t S_CLASSCALLTYPE
SteamAPI_ISteamController_GetMotionData(SELF, ControllerHandle_t controllerHandle)
{
	ControllerMotionData_t ret = {0};
	xlogf("%s(self = %p, controllerHandle = %llu)\n", __func__, self, controllerHandle);
	return ret;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamController_TriggerRepeatedHapticPulse(SELF, ControllerHandle_t controllerHandle, ESteamControllerPad eTargetPad, unsigned short usDurationMicroSec)
{
	xlogf("%s(self = %p, controllerHandle = %llu, eTargetPad = %d, usDurationMicroSec = %d)\n",
	      __func__, self, controllerHandle, eTargetPad, usDurationMicroSec);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamController_TriggerVibration(SELF, ControllerHandle_t controllerHandle, unsigned short usLeftSpeed, unsigned short usRightSpeed)
{
	xlogf("%s(self = %p, controllerHandle = %llu, usLeftSpeed = %d, usRightSpeed = %d)\n",
	      __func__, self, controllerHandle, usLeftSpeed, usRightSpeed);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamController_SetLEDColor(SELF, ControllerHandle_t controllerHandle, uint8 nColorR, uint8 nColorG, uint8 nColorB, unsigned int nFlags)
{
	xlogf("%s(self = %p, controllerHandle = %llu, nColorR = %d, nColorG = %d, nColorB = %d, nFlags = %d)\n",
	      __func__, self, controllerHandle, nColorR, nColorG, nColorB, nFlags);
}

S_CLASSAPI ESteamInputType S_CLASSCALLTYPE
SteamAPI_ISteamController_GetInputTypeForHandle(SELF, ControllerHandle_t controllerHandle)
{
	xlogf("%s(self = %p, controllerHandle = %llu)\n",
	      __func__, self, controllerHandle);
	return 0;
}

S_CLASSAPI ControllerHandle_t S_CLASSCALLTYPE
SteamAPI_ISteamController_GetControllerForGamepadIndex(SELF, int nIndex)
{
	xlogf("%s(self = %p, nIndex = %d)\n", __func__, self, nIndex);
	return 0;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamController_GetGamepadIndexForController(SELF, ControllerHandle_t ulControllerHandle)
{
	xlogf("%s(self = %p, controllerHandle = %llu)\n",
	      __func__, self, ulControllerHandle);
	return 0;
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamController_GetStringForXboxOrigin(SELF, EXboxOrigin eOrigin)
{
	xlogf("%s(self = %p, eOrigin = %d)\n", __func__, self, eOrigin);
	return "?";
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamController_GetGlyphForXboxOrigin(SELF, EXboxOrigin eOrigin)
{
	xlogf("%s(self = %p, eOrigin = %d)\n", __func__, self, eOrigin);
	return "?";
}

S_CLASSAPI EControllerActionOrigin S_CLASSCALLTYPE
SteamAPI_ISteamController_GetActionOriginFromXboxOrigin_(SELF, ControllerHandle_t controllerHandle, EXboxOrigin eOrigin)
{
	xlogf("%s(self = %p, controllerHandle = %lld, eOrigin = %d)\n",
	      __func__, self, controllerHandle, eOrigin);
	return 0;
}

S_CLASSAPI EControllerActionOrigin S_CLASSCALLTYPE
SteamAPI_ISteamController_TranslateActionOrigin(SELF, ESteamInputType eDestinationInputType, EControllerActionOrigin eSourceOrigin)
{
	xlogf("%s(self = %p, eDestinationInputType = %d, eSourceOrigin = %d)\n",
	      __func__, self, eDestinationInputType, eSourceOrigin);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamController_GetControllerBindingRevision(SELF, ControllerHandle_t controllerHandle, int *pMajor, int *pMinor)
{
	xlogf("%s(self = %p, controllerHandle = %lld, pMajor = %p, pMinor = %p)\n",
	      __func__, self, controllerHandle, pMajor, pMinor);
	return false;
}