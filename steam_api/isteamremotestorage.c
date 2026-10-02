#include "steam.h"

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_FileWrite(SELF, const char *pchFile, const void *pvData, int32 cubData)
{
	FILE *fp;
	char path[PATH_MAX];

	xlogf("%s(self = %p, pchFile = %s, pvData = %p, cubData = %d)\n", __func__, self, pchFile, pvData, cubData);

	snprintf(path, sizeof(path), "%s", pchFile);
	mkdirp(dirname(path));

	fp = xfopen(pchFile, "wb");
	if (!fp)
		return false;

	fwrite(pvData, cubData, 1, fp);
	fclose(fp);
	return true;
}

S_CLASSAPI int32 S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_FileRead(SELF, const char *pchFile, void *pvData, int32 cubDataToRead)
{
	FILE *fp;
	int32 nr = -1;

	fp = xfopen(pchFile, "rb");
	if (fp) {
		nr = fread(pvData, 1, cubDataToRead, fp);
		fclose(fp);
	}

	xlogf("%s(self = %p, pchFile = %s, pvData = %p, cubDataToRead = %d) -> %d\n", __func__, self, pchFile, pvData, cubDataToRead, nr);
	return nr;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_FileWriteAsync(SELF, const char *pchFile, const void *pvData, uint32 cubData)
{
	xlogf("%s(self = %p, pchFile = %s, pvData = %p, cubData = %u)\n", __func__,
	      self, pchFile, pvData, cubData);
	return 0;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_FileReadAsync(SELF, const char *pchFile, uint32 nOffset, uint32 cubDataToRead)
{
	xlogf("%s(self = %p, pchFile = %s, nOffset = %u, cubDataToRead = %u)\n",
	      __func__, self, pchFile, nOffset, cubDataToRead);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_FileReadAsyncComplete(SELF, SteamAPICall_t nReadCall, void *pvData, uint32 cubDataToRead)
{
	xlogf("%s(self = %p, nReadCall = %llu, pvData = %p, cubDataToRead = %d)\n", __func__, self, nReadCall, pvData, cubDataToRead);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_FileForget(SELF, const char *pchFile)
{
	xlogf("%s(self = %p, pchFile = %s)\n", __func__, self, pchFile);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_FileDelete(SELF, const char *pchFile)
{
	char path[PATH_MAX * 2];

	xlogf("%s(self = %p, pchFile = %s)\n", __func__, self, pchFile);
	snprintf(path, sizeof(path), "%s/%s", ctx.rootDir, pchFile);
	unlink(path);
	return true;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_FileShare(SELF, const char *pchFile)
{
	xlogf("%s(self = %p, pchFile = %s)\n", __func__, self, pchFile);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_SetSyncPlatforms(SELF, const char *pchFile, ERemoteStoragePlatform eRemoteStoragePlatform)
{
	xlogf("%s(self = %p, pchFile = %s, eRemoteStoragePlatform = %d)\n",
	      __func__, self, pchFile, eRemoteStoragePlatform);
	return false;
}

S_CLASSAPI int32 S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_GetFileCount(SELF)
{
	CSteamContext *p = &ctx;
	CSteamFile *files;
	int32 numFiles;

	files = getAllFileListing(p->rootDir, &numFiles);
	free(p->files);
	p->files = files;
	p->numFiles = numFiles;

	xlogf("%s(self = %p) -> %d\n", __func__, self, numFiles);
	return numFiles;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamRemoteStorage_IsCloudEnabledForAccount(SELF)
{
	bool enabled = false;
	xlogf("%s(self = %p) -> %d\n", __func__, self, enabled);
	return enabled;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamRemoteStorage_IsCloudEnabledForApp(SELF)
{
	bool enabled = false;
	xlogf("%s(self = %p) -> %d\n", __func__, self, enabled);
	return enabled;
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_GetFileNameAndSize(SELF, int iFile, int32 *pnFileSizeInBytes)
{
	CSteamContext *p = &ctx;

	if (iFile < 0 || (size_t)iFile >= p->numFiles) {
		xlogf("%s(self = %p, iFile = %d, pnFileSizeInBytes = %p) -> nil\n", __func__, self, iFile, pnFileSizeInBytes);
		*pnFileSizeInBytes = 0;
		return NULL;
	}

	*pnFileSizeInBytes = p->files[iFile].size;
	xlogf("%s(self = %p, iFile = %d, pnFileSizeInBytes = %p) -> (%s, %d)\n", __func__, self, iFile, pnFileSizeInBytes, p->files[iFile].path, p->files[iFile].size);
	return p->files[iFile].path;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_FileExists(SELF, const char *pchFile)
{
	struct stat st;
	bool exists;

	exists = xstat(pchFile, &st) >= 0;
	xlogf("%s(self = %p, pchFile = %s) -> %d\n", __func__, self, pchFile, exists);
	return exists;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_FilePersisted(SELF, const char *pchFile)
{
	xlogf("%s(self = %p, pchFile = %s)\n", __func__, self, pchFile);
	return false;
}

S_CLASSAPI int32 S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_GetFileSize(SELF, const char *pchFile)
{
	struct stat st;
	int32 size;

	size = 0;
	if (xstat(pchFile, &st) >= 0)
		size = st.st_size;

	xlogf("%s(self = %p, pchFile = %s) -> %d\n", __func__, self, pchFile, size);
	return size;
}

S_CLASSAPI int64 S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_GetFileTimestamp(SELF, const char *pchFile)
{
	xlogf("%s(self = %p, pchFile = %s)\n", __func__, self, pchFile);
	return 0;
}

S_CLASSAPI ERemoteStoragePlatform S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_GetSyncPlatforms(SELF, const char *pchFile)
{
	xlogf("%s(self = %p, pchFile = %s)\n", __func__, self, pchFile);
	return 0;
}

S_CLASSAPI UGCFileWriteStreamHandle_t S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_FileWriteStreamOpen(SELF, const char *pchFile)
{
	xlogf("%s(self = %p, pchFile = %s)\n", __func__, self, pchFile);
	return 1;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_FileWriteStreamWriteChunk(SELF, UGCFileWriteStreamHandle_t writeHandle, const void *pvData, int32 cubData)
{
	xlogf("%s(self = %p, writeHandle = %#llx, pvData = %p, cubData = %d)\n", __func__, self, writeHandle, pvData, cubData);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_FileWriteStreamClose(SELF, UGCFileWriteStreamHandle_t writeHandle)
{
	xlogf("%s(self = %p, writeHandle = %llu)\n", __func__, self, writeHandle);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_FileWriteStreamCancel(SELF, UGCFileWriteStreamHandle_t writeHandle)
{
	xlogf("%s(self = %p, writeHandle = %llu)\n", __func__, self, writeHandle);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_GetQuota32(SELF, int32 *pnTotalBytes, int32 *puAvailableBytes)
{
	xlogf("%s(self = %p, pnTotalBytes = %p, puAvailableBytes = %p)\n", __func__, self, pnTotalBytes, puAvailableBytes);
	if (pnTotalBytes)
		*pnTotalBytes = 0;
	if (puAvailableBytes)
		*puAvailableBytes = 0;
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_GetQuota64(SELF, uint64 *pnTotalBytes, uint64 *puAvailableBytes)
{
	xlogf("%s(self = %p, pnTotalBytes = %p, puAvailableBytes = %p)\n", __func__, self, pnTotalBytes, puAvailableBytes);
	if (pnTotalBytes)
		*pnTotalBytes = 0;
	if (puAvailableBytes)
		*puAvailableBytes = 0;
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_IsCloudEnabledForAccount(SELF)
{
	bool enabled = false;
	printf("%s(self = %p) -> %d\n", __func__, self, enabled);
	return enabled;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_IsCloudEnabledForApp(SELF)
{
	bool enabled = false;
	xlogf("%s(self = %p) -> %d\n", __func__, self, enabled);
	return enabled;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_SetCloudEnabledForApp(SELF, bool bEnabled)
{
	xlogf("%s(self = %p, bEnabled = %d)\n", __func__, self, bEnabled);
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_UGCDownload(SELF, UGCHandle_t hContent, uint32 unPriority)
{
	xlogf("%s(self = %p, hContent = %llu, unPriority = %d)\n", __func__, self, hContent, unPriority);
	return 1;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_GetUGCDownloadProgress(SELF, UGCHandle_t hContent, int32 *pnBytesDownloaded, int32 *pnBytesExpected)
{
	xlogf("%s(self = %p, hContent = %llu, pnBytesDownloaded = %p, pnBytesExpected = %p)\n", __func__, self, hContent, pnBytesDownloaded, pnBytesExpected);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_GetUGCDetails(SELF, UGCHandle_t hContent, AppId_t *pnAppID, char **ppchName, int32 *pnFileSizeInBytes, CSteamID *pSteamIDOwner)
{
	xlogf("%s(self = %p, hContent = %llu, pnAppID = %p, ppchName = %p, pnFileSizeInBytes = %p, pSteamIDOwner = %p)\n", __func__, self, hContent, pnAppID, ppchName, pnFileSizeInBytes, pSteamIDOwner);
	return true;
}

S_CLASSAPI int32 S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_UGCRead(SELF, UGCHandle_t hContent, void *pvData, int32 cubDataToRead, uint32 cOffset, EUGCReadAction eAction)
{
	xlogf("%s(self = %p, hContent = %llu, pvData = %p, cubDataToRead = %d, cOffset = %d, eAction = %d)\n", __func__, self, hContent, pvData, cubDataToRead, cOffset, eAction);
	return 0;
}

S_CLASSAPI int32 S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_GetCachedUGCCount(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI UGCHandle_t S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_GetCachedUGCHandle(SELF, int32 iCachedContent)
{
	xlogf("%s(self = %p, iCachedContent = %d)\n", __func__, self, iCachedContent);
	return 0;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_PublishWorkshopFile(SELF, const char *pchFile, const char *pchPreviewFile, AppId_t nConsumerAppId, const char *pchTitle, const char *pchDescription, ERemoteStoragePublishedFileVisibility eVisibility, SteamParamStringArray_t *pTags, EWorkshopFileType eWorkshopFileType)
{
	xlogf("%s(self = %p, pchFile = %s, pchPreviewFIle = %s, nConsumerAppId = %d, pchTitle = %s, pchDescription = %s, eVisibility = %d, pTags = %p, eWorkshopFileType = %x)\n", __func__, self, pchFile, pchPreviewFile, nConsumerAppId, pchTitle, pchDescription, eVisibility, pTags, eWorkshopFileType);
	return 1;
}

S_CLASSAPI PublishedFileUpdateHandle_t S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_CreatePublishedFileUpdateRequest(SELF, PublishedFileId_t unPublishedFileId)
{
	xlogf("%s(self = %p, unPublishedFileId = %llu)\n", __func__, self, unPublishedFileId);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_UpdatePublishedFileFile(SELF, PublishedFileUpdateHandle_t updateHandle, const char *pchFile)
{
	xlogf("%s(self = %p, updateHandle = %llu, pchFile = %s)\n", __func__, self, updateHandle, pchFile);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_UpdatePublishedFilePreviewFile(SELF, PublishedFileUpdateHandle_t updateHandle, const char *pchPreviewFile)
{
	xlogf("%s(self = %p, updateHandle = %llu, pchPreviewFile = %s)\n", __func__, self, updateHandle, pchPreviewFile);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_UpdatePublishedFileTitle(SELF, PublishedFileUpdateHandle_t updateHandle, const char *pchTitle)
{
	xlogf("%s(self = %p, updateHandle = %llu, pchTitle = %s)\n", __func__, self, updateHandle, pchTitle);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_UpdatePublishedFileDescription(SELF, PublishedFileUpdateHandle_t updateHandle, const char *pchDescription)
{
	xlogf("%s(self = %p, updateHandle = %llu, pchDescription = %s)\n", __func__, self, updateHandle, pchDescription);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_UpdatePublishedFileVisibility(SELF, PublishedFileUpdateHandle_t updateHandle, ERemoteStoragePublishedFileVisibility eVisibility)
{
	xlogf("%s(self = %p, updateHandle = %llu, eVisibility = %d)\n", __func__, self, updateHandle, eVisibility);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_UpdatePublishedFileTags(SELF, PublishedFileUpdateHandle_t updateHandle, SteamParamStringArray_t *pTags)
{
	xlogf("%s(self = %p, updateHandle = %llu, pTags = %p)\n", __func__, self, updateHandle, pTags);
	return true;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_CommitPublishedFileUpdate(SELF, PublishedFileUpdateHandle_t updateHandle)
{
	xlogf("%s(self = %p, updateHandle = %llu)\n", __func__, self, updateHandle);
	return 1;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_GetPublishedFileDetails(SELF, PublishedFileId_t unPublishedFileId, uint32 unMaxSecondsOld)
{
	xlogf("%s(self = %p, unPublishedFileId = %llu, unMaxSecondsOld = %d)\n", __func__, self, unPublishedFileId, unMaxSecondsOld);
	return 1;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_DeletePublishedFile(SELF, PublishedFileId_t unPublishedFileId)
{
	xlogf("%s(self = %p, unPublishedFileId = %llu)\n", __func__, self, unPublishedFileId);
	return 1;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_EnumerateUserPublishedFiles(SELF, uint32 unStartIndex)
{
	xlogf("%s(self = %p, unStartIndex = %d)\n", __func__, self, unStartIndex);
	return 1;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_SubscribePublishedFile(SELF, PublishedFileId_t unPublishedFileId)
{
	xlogf("%s(self = %p, unPublishedFileId = %llu)\n", __func__, self, unPublishedFileId);
	return 1;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_EnumerateUserSubscribedFiles(SELF, uint32 unStartIndex)
{
	xlogf("%s(self = %p, unStartIndex = %d)\n", __func__, self, unStartIndex);
	return 1;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_UnsubscribePublishedFile(SELF, PublishedFileId_t unPublishedFileId)
{
	xlogf("%s(self = %p, unPublishedFileId = %llu)\n", __func__, self, unPublishedFileId);
	return 1;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_UpdatePublishedFileSetChangeDescription(SELF, PublishedFileUpdateHandle_t updateHandle, const char *pchChangeDescription)
{
	xlogf("%s(self = %p, updateHandle = %llu, pchChangeDescription = %s)\n", __func__, self, updateHandle, pchChangeDescription);
	return true;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_GetPublishedItemVoteDetails(SELF, PublishedFileId_t unPublishedFileId)
{
	xlogf("%s(self = %p, unPublishedFileId = %llu)\n", __func__, self, unPublishedFileId);
	return 1;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_UpdateUserPublishedItemVote(SELF, PublishedFileId_t unPublishedFileId, bool bVoteUp)
{
	xlogf("%s(self = %p, unPublishedFileId = %llu, bVoteUp = %d)\n", __func__, self, unPublishedFileId, bVoteUp);
	return false;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_GetUserPublishedItemVoteDetails(SELF, PublishedFileId_t unPublishedFileId)
{
	xlogf("%s(self = %p, unPublishedFileId = %llu)\n", __func__, self, unPublishedFileId);
	return 1;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_EnumerateUserSharedWorkshopFiles(SELF, CSteamID steamId, uint32 unStartIndex, SteamParamStringArray_t *pRequiredTags, SteamParamStringArray_t *pExcludedTags)
{
	xlogf("%s(self = %p, steamId = %llu, unStartIndex = %d, pRequiredTags = %p, pExcludedTags = %p)\n", __func__, self, steamId.m_gameID, unStartIndex, pRequiredTags, pExcludedTags);
	return 1;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_SetUserPublishedFileAction(SELF, PublishedFileId_t unPublishedFileId, EWorkshopFileAction eAction)
{
	xlogf("%s(self = %p, unPublishedFileId = %llu, eAction = %d)\n", __func__, self, unPublishedFileId, eAction);
	return 1;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_PublishVideo(SELF, EWorkshopVideoProvider eVideoProvider, const char *pchVideoAccount, const char *pchVideoIdentifier, const char *pchPreviewFile, AppId_t nConsumerAppId, const char *pchTitle, const char *pchDescription, ERemoteStoragePublishedFileVisibility eVisibility, SteamParamStringArray_t *pTags)
{
	xlogf("%s(self = %p, eVideoProvider = %d, pchVideoAccount = %s, pchVideoIdentifier = %s, pchPreviewFile = %s, nConsumerAppId = %d, pchTitle = %s, pchDescription = %s, eVisibility = %d, pTags= %p)\n", __func__, self, eVideoProvider, pchVideoAccount, pchVideoIdentifier, pchPreviewFile, nConsumerAppId, pchTitle, pchDescription, eVisibility, pTags);
	return 1;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_EnumeratePublishedFilesByUserAction(SELF, EWorkshopFileAction eAction, uint32 unStartIndex)
{
	xlogf("%s(self = %p, eAction = %d, unStartIndex = %d)\n", __func__, self, eAction, unStartIndex);
	return 1;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_EnumeratePublishedWorkshopFiles(SELF, EWorkshopEnumerationType eEnumerationType, uint32 unStartIndex, uint32 unCount, uint32 unDays, SteamParamStringArray_t *pTags, SteamParamStringArray_t *pUserTags)
{
	xlogf("%s(self = %p, eEnumerationType = %d, unStartIndex = %d, unCount = %d, unDays = %d, pTags = %p, pUserTags = %p)\n", __func__, self, eEnumerationType, unStartIndex, unCount, unDays, pTags, pUserTags);
	return 1;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_UGCDownloadToLocation(SELF, UGCHandle_t hContent, const char *pchLocation, uint32 unPriority)
{
	xlogf("%s(self = %p, hContent = %llu, pchLocation = %s, unPriority = %d)\n", __func__, self, hContent, pchLocation, unPriority);
	return 1;
}

S_CLASSAPI int32 S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_GetLocalFileChangeCount(SELF)
{
	xlogf("%s(self = %p)", __func__, self);
	return 0;
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_GetLocalFileChange(SELF, int iFile, ERemoteStorageLocalFileChange *pEChangeType, ERemoteStorageFilePathType *pEFilePathType)
{
	xlogf("%s(self = %p, iFile = %d, pEChangeType = %p, pEFilePathType = %p)", __func__, self, iFile, pEChangeType, pEFilePathType);
	return NULL;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_BeginFileWriteBatch(SELF)
{
	xlogf("%s(self = %p)", __func__, self);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamRemoteStorage_EndFileWriteBatch(SELF)
{
	xlogf("%s(self = %p)", __func__, self);
	return true;
}