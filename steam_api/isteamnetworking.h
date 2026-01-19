#pragma once

#include "steamtypes.h"

// handle to a socket
typedef uint32 SNetSocket_t;       // CreateP2PConnectionSocket()
typedef uint32 SNetListenSocket_t; // CreateListenSocket()

// describes how the socket is currently connected
typedef enum {
	k_ESNetSocketConnectionTypeNotConnected = 0,
	k_ESNetSocketConnectionTypeUDP = 1,
	k_ESNetSocketConnectionTypeUDPRelay = 2,
} ESNetSocketConnectionType;

typedef struct
{
	uint8 m_bConnectionActive; // true if we've got an active open connection
	uint8 m_bConnecting;       // true if we're currently trying to establish a connection
	uint8 m_eP2PSessionError;  // last error recorded (see enum above)
	uint8 m_bUsingRelay;       // true if it's going through a relay server (TURN)
	int32 m_nBytesQueuedForSend;
	int32 m_nPacketsQueuedForSend;
	uint32 m_nRemoteIP;   // potential IP:Port of remote host. Could be TURN server.
	uint16 m_nRemotePort; // Only exists for compatibility with older authentication api's
} P2PSessionState_t;

typedef void ISteamNetworking;

typedef struct CSteamNetworking CSteamNetworking;

struct CSteamNetworking {
	CSteamBase base;
};

// SendP2PPacket() send types
// Typically k_EP2PSendUnreliable is what you want for UDP-like packets, k_EP2PSendReliable for TCP-like packets
typedef enum {
	// Basic UDP send. Packets can't be bigger than 1200 bytes (your typical MTU size). Can be lost, or arrive out of order (rare).
	// The sending API does have some knowledge of the underlying connection, so if there is no NAT-traversal accomplished or
	// there is a recognized adjustment happening on the connection, the packet will be batched until the connection is open again.
	k_EP2PSendUnreliable = 0,

	// As above, but if the underlying p2p connection isn't yet established the packet will just be thrown away. Using this on the first
	// packet sent to a remote host almost guarantees the packet will be dropped.
	// This is only really useful for kinds of data that should never buffer up, i.e. voice payload packets
	k_EP2PSendUnreliableNoDelay = 1,

	// Reliable message send. Can send up to 1MB of data in a single message.
	// Does fragmentation/re-assembly of messages under the hood, as well as a sliding window for efficient sends of large chunks of data.
	k_EP2PSendReliable = 2,

	// As above, but applies the Nagle algorithm to the send - sends will accumulate
	// until the current MTU size (typically ~1200 bytes, but can change) or ~200ms has passed (Nagle algorithm).
	// Useful if you want to send a set of smaller messages but have the coalesced into a single packet
	// Since the reliable stream is all ordered, you can do several small message sends with k_EP2PSendReliableWithBuffering and then
	// do a normal k_EP2PSendReliable to force all the buffered data to be sent.
	k_EP2PSendReliableWithBuffering = 3,

} EP2PSend;

