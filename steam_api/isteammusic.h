#pragma once

#include "steamtypes.h"

typedef enum {
	AudioPlayback_Undefined = 0,
	AudioPlayback_Playing = 1,
	AudioPlayback_Paused = 2,
	AudioPlayback_Idle = 3
} AudioPlayback_Status;

typedef void ISteamMusic;

typedef struct CSteamMusic CSteamMusic;

struct CSteamMusic {
	CSteamBase base;
};

S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusic_BIsEnabled(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamMusic_BIsPlaying(SELF);
S_CLASSAPI AudioPlayback_Status S_CLASSCALLTYPE SteamAPI_ISteamMusic_GetPlaybackStatus(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamMusic_PlayPrevious(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamMusic_Play(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamMusic_Pause(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamMusic_PlayNext(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_ISteamMusic_SetVolume(SELF, float flVolume);
S_CLASSAPI float S_CLASSCALLTYPE SteamAPI_ISteamMusic_GetVolume(SELF);