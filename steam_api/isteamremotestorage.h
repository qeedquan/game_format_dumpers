#pragma once

#include "steamtypes.h"
#include "steamclientpublic.h"

typedef uint64 UGCFileWriteStreamHandle_t;
typedef uint64 UGCHandle_t;
typedef uint64 PublishedFileUpdateHandle_t;
typedef uint64 PublishedFileId_t;

typedef struct SteamParamStringArray_t SteamParamStringArray_t;

struct SteamParamStringArray_t {
	const char **m_ppStrings;
	int32 m_nNumStrings;
};

// Ways to handle a synchronization conflict
typedef enum {
	k_EResolveConflictKeepClient = 1, // The local version of each file will be
	                                  // used to overwrite the server version
	k_EResolveConflictKeepServer = 2, // The server version of each file will be
	                                  // used to overwrite the local version
} EResolveConflict;

typedef enum {
	k_ERemoteStoragePlatformNone,
	k_ERemoteStoragePlatformWindows = (1 << 0),
	k_ERemoteStoragePlatformOSX = (1 << 1),
	k_ERemoteStoragePlatformPS3 = (1 << 2),
	k_ERemoteStoragePlatformLinux = (1 << 3),
	k_ERemoteStoragePlatformReserved2 = (1 << 4),
} ERemoteStoragePlatform;

#define k_ERemoteStoragePlatformAll = 0xfffffffful

typedef enum {
	k_ERemoteStoragePublishedFileVisibilityPublic,
	k_ERemoteStoragePublishedFileVisibilityFriendsOnly = 1,
	k_ERemoteStoragePublishedFileVisibilityPrivate = 2,
} ERemoteStoragePublishedFileVisibility;

typedef enum {
	k_EWorkshopFileTypeFirst,

	k_EWorkshopFileTypeCommunity,                   // normal Workshop item that can be subscribed
	                                                // to
	k_EWorkshopFileTypeMicrotransaction = 1,        // Workshop item that is meant to be
	                                                // voted on for the purpose of
	                                                // selling in-game
	k_EWorkshopFileTypeCollection = 2,              // a collection of Workshop or Greenlight items
	k_EWorkshopFileTypeArt = 3,                     // artwork
	k_EWorkshopFileTypeVideo = 4,                   // external video
	k_EWorkshopFileTypeScreenshot = 5,              // screenshot
	k_EWorkshopFileTypeGame = 6,                    // Greenlight game entry
	k_EWorkshopFileTypeSoftware = 7,                // Greenlight software entry
	k_EWorkshopFileTypeConcept = 8,                 // Greenlight concept
	k_EWorkshopFileTypeWebGuide = 9,                // Steam web guide
	k_EWorkshopFileTypeIntegratedGuide = 10,        // application integrated guide
	k_EWorkshopFileTypeMerch = 11,                  // Workshop merchandise meant to be voted on
	                                                // for the purpose of being sold
	k_EWorkshopFileTypeControllerBinding = 12,      // Steam Controller bindings
	k_EWorkshopFileTypeSteamworksAccessInvite = 13, // internal
	k_EWorkshopFileTypeSteamVideo = 14,             // Steam video
	k_EWorkshopFileTypeGameManagedItem = 15,        // managed completely by the game,
	                                                // not the user, and not shown on the
	                                                // web

	// Update k_EWorkshopFileTypeMax if you add values.
	k_EWorkshopFileTypeMax = 16
} EWorkshopFileType;

typedef enum {
	k_EWorkshopVoteUnvoted,
	k_EWorkshopVoteFor = 1,
	k_EWorkshopVoteAgainst = 2,
	k_EWorkshopVoteLater = 3,
} EWorkshopVote;

typedef enum {
	k_EWorkshopFileActionPlayed,
	k_EWorkshopFileActionCompleted = 1,
} EWorkshopFileAction;

typedef enum {
	k_EWorkshopEnumerationTypeRankedByVote,
	k_EWorkshopEnumerationTypeRecent = 1,
	k_EWorkshopEnumerationTypeTrending = 2,
	k_EWorkshopEnumerationTypeFavoritesOfFriends = 3,
	k_EWorkshopEnumerationTypeVotedByFriends = 4,
	k_EWorkshopEnumerationTypeContentByFriends = 5,
	k_EWorkshopEnumerationTypeRecentFromFollowedUsers = 6,
} EWorkshopEnumerationType;

typedef enum {
	k_EWorkshopVideoProviderNone,
	k_EWorkshopVideoProviderYoutube = 1
} EWorkshopVideoProvider;

typedef enum {
	// Keeps the file handle open unless the last byte is read.  You can use this
	// when reading large files (over 100MB) in sequential chunks.
	// If the last byte is read, this will behave the same as k_EUGCRead_Close.
	// Otherwise, it behaves the same as k_EUGCRead_ContinueReading.
	// This value maintains the same behavior as before the EUGCReadAction
	// parameter was introduced.
	k_EUGCRead_ContinueReadingUntilFinished,

	// Keeps the file handle open.  Use this when using UGCRead to seek to
	// different parts of the file.
	// When you are done seeking around the file, make a final call with
	// k_EUGCRead_Close to close it.
	k_EUGCRead_ContinueReading = 1,

	// Frees the file handle.  Use this when you're done reading the content.
	// To read the file from Steam again you will need to call UGCDownload again.
	k_EUGCRead_Close = 2,
} EUGCReadAction;

