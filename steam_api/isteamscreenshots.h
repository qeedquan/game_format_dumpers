#pragma once

typedef void ISteamScreenshots;

typedef struct CSteamScreenshots CSteamScreenshots;

struct CSteamScreenshots {
	CSteamBase base;
};

typedef uint32 ScreenshotHandle;

#define INVALID_SCREENSHOT_HANDLE 0

enum {
	k_nScreenshotMaxTaggedUsers = 32,
	k_cubUFSTagTypeMax = 255,
	k_cubUFSTagValueMax = 255,
	k_ScreenshotThumbWidth = 200
};

typedef struct {
	ScreenshotHandle m_hLocal;
	EResult m_eResult;
} ScreenshotReady_t;

typedef struct {
	double m_dPercentScreenshot;
	double m_dPercentBatch;
	int32 m_nFailed;
} ScreenshotUploadProgress_t;

typedef struct {
	ScreenshotHandle m_hLocal;
	CGameID m_gameID;
	RTime32 m_timeCreated;
	uint32 m_nWidth;
	uint32 m_nHeight;
} ScreenshotWritten_t;

typedef struct {
	ScreenshotHandle m_hLocal;
	CGameID m_gameID;
	UGCHandle_t m_hFile;
	RTime32 m_timeCreated;
	uint32 m_nWidth;
	uint32 m_nHeight;
	EUCMFilePrivacyState m_ePrivacy;
	char m_pchCaption[540];
	uint8 pubUnknownData[28];
} ScreenshotUploaded_t;

typedef struct {
	int m_nAttempted;
	int m_nResultsOK;
} ScreenshotBatchComplete_t;

typedef struct {
	EResult m_eResult;
	ScreenshotHandle m_hLocal;
	CGameID m_gameID;
} ScreenshotDeleted_t;

typedef struct {
	CGameID m_gameID;
} ScreenshotTriggered_t;

typedef uint32 ScreenshotHandle;

#define INVALID_SCREENSHOT_HANDLE 0

typedef enum {
	k_EVRScreenshotType_None = 0,
	k_EVRScreenshotType_Mono = 1,
	k_EVRScreenshotType_Stereo = 2,
	k_EVRScreenshotType_MonoCubemap = 3,
	k_EVRScreenshotType_MonoPanorama = 4,
	k_EVRScreenshotType_StereoPanorama = 5
} EVRScreenshotType;

S_CLASSAPI ScreenshotHandle S_CLASSCALLTYPE SteamAPI_ISteamScreenshots_WriteScreenshot(SELF, void *pubRGB, uint32 cubRGB, int nWidth, int nHeight);
S_CLASSAPI ScreenshotHandle S_CLASSCALLTYPE SteamAPI_ISteamScreenshots_AddScreenshotToLibrary(SELF, const char *pchJpegOrTGAFilename, const char *pchJpegOrTGAThumbFilename, int nWidth, int nHeight);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamScreenshots_TriggerScreenshot(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamScreenshots_HookScreenshots(SELF, bool bHook);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamScreenshots_SetLocation(SELF, ScreenshotHandle hScreenshot, const char *pchLocation);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamScreenshots_TagUser(SELF, ScreenshotHandle hScreenshot, CSteamID steamID);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamScreenshots_TagPublishedFile(SELF, ScreenshotHandle hScreenshot, PublishedFileId_t unPublishedFileId);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamScreenshots_IsScreenshotsHooked(SELF);
S_CLASSAPI ScreenshotHandle S_CLASSCALLTYPE SteamAPI_ISteamScreenshots_AddVRScreenshotToLibrary(SELF, EVRScreenshotType eType, const char *pchFilename, const char *pchVRFilename);
