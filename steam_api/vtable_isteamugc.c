#include "steam.h"

static void *vtable_ISteamUGC007[] = {
    SteamAPI_ISteamUGC_CreateQueryUserUGCRequest,
    SteamAPI_ISteamUGC_CreateQueryAllUGCRequest,
    SteamAPI_ISteamUGC_CreateQueryUGCDetailsRequest,
    SteamAPI_ISteamUGC_SendQueryUGCRequest,
    SteamAPI_ISteamUGC_GetQueryUGCResult,
    SteamAPI_ISteamUGC_GetQueryUGCPreviewURL,
    SteamAPI_ISteamUGC_GetQueryUGCMetadata,
    SteamAPI_ISteamUGC_GetQueryUGCChildren,
    SteamAPI_ISteamUGC_GetQueryUGCStatistic,
    SteamAPI_ISteamUGC_GetQueryUGCNumAdditionalPreviews,
    SteamAPI_ISteamUGC_GetQueryUGCAdditionalPreview,
    SteamAPI_ISteamUGC_GetQueryUGCNumKeyValueTags,
    SteamAPI_ISteamUGC_GetQueryUGCKeyValueTag,
    SteamAPI_ISteamUGC_ReleaseQueryUGCRequest,
    SteamAPI_ISteamUGC_AddRequiredTag,
    SteamAPI_ISteamUGC_AddExcludedTag,
    SteamAPI_ISteamUGC_SetReturnKeyValueTags,
    SteamAPI_ISteamUGC_SetReturnLongDescription,
    SteamAPI_ISteamUGC_SetReturnMetadata,
    SteamAPI_ISteamUGC_SetReturnChildren,
    SteamAPI_ISteamUGC_SetReturnAdditionalPreviews,
    SteamAPI_ISteamUGC_SetReturnTotalOnly,
    SteamAPI_ISteamUGC_SetLanguage,
    SteamAPI_ISteamUGC_SetAllowCachedResponse,
    SteamAPI_ISteamUGC_SetCloudFileNameFilter,
    SteamAPI_ISteamUGC_SetMatchAnyTag,
    SteamAPI_ISteamUGC_SetSearchText,
    SteamAPI_ISteamUGC_SetRankedByTrendDays,
    SteamAPI_ISteamUGC_AddRequiredKeyValueTag,
    SteamAPI_ISteamUGC_RequestUGCDetails,
    SteamAPI_ISteamUGC_CreateItem,
    SteamAPI_ISteamUGC_StartItemUpdate,
    SteamAPI_ISteamUGC_SetItemTitle,
    SteamAPI_ISteamUGC_SetItemDescription,
    SteamAPI_ISteamUGC_SetItemUpdateLanguage,
    SteamAPI_ISteamUGC_SetItemMetadata,
    SteamAPI_ISteamUGC_SetItemVisibility,
    SteamAPI_ISteamUGC_SetItemTags,
    SteamAPI_ISteamUGC_SetItemContent,
    SteamAPI_ISteamUGC_SetItemPreview,
    SteamAPI_ISteamUGC_RemoveItemKeyValueTags,
    SteamAPI_ISteamUGC_AddItemKeyValueTag,
    SteamAPI_ISteamUGC_SubmitItemUpdate,
    SteamAPI_ISteamUGC_GetItemUpdateProgress,
    SteamAPI_ISteamUGC_SetUserItemVote,
    SteamAPI_ISteamUGC_GetUserItemVote,
    SteamAPI_ISteamUGC_AddItemToFavorites,
    SteamAPI_ISteamUGC_RemoveItemFromFavorites,
    SteamAPI_ISteamUGC_SubscribeItem,
    SteamAPI_ISteamUGC_UnsubscribeItem,
    SteamAPI_ISteamUGC_GetNumSubscribedItems,
    SteamAPI_ISteamUGC_GetSubscribedItems,
    SteamAPI_ISteamUGC_GetItemState,
    SteamAPI_ISteamUGC_GetItemInstallInfo,
    SteamAPI_ISteamUGC_GetItemDownloadInfo,
    SteamAPI_ISteamUGC_DownloadItem,
    SteamAPI_ISteamUGC_BInitWorkshopForGameServer,
    SteamAPI_ISteamUGC_SuspendDownloads,
};

