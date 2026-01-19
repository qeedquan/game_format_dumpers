#include "steam.h"

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusic_BIsEnabled(SELF)
{
	xlogf("%s(self = %p)", __func__, self);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamMusic_BIsPlaying(SELF)
{
	xlogf("%s(self = %p)", __func__, self);
	return false;
}

S_CLASSAPI AudioPlayback_Status S_CLASSCALLTYPE
SteamAPI_ISteamMusic_GetPlaybackStatus(SELF)
{
	xlogf("%s(self = %p)", __func__, self);
	return 1;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamMusic_PlayPrevious(SELF)
{
	xlogf("%s(self = %p)", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamMusic_Play(SELF)
{
	xlogf("%s(self = %p)", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamMusic_Pause(SELF)
{
	xlogf("%s(self = %p)", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamMusic_PlayNext(SELF)
{
	xlogf("%s(self = %p)", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_ISteamMusic_SetVolume(SELF, float flVolume)
{
	xlogf("%s(self = %p, flVolume = %f)", __func__, self, flVolume);
}

S_CLASSAPI float S_CLASSCALLTYPE
SteamAPI_ISteamMusic_GetVolume(SELF)
{
	xlogf("%s(self = %p)", __func__, self);
	return 0;
}