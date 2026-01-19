#pragma once

#include "steamtypes.h"

typedef uint64 UGCQueryHandle_t;
typedef uint64 UGCUpdateHandle_t;

// Different lists of published UGC for a user.
// If the current logged in user is different than the specified user, then some options may not be allowed.
typedef enum {
	k_EUserUGCList_Published,
	k_EUserUGCList_VotedOn,
	k_EUserUGCList_VotedUp,
	k_EUserUGCList_VotedDown,
	k_EUserUGCList_WillVoteLater,
	k_EUserUGCList_Favorited,
	k_EUserUGCList_Subscribed,
	k_EUserUGCList_UsedOrPlayed,
	k_EUserUGCList_Followed,
} EUserUGCList;

// Matching UGC types for queries
typedef enum {
	k_EUGCMatchingUGCType_Items = 0, // both mtx items and ready-to-use items
	k_EUGCMatchingUGCType_Items_Mtx = 1,
	k_EUGCMatchingUGCType_Items_ReadyToUse = 2,
	k_EUGCMatchingUGCType_Collections = 3,
	k_EUGCMatchingUGCType_Artwork = 4,
	k_EUGCMatchingUGCType_Videos = 5,
	k_EUGCMatchingUGCType_Screenshots = 6,
	k_EUGCMatchingUGCType_AllGuides = 7, // both web guides and integrated guides
	k_EUGCMatchingUGCType_WebGuides = 8,
	k_EUGCMatchingUGCType_IntegratedGuides = 9,
	k_EUGCMatchingUGCType_UsableInGame = 10, // ready-to-use items and integrated guides
	k_EUGCMatchingUGCType_ControllerBindings = 11,
	k_EUGCMatchingUGCType_GameManagedItems = 12, // game managed items (not managed by users)
} EUGCMatchingUGCType;

// Sort order for user published UGC lists (defaults to creation order descending)
typedef enum {
	k_EUserUGCListSortOrder_CreationOrderDesc,
	k_EUserUGCListSortOrder_CreationOrderAsc,
	k_EUserUGCListSortOrder_TitleAsc,
	k_EUserUGCListSortOrder_LastUpdatedDesc,
	k_EUserUGCListSortOrder_SubscriptionDateDesc,
	k_EUserUGCListSortOrder_VoteScoreDesc,
	k_EUserUGCListSortOrder_ForModeration,
} EUserUGCListSortOrder;

// Combination of sorting and filtering for queries across all UGC
typedef enum {
	k_EUGCQuery_RankedByVote = 0,
	k_EUGCQuery_RankedByPublicationDate = 1,
	k_EUGCQuery_AcceptedForGameRankedByAcceptanceDate = 2,
	k_EUGCQuery_RankedByTrend = 3,
	k_EUGCQuery_FavoritedByFriendsRankedByPublicationDate = 4,
	k_EUGCQuery_CreatedByFriendsRankedByPublicationDate = 5,
	k_EUGCQuery_RankedByNumTimesReported = 6,
	k_EUGCQuery_CreatedByFollowedUsersRankedByPublicationDate = 7,
	k_EUGCQuery_NotYetRated = 8,
	k_EUGCQuery_RankedByTotalVotesAsc = 9,
	k_EUGCQuery_RankedByVotesUp = 10,
	k_EUGCQuery_RankedByTextSearch = 11,
	k_EUGCQuery_RankedByTotalUniqueSubscriptions = 12,
} EUGCQuery;

typedef enum {
	k_EItemUpdateStatusInvalid = 0,              // The item update handle was invalid, job might be finished, listen too SubmitItemUpdateResult_t
	k_EItemUpdateStatusPreparingConfig = 1,      // The item update is processing configuration data
	k_EItemUpdateStatusPreparingContent = 2,     // The item update is reading and processing content files
	k_EItemUpdateStatusUploadingContent = 3,     // The item update is uploading content changes to Steam
	k_EItemUpdateStatusUploadingPreviewFile = 4, // The item update is uploading new preview file image
	k_EItemUpdateStatusCommittingChanges = 5     // The item update is committing all changes
} EItemUpdateStatus;

static const uint32 kNumUGCResultsPerPage = 50;
static const uint32 k_cchDeveloperMetadataMax = 5000;