static void *vtable_ISteamUGC008[] = {
    SteamAPI_ISteamUGC_CreateQueryUserUGCRequest,
    SteamAPI_ISteamUGC_CreateQueryAllUGCRequest,
    SteamAPI_ISteamUGC_CreateQueryUGCDetailsRequest,
    SteamAPI_ISteamUGC_SendQueryUGCRequest,
    SteamAPI_ISteamUGC_GetQueryUGCResult,
    SteamAPI_ISteamUGC_GetQueryUGCPreviewURL,
    SteamAPI_ISteamUGC_GetQueryUGCMetadata,
    SteamAPI_ISteamUGC_GetQueryUGCChildren,
    SteamAPI_ISteamUGC_GetQueryUGCStatistic,
    SteamAPI_ISteamUGC_GetQueryUGCNumAdditionalPreviews,
    SteamAPI_ISteamUGC_GetQueryUGCAdditionalPreview,
    SteamAPI_ISteamUGC_GetQueryUGCNumKeyValueTags,
    SteamAPI_ISteamUGC_GetQueryUGCKeyValueTag,
    SteamAPI_ISteamUGC_ReleaseQueryUGCRequest,
    SteamAPI_ISteamUGC_AddRequiredTag,
    SteamAPI_ISteamUGC_AddExcludedTag,
    SteamAPI_ISteamUGC_SetReturnKeyValueTags,
    SteamAPI_ISteamUGC_SetReturnLongDescription,
    SteamAPI_ISteamUGC_SetReturnMetadata,
    SteamAPI_ISteamUGC_SetReturnChildren,
    SteamAPI_ISteamUGC_SetReturnAdditionalPreviews,
    SteamAPI_ISteamUGC_SetReturnTotalOnly,
    SteamAPI_ISteamUGC_SetLanguage,
    SteamAPI_ISteamUGC_SetAllowCachedResponse,
    SteamAPI_ISteamUGC_SetCloudFileNameFilter,
    SteamAPI_ISteamUGC_SetMatchAnyTag,
    SteamAPI_ISteamUGC_SetSearchText,
    SteamAPI_ISteamUGC_SetRankedByTrendDays,
    SteamAPI_ISteamUGC_AddRequiredKeyValueTag,
    SteamAPI_ISteamUGC_RequestUGCDetails,
    SteamAPI_ISteamUGC_CreateItem,
    SteamAPI_ISteamUGC_StartItemUpdate,
    SteamAPI_ISteamUGC_SetItemTitle,
    SteamAPI_ISteamUGC_SetItemDescription,
    SteamAPI_ISteamUGC_SetItemUpdateLanguage,
    SteamAPI_ISteamUGC_SetItemMetadata,
    SteamAPI_ISteamUGC_SetItemVisibility,
    SteamAPI_ISteamUGC_SetItemTags,
    SteamAPI_ISteamUGC_SetItemContent,
    SteamAPI_ISteamUGC_SetItemPreview,
    SteamAPI_ISteamUGC_RemoveItemKeyValueTags,
    SteamAPI_ISteamUGC_AddItemKeyValueTag,
    SteamAPI_ISteamUGC_AddItemPreviewFile,
    SteamAPI_ISteamUGC_AddItemPreviewVideo,
    SteamAPI_ISteamUGC_UpdateItemPreviewFile,
    SteamAPI_ISteamUGC_UpdateItemPreviewVideo,
    SteamAPI_ISteamUGC_RemoveItemPreview,
    SteamAPI_ISteamUGC_SubmitItemUpdate,
    SteamAPI_ISteamUGC_GetItemUpdateProgress,
    SteamAPI_ISteamUGC_SetUserItemVote,
    SteamAPI_ISteamUGC_GetUserItemVote,
    SteamAPI_ISteamUGC_AddItemToFavorites,
    SteamAPI_ISteamUGC_RemoveItemFromFavorites,
    SteamAPI_ISteamUGC_SubscribeItem,
    SteamAPI_ISteamUGC_UnsubscribeItem,
    SteamAPI_ISteamUGC_GetNumSubscribedItems,
    SteamAPI_ISteamUGC_GetSubscribedItems,
    SteamAPI_ISteamUGC_GetItemState,
    SteamAPI_ISteamUGC_GetItemInstallInfo,
    SteamAPI_ISteamUGC_GetItemDownloadInfo,
    SteamAPI_ISteamUGC_DownloadItem,
    SteamAPI_ISteamUGC_BInitWorkshopForGameServer,
    SteamAPI_ISteamUGC_SuspendDownloads,
    SteamAPI_ISteamUGC_StartPlaytimeTracking,
    SteamAPI_ISteamUGC_StopPlaytimeTracking,
    SteamAPI_ISteamUGC_StopPlaytimeTrackingForAllItems,
};

