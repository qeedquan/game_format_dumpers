#include "steam.h"

S_CLASSAPI bool S_CLASSCALLTYPE
SteamController_Init(void)
{
	xlogf("%s()\n", __func__);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamController_Shutdown(void)
{
	xlogf("%s()\n", __func__);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamController_Init(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamController_Shutdown(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return true;
}

S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamController_RunFrame(SELF)
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

S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamController_ActivateActionSet(SELF)
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

S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamController_StopAnalogActionMomentum(SELF)
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
SteamController_GetControllerState(uint32_t index, void *state)
{
	xlogf("%s(index = %d, state = %p)\n", __func__, index, state);
	return false;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamController_SetOverrideMode(const char *pchMode)
{
	xlogf("%s(pchMode = %s)\n", __func__, pchMode);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamController_TriggerHapticPulse(ControllerHandle_t controllerHandle, ESteamControllerPad eTargetPad, unsigned short usDurationMicroSec)
{
	xlogf("%s(controllerHandle = %llu, eTargetPad = %d, usDurationMicroSec = %d)\n", __func__, controllerHandle, eTargetPad, usDurationMicroSec);
}
