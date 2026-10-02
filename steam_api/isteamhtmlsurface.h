#pragma once

#include "steamtypes.h"

typedef uint32 HHTMLBrowser;

typedef enum {
	dc_user = 0,
	dc_none,
	dc_arrow,
	dc_ibeam,
	dc_hourglass,
	dc_waitarrow,
	dc_crosshair,
	dc_up,
	dc_sizenw,
	dc_sizese,
	dc_sizene,
	dc_sizesw,
	dc_sizew,
	dc_sizee,
	dc_sizen,
	dc_sizes,
	dc_sizewe,
	dc_sizens,
	dc_sizeall,
	dc_no,
	dc_hand,
	dc_blank, // don't show any custom cursor, just use your default
	dc_middle_pan,
	dc_north_pan,
	dc_north_east_pan,
	dc_east_pan,
	dc_south_east_pan,
	dc_south_pan,
	dc_south_west_pan,
	dc_west_pan,
	dc_north_west_pan,
	dc_alias,
	dc_cell,
	dc_colresize,
	dc_copycur,
	dc_verticaltext,
	dc_rowresize,
	dc_zoomin,
	dc_zoomout,
	dc_help,
	dc_custom,

	dc_last, // custom cursors start from this value and up
} EMouseCursor;

typedef enum {
	k_eHTMLKeyModifier_None = 0,
	k_eHTMLKeyModifier_AltDown = 1 << 0,
	k_eHTMLKeyModifier_CtrlDown = 1 << 1,
	k_eHTMLKeyModifier_ShiftDown = 1 << 2,
} EHTMLKeyModifiers;

typedef void ISteamHTMLSurface;

typedef struct CSteamHTMLSurface CSteamHTMLSurface;

struct CSteamHTMLSurface {
	CSteamBase base;
};

S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_Init(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_Shutdown(SELF);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_CreateBrowser(SELF, const char *pchUserAgent, const char *pchUserCSS);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_RemoveBrowser(SELF, HHTMLBrowser unBrowserHandle);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_LoadURL(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_SetSize(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_StopLoad(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_Reload(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_GoBack(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_SetVerticalScroll(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_GoForward(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_AddHeader(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_ExecuteJavascript(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_MouseUp(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_MouseDown(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_MouseDoubleClick(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_MouseMove(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_MouseWheel(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_KeyDown(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_KeyUp(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_KeyChar(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_SetHorizontalScroll(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_SetKeyFocus(SELF, HHTMLBrowser unBrowserHandle, bool bHasKeyFocus);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_ViewSource(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_CopyToClipboard(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_PasteFromClipboard(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_Find(SELF, HHTMLBrowser unBrowserHandle, const char *pchSearchStr, bool bCurrentlyInFind, bool bReverse);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_StopFind(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_GetLinkAtPosition(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_SetCookie(SELF, const char *pchHostname, const char *pchKey, const char *pchValue, const char *pchPath, RTime32 nExpires, bool bSecure, bool bHTTPOnly);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_SetPageScaleFactor(SELF, HHTMLBrowser unBrowserHandle, float flZoom, int nPointX, int nPointY);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_SetBackgroundMode(SELF, HHTMLBrowser unBrowserHandle, bool bBackgroundMode);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_AllowStartRequest(SELF, HHTMLBrowser unBrowserHandle, bool bAllowed);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_JSDialogResponse(SELF, HHTMLBrowser unBrowserHandle, bool bResult);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_FileLoadDialogResponse(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_SetDPIScalingFactor(SELF, HHTMLBrowser unBrowserHandle, float flDPIScaling);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamHTMLSurface_OpenDeveloperTools(SELF, HHTMLBrowser unBrowserHandle);