static void *vtable_ISteamUGC009[] = {
    SteamAPI_ISteamUGC_CreateQueryUserUGCRequest,
    SteamAPI_ISteamUGC_CreateQueryAllUGCRequest,
    SteamAPI_ISteamUGC_CreateQueryUGCDetailsRequest,
    SteamAPI_ISteamUGC_SendQueryUGCRequest,
    SteamAPI_ISteamUGC_GetQueryUGCResult,
    SteamAPI_ISteamUGC_GetQueryUGCPreviewURL,
    SteamAPI_ISteamUGC_GetQueryUGCMetadata,
    SteamAPI_ISteamUGC_GetQueryUGCChildren,
    SteamAPI_ISteamUGC_GetQueryUGCStatistic,
    SteamAPI_ISteamUGC_GetQueryUGCNumAdditionalPreviews,
    SteamAPI_ISteamUGC_GetQueryUGCAdditionalPreview,
    SteamAPI_ISteamUGC_GetQueryUGCNumKeyValueTags,
    SteamAPI_ISteamUGC_GetQueryUGCKeyValueTag,
    SteamAPI_ISteamUGC_ReleaseQueryUGCRequest,
    SteamAPI_ISteamUGC_AddRequiredTag,
    SteamAPI_ISteamUGC_AddExcludedTag,
    SteamAPI_ISteamUGC_SetReturnOnlyIDs,
    SteamAPI_ISteamUGC_SetReturnKeyValueTags,
    SteamAPI_ISteamUGC_SetReturnLongDescription,
    SteamAPI_ISteamUGC_SetReturnMetadata,
    SteamAPI_ISteamUGC_SetReturnChildren,
    SteamAPI_ISteamUGC_SetReturnAdditionalPreviews,
    SteamAPI_ISteamUGC_SetReturnTotalOnly,
    SteamAPI_ISteamUGC_SetLanguage,
    SteamAPI_ISteamUGC_SetAllowCachedResponse,
    SteamAPI_ISteamUGC_SetCloudFileNameFilter,
    SteamAPI_ISteamUGC_SetMatchAnyTag,
    SteamAPI_ISteamUGC_SetSearchText,
    SteamAPI_ISteamUGC_SetRankedByTrendDays,
    SteamAPI_ISteamUGC_AddRequiredKeyValueTag,
    SteamAPI_ISteamUGC_RequestUGCDetails,
    SteamAPI_ISteamUGC_CreateItem,
    SteamAPI_ISteamUGC_StartItemUpdate,
    SteamAPI_ISteamUGC_SetItemTitle,
    SteamAPI_ISteamUGC_SetItemDescription,
    SteamAPI_ISteamUGC_SetItemUpdateLanguage,
    SteamAPI_ISteamUGC_SetItemMetadata,
    SteamAPI_ISteamUGC_SetItemVisibility,
    SteamAPI_ISteamUGC_SetItemTags,
    SteamAPI_ISteamUGC_SetItemContent,
    SteamAPI_ISteamUGC_SetItemPreview,
    SteamAPI_ISteamUGC_RemoveItemKeyValueTags,
    SteamAPI_ISteamUGC_AddItemKeyValueTag,
    SteamAPI_ISteamUGC_AddItemPreviewFile,
    SteamAPI_ISteamUGC_AddItemPreviewVideo,
    SteamAPI_ISteamUGC_UpdateItemPreviewFile,
    SteamAPI_ISteamUGC_UpdateItemPreviewVideo,
    SteamAPI_ISteamUGC_RemoveItemPreview,
    SteamAPI_ISteamUGC_SubmitItemUpdate,
    SteamAPI_ISteamUGC_GetItemUpdateProgress,
    SteamAPI_ISteamUGC_SetUserItemVote,
    SteamAPI_ISteamUGC_GetUserItemVote,
    SteamAPI_ISteamUGC_AddItemToFavorites,
    SteamAPI_ISteamUGC_RemoveItemFromFavorites,
    SteamAPI_ISteamUGC_SubscribeItem,
    SteamAPI_ISteamUGC_UnsubscribeItem,
    SteamAPI_ISteamUGC_GetNumSubscribedItems,
    SteamAPI_ISteamUGC_GetSubscribedItems,
    SteamAPI_ISteamUGC_GetItemState,
    SteamAPI_ISteamUGC_GetItemInstallInfo,
    SteamAPI_ISteamUGC_GetItemDownloadInfo,
    SteamAPI_ISteamUGC_DownloadItem,
    SteamAPI_ISteamUGC_BInitWorkshopForGameServer,
    SteamAPI_ISteamUGC_SuspendDownloads,
    SteamAPI_ISteamUGC_StartPlaytimeTracking,
    SteamAPI_ISteamUGC_StopPlaytimeTracking,
    SteamAPI_ISteamUGC_StopPlaytimeTrackingForAllItems,
};

