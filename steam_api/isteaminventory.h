#pragma once

#include "steamtypes.h"

typedef void ISteamInventory;
typedef struct SteamItemDetails_t SteamItemDetails_t;

typedef struct CSteamInventory CSteamInventory;

struct CSteamInventory {
	CSteamBase base;
};

typedef int32 SteamInventoryResult_t;
typedef int32 SteamItemDef_t;
typedef uint64 SteamItemInstanceID_t;
typedef uint64 SteamInventoryUpdateHandle_t;

enum {
	k_SteamInventoryResultInvalid = -1,
	k_SteamItemInstanceIDInvalid = -1,
};

struct SteamItemDetails_t {
	SteamItemInstanceID_t m_itemId;
	SteamItemDef_t m_iDefinition;
	uint16 m_unQuantity;
	uint16 m_unFlags; // see ESteamItemFlags
};

typedef int32 SteamInventoryResult_t;

S_CLASSAPI EResult S_CLASSCALLTYPE SteamAPI_ISteamInventory_GetResultStatus(SELF, SteamInventoryResult_t resultHandle);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamInventory_GetResultItems(SELF, SteamInventoryResult_t resultHandle, struct SteamItemDetails_t *pOutItemsArray, uint32 *punOutItemsArraySize);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamInventory_GetResultItemProperty(SELF, SteamInventoryResult_t resultHandle, uint32 unItemIndex, const char *pchPropertyName, char *pchValueBuffer, uint32 *punValueBufferSizeOut);
S_CLASSAPI uint32 S_CLASSCALLTYPE SteamAPI_ISteamInventory_GetResultTimestamp(SELF, SteamInventoryResult_t resultHandle);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamInventory_CheckResultSteamID(SELF, SteamInventoryResult_t resultHandle, CSteamID steamIDExpected);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamInventory_DestroyResult(SELF, SteamInventoryResult_t resultHandle);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamInventory_GetAllItems(SELF, SteamInventoryResult_t *pResultHandle);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamInventory_GetItemsByID(SELF, SteamInventoryResult_t *pResultHandle, const SteamItemInstanceID_t *pInstanceIDs, uint32 unCountInstanceIDs);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamInventory_SerializeResult(SELF, SteamInventoryResult_t resultHandle, void *pOutBuffer, uint32 *punOutBufferSize);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamInventory_DeserializeResult(SELF, SteamInventoryResult_t *pOutResultHandle, const void *pBuffer, uint32 unBufferSize, bool bRESERVED_MUST_BE_FALSE);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamInventory_GenerateItems(SELF, SteamInventoryResult_t *pResultHandle, const SteamItemDef_t *pArrayItemDefs, const uint32 *punArrayQuantity, uint32 unArrayLength);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamInventory_GrantPromoItems(SELF, SteamInventoryResult_t *pResultHandle);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamInventory_AddPromoItem(SELF, SteamInventoryResult_t *pResultHandle, SteamItemDef_t itemDef);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamInventory_AddPromoItems(SELF, SteamInventoryResult_t *pResultHandle, const SteamItemDef_t *pArrayItemDefs, uint32 unArrayLength);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamInventory_ConsumeItem(SELF, SteamInventoryResult_t *pResultHandle, SteamItemInstanceID_t itemConsume, uint32 unQuantity);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamInventory_ExchangeItems(SELF, SteamInventoryResult_t *pResultHandle, const SteamItemDef_t *pArrayGenerate, const uint32 *punArrayGenerateQuantity, uint32 unArrayGenerateLength, const SteamItemInstanceID_t *pArrayDestroy, const uint32 *punArrayDestroyQuantity, uint32 unArrayDestroyLength);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamInventory_TransferItemQuantity(SELF, SteamInventoryResult_t *pResultHandle, SteamItemInstanceID_t itemIdSource, uint32 unQuantity, SteamItemInstanceID_t itemIdDest);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamInventory_SendItemDropHeartbeat(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamInventory_TriggerItemDrop(SELF, SteamInventoryResult_t *pResultHandle, SteamItemDef_t dropListDefinition);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamInventory_TradeItems(SELF, SteamInventoryResult_t *pResultHandle, CSteamID steamIDTradePartner, const SteamItemInstanceID_t *pArrayGive, const uint32 *pArrayGiveQuantity, uint32 nArrayGiveLength, const SteamItemInstanceID_t *pArrayGet, const uint32 *pArrayGetQuantity, uint32 nArrayGetLength);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamInventory_LoadItemDefinitions(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamInventory_GetItemDefinitionIDs(SELF, SteamItemDef_t *pItemDefIDs, uint32 *punItemDefIDsArraySize);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamInventory_GetItemDefinitionProperty(SELF, SteamItemDef_t iDefinition, const char *pchPropertyName, char *pchValueBuffer, uint32 *punValueBufferSize);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamInventory_RequestEligiblePromoItemDefinitionsIDs(SELF, CSteamID steamID);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamInventory_GetEligiblePromoItemDefinitionIDs(SELF, CSteamID steamID, SteamItemDef_t *pItemDefIDs, uint32 *punItemDefIDsArraySize);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamInventory_StartPurchase(SELF, const SteamItemDef_t *pArrayItemDefs, const uint32 *punArrayQuantity, uint32 unArrayLength);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamInventory_RequestPrices(SELF);
S_CLASSAPI uint32 S_CLASSCALLTYPE SteamAPI_ISteamInventory_GetNumItemsWithPrices(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamInventory_GetItemsWithPrices(SELF, SteamItemDef_t *pArrayItemDefs, uint64 *pPrices, uint32 unArrayLength);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamInventory_GetItemPrice(SELF, SteamItemDef_t iDefinition, uint64 *pPrice);
S_CLASSAPI SteamInventoryUpdateHandle_t S_CLASSCALLTYPE SteamAPI_ISteamInventory_StartUpdateProperties(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamInventory_RemoveProperty(SELF, SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char *pchPropertyName);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamInventory_SetPropertyString(SELF, SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char *pchPropertyName, const char *pchPropertyValue);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamInventory_SetPropertyBool(SELF, SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char *pchPropertyName, bool bValue);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamInventory_SetPropertyInt64(SELF, SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char *pchPropertyName, int64 nValue);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamInventory_SetPropertyFloat(SELF, SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char *pchPropertyName, float flValue);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamInventory_SubmitUpdateProperties(SELF, SteamInventoryUpdateHandle_t handle, SteamInventoryResult_t *pResultHandle);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamInventory_InspectItem(SELF, SteamInventoryResult_t *pResultHandle, const char *pchItemToken);