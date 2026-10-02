#include "steam.h"

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamGameServerStats_ClearUserAchievement(SELF, CSteamID steamIDUser, const char *pchName)
{
	printf("%s(self = %p, steamIDUser = %ld, pchName = %s)\n", __func__, self, (long)steamIDUser.m_gameID, pchName);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamGameServerStats_GetUserAchievement(SELF, CSteamID steamIDUser, const char *pchName, bool *pbAchieved)
{
	printf("%s(self = %p, steamIDUser = %ld, pchName = %s, pbAchieved = %p)\n", __func__, self, (long)steamIDUser.m_gameID, pchName, pbAchieved);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamGameServerStats_GetUserStat(SELF, CSteamID steamIDUser, const char *pchName, int32 *pData)
{
	printf("%s(self = %p, steamIDUser = %ld, pchName = %s, pData = %p)\n", __func__, self, (long)steamIDUser.m_gameID, pchName, pData);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamGameServerStats_GetUserStat0(SELF, CSteamID steamIDUser, const char *pchName, float *pData)
{
	printf("%s(self = %p, steamIDUser = %ld, pchName = %s, pData = %p)\n", __func__, self, (long)steamIDUser.m_gameID, pchName, pData);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamGameServerStats_SetUserStat(SELF, CSteamID steamIDUser, const char *pchName, int32 nData)
{
	printf("%s(self = %p, steamIDUser = %ld, pchName = %s, nData = %d)\n", __func__, self, (long)steamIDUser.m_gameID, pchName, nData);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamGameServerStats_SetUserStat0(SELF, CSteamID steamIDUser, const char *pchName, float fData)
{
	printf("%s(self = %p, steamIDUser = %ld, pchName = %s, fData = %f)\n", __func__, self, (long)steamIDUser.m_gameID, pchName, fData);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamGameServerStats_UpdateUserAvgRateStat(SELF, CSteamID steamIDUser, const char *pchName, float flCountThisSession, double dSessionLength)
{
	printf("%s(self = %p, steamIDUser = %ld, pchName = %s, flCountThisSession = %f, dSessionLength = %lf)\n", __func__, self, (long)steamIDUser.m_gameID, pchName, flCountThisSession, dSessionLength);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamGameServerStats_SetUserAchievement(SELF, CSteamID steamIDUser, const char *pchName)
{
	printf("%s(self = %p, steamIDUser = %ld, pchName = %s)\n", __func__, self, (long)steamIDUser.m_gameID, pchName);
	return true;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamGameServerStats_StoreUserStats(SELF, CSteamID steamIDUser)
{
	printf("%s(self = %p, steamIDUser = %ld)\n", __func__, self, (long)steamIDUser.m_gameID);
	return 0;
}

S_CLASSAPI SteamAPICall_t S_CLASSCALLTYPE
SteamAPI_ISteamGameServerStats_RequestUserStats(SELF, CSteamID steamIDUser)
{
	printf("%s(self = %p, steamIDUser = %ld)\n", __func__, self, (long)steamIDUser.m_gameID);
	return 0;
}