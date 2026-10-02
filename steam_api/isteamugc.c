#include "steam.h"

S_CLASSAPI UGCQueryHandle_t S_CLASSCALLTYPE
SteamAPI_ISteamUGC_CreateQueryUserUGCRequest(SELF, AccountID_t unAccountID, EUserUGCList eListType, EUGCMatchingUGCType eMatchingUGCType, EUserUGCListSortOrder eSortOrder, AppId_t nCreatorAppID, AppId_t nConsumerAppID, uint32 unPage)
{
	xlogf("%s(self = %p, unAccountID = %d, eListType = %d, eMatchingUGCType = %d, eSortOrder = %d, nCreatorAppID = %d, nConsumerAppID = %d, unPage = %d)\n", __func__, self, unAccountID, eListType, eMatchingUGCType, eSortOrder, nCreatorAppID, nConsumerAppID, unPage);
	return 1;
}

S_CLASSAPI UGCQueryHandle_t S_CLASSCALLTYPE
SteamAPI_ISteamUGC_CreateQueryAllUGCRequest(SELF, EUGCQuery eQueryType, EUGCMatchingUGCType eMatchingeMatchingUGCTypeFileType, AppId_t nCreatorAppID, AppId_t nConsumerAppID, uint32 unPage)
{
	xlogf("%s(self = %p, eQueryType = %d, eMatchingeMatchingUGCTypeFileType = %d, nCreatorAppID = %d, nConsumerAppID = %d, unPage = %d)\n", __func__, self, eQueryType, eMatchingeMatchingUGCTypeFileType, nCreatorAppID, nConsumerAppID, unPage);
	return 1;
}

