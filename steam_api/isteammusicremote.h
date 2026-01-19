#pragma once

#include "steamtypes.h"

typedef void ISteamMusicRemote;

typedef struct CSteamMusicRemote CSteamMusicRemote;

struct CSteamMusicRemote {
	CSteamBase base;
};

S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_RegisterSteamMusicRemote(SELF, const char *pchName);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_DeregisterSteamMusicRemote(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_BIsCurrentMusicRemote(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_BActivationSuccess(SELF, bool bValue);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_SetDisplayName(SELF, const char *pchDisplayName);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_SetPNGIcon_64x64(SELF, void *pvBuffer, uint32 cbBufferLength);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_EnablePlayPrevious(SELF, bool bValue);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_EnablePlayNext(SELF, bool bValue);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_EnableShuffled(SELF, bool bValue);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_EnableLooped(SELF, bool bValue);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_EnableQueue(SELF, bool bValue);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_EnablePlaylists(SELF, bool bValue);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_UpdatePlaybackStatus(SELF, AudioPlayback_Status nStatus);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_UpdateShuffled(SELF, bool bValue);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_UpdateLooped(SELF, bool bValue);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_UpdateVolume(SELF, float flValue);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_CurrentEntryWillChange(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_CurrentEntryIsAvailable(SELF, bool bAvailable);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_UpdateCurrentEntryText(SELF, const char *pchText);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_UpdateCurrentEntryElapsedSeconds(SELF, int nValue);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_UpdateCurrentEntryCoverArt(SELF, void *pvBuffer, uint32 cbBufferLength);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_CurrentEntryDidChange(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_QueueWillChange(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_ResetQueueEntries(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_SetQueueEntry(SELF, int nID, int nPosition, const char *pchEntryText);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_SetCurrentQueueEntry(SELF, int nID);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_QueueDidChange(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_PlaylistWillChange(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_ResetPlaylistEntries(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_SetPlaylistEntry(SELF, int nID, int nPosition, const char *pchEntryText);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_SetCurrentPlaylistEntry(SELF, int nID);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusicRemote_PlaylistDidChange(SELF);