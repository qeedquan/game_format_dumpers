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
