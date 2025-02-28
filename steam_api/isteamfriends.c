#include "steam.h"

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetPersonaName(SELF)
{
	xlogf("%s(self = %p) -> %s\n", __func__, self, ctx.personaName);
	return ctx.personaName;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamFriends_SetPersonaName(SELF, const char *pchPersonaName)
{
	xlogf("%s(self = %p, pchPersonaName = %s)\n", __func__, self, pchPersonaName);
	snprintf(ctx.personaName, sizeof(ctx.personaName), "%s", pchPersonaName);
	return 1;
}

S_CLASSAPI EPersonaState S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetPersonaState(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 1;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetFriendCount(SELF, int iFriendFlags)
{
	xlogf("%s(self = %p, iFriendFlags = %d)\n", __func__, self, iFriendFlags);
	return 0;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetFriendCountFromSource(SELF, CSteamID steamIDSource)
{
	xlogf("%s(self = %p, steamIDSource = %llu)\n", __func__, self, steamIDSource.m_gameID);
	return 0;
}

S_CLASSAPI CSteamID S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetFriendByIndex(SELF, int iFriend, int iFriendFlags)
{
	xlogf("%s(self = %p, iFriend = %d, iFriendFlags = %x)\n", __func__, self, iFriend, iFriendFlags);
	CSteamID id = {0};
	return id;
}

S_CLASSAPI EFriendRelationship S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetFriendRelationship(SELF, CSteamID steamIDFriend)
{
	xlogf("%s(self = %p, steamIDFriend = %llu)\n", __func__, self, steamIDFriend.m_gameID);
	return 0;
}

S_CLASSAPI EPersonaState S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetFriendPersonaState(SELF, CSteamID steamIDFriend)
{
	xlogf("%s(self = %p, steamIDFriend = %llu)\n", __func__, self, steamIDFriend.m_gameID);
	return 0;
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetFriendPersonaNameHistory(SELF, CSteamID steamIDFriend, int iPersonaName)
{
	xlogf("%s(self = %p, steamIDFriend = %llu, iPersonaName = %d)\n", __func__, self, steamIDFriend.m_gameID, iPersonaName);
	return NULL;
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetFriendPersonaName(SELF, CSteamID steamIDFriend)
{
	xlogf("%s(self = %p, steamIDFriend = %llu)\n", __func__, self, steamIDFriend.m_gameID);
	return "";
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetFriendGamePlayed(SELF, CSteamID steamIDFriend, FriendGameInfo_t *pFriendGameInfo)
{
	xlogf("%s(self = %p, steamIDFriend = %llu, pFriendGameInfo = %p)\n", __func__, self, steamIDFriend.m_gameID, pFriendGameInfo);
	return true;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetFriendSteamLevel(SELF, CSteamID steamIDFriend)
{
	xlogf("%s(self = %p, steamIDFriend = %llu)\n", __func__, self, steamIDFriend.m_gameID);
	return 0;
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetPlayerNickname(SELF, CSteamID steamIDPlayer)
{
	xlogf("%s(self = %p, steamIDFriend = %llu)\n", __func__, self, steamIDPlayer.m_gameID);
	return NULL;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetFriendsGroupCount(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI FriendsGroupID_t S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetFriendsGroupIDByIndex(SELF, int iFG)
{
	xlogf("%s(self = %p, iFG = %d)\n", __func__, self, iFG);
	return 0;
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetFriendsGroupName(SELF, FriendsGroupID_t friendsGroupID)
{
	xlogf("%s(self = %p, friendsGroupID = %d)\n", __func__, self, friendsGroupID);
	return NULL;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetFriendsGroupMembersCount(SELF, FriendsGroupID_t friendsGroupID)
{
	xlogf("%s(self = %p, friendsGroupID = %d)\n", __func__, self, friendsGroupID);
	return 0;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetFriendsGroupMembersList(SELF, FriendsGroupID_t friendsGroupID, CSteamID *pOutSteamIDMembers, int nMembersCount)
{
	xlogf("%s(self = %p, friendsGroupID = %d, pOutSteamIDMembers = %p, nMembersCount = %d)\n", __func__, self, friendsGroupID, pOutSteamIDMembers, nMembersCount);
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamFriends_HasFriend(SELF, CSteamID steamIDFriend, int iFriendFlags)
{
	xlogf("%s(self = %p, steamIDFriend = %llu, iFriendFlags = %d)\n", __func__, self, steamIDFriend.m_gameID, iFriendFlags);
	return false;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetClanCount(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI CSteamID S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetClanByIndex(SELF, int iClan)
{
	xlogf("%s(self = %p, iClan = %d)\n", __func__, self, iClan);
	CSteamID id = {0};
	return id;
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetClanName(SELF, CSteamID steamIDClan)
{
	xlogf("%s(self = %p, steamIDClan = %llu)\n", __func__, self, steamIDClan.m_gameID);
	return "";
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetClanTag(SELF, CSteamID steamIDClan)
{
	xlogf("%s(self = %p, steamIDClan = %llu)\n", __func__, self, steamIDClan.m_gameID);
	return NULL;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetClanActivityCounts(SELF, CSteamID steamIDClan, int *pnOnline, int *pnInGame, int *pnChatting)
{
	xlogf("%s(self = %p, steamIDClan = %llu, pnOnline = %p, pnInGame = %p, pnChatting = %p)\n", __func__, self, steamIDClan.m_gameID, pnOnline, pnInGame, pnChatting);
	return true;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamFriends_DownloadClanActivityCounts(SELF, CSteamID *psteamIDClans, int cClansToRequest)
{
	xlogf("%s(self = %p, psteamIDClans = %p, cClansToRequest = %d)\n", __func__, self, psteamIDClans, cClansToRequest);
	return 1;
}

S_CLASSAPI CSteamID S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetFriendFromSourceByIndex(SELF, CSteamID steamIDSource, int iFriend)
{
	xlogf("%s(self = %p, steamIDSource = %llu, iFriend = %d)\n", __func__, self, steamIDSource.m_gameID, iFriend);
	CSteamID id = {0};
	return id;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamFriends_IsUserInSource(SELF, CSteamID steamIDUser, CSteamID steamIDSource)
{
	xlogf("%s(self = %p, steamIDUser = %llu, steamIDSource = %llu)\n", __func__, self, steamIDUser.m_gameID, steamIDSource.m_gameID);
	return false;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamFriends_SetInGameVoiceSpeaking(SELF, CSteamID steamIDUser, bool bSpeaking)
{
	xlogf("%s(self = %p, steamIDUser = %llu, bSpeaking = %d)\n", __func__, self, steamIDUser.m_gameID, bSpeaking);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamFriends_ActivateGameOverlayToStore(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamFriends_ActivateGameOverlay(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamFriends_ActivateGameOverlayToUser(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamFriends_ActivateGameOverlayToWebPage(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamFriends_SetPlayedWith(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamFriends_ActivateGameOverlayInviteDialog(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetSmallFriendAvatar(SELF, CSteamID steamIDFriend)
{
	xlogf("%s(self = %p, steamIDFriend = %llu)\n", __func__, self, steamIDFriend.m_gameID);
	return 0;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetMediumFriendAvatar(SELF, CSteamID steamIDFriend)
{
	xlogf("%s(self = %p, steamIDFriend = %llu)\n", __func__, self, steamIDFriend.m_gameID);
	return 0;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetLargeFriendAvatar(SELF, CSteamID steamIDFriend)
{
	xlogf("%s(self = %p, steamIDFriend = %llu)\n", __func__, self, steamIDFriend.m_gameID);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamFriends_RequestUserInformation(SELF, CSteamID steamIDUser, bool bRequireNameOnly)
{
	xlogf("%s(self = %p, steamIDUser = %llu, bRequireNameOnly = %d)\n", __func__, self, steamIDUser.m_gameID, bRequireNameOnly);
	return true;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamFriends_RequestClanOfficerList(SELF, CSteamID steamIDClan)
{
	xlogf("%s(self = %p, steamIDClan = %llu)\n", __func__, self, steamIDClan.m_gameID);
	return 1;
}

S_CLASSAPI CSteamID S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetClanOwner(SELF, CSteamID steamIDClan)
{
	xlogf("%s(self = %p, steamIDClan = %llu)\n", __func__, self, steamIDClan.m_gameID);
	CSteamID id = {0};
	return id;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetClanOfficerCount(SELF, CSteamID steamIDClan)
{
	xlogf("%s(self = %p, steamIDClan = %llu)\n", __func__, self, steamIDClan.m_gameID);
	return 0;
}

S_CLASSAPI CSteamID S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetClanOfficerByIndex(SELF, CSteamID steamIDClan, int iOfficer)
{
	xlogf("%s(self = %p, steamIDClan = %llu, iOfficer = %d)\n", __func__, self, steamIDClan.m_gameID, iOfficer);
	CSteamID id = {0};
	return id;
}

S_CLASSAPI uint32 S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetUserRestrictions(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamFriends_SetRichPresence(SELF, const char *pchKey, const char *pchValue)
{
	xlogf("%s(self = %p, pchKey = %s, pchValue = %s)\n", __func__, self, pchKey, pchValue);
	return true;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamFriends_ClearRichPresence(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetFriendRichPresence(SELF, CSteamID steamIDFriend, const char *pchKey)
{
	xlogf("%s(self = %p, steamIDFriend = %llu, pchKey = %s)\n", __func__, self, steamIDFriend.m_gameID, pchKey);
	return NULL;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetFriendRichPresenceKeyCount(SELF, CSteamID steamIDFriend)
{
	xlogf("%s(self = %p, steamIDFriend = %llu)\n", __func__, self, steamIDFriend.m_gameID);
	return 0;
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetFriendRichPresenceKeyByIndex(SELF, CSteamID steamIDFriend, int iKey)
{
	xlogf("%s(self = %p, steamIDFriend = %llu, iKey = %d)\n", __func__, self, steamIDFriend.m_gameID, iKey);
	return NULL;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamFriends_RequestFriendRichPresence(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamFriends_InviteUserToGame(SELF, CSteamID steamIDFriend, const char *pchConnectString)
{
	xlogf("%s(self = %p, steamIDFriend = %llu, pchConnectString = %s)\n", __func__, self, steamIDFriend.m_gameID, pchConnectString);
	return true;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetCoplayFriendCount(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI CSteamID S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetCoplayFriend(SELF, int iCoplayFriend)
{
	xlogf("%s(self = %p, iCoplayFriend = %d)\n", __func__, self, iCoplayFriend);
	CSteamID id = {0};
	return id;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetFriendCoplayTime(SELF, CSteamID steamIDFriend)
{
	xlogf("%s(self = %p, steamIDFriend = %llu)\n", __func__, self, steamIDFriend.m_gameID);
	return 0;
}

S_CLASSAPI AppId_t S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetFriendCoplayGame(SELF, CSteamID steamIDFriend)
{
	xlogf("%s(self = %p, steamIDFriend = %llu)\n", __func__, self, steamIDFriend.m_gameID);
	return 0;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamFriends_JoinClanChatRoom(SELF, CSteamID steamIDClan)
{
	xlogf("%s(self = %p, steamIDClan = %llu)\n", __func__, self, steamIDClan.m_gameID);
	return 1;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamFriends_LeaveClanChatRoom(SELF, CSteamID steamIDClan)
{
	xlogf("%s(self = %p, steamIDClan = %llu)\n", __func__, self, steamIDClan.m_gameID);
	return true;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetClanChatMemberCount(SELF, CSteamID steamIDClan)
{
	xlogf("%s(self = %p, steamIDClan = %llu)\n", __func__, self, steamIDClan.m_gameID);
	return 0;
}

S_CLASSAPI CSteamID S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetChatMemberByIndex(SELF, CSteamID steamIDClan, int iUser)
{
	xlogf("%s(self = %p, steamIDClan = %llu, iUser = %d)\n", __func__, self, steamIDClan.m_gameID, iUser);
	CSteamID id = {0};
	return id;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamFriends_SendClanChatMessage(SELF, CSteamID steamIDClanChat, const char *pchText)
{
	xlogf("%s(self = %p, steamIDClanChat = %llu, pchText = %s)\n", __func__, self, steamIDClanChat.m_gameID, pchText);
	return false;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetClanChatMessage(SELF, CSteamID steamIDClanChat, int iMessage, void *prgchText, int cchTextMax, EChatEntryType *peChatEntryType, CSteamID *psteamidChatter)
{
	xlogf("%s(self = %p, steamIDClanChat = %llu, iMessage = %d, prgchText = %p, cchTextMax = %d, peChatEntryType = %p, psteamidChatter = %p)\n", __func__, self, steamIDClanChat.m_gameID, iMessage, prgchText, cchTextMax, peChatEntryType, psteamidChatter);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamFriends_IsClanChatAdmin(SELF, CSteamID steamIDClanChat, CSteamID steamIDUser)
{
	xlogf("%s(self = %p, steamIDClanChat = %llu, steamIDUser = %llu)\n", __func__, self, steamIDClanChat.m_gameID, steamIDUser.m_gameID);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamFriends_IsClanChatWindowOpenInSteam(SELF, CSteamID steamIDClanChat)
{
	xlogf("%s(self = %p, steamIDClanChat = %llu)\n", __func__, self, steamIDClanChat.m_gameID);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamFriends_OpenClanChatWindowInSteam(SELF, CSteamID steamIDClanChat)
{
	xlogf("%s(self = %p, steamIDClanChat = %llu)\n", __func__, self, steamIDClanChat.m_gameID);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamFriends_CloseClanChatWindowInSteam(SELF, CSteamID steamIDClanChat)
{
	xlogf("%s(self = %p, steamIDClanChat = %llu)\n", __func__, self, steamIDClanChat.m_gameID);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamFriends_SetListenForFriendsMessages(SELF, bool bInterceptEnabled)
{
	xlogf("%s(self = %p, bInterceptEnabled = %d)\n", __func__, self, bInterceptEnabled);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamFriends_ReplyToFriendMessage(SELF, CSteamID steamIDFriend, const char *pchMsgToSend)
{
	xlogf("%s(self = %p, steamIDFriend = %llu, pchMsgToSend = %s)\n", __func__, self, steamIDFriend.m_gameID, pchMsgToSend);
	return true;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetFriendMessage(SELF, CSteamID steamIDFriend, int iMessageID, void *pvData, int cubData, EChatEntryType *peChatEntryType)
{
	xlogf("%s(self = %p, steamIDFriend = %llu, iMessageID = %d, pvData = %p, cubData = %d, peChatEntryType = %p)\n", __func__, self, steamIDFriend.m_gameID, iMessageID, pvData, cubData, peChatEntryType);
	return 0;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetFollowerCount(SELF, CSteamID steamID)
{
	xlogf("%s(self = %p, steamID = %llu)\n", __func__, self, steamID.m_gameID);
	return 1;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamFriends_IsFollowing(SELF, CSteamID steamID)
{
	xlogf("%s(self = %p, steamID = %llu)\n", __func__, self, steamID.m_gameID);
	return 1;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamFriends_EnumerateFollowingList(SELF, uint32 unStartIndex)
{
	xlogf("%s(self = %p, unStartIndex = %d)\n", __func__, self, unStartIndex);
	return 1;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamFriends_IsClanPublic(SELF, CSteamID steamID)
{
	xlogf("%s(self = %p, steamID = %llu)\n", __func__, self, steamID.m_gameID);
	return 1;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamFriends_IsClanOfficialGameGroup(SELF, CSteamID steamID)
{
	xlogf("%s(self = %p, steamID = %llu)\n", __func__, self, steamID.m_gameID);
	return 1;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamFriends_GetNumChatsWithUnreadPriorityMessages(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamFriends_ActivateGameOverlayRemotePlayTogetherInviteDialog(SELF, CSteamID steamIDLobby)
{
	xlogf("%s(self = %p, steamIDLobby = %llu)\n", __func__, self, steamIDLobby.m_gameID);
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamFriends_RegisterProtocolInOverlayBrowser(SELF, const char *pchProtocol)
{
	xlogf("%s(self = %p, pchProtocol = %s)\n", __func__, self, pchProtocol);
	return false;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamFriends_ActivateGameOverlayInviteDialogConnectString(SELF, const char *pchConnectString)
{
	xlogf("%s(self = %p, pchConnectString = %s)\n", __func__, self, pchConnectString);
}