// Details for a single published file/UGC
typedef struct {
	PublishedFileId_t m_nPublishedFileId;
	EResult m_eResult;                                            // The result of the operation.
	EWorkshopFileType m_eFileType;                                // Type of the file
	AppId_t m_nCreatorAppID;                                      // ID of the app that created this file.
	AppId_t m_nConsumerAppID;                                     // ID of the app that will consume this file.
	char m_rgchTitle[k_cchPublishedDocumentTitleMax];             // title of document
	char m_rgchDescription[k_cchPublishedDocumentDescriptionMax]; // description of document
	uint64 m_ulSteamIDOwner;                                      // Steam ID of the user who created this content.
	uint32 m_rtimeCreated;                                        // time when the published file was created
	uint32 m_rtimeUpdated;                                        // time when the published file was last updated
	uint32 m_rtimeAddedToUserList;                                // time when the user added the published file to their list (not always applicable)
	ERemoteStoragePublishedFileVisibility m_eVisibility;          // visibility
	bool m_bBanned;                                               // whether the file was banned
	bool m_bAcceptedForUse;                                       // developer has specifically flagged this item as accepted in the Workshop
	bool m_bTagsTruncated;                                        // whether the list of tags was too long to be returned in the provided buffer
	char m_rgchTags[k_cchTagListMax];                             // comma separated list of all tags associated with this file
	// file/url information
	UGCHandle_t m_hFile;                      // The handle of the primary file
	UGCHandle_t m_hPreviewFile;               // The handle of the preview file
	char m_pchFileName[k_cchFilenameMax];     // The cloud filename of the primary file
	int32 m_nFileSize;                        // Size of the primary file
	int32 m_nPreviewFileSize;                 // Size of the preview file
	char m_rgchURL[k_cchPublishedFileURLMax]; // URL (for a video or a website)
	// voting information
	uint32 m_unVotesUp;   // number of votes up
	uint32 m_unVotesDown; // number of votes down
	float m_flScore;      // calculated score
	// collection details
	uint32 m_unNumChildren;
} SteamUGCDetails_t;

typedef enum {
	k_EItemStatistic_NumSubscriptions = 0,
	k_EItemStatistic_NumFavorites = 1,
	k_EItemStatistic_NumFollowers = 2,
	k_EItemStatistic_NumUniqueSubscriptions = 3,
	k_EItemStatistic_NumUniqueFavorites = 4,
	k_EItemStatistic_NumUniqueFollowers = 5,
	k_EItemStatistic_NumUniqueWebsiteViews = 6,
	k_EItemStatistic_ReportScore = 7,
} EItemStatistic;

typedef enum {
	k_EItemPreviewType_Image = 0,                          // standard image file expected (e.g. jpg, png, gif, etc.)
	k_EItemPreviewType_YouTubeVideo = 1,                   // video id is stored
	k_EItemPreviewType_Sketchfab = 2,                      // model id is stored
	k_EItemPreviewType_EnvironmentMap_HorizontalCross = 3, // standard image file expected - cube map in the layout
	                                                       // +---+---+-------+
	                                                       // |   |Up |       |
	                                                       // +---+---+---+---+
	                                                       // | L | F | R | B |
	                                                       // +---+---+---+---+
	                                                       // |   |Dn |       |
	                                                       // +---+---+---+---+
	k_EItemPreviewType_EnvironmentMap_LatLong = 4,         // standard image file expected
	k_EItemPreviewType_ReservedMax = 255,                  // you can specify your own types above this value
} EItemPreviewType;

typedef void ISteamUGC;

typedef struct CSteamUGC CSteamUGC;

struct CSteamUGC {
	CSteamBase base;
};