S_CLASSAPI UGCQueryHandle_t S_CLASSCALLTYPE
SteamAPI_ISteamUGC_CreateQueryUGCDetailsRequest(SELF, PublishedFileId_t *pvecPublishedFileID, uint32 unNumPublishedFileIDs)
{
	xlogf("%s(self = %p, pvecPublishedFileID = %p, unNumPublishedFileIDs = %d)\n", __func__, self, pvecPublishedFileID, unNumPublishedFileIDs);
	return 1;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUGC_SendQueryUGCRequest(SELF, UGCQueryHandle_t handle)
{
	xlogf("%s(self = %p, handle = %llu)\n", __func__, self, handle);
	return 1;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_GetQueryUGCResult(SELF, UGCQueryHandle_t handle, uint32 index, SteamUGCDetails_t *pDetails)
{
	xlogf("%s(self = %p, handle = %llu, index = %d, pDetails = %p)\n", __func__, self, handle, index, pDetails);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_GetQueryUGCPreviewURL(SELF, UGCQueryHandle_t handle, uint32 index, char *pchURL, uint32 cchURLSize)
{
	xlogf("%s(self = %p, handle = %llu, index = %d, pchURL = %s, cchURLSize = %d)\n", __func__, self, handle, index, pchURL, cchURLSize);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_GetQueryUGCMetadata(SELF, UGCQueryHandle_t handle, uint32 index, char *pchMetadata, uint32 cchMetadatasize)
{
	xlogf("%s(self = %p, handle = %llu, index = %d, pchMetadata = %s, cchMetadatasize = %d)\n", __func__, self, handle, index, pchMetadata, cchMetadatasize);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_GetQueryUGCChildren(SELF, UGCQueryHandle_t handle, uint32 index, PublishedFileId_t *pvecPublishedFileID, uint32 cMaxEntries)
{
	xlogf("%s(self = %p, handle = %llu, index = %d, pvecPublishedFileID = %p, cMaxEntries = %d)\n", __func__, self, handle, index, pvecPublishedFileID, cMaxEntries);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_GetQueryUGCStatistic(SELF, UGCQueryHandle_t handle, uint32 index, EItemStatistic eStatType, uint32 *pStatValue)
{
	xlogf("%s(self = %p, handle = %llu, index = %d, eStatType = %d, pStatValue = %p)\n", __func__, self, handle, index, eStatType, pStatValue);
	return true;
}

S_CLASSAPI uint32 S_CLASSCALLTYPE
SteamAPI_ISteamUGC_GetQueryUGCNumAdditionalPreviews(SELF, UGCQueryHandle_t handle, uint32 index)
{
	xlogf("%s(self = %p, handle = %llu, index = %d)\n", __func__, self, handle, index);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_GetQueryUGCAdditionalPreview(SELF, UGCQueryHandle_t handle, uint32 index, uint32 previewIndex, char *pchURLOrVideoID, uint32 cchURLSize, bool *pbIsImage)
{
	xlogf("%s(self = %p, handle = %llu, index = %d, previewIndex = %d, pchURLOrVideoID = %s, cchURLSize = %d, pbIsImage = %p)\n", __func__, self, handle, index, previewIndex, pchURLOrVideoID, cchURLSize, pbIsImage);
	return true;
}

S_CLASSAPI uint32 S_CLASSCALLTYPE
SteamAPI_ISteamUGC_GetQueryUGCNumKeyValueTags(SELF, UGCQueryHandle_t handle, uint32 index)
{
	xlogf("%s(self = %p, handle = %llu, index = %d)\n", __func__, self, handle, index);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_GetQueryUGCKeyValueTag(SELF, UGCQueryHandle_t handle, uint32 index, uint32 keyValueTagIndex, char *pchKey, uint32 cchKeySize, char *pchValue, uint32 cchValueSize)
{
	xlogf("%s(self = %p, handle = %llu, index = %d, keyValueTagIndex = %d, pchKey = %s, cchKeySize = %d, pchValue = %s, cchValueSize = %d)\n", __func__, self, handle, index, keyValueTagIndex, pchKey, cchKeySize, pchValue, cchValueSize);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_ReleaseQueryUGCRequest(SELF, UGCQueryHandle_t handle)
{
	xlogf("%s(self = %p, handle = %llu)\n", __func__, self, handle);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_AddRequiredTag(SELF, UGCQueryHandle_t handle, const char *pTagName)
{
	xlogf("%s(self = %p, handle = %llu, pTagName = %s)\n", __func__, self, handle, pTagName);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_AddExcludedTag(SELF, UGCQueryHandle_t handle, const char *pTagName)
{
	xlogf("%s(self = %p, handle = %llu, pTagName = %s)\n", __func__, self, handle, pTagName);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_SetReturnKeyValueTags(SELF, UGCQueryHandle_t handle, bool bReturnKeyValueTags)
{
	xlogf("%s(self = %p, handle = %llu, bReturnKeyValueTags = %d)\n", __func__, self, handle, bReturnKeyValueTags);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_SetReturnLongDescription(SELF, UGCQueryHandle_t handle, bool bReturnLongDescription)
{
	xlogf("%s(self = %p, handle = %llu, bReturnLongDescription = %d)\n", __func__, self, handle, bReturnLongDescription);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_SetReturnMetadata(SELF, UGCQueryHandle_t handle, bool bReturnMetadata)
{
	xlogf("%s(self = %p, handle = %llu, bReturnMetadata = %d)\n", __func__, self, handle, bReturnMetadata);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_SetReturnChildren(SELF, UGCQueryHandle_t handle, bool bReturnChildren)
{
	xlogf("%s(self = %p, handle = %llu, bReturnChildren = %d)\n", __func__, self, handle, bReturnChildren);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_SetReturnAdditionalPreviews(SELF, UGCQueryHandle_t handle, bool bReturnAdditionalPreviews)
{
	xlogf("%s(self = %p, handle = %llu, bReturnAdditionalPreviews = %d)\n", __func__, self, handle, bReturnAdditionalPreviews);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_SetReturnTotalOnly(SELF, UGCQueryHandle_t handle, bool bReturnTotalOnly)
{
	xlogf("%s(self = %p, handle = %llu, bReturnTotalOnly = %d)\n", __func__, self, handle, bReturnTotalOnly);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_SetLanguage(SELF, UGCQueryHandle_t handle, const char *pchLanguage)
{
	xlogf("%s(self = %p, handle = %llu, pchLanguage = %s)\n", __func__, self, handle, pchLanguage);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_SetAllowCachedResponse(SELF, UGCQueryHandle_t handle, uint32 unMaxAgeSeconds)
{
	xlogf("%s(self = %p, handle = %llu, unMaxAgeSeconds = %d)\n", __func__, self, handle, unMaxAgeSeconds);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_SetCloudFileNameFilter(SELF, UGCQueryHandle_t handle, uint32 unMaxAgeSeconds)
{
	xlogf("%s(self = %p, handle = %llu, unMaxAgeSeconds = %d)\n", __func__, self, handle, unMaxAgeSeconds);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_SetMatchAnyTag(SELF, UGCQueryHandle_t handle, bool bMatchAnyTag)
{
	xlogf("%s(self = %p, handle = %llu, bMatchAnyTag = %d)\n", __func__, self, handle, bMatchAnyTag);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_SetSearchText(SELF, UGCQueryHandle_t handle, const char *pSearchText)
{
	xlogf("%s(self = %p, handle = %llu, pSearchText = %s)\n", __func__, self, handle, pSearchText);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_SetRankedByTrendDays(SELF, UGCQueryHandle_t handle, uint32 unDays)
{
	xlogf("%s(self = %p, handle = %llu, unDays = %d)\n", __func__, self, handle, unDays);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_AddRequiredKeyValueTag(SELF, UGCQueryHandle_t handle, const char *pKey, const char *pValue)
{
	xlogf("%s(self = %p, handle = %llu, pKey = %s, pValue = %s)\n", __func__, self, handle, pKey, pValue);
	return true;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUGC_RequestUGCDetails(SELF, PublishedFileId_t nPublishedFileID, uint32 unMaxAgeSeconds)
{
	xlogf("%s(self = %p, nPublishedFileID = %llu, unMaxAgeSeconds = %d)\n", __func__, self, nPublishedFileID, unMaxAgeSeconds);
	return 1;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUGC_CreateItem(SELF, AppId_t nConsumerAppId, EWorkshopFileType eFileType)
{
	xlogf("%s(self = %p, nConsumerAppId = %d, eFileType = %d)\n", __func__, self, nConsumerAppId, eFileType);
	return 1;
}

S_CLASSAPI UGCUpdateHandle_t S_CLASSCALLTYPE
SteamAPI_ISteamUGC_StartItemUpdate(SELF, AppId_t nConsumerAppId, PublishedFileId_t nPublishedFileID)
{
	xlogf("%s(self = %p, nConsumerAppId = %d, nPublishedFileID = %llu)\n", __func__, self, nConsumerAppId, nPublishedFileID);
	return 1;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_SetItemTitle(SELF, UGCUpdateHandle_t handle, const char *pchTitle)
{
	xlogf("%s(self = %p, handle = %llu, pchTitle = %s)\n", __func__, self, handle, pchTitle);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_SetItemDescription(SELF, UGCUpdateHandle_t handle, const char *pchDescription)
{
	xlogf("%s(self = %p, handle = %llu, pchDescription = %s)\n", __func__, self, handle, pchDescription);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_SetItemUpdateLanguage(SELF, UGCUpdateHandle_t handle, const char *pchLanguage)
{
	xlogf("%s(self = %p, handle = %llu, pchDescription = %s)\n", __func__, self, handle, pchLanguage);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_SetItemMetadata(SELF, UGCUpdateHandle_t handle, const char *pchMetaData)
{
	xlogf("%s(self = %p, handle = %llu, pchMetaData = %s)\n", __func__, self, handle, pchMetaData);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_SetItemVisibility(SELF, UGCUpdateHandle_t handle, ERemoteStoragePublishedFileVisibility eVisibility)
{
	xlogf("%s(self = %p, handle = %llu, eVisibility = %d)\n", __func__, self, handle, eVisibility);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_SetItemTags(SELF, UGCUpdateHandle_t updateHandle, const SteamParamStringArray_t *pTags)
{
	xlogf("%s(self = %p, updateHandle = %llu, pTags = %p)\n", __func__, self, updateHandle, pTags);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_SetItemContent(SELF, UGCUpdateHandle_t handle, const char *pszContentFolder)
{
	xlogf("%s(self = %p, handle = %llu, pszContentFolder = %s)\n", __func__, self, handle, pszContentFolder);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_SetItemPreview(SELF, UGCUpdateHandle_t handle, const char *pszPreviewFile)
{
	xlogf("%s(self = %p, handle = %llu, pszPreviewFile = %s)\n", __func__, self, handle, pszPreviewFile);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_RemoveItemKeyValueTags(SELF, UGCUpdateHandle_t handle, const char *pchKey)
{
	xlogf("%s(self = %p, handle = %llu, pchKey = %s)\n", __func__, self, handle, pchKey);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_AddItemKeyValueTag(SELF, UGCUpdateHandle_t handle, const char *pchKey, const char *pchValue)
{
	xlogf("%s(self = %p, handle = %llu, pchKey = %s, pchValue = %s)\n", __func__, self, handle, pchKey, pchValue);
	return true;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUGC_SubmitItemUpdate(SELF, UGCUpdateHandle_t handle, const char *pchChangeNote)
{
	xlogf("%s(self = %p, handle = %llu, pchChangeNote = %s)\n", __func__, self, handle, pchChangeNote);
	return 1;
}

S_CLASSAPI EItemUpdateStatus S_CLASSCALLTYPE
SteamAPI_ISteamUGC_GetItemUpdateProgress(SELF, UGCUpdateHandle_t handle, uint64 *punBytesProcessed, uint64 *punBytesTotal)
{
	xlogf("%s(self = %p, handle = %llu, punBytesProcessed = %p, punBytesTotal = %p)\n", __func__, self, handle, punBytesProcessed, punBytesTotal);
	return 0;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUGC_SetUserItemVote(SELF, PublishedFileId_t nPublishedFileID, bool bVoteUp)
{
	xlogf("%s(self = %p, nPublishedFileID = %llu, bVoteUp = %d)\n", __func__, self, nPublishedFileID, bVoteUp);
	return 1;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUGC_GetUserItemVote(SELF, PublishedFileId_t nPublishedFileID)
{
	xlogf("%s(self = %p, nPublishedFileID = %llu)\n", __func__, self, nPublishedFileID);
	return 1;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUGC_AddItemToFavorites(SELF, AppId_t nAppId, PublishedFileId_t nPublishedFileID)
{
	xlogf("%s(self = %p, nAppId = %d, nPublishedFileID = %llu)\n", __func__, self, nAppId, nPublishedFileID);
	return 1;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUGC_RemoveItemFromFavorites(SELF, AppId_t nAppId, PublishedFileId_t nPublishedFileID)
{
	xlogf("%s(self = %p, nAppId = %d, nPublishedFileID = %llu)\n", __func__, self, nAppId, nPublishedFileID);
	return 1;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUGC_SubscribeItem(SELF, PublishedFileId_t nPublishedFileID)
{
	xlogf("%s(self = %p, nPublishedFileID = %llu)\n", __func__, self, nPublishedFileID);
	return 1;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUGC_UnsubscribeItem(SELF, PublishedFileId_t nPublishedFileID)
{
	xlogf("%s(self = %p, nPublishedFileID = %llu)\n", __func__, self, nPublishedFileID);
	return 1;
}

S_CLASSAPI uint32 S_CLASSCALLTYPE
SteamAPI_ISteamUGC_GetNumSubscribedItems(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI uint32 S_CLASSCALLTYPE
SteamAPI_ISteamUGC_GetSubscribedItems(SELF, PublishedFileId_t *pvecPublishedFileID, uint32 cMaxEntries)
{
	xlogf("%s(self = %p, pvecPublishedFileID = %p, cMaxEntries = %d)\n", __func__, self, pvecPublishedFileID, cMaxEntries);
	return 0;
}

S_CLASSAPI uint32 S_CLASSCALLTYPE
SteamAPI_ISteamUGC_GetItemState(SELF, PublishedFileId_t nPublishedFileID)
{
	xlogf("%s(self = %p, nPublishedFileID = %llu)\n", __func__, self, nPublishedFileID);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_GetItemInstallInfo(SELF, PublishedFileId_t nPublishedFileID, uint64 *punSizeOnDisk, char *pchFolder, uint32 cchFolderSize, uint32 *punTimeStamp)
{
	xlogf("%s(self = %p, nPublishedFileID = %llu, punSizeOnDisk = %p, pchFolder = %s, cchFolderSize = %d, punTimeStamp = %p)\n", __func__, self, nPublishedFileID, punSizeOnDisk, pchFolder, cchFolderSize, punTimeStamp);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_GetItemDownloadInfo(SELF, PublishedFileId_t nPublishedFileID, uint64 *punBytesDownloaded, uint64 *punBytesTotal)
{
	xlogf("%s(self = %p, nPublishedFileID = %llu, punBytesDownloaded = %p, punBytesTotal = %p)\n", __func__, self, nPublishedFileID, punBytesDownloaded, punBytesTotal);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_DownloadItem(SELF, PublishedFileId_t nPublishedFileID, bool bHighPriority)
{
	xlogf("%s(self = %p, nPublishedFileID = %llu, bHighPriority = %d)\n", __func__, self, nPublishedFileID, bHighPriority);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_BInitWorkshopForGameServer(SELF, DepotId_t unWorkshopDepotID, const char *pszFolder)
{
	xlogf("%s(self = %p, unWorkshopDepotID = %d, pszFolder = %s)\n", __func__, self, unWorkshopDepotID, pszFolder);
	return true;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamUGC_SuspendDownloads(SELF, bool bSuspend)
{
	xlogf("%s(self = %p, bSuspend = %d)\n", __func__, self, bSuspend);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamUGC_StartPlaytimeTracking(SELF, bool *pvecPublishedFileId, uint32 unNumPublishedFileIDs)
{
	xlogf("%s(self = %p, pvecPublishedFileId = %p, unNumPublishedFileIDs = %d)\n", __func__, self, pvecPublishedFileId, unNumPublishedFileIDs);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamUGC_StopPlaytimeTracking(SELF, bool *pvecPublishedFileId, uint32 unNumPublishedFileIDs)
{
	xlogf("%s(self = %p, pvecPublishedFileId = %p, unNumPublishedFileIDs = %d)\n", __func__, self, pvecPublishedFileId, unNumPublishedFileIDs);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamUGC_StopPlaytimeTrackingForAllItems(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI uint32 S_CLASSCALLTYPE
SteamAPI_ISteamUGC_GetQueryUGCNumTags(SELF, UGCQueryHandle_t handle, uint32 index)
{
	xlogf("%s(self = %p, handle = %llu, index = %d)\n",
	      __func__, self, handle, index);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_GetQueryUGCTag(SELF, UGCQueryHandle_t handle, uint32 index, uint32 indexTag, char *pchValue, uint32 cchValueSize)
{
	xlogf("%s(self = %p, handle = %llu, index = %d, indexTag = %d, pchValue = %s, cchValueSize = %d)\n",
	      __func__, self, handle, index, indexTag, pchValue, cchValueSize);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_GetQueryUGCTagDisplayName(SELF, UGCQueryHandle_t handle, uint32 index, uint32 indexTag, char *pchValue, uint32 cchValueSize)
{
	xlogf("%s(self = %p, handle = %llu, index = %d, indexTag = %d, pchValue = %s, cchValueSize = %d)\n",
	      __func__, self, handle, index, indexTag, pchValue, cchValueSize);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_AddRequiredTagGroup(SELF, UGCQueryHandle_t handle, const SteamParamStringArray_t *pTagGroups)
{
	xlogf("%s(self = %p, handle = %llu, pTagGroups = %p)\n",
	      __func__, self, handle, pTagGroups);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_SetReturnOnlyIDs(SELF, UGCQueryHandle_t handle, bool bReturnOnlyIDs)
{
	xlogf("%s(self = %p, handle = %llu, bReturnOnlyIDs = %d)\n",
	      __func__, self, handle, bReturnOnlyIDs);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_SetReturnPlaytimeStats(SELF, UGCQueryHandle_t handle, uint32 unDays)
{
	xlogf("%s(self = %p, handle = %llu, unDays = %d)\n",
	      __func__, self, handle, unDays);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_SetTimeCreatedDateRange(SELF, UGCQueryHandle_t handle, RTime32 rtStart, RTime32 rtEnd)
{
	xlogf("%s(self = %p, handle = %llu, rtStart = %d, rtEnd = %d)\n",
	      __func__, self, handle, rtStart, rtEnd);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_SetTimeUpdatedDateRange(SELF, UGCQueryHandle_t handle, RTime32 rtStart, RTime32 rtEnd)
{
	xlogf("%s(self = %p, handle = %llu, rtStart = %d, rtEnd = %d)\n",
	      __func__, self, handle, rtStart, rtEnd);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_SetAllowLegacyUpload(SELF, UGCUpdateHandle_t handle, bool bAllowLegacyUpload)
{
	xlogf("%s(self = %p, handle = %llu, bAllowLegacyUpload = %d)\n",
	      __func__, self, handle, bAllowLegacyUpload);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_RemoveAllItemKeyValueTags(SELF, UGCUpdateHandle_t handle)
{
	xlogf("%s(self = %p, handle = %llu)\n",
	      __func__, self, handle);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_AddItemPreviewFile(SELF, UGCUpdateHandle_t handle, const char *pszPreviewFile, EItemPreviewType type)
{
	xlogf("%s(self = %p, handle = %llu, pszPreviewFile = %s, type = %d)\n",
	      __func__, self, handle, pszPreviewFile, type);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_AddItemPreviewVideo(SELF, UGCUpdateHandle_t handle, const char *pszVideoID)
{
	xlogf("%s(self = %p, handle = %llu, pszVideoID = %s)\n",
	      __func__, self, handle, pszVideoID);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_UpdateItemPreviewFile(SELF, UGCUpdateHandle_t handle, uint32 index, const char *pszPreviewFile)
{
	xlogf("%s(self = %p, handle = %llu, index = %d, pszPreviewFile = %s)\n",
	      __func__, self, handle, index, pszPreviewFile);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_UpdateItemPreviewVideo(SELF, UGCUpdateHandle_t handle, uint32 index, const char *pszVideoID)
{
	xlogf("%s(self = %p, handle = %llu, index = %d, pszPreviewFile = %s)\n",
	      __func__, self, handle, index, pszVideoID);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_RemoveItemPreview(SELF, UGCUpdateHandle_t handle, uint32 index)
{
	xlogf("%s(self = %p, handle = %llu, index = %d)\n",
	      __func__, self, handle, index);
	return false;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUGC_AddDependency(SELF, PublishedFileId_t nParentPublishedFileID, PublishedFileId_t nChildPublishedFileID)
{
	xlogf("%s(self = %p, nParentPublishedFileID = %lld, nChildPublishedFileID = %lld)\n", __func__, self, nParentPublishedFileID, nChildPublishedFileID);
	return 0;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUGC_RemoveDependency(SELF, PublishedFileId_t nParentPublishedFileID, PublishedFileId_t nChildPublishedFileID)
{
	xlogf("%s(self = %p, nParentPublishedFileID = %lld, nChildPublishedFileID = %lld)\n", __func__, self, nParentPublishedFileID, nChildPublishedFileID);
	return 0;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUGC_AddAppDependency(SELF, PublishedFileId_t nPublishedFileID, AppId_t nAppID)
{
	xlogf("%s(self = %p, nPublishedFileID = %lld, nAppID = %d)\n", __func__, self, nPublishedFileID, nAppID);
	return 0;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUGC_RemoveAppDependency(SELF, PublishedFileId_t nPublishedFileID, AppId_t nAppID)
{
	xlogf("%s(self = %p, nPublishedFileID = %lld, nAppID = %d)\n", __func__, self, nPublishedFileID, nAppID);
	return 0;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUGC_GetAppDependencies(SELF, PublishedFileId_t nPublishedFileID)
{
	xlogf("%s(self = %p, nPublishedFileID = %lld)\n", __func__, self, nPublishedFileID);
	return 0;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUGC_DeleteItem(SELF, PublishedFileId_t nPublishedFileID)
{
	xlogf("%s(self = %p, nPublishedFileID = %lld)\n", __func__, self, nPublishedFileID);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamUGC_ShowWorkshopEULA(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamUGC_GetWorkshopEULAStatus(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}
