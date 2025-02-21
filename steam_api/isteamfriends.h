#pragma once

#include "steamtypes.h"

//-----------------------------------------------------------------------------
// Purpose: list of states a friend can be in
//-----------------------------------------------------------------------------
typedef enum {
	k_EPersonaStateOffline = 0,        // friend is not currently logged on
	k_EPersonaStateOnline = 1,         // friend is logged on
	k_EPersonaStateBusy = 2,           // user is on, but busy
	k_EPersonaStateAway = 3,           // auto-away feature
	k_EPersonaStateSnooze = 4,         // auto-away for a long time
	k_EPersonaStateLookingToTrade = 5, // Online, trading
	k_EPersonaStateLookingToPlay = 6,  // Online, wanting to play
	k_EPersonaStateMax,
} EPersonaState;

//-----------------------------------------------------------------------------
// Purpose: set of relationships to other users
//-----------------------------------------------------------------------------
typedef enum {
	k_EFriendRelationshipNone = 0,
	k_EFriendRelationshipBlocked = 1, // this doesn't get stored; the user has just done an Ignore on an friendship invite
	k_EFriendRelationshipRequestRecipient = 2,
	k_EFriendRelationshipFriend = 3,
	k_EFriendRelationshipRequestInitiator = 4,
	k_EFriendRelationshipIgnored = 5, // this is stored; the user has explicit blocked this other user from comments/chat/etc
	k_EFriendRelationshipIgnoredFriend = 6,
	k_EFriendRelationshipSuggested = 7,

	// keep this updated
	k_EFriendRelationshipMax = 8,
} EFriendRelationship;

//-----------------------------------------------------------------------------
// Purpose: Chat Entry Types (previously was only friend-to-friend message types)
//-----------------------------------------------------------------------------
typedef enum {
	k_EChatEntryTypeInvalid = 0,
	k_EChatEntryTypeChatMsg = 1,    // Normal text message from another user
	k_EChatEntryTypeTyping = 2,     // Another user is typing (not used in multi-user chat)
	k_EChatEntryTypeInviteGame = 3, // Invite from other user into that users current game
	k_EChatEntryTypeEmote = 4,      // text emote message (deprecated, should be treated as ChatMsg)
	// k_EChatEntryTypeLobbyGameStart = 5,	// lobby game is starting (dead - listen for LobbyGameCreated_t callback instead)
	k_EChatEntryTypeLeftConversation = 6, // user has left the conversation ( closed chat window )
	// Above are previous FriendMsgType entries, now merged into more generic chat entry types
	k_EChatEntryTypeEntered = 7,         // user has entered the conversation (used in multi-user chat and group chat)
	k_EChatEntryTypeWasKicked = 8,       // user was kicked (data: 64-bit steamid of actor performing the kick)
	k_EChatEntryTypeWasBanned = 9,       // user was banned (data: 64-bit steamid of actor performing the ban)
	k_EChatEntryTypeDisconnected = 10,   // user disconnected
	k_EChatEntryTypeHistoricalChat = 11, // a chat message from user's chat history or offilne message
	k_EChatEntryTypeReserved1 = 12,
	k_EChatEntryTypeReserved2 = 13,
	k_EChatEntryTypeLinkBlocked = 14, // a link was removed by the chat filter.
} EChatEntryType;

typedef int16 FriendsGroupID_t;

typedef struct FriendGameInfo_t FriendGameInfo_t;

struct FriendGameInfo_t {
	CGameID m_gameID;
	uint32 m_unGameIP;
	uint16 m_usGamePort;
	uint16 m_usQueryPort;
	CSteamID m_steamIDLobby;
};

typedef void ISteamFriends;

typedef struct CSteamFriends CSteamFriends;

struct CSteamFriends {
	CSteamBase base;
};