static void *vtable_ISteamUGC010[] = {
    SteamAPI_ISteamUGC_CreateQueryUserUGCRequest,
    SteamAPI_ISteamUGC_CreateQueryAllUGCRequest,
    SteamAPI_ISteamUGC_CreateQueryUGCDetailsRequest,
    SteamAPI_ISteamUGC_SendQueryUGCRequest,
    SteamAPI_ISteamUGC_GetQueryUGCResult,
    SteamAPI_ISteamUGC_GetQueryUGCPreviewURL,
    SteamAPI_ISteamUGC_GetQueryUGCMetadata,
    SteamAPI_ISteamUGC_GetQueryUGCChildren,
    SteamAPI_ISteamUGC_GetQueryUGCStatistic,
    SteamAPI_ISteamUGC_GetQueryUGCNumAdditionalPreviews,
    SteamAPI_ISteamUGC_GetQueryUGCAdditionalPreview,
    SteamAPI_ISteamUGC_GetQueryUGCNumKeyValueTags,
    SteamAPI_ISteamUGC_GetQueryUGCKeyValueTag,
    SteamAPI_ISteamUGC_ReleaseQueryUGCRequest,
    SteamAPI_ISteamUGC_AddRequiredTag,
    SteamAPI_ISteamUGC_AddExcludedTag,
    SteamAPI_ISteamUGC_SetReturnOnlyIDs,
    SteamAPI_ISteamUGC_SetReturnKeyValueTags,
    SteamAPI_ISteamUGC_SetReturnLongDescription,
    SteamAPI_ISteamUGC_SetReturnMetadata,
    SteamAPI_ISteamUGC_SetReturnChildren,
    SteamAPI_ISteamUGC_SetReturnAdditionalPreviews,
    SteamAPI_ISteamUGC_SetReturnTotalOnly,
    SteamAPI_ISteamUGC_SetReturnPlaytimeStats,
    SteamAPI_ISteamUGC_SetLanguage,
    SteamAPI_ISteamUGC_SetAllowCachedResponse,
    SteamAPI_ISteamUGC_SetCloudFileNameFilter,
    SteamAPI_ISteamUGC_SetMatchAnyTag,
    SteamAPI_ISteamUGC_SetSearchText,
    SteamAPI_ISteamUGC_SetRankedByTrendDays,
    SteamAPI_ISteamUGC_AddRequiredKeyValueTag,
    SteamAPI_ISteamUGC_RequestUGCDetails,
    SteamAPI_ISteamUGC_CreateItem,
    SteamAPI_ISteamUGC_StartItemUpdate,
    SteamAPI_ISteamUGC_SetItemTitle,
    SteamAPI_ISteamUGC_SetItemDescription,
    SteamAPI_ISteamUGC_SetItemUpdateLanguage,
    SteamAPI_ISteamUGC_SetItemMetadata,
    SteamAPI_ISteamUGC_SetItemVisibility,
    SteamAPI_ISteamUGC_SetItemTags,
    SteamAPI_ISteamUGC_SetItemContent,
    SteamAPI_ISteamUGC_SetItemPreview,
    SteamAPI_ISteamUGC_RemoveItemKeyValueTags,
    SteamAPI_ISteamUGC_AddItemKeyValueTag,
    SteamAPI_ISteamUGC_AddItemPreviewFile,
    SteamAPI_ISteamUGC_AddItemPreviewVideo,
    SteamAPI_ISteamUGC_UpdateItemPreviewFile,
    SteamAPI_ISteamUGC_UpdateItemPreviewVideo,
    SteamAPI_ISteamUGC_RemoveItemPreview,
    SteamAPI_ISteamUGC_SubmitItemUpdate,
    SteamAPI_ISteamUGC_GetItemUpdateProgress,
    SteamAPI_ISteamUGC_SetUserItemVote,
    SteamAPI_ISteamUGC_GetUserItemVote,
    SteamAPI_ISteamUGC_AddItemToFavorites,
    SteamAPI_ISteamUGC_RemoveItemFromFavorites,
    SteamAPI_ISteamUGC_SubscribeItem,
    SteamAPI_ISteamUGC_UnsubscribeItem,
    SteamAPI_ISteamUGC_GetNumSubscribedItems,
    SteamAPI_ISteamUGC_GetSubscribedItems,
    SteamAPI_ISteamUGC_GetItemState,
    SteamAPI_ISteamUGC_GetItemInstallInfo,
    SteamAPI_ISteamUGC_GetItemDownloadInfo,
    SteamAPI_ISteamUGC_DownloadItem,
    SteamAPI_ISteamUGC_BInitWorkshopForGameServer,
    SteamAPI_ISteamUGC_SuspendDownloads,
    SteamAPI_ISteamUGC_StartPlaytimeTracking,
    SteamAPI_ISteamUGC_StopPlaytimeTracking,
    SteamAPI_ISteamUGC_StopPlaytimeTrackingForAllItems,
    SteamAPI_ISteamUGC_AddDependency,
    SteamAPI_ISteamUGC_RemoveDependency,
    SteamAPI_ISteamUGC_AddAppDependency,
    SteamAPI_ISteamUGC_RemoveAppDependency,
    SteamAPI_ISteamUGC_GetAppDependencies,
    SteamAPI_ISteamUGC_DeleteItem,
};

