#include "steam.h"

S_CLASSAPI EResult S_CLASSCALLTYPE
SteamAPI_ISteamInventory_GetResultStatus(SELF, SteamInventoryResult_t resultHandle)
{
	xlogf("%s(self = %p, resultHandler = %d)\n", __func__, self, resultHandle);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInventory_GetResultItems(SELF, SteamInventoryResult_t resultHandle, struct SteamItemDetails_t *pOutItemsArray, uint32 *punOutItemsArraySize)
{
	xlogf("%s(self = %p, resultHandle = %ld, pOutItemsArray = %p, punOutItemsArraySize = %p)\n", __func__, self, (long)resultHandle, pOutItemsArray, punOutItemsArraySize);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInventory_GetResultItemProperty(SELF, SteamInventoryResult_t resultHandle, uint32 unItemIndex, const char *pchPropertyName, char *pchValueBuffer, uint32 *punValueBufferSizeOut)
{
	xlogf("%s(self = %p, resultHandle = %ld, unItemIndex = %u, pchPropertyName = %s, pchValueBuffer = %p, punValueBufferSizeOut = %p)\n",
	      __func__, self, (long)resultHandle, unItemIndex, pchPropertyName, pchValueBuffer, punValueBufferSizeOut);
	return true;
}

S_CLASSAPI uint32 S_CLASSCALLTYPE
SteamAPI_ISteamInventory_GetResultTimestamp(SELF, SteamInventoryResult_t resultHandle)
{
	xlogf("%s(self = %p, resultHandle = %d)\n", __func__, self, resultHandle);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInventory_CheckResultSteamID(SELF, SteamInventoryResult_t resultHandle, CSteamID steamIDExpected)
{
	xlogf("%s(self = %p, resultHandle = %d, gameID = %llu)\n", __func__, self, resultHandle, steamIDExpected.m_gameID);
	return true;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamInventory_DestroyResult(SELF, SteamInventoryResult_t resultHandle)
{
	xlogf("%s(self = %p, resultHandle = %d)\n", __func__, self, resultHandle);
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInventory_GetAllItems(SELF, SteamInventoryResult_t *pResultHandle)
{
	xlogf("%s(self = %p, pResultHandle = %p)\n", __func__, self, pResultHandle);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInventory_GetItemsByID(SELF, SteamInventoryResult_t *pResultHandle, const SteamItemInstanceID_t *pInstanceIDs, uint32 unCountInstanceIDs)
{
	xlogf("%s(self = %p, pResultHandle = %p, pInstanceIDs = %p, unCountInstanceIDs = %d)\n", __func__, self, pResultHandle, pInstanceIDs, unCountInstanceIDs);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInventory_SerializeResult(SELF, SteamInventoryResult_t resultHandle, void *pOutBuffer, uint32 *punOutBufferSize)
{
	xlogf("%s(self = %p, resultHandle = %d, pOutBuffer = %p, punOutBufferSize = %p)\n", __func__, self, resultHandle, pOutBuffer, punOutBufferSize);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInventory_DeserializeResult(SELF, SteamInventoryResult_t *pOutResultHandle, const void *pBuffer, uint32 unBufferSize, bool bRESERVED_MUST_BE_FALSE)
{
	xlogf("%s(self = %p, pOutResultHandle = %p, pBuffer = %p, unBufferSize = %d, bRESERVED_MUST_BE_FALSE = %d)\n", __func__, self, pOutResultHandle, pBuffer, unBufferSize, bRESERVED_MUST_BE_FALSE);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInventory_GenerateItems(SELF, SteamInventoryResult_t *pResultHandle, const SteamItemDef_t *pArrayItemDefs, const uint32 *punArrayQuantity, uint32 unArrayLength)
{
	xlogf("%s(self = %p, pResultHandle = %p, pArrayItemDefs = %p, punArrayQuantity = %p, unArrayLength = %d)\n", __func__, self, pResultHandle, pArrayItemDefs, punArrayQuantity, unArrayLength);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInventory_GrantPromoItems(SELF, SteamInventoryResult_t *pResultHandle)
{
	xlogf("%s(self = %p, pResultHandle = %p)\n", __func__, self, pResultHandle);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInventory_AddPromoItem(SELF, SteamInventoryResult_t *pResultHandle, SteamItemDef_t itemDef)
{
	xlogf("%s(self = %p, pResultHandle = %p, itemDef = %d)\n", __func__, self, pResultHandle, itemDef);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInventory_AddPromoItems(SELF, SteamInventoryResult_t *pResultHandle, const SteamItemDef_t *pArrayItemDefs, uint32 unArrayLength)
{
	xlogf("%s(self = %p, pResultHandle = %p, pArrayItemDefs = %p, unArrayLength = %d)\n", __func__, self, pResultHandle, pArrayItemDefs, unArrayLength);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInventory_ConsumeItem(SELF, SteamInventoryResult_t *pResultHandle, SteamItemInstanceID_t itemConsume, uint32 unQuantity)
{
	xlogf("%s(self = %p, pResultHandle = %p, itemConsume = %llu, unQuantity = %d)\n", __func__, self, pResultHandle, itemConsume, unQuantity);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInventory_ExchangeItems(SELF, SteamInventoryResult_t *pResultHandle, const SteamItemDef_t *pArrayGenerate, const uint32 *punArrayGenerateQuantity, uint32 unArrayGenerateLength, const SteamItemInstanceID_t *pArrayDestroy, const uint32 *punArrayDestroyQuantity, uint32 unArrayDestroyLength)
{
	xlogf("%s(self = %p, pResultHandle = %p, pArrayGenerate = %p,  punArrayGenerateQuantity = %p, unArrayGenerateLength = %d, pArrayDestroy = %p, punArrayDestroyQuantity = %p, unArrayDestroyLength = %d)\n", __func__, self, pResultHandle, pArrayGenerate, punArrayGenerateQuantity, unArrayGenerateLength, pArrayDestroy, punArrayDestroyQuantity, unArrayDestroyLength);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInventory_TransferItemQuantity(SELF, SteamInventoryResult_t *pResultHandle, SteamItemInstanceID_t itemIdSource, uint32 unQuantity, SteamItemInstanceID_t itemIdDest)
{
	xlogf("%s(self = %p, pResultHandle = %p, itemIdSource = %llu, unQuantity = %d, itemIdDest = %llu)\n", __func__, self, pResultHandle, itemIdSource, unQuantity, itemIdDest);
	return false;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamInventory_SendItemDropHeartbeat(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInventory_TriggerItemDrop(SELF, SteamInventoryResult_t *pResultHandle, SteamItemDef_t dropListDefinition)
{
	xlogf("%s(self = %p, pResultHandle = %p, dropListDefinition = %d)\n", __func__, self, pResultHandle, dropListDefinition);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInventory_TradeItems(SELF, SteamInventoryResult_t *pResultHandle, CSteamID steamIDTradePartner, const SteamItemInstanceID_t *pArrayGive, const uint32 *pArrayGiveQuantity, uint32 nArrayGiveLength, const SteamItemInstanceID_t *pArrayGet, const uint32 *pArrayGetQuantity, uint32 nArrayGetLength)
{
	xlogf("%s(self = %p, pResultHandle = %p, steamIDTradePartner = %llu, pArrayGive = %p, pArrayGiveQuantity = %p, nArrayGiveLength = %d, pArrayGet = %p, pArrayGetQuantity = %p, nArrayGetLength = %d)\n", __func__, self, pResultHandle, steamIDTradePartner.m_gameID, pArrayGive, pArrayGiveQuantity, nArrayGiveLength, pArrayGet, pArrayGetQuantity, nArrayGetLength);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInventory_LoadItemDefinitions(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInventory_GetItemDefinitionIDs(SELF, SteamItemDef_t *pItemDefIDs, uint32 *punItemDefIDsArraySize)
{
	xlogf("%s(self = %p, pItemDefIDs = %p, punItemDefIDsArraySize = %p)\n", __func__, self, pItemDefIDs, punItemDefIDsArraySize);
	*punItemDefIDsArraySize = 0;
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInventory_GetItemDefinitionProperty(SELF, SteamItemDef_t iDefinition, const char *pchPropertyName, char *pchValueBuffer, uint32 *punValueBufferSize)
{
	xlogf("%s(self = %p, iDefinition = %d, pchPropertyName = %s, pchValueBuffer = %s, punValueBufferSize = %p)\n", __func__, self, iDefinition, pchPropertyName, pchValueBuffer, punValueBufferSize);
	return false;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamInventory_RequestEligiblePromoItemDefinitionsIDs(SELF, CSteamID steamID)
{
	xlogf("%s(self = %p, steamID = %llu)\n", __func__, self, steamID.m_ulGameID);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInventory_GetEligiblePromoItemDefinitionIDs(SELF, CSteamID steamID, SteamItemDef_t *pItemDefIDs, uint32 *punItemDefIDsArraySize)
{
	xlogf("%s(self = %p, steamID = %llu, pItemDefIDs = %p, punItemDefIDsArraySize = %p)\n",
	      __func__, self, steamID.m_ulGameID, pItemDefIDs, punItemDefIDsArraySize);
	return false;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamInventory_StartPurchase(SELF, const SteamItemDef_t *pArrayItemDefs, const uint32 *punArrayQuantity, uint32 unArrayLength)
{
	xlogf("%s(self = %p, pArrayItemDefs = %p, punArrayQuantity = %p, unArrayLength = %u)\n",
	      __func__, self, pArrayItemDefs, punArrayQuantity, unArrayLength);
	return 0;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamInventory_RequestPrices(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI uint32 S_CLASSCALLTYPE
SteamAPI_ISteamInventory_GetNumItemsWithPrices(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInventory_GetItemsWithPrices(SELF, SteamItemDef_t *pArrayItemDefs, uint64 *pPrices, uint32 unArrayLength)
{
	xlogf("%s(self = %p, pArrayItemDefs = %p, pPrices = %p, unArrayLength = %u)\n",
	      __func__, self, pArrayItemDefs, pPrices, unArrayLength);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInventory_GetItemPrice(SELF, SteamItemDef_t iDefinition, uint64 *pPrice)
{
	xlogf("%s(self = %p, iDefinition = %u, pPrice = %p)\n", __func__, self, iDefinition, pPrice);
	return false;
}

S_CLASSAPI SteamInventoryUpdateHandle_t S_CLASSCALLTYPE
SteamAPI_ISteamInventory_StartUpdateProperties(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInventory_RemoveProperty(SELF, SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char *pchPropertyName)
{
	xlogf("%s(self = %p, handle = %llu, nItemID = %llu, pchPropertyName = %s)\n",
	      __func__, self, handle, nItemID, pchPropertyName);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInventory_SetPropertyString(SELF, SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char *pchPropertyName, const char *pchPropertyValue)
{
	xlogf("%s(self = %p, handle = %llu, nItemID = %llu, pchPropertyName = %s, pchPropertyValue = %s)\n",
	      __func__, self, handle, nItemID, pchPropertyName, pchPropertyValue);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInventory_SetPropertyBool(SELF, SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char *pchPropertyName, bool bValue)
{
	xlogf("%s(self = %p, handle = %llu, nItemID = %llu, pchPropertyName = %s, bValue = %d)\n",
	      __func__, self, handle, nItemID, pchPropertyName, bValue);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInventory_SetPropertyInt64(SELF, SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char *pchPropertyName, int64 nValue)
{
	xlogf("%s(self = %p, handle = %llu, nItemID = %llu, pchPropertyName = %s, nValue = %lld)\n",
	      __func__, self, handle, nItemID, pchPropertyName, nValue);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInventory_SetPropertyFloat(SELF, SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char *pchPropertyName, float flValue)
{
	xlogf("%s(self = %p, handle = %llu, nItemID = %llu, pchPropertyName = %s, fValue = %f)\n",
	      __func__, self, handle, nItemID, pchPropertyName, flValue);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInventory_SubmitUpdateProperties(SELF, SteamInventoryUpdateHandle_t handle, SteamInventoryResult_t *pResultHandle)
{
	xlogf("%s(self = %p, handle = %llu, pResultHandle = %p)\n", __func__, self, handle, pResultHandle);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamInventory_InspectItem(SELF, SteamInventoryResult_t *pResultHandle, const char *pchItemToken)
{
	xlogf("%s(self = %p, pResultHandle = %p, pchItemToken = %s)\n", __func__, self, pResultHandle, pchItemToken);
	return false;
}