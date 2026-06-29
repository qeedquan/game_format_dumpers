#include "steam.h"

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_Init(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_Shutdown(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return true;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_CreateBrowser(SELF, const char *pchUserAgent, const char *pchUserCSS)
{
	xlogf("%s(self = %p, pchUserAgent = %s, pchUserCSS = %s)\n", __func__, self, pchUserAgent, pchUserCSS);
	return 1;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_RemoveBrowser(SELF, HHTMLBrowser unBrowserHandle)
{
	xlogf("%s(self = %p, unBrowserHandle = %d)\n", __func__, self, unBrowserHandle);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_LoadURL(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_SetSize(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_StopLoad(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_Reload(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_GoBack(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_SetVerticalScroll(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_GoForward(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_AddHeader(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_ExecuteJavascript(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_MouseUp(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_MouseDown(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_MouseDoubleClick(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_MouseMove(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_MouseWheel(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_KeyDown(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_KeyUp(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_KeyChar(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_SetHorizontalScroll(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_SetKeyFocus(SELF, HHTMLBrowser unBrowserHandle, bool bHasKeyFocus)
{
	xlogf("%s(self = %p, unBrowserHandle = %d, bHasKeyFocus = %d)\n", __func__, self, unBrowserHandle, bHasKeyFocus);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_ViewSource(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_CopyToClipboard(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_PasteFromClipboard(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_Find(SELF, HHTMLBrowser unBrowserHandle, const char *pchSearchStr, bool bCurrentlyInFind, bool bReverse)
{
	xlogf("%s(self = %p,  unBrowserHandle = %d, pchSearchStr = %s, bCurrentlyInFind = %d, bReverse = %d)\n", __func__, self, unBrowserHandle, pchSearchStr, bCurrentlyInFind, bReverse);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_StopFind(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_GetLinkAtPosition(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_SetCookie(SELF, const char *pchHostname, const char *pchKey, const char *pchValue, const char *pchPath, RTime32 nExpires, bool bSecure, bool bHTTPOnly)
{
	xlogf("%s(self = %p, pchHostname = %s, pchKey = %s, pchValue = %s, pchPath = %s, nExpires = %d, bSecure = %d, bHTTPOnly = %d)\n", __func__, self, pchHostname, pchKey, pchValue, pchPath, nExpires, bSecure, bHTTPOnly);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_SetPageScaleFactor(SELF, HHTMLBrowser unBrowserHandle, float flZoom, int nPointX, int nPointY)
{
	xlogf("%s(self = %p, unBrowserHandle = %d, flZoom = %f, nPointX = %d, nPointY = %d)\n", __func__, self, unBrowserHandle, flZoom, nPointX, nPointY);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_SetBackgroundMode(SELF, HHTMLBrowser unBrowserHandle, bool bBackgroundMode)
{
	xlogf("%s(self = %p, unBrowserHandle = %d, bBackgroundMode = %d)\n", __func__, self, unBrowserHandle, bBackgroundMode);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_AllowStartRequest(SELF, HHTMLBrowser unBrowserHandle, bool bAllowed)
{
	xlogf("%s(self = %p, unBrowserHandle = %d, bAllowed = %d)\n", __func__, self, unBrowserHandle, bAllowed);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_JSDialogResponse(SELF, HHTMLBrowser unBrowserHandle, bool bResult)
{
	xlogf("%s(self = %p, unBrowserHandle = %d, bResult = %d)\n", __func__, self, unBrowserHandle, bResult);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_FileLoadDialogResponse(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_DestructISteamHTMLSurface(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_SetDPIScalingFactor(SELF, HHTMLBrowser unBrowserHandle, float flDPIScaling)
{
	xlogf("%s(self = %p, unBrowserHandle = %d, flDPIScaling = %.3f)\n", __func__, self, unBrowserHandle, flDPIScaling);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamHTMLSurface_OpenDeveloperTools(SELF, HHTMLBrowser unBrowserHandle)
{
	xlogf("%s(self = %p, unBrowserHandle = %d)\n", __func__, self, unBrowserHandle);
}
