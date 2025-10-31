#include "steam.h"

IVRSystem *
VR_Init(EVRInitError *peError, EVRApplicationType eApplicationType)
{
	xlogf("%s(peError = %p, eApplicationType = %d)\n", __func__, peError, eApplicationType);
	return NULL;
}

void *
VR_GetGenericInterface(const char *pchInterfaceVersion, EVRInitError *peError)
{
	xlogf("%s(pchInterfaceVersion = %p, peError = %p)\n", __func__, pchInterfaceVersion, peError);
	return NULL;
}

void *
VR_GetControlPanel(void)
{
	xlogf("%s()\n", __func__);
	return NULL;
}

const char *
VR_GetStringForHmdError(EVRInitError error)
{
	xlogf("%s(error = %d)\n", __func__, error);
	return "Unknown Error";
}

bool
VR_IsHmdPresent(void)
{
	xlogf("%s()\n", __func__);
	return false;
}

bool
VR_IsRuntimeInstalled(void)
{
	xlogf("%s()\n", __func__);
	return false;
}

void
VR_Shutdown(void)
{
	xlogf("%s()\n", __func__);
}