S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamNetworking_SendP2PPacket(SELF, CSteamID steamIDRemote, const void *pubData, uint32 cubData, EP2PSend eP2PSendType, int nChannel);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamNetworking_IsP2PPacketAvailable(SELF, uint32 *pcubMsgSize, int nChannel);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamNetworking_ReadP2PPacket(SELF, void *pubDest, uint32 cubDest, uint32 *pcubMsgSize, CSteamID *psteamIDRemote, int nChannel);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamNetworking_AcceptP2PSessionWithUser(SELF, CSteamID steamIDRemote);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamNetworking_CloseP2PSessionWithUser(SELF, CSteamID steamIDRemote);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamNetworking_CloseP2PChannelWithUser(SELF, CSteamID steamIDRemote, int nChannel);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamNetworking_GetP2PSessionState(SELF, CSteamID steamIDRemote, P2PSessionState_t *pConnectionState);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamNetworking_AllowP2PPacketRelay(SELF, bool bAllow);
S_CLASSAPI SNetListenSocket_t S_CLASSCALLTYPE SteamAPI_ISteamNetworking_CreateListenSocket(SELF, int nVirtualP2PPort, SteamIPAddress_t nIP, uint16 nPort, bool bAllowUseOfPacketRelay);
S_CLASSAPI SNetListenSocket_t S_CLASSCALLTYPE SteamAPI_ISteamNetworking_CreateListenSocketUint32(SELF, int nVirtualP2PPort, uint32 nIP, uint16 nPort, bool bAllowUseOfPacketRelay);
S_CLASSAPI SNetSocket_t S_CLASSCALLTYPE SteamAPI_ISteamNetworking_CreateP2PConnectionSocket(SELF, CSteamID steamIDTarget, int nVirtualPort, int nTimeoutSec, bool bAllowUseOfPacketRelay);
S_CLASSAPI SNetSocket_t S_CLASSCALLTYPE SteamAPI_ISteamNetworking_CreateConnectionSocket(SELF, SteamIPAddress_t nIP, uint16 nPort, int nTimeoutSec);
S_CLASSAPI SNetSocket_t S_CLASSCALLTYPE SteamAPI_ISteamNetworking_CreateConnectionSocketUint32(SELF, uint32 nIP, uint16 nPort, int nTimeoutSec);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamNetworking_DestroySocket(SELF, SNetSocket_t hSocket, bool bNotifyRemoteEnd);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamNetworking_DestroyListenSocket(SELF, SNetListenSocket_t hSocket, bool bNotifyRemoteEnd);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamNetworking_SendDataOnSocket(SELF, SNetSocket_t hSocket, void *pubData, uint32 cubData, bool bReliable);
S_CLASSAPI SNetListenSocket_t S_CLASSCALLTYPE SteamAPI_ISteamNetworking_CreateListenSocketUint32(SELF, int nVirtualP2PPort, uint32 nIP, uint16 nPort, bool bAllowUseOfPacketRelay);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamNetworking_IsDataAvailableOnSocket(SELF, SNetSocket_t hSocket, uint32 *pcubMsgSize);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamNetworking_RetrieveDataFromSocket(SELF, SNetSocket_t hSocket, void *pubDest, uint32 cubDest, uint32 *pcubMsgSize);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamNetworking_IsDataAvailableOnSocket(SELF, SNetSocket_t hSocket, uint32 *pcubMsgSize);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamNetworking_IsDataAvailable(SELF, SNetListenSocket_t hListenSocket, uint32 *pcubMsgSize, SNetSocket_t *phSocket);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamNetworking_RetrieveDataFromSocket(SELF, SNetSocket_t hSocket, void *pubDest, uint32 cubDest, uint32 *pcubMsgSize);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamNetworking_RetrieveData(SELF, SNetListenSocket_t hListenSocket, void *pubDest, uint32 cubDest, uint32 *pcubMsgSize, SNetSocket_t *phSocket);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamNetworking_GetSocketInfo(SELF, SNetSocket_t hSocket, CSteamID *pSteamIDRemote, int *peSocketStatus, SteamIPAddress_t *punIPRemote, uint16 *punPortRemote);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamNetworking_GetListenSocketInfo(SELF, SNetListenSocket_t hListenSocket, SteamIPAddress_t *pnIP, uint16 *pnPort);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamNetworking_GetSocketInfoUint32(SELF, SNetSocket_t hSocket, CSteamID *pSteamIDRemote, int *peSocketStatus, uint32 *punIPRemote, uint16 *punPortRemote);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamNetworking_GetListenSocketInfoUint32(SELF, SNetListenSocket_t hListenSocket, uint32 *pnIP, uint16 *pnPort);
S_CLASSAPI ESNetSocketConnectionType S_CLASSCALLTYPE SteamAPI_ISteamNetworking_GetSocketConnectionType(SELF, SNetSocket_t hSocket);
S_CLASSAPI int S_CLASSCALLTYPE SteamAPI_ISteamNetworking_GetMaxPacketSize(SELF, SNetSocket_t hSocket);