S_CLASSAPI UGCQueryHandle_t S_CLASSCALLTYPE SteamAPI_ISteamUGC_CreateQueryUserUGCRequest(SELF, AccountID_t unAccountID, EUserUGCList eListType, EUGCMatchingUGCType eMatchingUGCType, EUserUGCListSortOrder eSortOrder, AppId_t nCreatorAppID, AppId_t nConsumerAppID, uint32 unPage);
S_CLASSAPI UGCQueryHandle_t S_CLASSCALLTYPE SteamAPI_ISteamUGC_CreateQueryAllUGCRequest(SELF, EUGCQuery eQueryType, EUGCMatchingUGCType eMatchingeMatchingUGCTypeFileType, AppId_t nCreatorAppID, AppId_t nConsumerAppID, uint32 unPage);
S_CLASSAPI UGCQueryHandle_t S_CLASSCALLTYPE SteamAPI_ISteamUGC_CreateQueryUGCDetailsRequest(SELF, PublishedFileId_t *pvecPublishedFileID, uint32 unNumPublishedFileIDs);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUGC_SendQueryUGCRequest(SELF, UGCQueryHandle_t handle);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_GetQueryUGCResult(SELF, UGCQueryHandle_t handle, uint32 index, SteamUGCDetails_t *pDetails);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_GetQueryUGCPreviewURL(SELF, UGCQueryHandle_t handle, uint32 index, char *pchURL, uint32 cchURLSize);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_GetQueryUGCMetadata(SELF, UGCQueryHandle_t handle, uint32 index, char *pchMetadata, uint32 cchMetadatasize);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_GetQueryUGCChildren(SELF, UGCQueryHandle_t handle, uint32 index, PublishedFileId_t *pvecPublishedFileID, uint32 cMaxEntries);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_GetQueryUGCStatistic(SELF, UGCQueryHandle_t handle, uint32 index, EItemStatistic eStatType, uint32 *pStatValue);
S_CLASSAPI uint32 S_CLASSCALLTYPE SteamAPI_ISteamUGC_GetQueryUGCNumAdditionalPreviews(SELF, UGCQueryHandle_t handle, uint32 index);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_GetQueryUGCAdditionalPreview(SELF, UGCQueryHandle_t handle, uint32 index, uint32 previewIndex, char *pchURLOrVideoID, uint32 cchURLSize, bool *pbIsImage);
S_CLASSAPI uint32 S_CLASSCALLTYPE SteamAPI_ISteamUGC_GetQueryUGCNumKeyValueTags(SELF, UGCQueryHandle_t handle, uint32 index);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_GetQueryUGCKeyValueTag(SELF, UGCQueryHandle_t handle, uint32 index, uint32 keyValueTagIndex, char *pchKey, uint32 cchKeySize, char *pchValue, uint32 cchValueSize);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_ReleaseQueryUGCRequest(SELF, UGCQueryHandle_t handle);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_AddRequiredTag(SELF, UGCQueryHandle_t handle, const char *pTagName);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_AddExcludedTag(SELF, UGCQueryHandle_t handle, const char *pTagName);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_SetReturnKeyValueTags(SELF, UGCQueryHandle_t handle, bool bReturnKeyValueTags);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_SetReturnLongDescription(SELF, UGCQueryHandle_t handle, bool bReturnLongDescription);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_SetReturnMetadata(SELF, UGCQueryHandle_t handle, bool bReturnMetadata);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_SetReturnChildren(SELF, UGCQueryHandle_t handle, bool bReturnChildren);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_SetReturnAdditionalPreviews(SELF, UGCQueryHandle_t handle, bool bReturnAdditionalPreviews);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_SetReturnTotalOnly(SELF, UGCQueryHandle_t handle, bool bReturnTotalOnly);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_SetLanguage(SELF, UGCQueryHandle_t handle, const char *pchLanguage);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_SetAllowCachedResponse(SELF, UGCQueryHandle_t handle, uint32 unMaxAgeSeconds);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_SetCloudFileNameFilter(SELF, UGCQueryHandle_t handle, uint32 unMaxAgeSeconds);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_SetMatchAnyTag(SELF, UGCQueryHandle_t handle, bool bMatchAnyTag);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_SetSearchText(SELF, UGCQueryHandle_t handle, const char *pSearchText);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_SetRankedByTrendDays(SELF, UGCQueryHandle_t handle, uint32 unDays);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_AddRequiredKeyValueTag(SELF, UGCQueryHandle_t handle, const char *pKey, const char *pValue);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUGC_RequestUGCDetails(SELF, PublishedFileId_t nPublishedFileID, uint32 unMaxAgeSeconds);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUGC_CreateItem(SELF, AppId_t nConsumerAppId, EWorkshopFileType eFileType);
S_CLASSAPI UGCUpdateHandle_t S_CLASSCALLTYPE SteamAPI_ISteamUGC_StartItemUpdate(SELF, AppId_t nConsumerAppId, PublishedFileId_t nPublishedFileID);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_SetItemTitle(SELF, UGCUpdateHandle_t handle, const char *pchTitle);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_SetItemDescription(SELF, UGCUpdateHandle_t handle, const char *pchDescription);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_SetItemUpdateLanguage(SELF, UGCUpdateHandle_t handle, const char *pchLanguage);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_SetItemMetadata(SELF, UGCUpdateHandle_t handle, const char *pchMetaData);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_SetItemVisibility(SELF, UGCUpdateHandle_t handle, ERemoteStoragePublishedFileVisibility eVisibility);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_SetItemTags(SELF, UGCUpdateHandle_t updateHandle, const SteamParamStringArray_t *pTags);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_SetItemContent(SELF, UGCUpdateHandle_t handle, const char *pszContentFolder);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_SetItemPreview(SELF, UGCUpdateHandle_t handle, const char *pszPreviewFile);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_RemoveItemKeyValueTags(SELF, UGCUpdateHandle_t handle, const char *pchKey);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_AddItemKeyValueTag(SELF, UGCUpdateHandle_t handle, const char *pchKey, const char *pchValue);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUGC_SubmitItemUpdate(SELF, UGCUpdateHandle_t handle, const char *pchChangeNote);
S_CLASSAPI EItemUpdateStatus S_CLASSCALLTYPE SteamAPI_ISteamUGC_GetItemUpdateProgress(SELF, UGCUpdateHandle_t handle, uint64 *punBytesProcessed, uint64 *punBytesTotal);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUGC_SetUserItemVote(SELF, PublishedFileId_t nPublishedFileID, bool bVoteUp);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUGC_GetUserItemVote(SELF, PublishedFileId_t nPublishedFileID);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUGC_AddItemToFavorites(SELF, AppId_t nAppId, PublishedFileId_t nPublishedFileID);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUGC_RemoveItemFromFavorites(SELF, AppId_t nAppId, PublishedFileId_t nPublishedFileID);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUGC_SubscribeItem(SELF, PublishedFileId_t nPublishedFileID);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUGC_UnsubscribeItem(SELF, PublishedFileId_t nPublishedFileID);
S_CLASSAPI uint32 S_CLASSCALLTYPE SteamAPI_ISteamUGC_GetNumSubscribedItems(SELF);
S_CLASSAPI uint32 S_CLASSCALLTYPE SteamAPI_ISteamUGC_GetSubscribedItems(SELF, PublishedFileId_t *pvecPublishedFileID, uint32 cMaxEntries);
S_CLASSAPI uint32 S_CLASSCALLTYPE SteamAPI_ISteamUGC_GetItemState(SELF, PublishedFileId_t nPublishedFileID);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_GetItemInstallInfo(SELF, PublishedFileId_t nPublishedFileID, uint64 *punSizeOnDisk, char *pchFolder, uint32 cchFolderSize, uint32 *punTimeStamp);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_GetItemDownloadInfo(SELF, PublishedFileId_t nPublishedFileID, uint64 *punBytesDownloaded, uint64 *punBytesTotal);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_DownloadItem(SELF, PublishedFileId_t nPublishedFileID, bool bHighPriority);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_BInitWorkshopForGameServer(SELF, DepotId_t unWorkshopDepotID, const char *pszFolder);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamUGC_SuspendDownloads(SELF, bool bSuspend);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamUGC_StartPlaytimeTracking(SELF, bool *pvecPublishedFileId, uint32 unNumPublishedFileIDs);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamUGC_StopPlaytimeTracking(SELF, bool *pvecPublishedFileId, uint32 unNumPublishedFileIDs);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamUGC_StopPlaytimeTrackingForAllItems(SELF);
S_CLASSAPI uint32 S_CLASSCALLTYPE SteamAPI_ISteamUGC_GetQueryUGCNumTags(SELF, UGCQueryHandle_t handle, uint32 index);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_GetQueryUGCTag(SELF, UGCQueryHandle_t handle, uint32 index, uint32 indexTag, char *pchValue, uint32 cchValueSize);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_GetQueryUGCTagDisplayName(SELF, UGCQueryHandle_t handle, uint32 index, uint32 indexTag, char *pchValue, uint32 cchValueSize);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_AddRequiredTagGroup(SELF, UGCQueryHandle_t handle, const SteamParamStringArray_t *pTagGroups);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_SetReturnOnlyIDs(SELF, UGCQueryHandle_t handle, bool bReturnOnlyIDs);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_SetReturnPlaytimeStats(SELF, UGCQueryHandle_t handle, uint32 unDays);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_SetTimeCreatedDateRange(SELF, UGCQueryHandle_t handle, RTime32 rtStart, RTime32 rtEnd);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_SetTimeUpdatedDateRange(SELF, UGCQueryHandle_t handle, RTime32 rtStart, RTime32 rtEnd);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_SetAllowLegacyUpload(SELF, UGCUpdateHandle_t handle, bool bAllowLegacyUpload);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_RemoveAllItemKeyValueTags(SELF, UGCUpdateHandle_t handle);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_AddItemPreviewFile(SELF, UGCUpdateHandle_t handle, const char *pszPreviewFile, EItemPreviewType type);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_AddItemPreviewVideo(SELF, UGCUpdateHandle_t handle, const char *pszVideoID);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_UpdateItemPreviewFile(SELF, UGCUpdateHandle_t handle, uint32 index, const char *pszPreviewFile);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_UpdateItemPreviewVideo(SELF, UGCUpdateHandle_t handle, uint32 index, const char *pszVideoID);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_RemoveItemPreview(SELF, UGCUpdateHandle_t handle, uint32 index);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUGC_AddDependency(SELF, PublishedFileId_t nParentPublishedFileID, PublishedFileId_t nChildPublishedFileID);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUGC_RemoveDependency(SELF, PublishedFileId_t nParentPublishedFileID, PublishedFileId_t nChildPublishedFileID);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUGC_AddAppDependency(SELF, PublishedFileId_t nPublishedFileID, AppId_t nAppID);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUGC_RemoveAppDependency(SELF, PublishedFileId_t nPublishedFileID, AppId_t nAppID);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUGC_GetAppDependencies(SELF, PublishedFileId_t nPublishedFileID);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUGC_DeleteItem(SELF, PublishedFileId_t nPublishedFileID);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamUGC_ShowWorkshopEULA(SELF);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamUGC_GetWorkshopEULAStatus(SELF);
