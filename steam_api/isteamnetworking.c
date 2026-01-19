#include "steam.h"

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamNetworking_SendP2PPacket(SELF, CSteamID steamIDRemote, const void *pubData, uint32 cubData, EP2PSend eP2PSendType, int nChannel)
{
	xlogf("%s(self = %p, steamIDRemote = %llu, pubData = %p, cubData = %d, eP2PSendType = %d, nChannel = %d)\n", __func__, self, steamIDRemote.m_gameID, pubData, cubData, eP2PSendType, nChannel);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamNetworking_IsP2PPacketAvailable(SELF, uint32 *pcubMsgSize, int nChannel)
{
	xlogf("%s(self = %p, pcubMsgSize = %p, nChannel = %d)\n", __func__, self, pcubMsgSize, nChannel);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamNetworking_ReadP2PPacket(SELF, void *pubDest, uint32 cubDest, uint32 *pcubMsgSize, CSteamID *psteamIDRemote, int nChannel)
{
	xlogf("%s(self = %p, pubDest = %p, cubDest = %d, pcubMsgSize = %p, psteamIDRemote = %p, nChannel = %d)\n", __func__, self, pubDest, cubDest, pcubMsgSize, psteamIDRemote, nChannel);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamNetworking_AcceptP2PSessionWithUser(SELF, CSteamID steamIDRemote)
{
	xlogf("%s(self = %p, steamIDRemote = %llu)\n", __func__, self, steamIDRemote.m_gameID);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamNetworking_CloseP2PSessionWithUser(SELF, CSteamID steamIDRemote)
{
	xlogf("%s(self = %p, steamIDRemote = %llu)\n", __func__, self, steamIDRemote.m_gameID);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamNetworking_CloseP2PChannelWithUser(SELF, CSteamID steamIDRemote, int nChannel)
{
	xlogf("%s(self = %p, steamIDRemote = %llu, nChannel = %d)\n", __func__, self, steamIDRemote.m_gameID, nChannel);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamNetworking_GetP2PSessionState(SELF, CSteamID steamIDRemote, P2PSessionState_t *pConnectionState)
{
	xlogf("%s(self = %p, steamIDRemote = %llu, pConnectionState = %p)\n", __func__, self, steamIDRemote.m_gameID, pConnectionState);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamNetworking_AllowP2PPacketRelay(SELF, bool bAllow)
{
	xlogf("%s(self = %p, bAllow = %d)\n", __func__, self, bAllow);
	return false;
}

S_CLASSAPI SNetListenSocket_t S_CLASSCALLTYPE
SteamAPI_ISteamNetworking_CreateListenSocket(SELF, int nVirtualP2PPort, SteamIPAddress_t nIP, uint16 nPort, bool bAllowUseOfPacketRelay)
{
	xlogf("%s(self = %p, nVirtualP2PPort = %d, nIP = %d, nPort = %d, bAllowUseOfPacketRelay = %d)\n", __func__, self, nVirtualP2PPort, nIP.m_unIPv4, nPort, bAllowUseOfPacketRelay);
	return 1;
}

S_CLASSAPI SNetListenSocket_t S_CLASSCALLTYPE
SteamAPI_ISteamNetworking_CreateListenSocketUint32(SELF, int nVirtualP2PPort, uint32 nIP, uint16 nPort, bool bAllowUseOfPacketRelay)
{
	xlogf("%s(self = %p, nVirtualP2PPort = %d, nIP = %d, nPort = %d, bAllowUseOfPacketRelay = %d)\n", __func__, self, nVirtualP2PPort, nIP, nPort, bAllowUseOfPacketRelay);
	return 1;
}

S_CLASSAPI SNetSocket_t S_CLASSCALLTYPE
SteamAPI_ISteamNetworking_CreateP2PConnectionSocket(SELF, CSteamID steamIDTarget, int nVirtualPort, int nTimeoutSec, bool bAllowUseOfPacketRelay)
{
	xlogf("%s(self = %p, steamIDTarget = %llu, nVirtualPort = %d, nTimeoutSec = %d, bAllowUseOfPacketRelay = %d)\n", __func__, self, steamIDTarget.m_gameID, nVirtualPort, nTimeoutSec, bAllowUseOfPacketRelay);
	return 0;
}

S_CLASSAPI SNetSocket_t S_CLASSCALLTYPE
SteamAPI_ISteamNetworking_CreateConnectionSocket(SELF, SteamIPAddress_t nIP, uint16 nPort, int nTimeoutSec)
{
	xlogf("%s(self = %p, nIP = %d, nPort = %d, nTimeoutSec = %d)\n", __func__, self, nIP.m_unIPv4, nPort, nTimeoutSec);
	return 0;
}

S_CLASSAPI SNetSocket_t S_CLASSCALLTYPE
SteamAPI_ISteamNetworking_CreateConnectionSocketUint32(SELF, uint32 nIP, uint16 nPort, int nTimeoutSec)
{
	xlogf("%s(self = %p, nIP = %d, nPort = %d, nTimeoutSec = %d)\n", __func__, self, nIP, nPort, nTimeoutSec);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamNetworking_DestroySocket(SELF, SNetSocket_t hSocket, bool bNotifyRemoteEnd)
{
	xlogf("%s(self = %p, hSocket = %d, bNotifyRemoteEnd = %d)\n", __func__, self, hSocket, bNotifyRemoteEnd);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamNetworking_DestroyListenSocket(SELF, SNetListenSocket_t hSocket, bool bNotifyRemoteEnd)
{
	xlogf("%s(self = %p, hSocket = %d, bNotifyRemoteEnd = %d)\n", __func__, self, hSocket, bNotifyRemoteEnd);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamNetworking_SendDataOnSocket(SELF, SNetSocket_t hSocket, void *pubData, uint32 cubData, bool bReliable)
{
	xlogf("%s(self = %p, hSocket = %d, pubData = %p, cubData = %d, bReliable = %d)\n", __func__, self, hSocket, pubData, cubData, bReliable);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamNetworking_IsDataAvailableOnSocket(SELF, SNetSocket_t hSocket, uint32 *pcubMsgSize)
{
	xlogf("%s(self = %p, hSocket = %d, pcubMsgSize = %p)\n", __func__, self, hSocket, pcubMsgSize);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamNetworking_RetrieveDataFromSocket(SELF, SNetSocket_t hSocket, void *pubDest, uint32 cubDest, uint32 *pcubMsgSize)
{
	xlogf("%s(self = %p, hSocket = %d, pubDest = %p, cubDest = %d, pcubMsgSize = %p)\n", __func__, self, hSocket, pubDest, cubDest, pcubMsgSize);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamNetworking_IsDataAvailable(SELF, SNetListenSocket_t hListenSocket, uint32 *pcubMsgSize, SNetSocket_t *phSocket)
{
	xlogf("%s(self = %p, hListenSocket = %d, pcubMsgSize = %p, phSocket = %p)\n", __func__, self, hListenSocket, pcubMsgSize, phSocket);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamNetworking_RetrieveData(SELF, SNetListenSocket_t hListenSocket, void *pubDest, uint32 cubDest, uint32 *pcubMsgSize, SNetSocket_t *phSocket)
{
	xlogf("%s(self = %p, hListenSocket = %d, pubDest = %p, cubDest = %d, pcubMsgSize = %p, phSocket = %p)\n", __func__, self, hListenSocket, pubDest, cubDest, pcubMsgSize, phSocket);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamNetworking_GetSocketInfo(SELF, SNetSocket_t hSocket, CSteamID *pSteamIDRemote, int *peSocketStatus, SteamIPAddress_t *punIPRemote, uint16 *punPortRemote)
{
	xlogf("%s(self = %p, hSocket = %d, pSteamIDRemote = %p, peSocketStatus = %p, punIPRemote = %p, punPortRemote = %p)\n", __func__, self, hSocket, pSteamIDRemote, peSocketStatus, punIPRemote, punPortRemote);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamNetworking_GetListenSocketInfo(SELF, SNetListenSocket_t hListenSocket, SteamIPAddress_t *pnIP, uint16 *pnPort)
{
	xlogf("%s(self = %p, hSocket = %d, pnIP = %p, pnPort = %p)\n", __func__, self, hListenSocket, pnIP, pnPort);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamNetworking_GetSocketInfoUint32(SELF, SNetSocket_t hSocket, CSteamID *pSteamIDRemote, int *peSocketStatus, uint32 *punIPRemote, uint16 *punPortRemote)
{
	xlogf("%s(self = %p, hSocket = %d, pSteamIDRemote = %p, peSocketStatus = %p, punIPRemote = %p, punPortRemote = %p)\n", __func__, self, hSocket, pSteamIDRemote, peSocketStatus, punIPRemote, punPortRemote);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamNetworking_GetListenSocketInfoUint32(SELF, SNetListenSocket_t hListenSocket, uint32 *pnIP, uint16 *pnPort)
{
	xlogf("%s(self = %p, hSocket = %d, pnIP = %p, pnPort = %p)\n", __func__, self, hListenSocket, pnIP, pnPort);
	return true;
}

S_CLASSAPI ESNetSocketConnectionType S_CLASSCALLTYPE
SteamAPI_ISteamNetworking_GetSocketConnectionType(SELF, SNetSocket_t hSocket)
{
	xlogf("%s(self = %p, hSocket = %d)\n", __func__, self, hSocket);
	return 0;
}

S_CLASSAPI int S_CLASSCALLTYPE
SteamAPI_ISteamNetworking_GetMaxPacketSize(SELF, SNetSocket_t hSocket)
{
	xlogf("%s(self = %p, hSocket = %d)\n", __func__, self, hSocket);
	return 1400;
}
