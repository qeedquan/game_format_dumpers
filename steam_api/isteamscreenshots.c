#include "steam.h"

S_CLASSAPI ScreenshotHandle S_CLASSCALLTYPE
SteamAPI_ISteamScreenshots_WriteScreenshot(SELF, void *pubRGB, uint32 cubRGB, int nWidth, int nHeight)
{
	xlogf("%s(self = %p, pubRGB = %p, cubRGB = %d, nWidth = %d, nHeight = %d)\n", __func__, self, pubRGB, cubRGB, nWidth, nHeight);
	return 1;
}

S_CLASSAPI ScreenshotHandle S_CLASSCALLTYPE
SteamAPI_ISteamScreenshots_AddScreenshotToLibrary(SELF, const char *pchJpegOrTGAFilename, const char *pchJpegOrTGAThumbFilename, int nWidth, int nHeight)
{
	xlogf("%s(self = %p, pchJpegOrTGAFilename = %s, pchJpegOrTGAThumbFilename = %s, nWidth = %d, nHeight = %d)\n", __func__, self, pchJpegOrTGAFilename, pchJpegOrTGAThumbFilename, nWidth, nHeight);
	return 1;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamScreenshots_TriggerScreenshot(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamScreenshots_HookScreenshots(SELF, bool bHook)
{
	xlogf("%s(self = %p, bHook = %d)\n", __func__, self, bHook);
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamScreenshots_SetLocation(SELF, ScreenshotHandle hScreenshot, const char *pchLocation)
{
	xlogf("%s(self = %p, hScreenshot = %d, pchLocation = %s)\n", __func__, self, hScreenshot, pchLocation);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamScreenshots_TagUser(SELF, ScreenshotHandle hScreenshot, CSteamID steamID)
{
	xlogf("%s(self = %p, hScreenshot = %d, steamID = %llu)\n", __func__, self, hScreenshot, steamID.m_gameID);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamScreenshots_TagPublishedFile(SELF, ScreenshotHandle hScreenshot, PublishedFileId_t unPublishedFileId)
{
	xlogf("%s(self = %p, hScreenshot = %d, unPublishedFileId = %llu)\n", __func__, self, hScreenshot, unPublishedFileId);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamScreenshots_IsScreenshotsHooked(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return true;
}

S_CLASSAPI ScreenshotHandle S_CLASSCALLTYPE
SteamAPI_ISteamScreenshots_AddVRScreenshotToLibrary(SELF, EVRScreenshotType eType, const char *pchFilename, const char *pchVRFilename)
{
	xlogf("%s(self = %p, eType = %d, pchFilename = %s, pchVRFilename = %s)\n", __func__, self, eType, pchFilename, pchVRFilename);
	return 0;
}