S_CLASSAPI const char *S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetPersonaName(SELF);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamFriends_SetPersonaName(SELF, const char *pchPersonaName);
S_CLASSAPI EPersonaState S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetPersonaState(SELF);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetFriendCount(SELF, int iFriendFlags);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetFriendCountFromSource(SELF, CSteamID steamIDSource);
S_CLASSAPI CSteamID S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetFriendByIndex(SELF, int iFriend, int iFriendFlags);
S_CLASSAPI EFriendRelationship S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetFriendRelationship(SELF, CSteamID steamIDFriend);
S_CLASSAPI EPersonaState S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetFriendPersonaState(SELF, CSteamID steamIDFriend);
S_CLASSAPI const char *S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetFriendPersonaNameHistory(SELF, CSteamID steamIDFriend, int iPersonaName);
S_CLASSAPI const char *S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetFriendPersonaName(SELF, CSteamID steamIDFriend);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetFriendGamePlayed(SELF, CSteamID steamIDFriend, FriendGameInfo_t *pFriendGameInfo);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetFriendSteamLevel(SELF, CSteamID steamIDFriend);
S_CLASSAPI const char *S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetPlayerNickname(SELF, CSteamID steamIDPlayer);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetFriendsGroupCount(SELF);
S_CLASSAPI FriendsGroupID_t S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetFriendsGroupIDByIndex(SELF, int iFG);
S_CLASSAPI const char *S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetFriendsGroupName(SELF, FriendsGroupID_t friendsGroupID);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetFriendsGroupMembersCount(SELF, FriendsGroupID_t friendsGroupID);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetFriendsGroupMembersList(SELF, FriendsGroupID_t friendsGroupID, CSteamID *pOutSteamIDMembers, int nMembersCount);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamFriends_HasFriend(SELF, CSteamID steamIDFriend, int iFriendFlags);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetClanCount(SELF);
S_CLASSAPI CSteamID S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetClanByIndex(SELF, int iClan);
S_CLASSAPI const char *S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetClanName(SELF, CSteamID steamIDClan);
S_CLASSAPI const char *S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetClanTag(SELF, CSteamID steamIDClan);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetClanActivityCounts(SELF, CSteamID steamIDClan, int *pnOnline, int *pnInGame, int *pnChatting);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamFriends_DownloadClanActivityCounts(SELF, CSteamID *psteamIDClans, int cClansToRequest);
S_CLASSAPI CSteamID S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetFriendFromSourceByIndex(SELF, CSteamID steamIDSource, int iFriend);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamFriends_IsUserInSource(SELF, CSteamID steamIDUser, CSteamID steamIDSource);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamFriends_SetInGameVoiceSpeaking(SELF, CSteamID steamIDUser, bool bSpeaking);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamFriends_ActivateGameOverlayToStore(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamFriends_ActivateGameOverlay(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamFriends_ActivateGameOverlayToUser(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamFriends_ActivateGameOverlayToWebPage(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamFriends_SetPlayedWith(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamFriends_ActivateGameOverlayInviteDialog(SELF);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetSmallFriendAvatar(SELF, CSteamID steamIDFriend);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetMediumFriendAvatar(SELF, CSteamID steamIDFriend);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetLargeFriendAvatar(SELF, CSteamID steamIDFriend);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamFriends_RequestUserInformation(SELF, CSteamID steamIDUser, bool bRequireNameOnly);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamFriends_RequestClanOfficerList(SELF, CSteamID steamIDClan);
S_CLASSAPI CSteamID S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetClanOwner(SELF, CSteamID steamIDClan);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetClanOfficerCount(SELF, CSteamID steamIDClan);
S_CLASSAPI CSteamID S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetClanOfficerByIndex(SELF, CSteamID steamIDClan, int iOfficer);
S_CLASSAPI uint32 S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetUserRestrictions(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamFriends_SetRichPresence(SELF, const char *pchKey, const char *pchValue);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamFriends_ClearRichPresence(SELF);
S_CLASSAPI const char *S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetFriendRichPresence(SELF, CSteamID steamIDFriend, const char *pchKey);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetFriendRichPresenceKeyCount(SELF, CSteamID steamIDFriend);
S_CLASSAPI const char *S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetFriendRichPresenceKeyByIndex(SELF, CSteamID steamIDFriend, int iKey);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamFriends_RequestFriendRichPresence(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamFriends_InviteUserToGame(SELF, CSteamID steamIDFriend, const char *pchConnectString);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetCoplayFriendCount(SELF);
S_CLASSAPI CSteamID S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetCoplayFriend(SELF, int iCoplayFriend);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetFriendCoplayTime(SELF, CSteamID steamIDFriend);
S_CLASSAPI AppId_t S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetFriendCoplayGame(SELF, CSteamID steamIDFriend);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamFriends_JoinClanChatRoom(SELF, CSteamID steamIDClan);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamFriends_LeaveClanChatRoom(SELF, CSteamID steamIDClan);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetClanChatMemberCount(SELF, CSteamID steamIDClan);
S_CLASSAPI CSteamID S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetChatMemberByIndex(SELF, CSteamID steamIDClan, int iUser);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamFriends_SendClanChatMessage(SELF, CSteamID steamIDClanChat, const char *pchText);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetClanChatMessage(SELF, CSteamID steamIDClanChat, int iMessage, void *prgchText, int cchTextMax, EChatEntryType *peChatEntryType, CSteamID *psteamidChatter);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamFriends_IsClanChatAdmin(SELF, CSteamID steamIDClanChat, CSteamID steamIDUser);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamFriends_IsClanChatWindowOpenInSteam(SELF, CSteamID steamIDClanChat);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamFriends_OpenClanChatWindowInSteam(SELF, CSteamID steamIDClanChat);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamFriends_CloseClanChatWindowInSteam(SELF, CSteamID steamIDClanChat);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamFriends_SetListenForFriendsMessages(SELF, bool bInterceptEnabled);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamFriends_ReplyToFriendMessage(SELF, CSteamID steamIDFriend, const char *pchMsgToSend);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamFriends_ReplyToFriendMessage(SELF, CSteamID steamIDFriend, const char *pchMsgToSend);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetFriendMessage(SELF, CSteamID steamIDFriend, int iMessageID, void *pvData, int cubData, EChatEntryType *peChatEntryType);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetFollowerCount(SELF, CSteamID steamID);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamFriends_IsFollowing(SELF, CSteamID steamID);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamFriends_EnumerateFollowingList(SELF, uint32 unStartIndex);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamFriends_IsClanPublic(SELF, CSteamID steamID);
S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE SteamAPI_ISteamFriends_IsClanOfficialGameGroup(SELF, CSteamID id);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamFriends_GetNumChatsWithUnreadPriorityMessages(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamFriends_ActivateGameOverlayRemotePlayTogetherInviteDialog(SELF, CSteamID steamIDLobby);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamFriends_RegisterProtocolInOverlayBrowser(SELF, const char *pchProtocol);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamFriends_ActivateGameOverlayInviteDialogConnectString(SELF, const char *pchConnectString);