typedef enum {
	k_EUCMFilePrivacyStateInvalid = -1,

	k_EUCMFilePrivacyStateUnpublished = 0,
	k_EUCMFilePrivacyStatePublished = 1,

	k_EUCMFilePrivacyStatePrivate = 2,
	k_EUCMFilePrivacyStateFriendsOnly = 4,
	k_EUCMFilePrivacyStatePublic = 8,
	k_EUCMFilePrivacyStateAll = 14,
} EUCMFilePrivacyState;

enum {
	k_iCallbackRemoteStorageAppSyncedClient = k_iClientRemoteStorageCallbacks + 1,
	k_iCallbackRemoteStorageAppSyncedServer = k_iClientRemoteStorageCallbacks + 2,
	k_iCallbackRemoteStorageAppSyncProgress = k_iClientRemoteStorageCallbacks + 3,
};

typedef struct {
	AppId_t m_nAppID;
	EResult m_eResult;
	int m_unNumDownloads;
} RemoteStorageAppSyncedClient_t;

typedef struct {
	AppId_t m_nAppID;
	EResult m_eResult;
	int m_unNumUploads;
} RemoteStorageAppSyncedServer_t;

typedef struct {
	char m_rgchCurrentFile[k_cchFilenameMax]; // Current file being transferred
	AppId_t m_nAppID;                         // App this info relates to
	uint32 m_uBytesTransferredThisChunk;      // Bytes transferred this chunk
	double m_dAppPercentComplete;             // Percent complete that this app's transfers are
	bool m_bUploading;                        // if false, downloading
} RemoteStorageAppSyncProgress_t;

typedef enum {
	k_ERemoteStorageLocalFileChange_Invalid = 0,

	// The file was updated from another device
	k_ERemoteStorageLocalFileChange_FileUpdated = 1,

	// The file was deleted by another device
	k_ERemoteStorageLocalFileChange_FileDeleted = 2,
} ERemoteStorageLocalFileChange;

typedef enum {
	k_ERemoteStorageFilePathType_Invalid = 0,

	// The file is directly accessed by the game and this is the full path
	k_ERemoteStorageFilePathType_Absolute = 1,

	// The file is accessed via the ISteamRemoteStorage API and this is the filename
	k_ERemoteStorageFilePathType_APIFilename = 2,
} ERemoteStorageFilePathType;

typedef void ISteamRemoteStorage;

typedef struct CSteamRemoteStorage CSteamRemoteStorage;

struct CSteamRemoteStorage {
	CSteamBase base;
};

