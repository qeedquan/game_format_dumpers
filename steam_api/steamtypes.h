#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long uvlong;

typedef long long vlong;

typedef uchar uint8;
typedef ushort uint16;
typedef uint uint32;
typedef uvlong uint64;

typedef char int8;
typedef short int16;
typedef int int32;
typedef vlong int64;

typedef uint64 GID_t;
typedef uint64 JobID_t;
typedef GID_t TxnID_t;

typedef uint32 PackageId_t;
typedef uint32 BundleId_t;

typedef uint32 AppId_t;

typedef uint64 AssetClassId_t;

typedef uint32 PhysicalItemId_t;

typedef uint32 DepotId_t;

typedef uint32 RTime32;

typedef uint32 CellID_t;

typedef uint64 SteamAPICall_t;

typedef uint32 AccountID_t;

typedef uint32 PartnerId_t;

typedef uint64 ManifestId_t;

typedef int32 HSteamUser;
typedef int32 HSteamPipe;

typedef void *BREAKPAD_HANDLE;

typedef struct CSteamBase CSteamBase;

struct CSteamBase {
	void *vptr;
	void *vtable[128];
	char version[64];
};

#if defined(_WIN32)
#define CONSTRUCTOR
#else
#define CONSTRUCTOR __attribute__((constructor))
#endif

#if !defined(S_CALLTYPE)
#if defined(_MSC_VER)
#define S_CALLTYPE
#else
#define S_CALLTYPE
#endif
#endif

#if !defined(S_CLASSCALLTYPE)
#if defined(_MSC_VER) && !defined(_WIN64)
#define S_CLASSCALLTYPE __fastcall
#else
#define S_CLASSCALLTYPE
#endif
#endif

#if !defined(SELF)
#if defined(_MSC_VER) && !defined(_WIN64)
#define SELF void *self, void *_EDX
#else
#define SELF void *self
#endif
#endif

#if !defined(S_API) && defined(_WIN32) && defined(_MSC_VER)
#define S_API __declspec(dllexport)
#elif !defined(S_API) && defined(_WIN32) && !defined(_MSC_VER)
#define S_API __declspec(dllexport)
#elif !defined(S_API) && defined(__i386__)
#define S_API
#define S_API
#else
#define S_API
#endif

#if !defined(S_CLASSAPI)
#if defined(_WIN32) && defined(_MSC_VER)
#define S_CLASSAPI __declspec(dllexport)
#elif defined(_WIN32) && !defined(_MSC_VER)
#define S_CLASSAPI __declspec(dllexport) __attribute__((thiscall))
#elif defined(__i386__)
#define S_CLASSAPI __attribute__((thiscall))
#else
#define S_CLASSAPI
#endif
#endif

#if defined(_WIN32)
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#if defined(R_STRUCT_PTR) || defined(_WIN32)
#define R_STRUCT_TYPE(x) x *
#define R_STRUCT_RET(x) &(x)
#else
#define R_STRUCT_TYPE(x) x
#define R_STRUCT_RET(x) (x)
#endif

#if defined(__i386__) || (defined(_WIN32) && !defined(_WIN64))
typedef uint32 uintp;
typedef int32 intp;
#else
typedef uint64 uintp;
typedef int64 intp;
#endif

typedef enum {
	k_ESteamIPTypeIPv4 = 0,
	k_ESteamIPTypeIPv6 = 1,
} ESteamIPType;

typedef struct {
	union {

		uint32 m_unIPv4;      // Host order
		uint8 m_rgubIPv6[16]; // Network order! Same as inaddr_in6.  (0011:2233:4455:6677:8899:aabb:ccdd:eeff)

		// Internal use only
		uint64 m_ipv6Qword[2]; // big endian
	};

	ESteamIPType m_eType;
} SteamIPAddress_t;

//-----------------------------------------------------------------------------
// Purpose: Base values for callback identifiers, each callback must
//			have a unique ID.
//-----------------------------------------------------------------------------
enum { k_iSteamUserCallbacks = 100 };
enum { k_iSteamGameServerCallbacks = 200 };
enum { k_iSteamFriendsCallbacks = 300 };
enum { k_iSteamBillingCallbacks = 400 };
enum { k_iSteamMatchmakingCallbacks = 500 };
enum { k_iSteamContentServerCallbacks = 600 };
enum { k_iSteamUtilsCallbacks = 700 };
enum { k_iClientFriendsCallbacks = 800 };
enum { k_iClientUserCallbacks = 900 };
enum { k_iSteamAppsCallbacks = 1000 };
enum { k_iSteamUserStatsCallbacks = 1100 };
enum { k_iSteamNetworkingCallbacks = 1200 };
enum { k_iClientRemoteStorageCallbacks = 1300 };
enum { k_iClientDepotBuilderCallbacks = 1400 };
enum { k_iSteamGameServerItemsCallbacks = 1500 };
enum { k_iClientUtilsCallbacks = 1600 };
enum { k_iSteamGameCoordinatorCallbacks = 1700 };
enum { k_iSteamGameServerStatsCallbacks = 1800 };
enum { k_iSteam2AsyncCallbacks = 1900 };
enum { k_iSteamGameStatsCallbacks = 2000 };
enum { k_iClientHTTPCallbacks = 2100 };
enum { k_iClientScreenshotsCallbacks = 2200 };
enum { k_iSteamScreenshotsCallbacks = 2300 };
enum { k_iClientAudioCallbacks = 2400 };
enum { k_iClientUnifiedMessagesCallbacks = 2500 };
enum { k_iSteamStreamLauncherCallbacks = 2600 };
enum { k_iClientControllerCallbacks = 2700 };
enum { k_iSteamControllerCallbacks = 2800 };
enum { k_iClientParentalSettingsCallbacks = 2900 };
enum { k_iClientDeviceAuthCallbacks = 3000 };
enum { k_iClientNetworkDeviceManagerCallbacks = 3100 };
enum { k_iClientMusicCallbacks = 3200 };
enum { k_iClientRemoteClientManagerCallbacks = 3300 };
enum { k_iClientUGCCallbacks = 3400 };
enum { k_iSteamStreamClientCallbacks = 3500 };
enum { k_IClientProductBuilderCallbacks = 3600 };
enum { k_iClientShortcutsCallbacks = 3700 };
enum { k_iClientRemoteControlManagerCallbacks = 3800 };
enum { k_iSteamAppListCallbacks = 3900 };
enum { k_iSteamMusicCallbacks = 4000 };
enum { k_iSteamMusicRemoteCallbacks = 4100 };
enum { k_iClientVRCallbacks = 4200 };
enum { k_iClientGameNotificationCallbacks = 4300 };
enum { k_iSteamGameNotificationCallbacks = 4400 };
enum { k_iSteamHTMLSurfaceCallbacks = 4500 };
enum { k_iClientVideoCallbacks = 4600 };
enum { k_iClientInventoryCallbacks = 4700 };
enum { k_iClientBluetoothManagerCallbacks = 4800 };
enum { k_iClientSharedConnectionCallbacks = 4900 };
enum { k_ISteamParentalSettingsCallbacks = 5000 };
enum { k_iClientShaderCallbacks = 5100 };

enum {
	k_cchPublishedDocumentTitleMax = 128 + 1,
	k_cchPublishedDocumentDescriptionMax = 8000,
	k_cchPublishedDocumentChangeDescriptionMax = 8000,
	k_unEnumeratePublishedFilesMaxResults = 50,
	k_cchTagListMax = 1024 + 1,
	k_cchFilenameMax = 260,
	k_cchPublishedFileURLMax = 256,
};