static void *vtable_ISteamUGC016[] = {
    SteamAPI_ISteamUGC_CreateQueryUserUGCRequest,
    SteamAPI_ISteamUGC_CreateQueryAllUGCRequest,
    SteamAPI_ISteamUGC_CreateQueryAllUGCRequest,
    SteamAPI_ISteamUGC_CreateQueryUGCDetailsRequest,
    SteamAPI_ISteamUGC_SendQueryUGCRequest,
    SteamAPI_ISteamUGC_GetQueryUGCResult,
    SteamAPI_ISteamUGC_GetQueryUGCNumTags,
    SteamAPI_ISteamUGC_GetQueryUGCTag,
    SteamAPI_ISteamUGC_GetQueryUGCTagDisplayName,
    SteamAPI_ISteamUGC_GetQueryUGCPreviewURL,
    SteamAPI_ISteamUGC_GetQueryUGCMetadata,
    SteamAPI_ISteamUGC_GetQueryUGCChildren,
    SteamAPI_ISteamUGC_GetQueryUGCStatistic,
    SteamAPI_ISteamUGC_GetQueryUGCNumAdditionalPreviews,
    SteamAPI_ISteamUGC_GetQueryUGCAdditionalPreview,
    SteamAPI_ISteamUGC_GetQueryUGCNumKeyValueTags,
    SteamAPI_ISteamUGC_GetQueryUGCKeyValueTag,
    SteamAPI_ISteamUGC_ReleaseQueryUGCRequest,
    SteamAPI_ISteamUGC_AddRequiredTag,
    SteamAPI_ISteamUGC_AddRequiredTagGroup,
    SteamAPI_ISteamUGC_AddExcludedTag,
    SteamAPI_ISteamUGC_SetReturnOnlyIDs,
    SteamAPI_ISteamUGC_SetReturnKeyValueTags,
    SteamAPI_ISteamUGC_SetReturnLongDescription,
    SteamAPI_ISteamUGC_SetReturnMetadata,
    SteamAPI_ISteamUGC_SetReturnChildren,
    SteamAPI_ISteamUGC_SetReturnAdditionalPreviews,
    SteamAPI_ISteamUGC_SetReturnTotalOnly,
    SteamAPI_ISteamUGC_SetReturnPlaytimeStats,
    SteamAPI_ISteamUGC_SetLanguage,
    SteamAPI_ISteamUGC_SetAllowCachedResponse,
    SteamAPI_ISteamUGC_SetCloudFileNameFilter,
    SteamAPI_ISteamUGC_SetMatchAnyTag,
    SteamAPI_ISteamUGC_SetSearchText,
    SteamAPI_ISteamUGC_SetRankedByTrendDays,
    SteamAPI_ISteamUGC_SetTimeCreatedDateRange,
    SteamAPI_ISteamUGC_SetTimeUpdatedDateRange,
    SteamAPI_ISteamUGC_AddRequiredKeyValueTag,
    SteamAPI_ISteamUGC_RequestUGCDetails,
    SteamAPI_ISteamUGC_CreateItem,
    SteamAPI_ISteamUGC_StartItemUpdate,
    SteamAPI_ISteamUGC_SetItemTitle,
    SteamAPI_ISteamUGC_SetItemDescription,
    SteamAPI_ISteamUGC_SetItemUpdateLanguage,
    SteamAPI_ISteamUGC_SetItemMetadata,
    SteamAPI_ISteamUGC_SetItemVisibility,
    SteamAPI_ISteamUGC_SetItemTags,
    SteamAPI_ISteamUGC_SetItemContent,
    SteamAPI_ISteamUGC_SetItemPreview,
    SteamAPI_ISteamUGC_SetAllowLegacyUpload,
    SteamAPI_ISteamUGC_RemoveAllItemKeyValueTags,
    SteamAPI_ISteamUGC_RemoveItemKeyValueTags,
    SteamAPI_ISteamUGC_AddItemKeyValueTag,
    SteamAPI_ISteamUGC_AddItemPreviewFile,
    SteamAPI_ISteamUGC_AddItemPreviewVideo,
    SteamAPI_ISteamUGC_UpdateItemPreviewFile,
    SteamAPI_ISteamUGC_UpdateItemPreviewVideo,
    SteamAPI_ISteamUGC_RemoveItemPreview,
    SteamAPI_ISteamUGC_SubmitItemUpdate,
    SteamAPI_ISteamUGC_GetItemUpdateProgress,
    SteamAPI_ISteamUGC_SetUserItemVote,
    SteamAPI_ISteamUGC_GetUserItemVote,
    SteamAPI_ISteamUGC_AddItemToFavorites,
    SteamAPI_ISteamUGC_RemoveItemFromFavorites,
    SteamAPI_ISteamUGC_SubscribeItem,
    SteamAPI_ISteamUGC_UnsubscribeItem,
    SteamAPI_ISteamUGC_GetNumSubscribedItems,
    SteamAPI_ISteamUGC_GetSubscribedItems,
    SteamAPI_ISteamUGC_GetItemState,
    SteamAPI_ISteamUGC_GetItemInstallInfo,
    SteamAPI_ISteamUGC_GetItemDownloadInfo,
    SteamAPI_ISteamUGC_DownloadItem,
    SteamAPI_ISteamUGC_BInitWorkshopForGameServer,
    SteamAPI_ISteamUGC_SuspendDownloads,
    SteamAPI_ISteamUGC_StartPlaytimeTracking,
    SteamAPI_ISteamUGC_StopPlaytimeTracking,
    SteamAPI_ISteamUGC_StopPlaytimeTrackingForAllItems,
    SteamAPI_ISteamUGC_AddDependency,
    SteamAPI_ISteamUGC_RemoveDependency,
    SteamAPI_ISteamUGC_AddAppDependency,
    SteamAPI_ISteamUGC_RemoveAppDependency,
    SteamAPI_ISteamUGC_GetAppDependencies,
    SteamAPI_ISteamUGC_DeleteItem,
    SteamAPI_ISteamUGC_ShowWorkshopEULA,
    SteamAPI_ISteamUGC_GetWorkshopEULAStatus,
};

VtableEntry vtable_ISteamUGC[] = {
    {7, vtable_ISteamUGC007, sizeof(vtable_ISteamUGC007), 0},
    {8, vtable_ISteamUGC008, sizeof(vtable_ISteamUGC008), 0},
    {9, vtable_ISteamUGC009, sizeof(vtable_ISteamUGC009), 0},
    {10, vtable_ISteamUGC010, sizeof(vtable_ISteamUGC010), 0},
    {16, vtable_ISteamUGC016, sizeof(vtable_ISteamUGC016), 0},
    {0, NULL, 0, 0},
};