S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_FileWrite(SELF, const char *pchFile, const void *pvData, int32 cubData);
S_CLASSAPI int32 S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_FileRead(SELF, const char *pchFile, void *pvData, int32 cubDataToRead);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_FileWriteAsync(SELF, const char *pchFile, const void *pvData, uint32 cubData);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_FileReadAsync(SELF, const char *pchFile, uint32 nOffset, uint32 cubDataToRead);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_FileReadAsyncComplete(SELF, SteamAPICall_t nReadCall, void *pvData, uint32 cubDataToRead);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_FileForget(SELF, const char *pchFile);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_FileDelete(SELF, const char *pchFile);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_FileShare(SELF, const char *pchFile);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_SetSyncPlatforms(SELF, const char *pchFile, ERemoteStoragePlatform eRemoteStoragePlatform);
S_CLASSAPI UGCFileWriteStreamHandle_t S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_FileWriteStreamOpen(SELF, const char *pchFile);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_FileWriteStreamWriteChunk(SELF, UGCFileWriteStreamHandle_t writeHandle, const void *pvData, int32 cubData);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_FileWriteStreamClose(SELF, UGCFileWriteStreamHandle_t writeHandle);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_FileWriteStreamCancel(SELF, UGCFileWriteStreamHandle_t writeHandle);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_FileExists(SELF, const char *pchFile);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_FilePersisted(SELF, const char *pchFile);
S_CLASSAPI int32 S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_GetFileSize(SELF, const char *pchFile);
S_CLASSAPI int64 S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_GetFileTimestamp(SELF, const char *pchFile);
S_CLASSAPI ERemoteStoragePlatform S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_GetSyncPlatforms(SELF, const char *pchFile);
S_CLASSAPI int32 S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_GetFileCount(SELF);
S_CLASSAPI const char *S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_GetFileNameAndSize(SELF, int iFile, int32 *pnFileSizeInBytes);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_GetQuota32(SELF, int32 *pnTotalBytes, int32 *puAvailableBytes);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_GetQuota64(SELF, uint64 *pnTotalBytes, uint64 *puAvailableBytes);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_IsCloudEnabledForAccount(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_IsCloudEnabledForApp(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_SetCloudEnabledForApp(SELF, bool bEnabled);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_UGCDownload(SELF, UGCHandle_t hContent, uint32 uUnk); // Returns a RemoteStorageDownloadUGCResult_t callback
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_GetUGCDownloadProgress(SELF, UGCHandle_t hContent, int32 *pnBytesDownloaded, int32 *pnBytesExpected);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_GetUGCDetails(SELF, UGCHandle_t hContent, AppId_t *pnAppID, char **ppchName, int32 *pnFileSizeInBytes, CSteamID *pSteamIDOwner);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_GetUGCDownloadProgress(SELF, UGCHandle_t hContent, int32 *pnBytesDownloaded, int32 *pnBytesExpected);
S_CLASSAPI int32 S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_UGCRead(SELF, UGCHandle_t hContent, void *pvData, int32 cubDataToRead, uint32 uOffset, EUGCReadAction eAction);
S_CLASSAPI int32 S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_GetCachedUGCCount(SELF);
S_CLASSAPI UGCHandle_t S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_GetCachedUGCHandle(SELF, int32 iCachedContent);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_PublishWorkshopFile(SELF, const char *pchFile, const char *pchPreviewFile, AppId_t nConsumerAppId, const char *pchTitle, const char *pchDescription, ERemoteStoragePublishedFileVisibility eVisibility, SteamParamStringArray_t *pTags, EWorkshopFileType eWorkshopFileType);
S_CLASSAPI PublishedFileUpdateHandle_t S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_CreatePublishedFileUpdateRequest(SELF, PublishedFileId_t unPublishedFileId);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_UpdatePublishedFileFile(SELF, JobID_t hUpdateRequest, const char *pchFile);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_UpdatePublishedFilePreviewFile(SELF, JobID_t hUpdateRequest, const char *pchPreviewFile);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_UpdatePublishedFileTitle(SELF, JobID_t hUpdateRequest, const char *pchTitle);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_UpdatePublishedFileDescription(SELF, JobID_t hUpdateRequest, const char *pchDescription);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_UpdatePublishedFileVisibility(SELF, JobID_t hUpdateRequest, ERemoteStoragePublishedFileVisibility eVisibility);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_UpdatePublishedFileTags(SELF, JobID_t hUpdateRequest, SteamParamStringArray_t *pTags);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_CommitPublishedFileUpdate(SELF, JobID_t hUpdateRequest);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_GetPublishedFileDetails(SELF, PublishedFileId_t unPublishedFileId, uint32);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_DeletePublishedFile(SELF, PublishedFileId_t unPublishedFileId);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_EnumerateUserPublishedFiles(SELF, uint32 uStartIndex);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_SubscribePublishedFile(SELF, PublishedFileId_t unPublishedFileId);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_EnumerateUserSubscribedFiles(SELF, uint32 uStartIndex);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_UnsubscribePublishedFile(SELF, PublishedFileId_t unPublishedFileId);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_UpdatePublishedFileSetChangeDescription(SELF, JobID_t hUpdateRequest, const char *cszDescription);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_GetPublishedItemVoteDetails(SELF, PublishedFileId_t unPublishedFileId);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_UpdateUserPublishedItemVote(SELF, PublishedFileId_t unPublishedFileId, bool bVoteUp);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_GetUserPublishedItemVoteDetails(SELF, PublishedFileId_t unPublishedFileId);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_EnumerateUserSharedWorkshopFiles(SELF, CSteamID steamId, uint32 unStartIndex, SteamParamStringArray_t *pRequiredTags, SteamParamStringArray_t *pExcludedTags);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_PublishVideo(SELF, EWorkshopVideoProvider eVideoProvider, const char *cszVideoAccountName, const char *cszVideoIdentifier, const char *cszFileName, AppId_t nConsumerAppId, const char *cszTitle, const char *cszDescription, ERemoteStoragePublishedFileVisibility eVisibility, SteamParamStringArray_t *pTags);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_SetUserPublishedFileAction(SELF, PublishedFileId_t unPublishedFileId, EWorkshopFileAction eAction);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_EnumeratePublishedFilesByUserAction(SELF, EWorkshopFileAction eAction, uint32 uStartIndex);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_EnumeratePublishedWorkshopFiles(SELF, EWorkshopEnumerationType eType, uint32 uStartIndex, uint32 cDays, uint32 cCount, SteamParamStringArray_t *pTags, SteamParamStringArray_t *pUserTags);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_UGCDownloadToLocation(SELF, UGCHandle_t hContent, const char *cszLocation, uint32 unPriority);

S_CLASSAPI int32 S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_GetLocalFileChangeCount(SELF);
S_CLASSAPI const char *S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_GetLocalFileChange(SELF, int iFile, ERemoteStorageLocalFileChange *pEChangeType, ERemoteStorageFilePathType *pEFilePathType);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_BeginFileWriteBatch(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamRemoteStorage_EndFileWriteBatch(SELF);