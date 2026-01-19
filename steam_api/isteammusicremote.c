#include "steam.h"

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_RegisterSteamMusicRemote(SELF, const char *pchName)
{
	xlogf("%s(self = %p, pchName = %s)\n", __func__, self, pchName);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_DeregisterSteamMusicRemote(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_BIsCurrentMusicRemote(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_BActivationSuccess(SELF, bool bValue)
{
	xlogf("%s(self = %p, bValue = %d)\n", __func__, self, bValue);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_SetDisplayName(SELF, const char *pchDisplayName)
{
	xlogf("%s(self = %p, pchDisplayName = %s)\n", __func__, self, pchDisplayName);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_SetPNGIcon_64x64(SELF, void *pvBuffer, uint32 cbBufferLength)
{
	xlogf("%s(self = %p, pvBuffer = %p, cbBufferLength = %d)\n", __func__, self, pvBuffer, cbBufferLength);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_EnablePlayPrevious(SELF, bool bValue)
{
	xlogf("%s(self = %p, bValue = %d)\n", __func__, self, bValue);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_EnablePlayNext(SELF, bool bValue)
{
	xlogf("%s(self = %p, bValue = %d)\n", __func__, self, bValue);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_EnableShuffled(SELF, bool bValue)
{
	xlogf("%s(self = %p, bValue = %d)\n", __func__, self, bValue);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_EnableLooped(SELF, bool bValue)
{
	xlogf("%s(self = %p, bValue = %d)\n", __func__, self, bValue);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_EnableQueue(SELF, bool bValue)
{
	xlogf("%s(self = %p, bValue = %d)\n", __func__, self, bValue);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_EnablePlaylists(SELF, bool bValue)
{
	xlogf("%s(self = %p, bValue = %d)\n", __func__, self, bValue);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_UpdatePlaybackStatus(SELF, AudioPlayback_Status nStatus)
{
	xlogf("%s(self = %p, nStatus = %d)\n", __func__, self, nStatus);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_UpdateShuffled(SELF, bool bValue)
{
	xlogf("%s(self = %p, bValue = %d)\n", __func__, self, bValue);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_UpdateLooped(SELF, bool bValue)
{
	xlogf("%s(self = %p, bValue = %d)\n", __func__, self, bValue);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_UpdateVolume(SELF, float flValue)
{
	xlogf("%s(self = %p, flValue = %f)\n", __func__, self, flValue);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_CurrentEntryWillChange(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_CurrentEntryIsAvailable(SELF, bool bAvailable)
{
	xlogf("%s(self = %p, bAvailable = %d)\n", __func__, self, bAvailable);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_UpdateCurrentEntryText(SELF, const char *pchText)
{
	xlogf("%s(self = %p, pchText = %s)\n", __func__, self, pchText);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_UpdateCurrentEntryElapsedSeconds(SELF, int nValue)
{
	xlogf("%s(self = %p, nValue = %d)\n", __func__, self, nValue);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_UpdateCurrentEntryCoverArt(SELF, void *pvBuffer, uint32 cbBufferLength)
{
	xlogf("%s(self = %p, pvBuffer = %p, cbBufferLength = %d)\n", __func__, self, pvBuffer, cbBufferLength);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_CurrentEntryDidChange(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_QueueWillChange(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_ResetQueueEntries(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_SetQueueEntry(SELF, int nID, int nPosition, const char *pchEntryText)
{
	xlogf("%s(self = %p, nID = %d, nPosition = %d, pchEntryText = %s)\n", __func__, self, nID, nPosition, pchEntryText);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_SetCurrentQueueEntry(SELF, int nID)
{
	xlogf("%s(self = %p, nID = %d)\n", __func__, self, nID);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_QueueDidChange(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_PlaylistWillChange(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_ResetPlaylistEntries(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_SetPlaylistEntry(SELF, int nID, int nPosition, const char *pchEntryText)
{
	xlogf("%s(self = %p, nID = %d, nPosition = %d, pchEntryText = %s)\n", __func__, self, nID, nPosition, pchEntryText);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_SetCurrentPlaylistEntry(SELF, int nID)
{
	xlogf("%s(self = %p, nID = %d)\n", __func__, self, nID);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusicRemote_PlaylistDidChange(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return false;
}