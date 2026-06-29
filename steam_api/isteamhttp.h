#pragma once

#include "steamtypes.h"

typedef uint32 HTTPRequestHandle;
typedef uint32 HTTPCookieContainerHandle;

// This enum is used in client API methods, do not re-number existing values.
typedef enum {
	k_EHTTPMethodInvalid = 0,
	k_EHTTPMethodGET,
	k_EHTTPMethodHEAD,
	k_EHTTPMethodPOST,
	k_EHTTPMethodPUT,
	k_EHTTPMethodDELETE,
	k_EHTTPMethodOPTIONS,

	// The remaining HTTP methods are not yet supported, per rfc2616 section 5.1.1 only GET and HEAD are required for
	// a compliant general purpose server.  We'll likely add more as we find uses for them.

	// k_EHTTPMethodTRACE,
	// k_EHTTPMethodCONNECT
} EHTTPMethod;

typedef void ISteamHTTP;

typedef struct CSteamHTTP CSteamHTTP;

struct CSteamHTTP {
	CSteamBase base;
};

S_CLASSAPI HTTPRequestHandle S_CLASSCALLTYPE SteamAPI_ISteamHTTP_CreateHTTPRequest(SELF, EHTTPMethod eHTTPRequestMethod, const char *pchAbsoluteURL);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamHTTP_SetHTTPRequestContextValue(SELF, HTTPRequestHandle hRequest, uint64 ulContextValue);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamHTTP_SetHTTPRequestNetworkActivityTimeout(SELF, HTTPRequestHandle hRequest, uint32 unTimeoutSeconds);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamHTTP_SetHTTPRequestHeaderValue(SELF, HTTPRequestHandle hRequest, const char *pchHeaderName, const char *pchHeaderValue);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamHTTP_SetHTTPRequestGetOrPostParameter(SELF, HTTPRequestHandle hRequest, const char *pchParamName, const char *pchParamValue);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamHTTP_SendHTTPRequestAndStreamResponse(SELF, HTTPRequestHandle hRequest, SteamAPICall_t *pCallHandle);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamHTTP_SendHTTPRequest(SELF, HTTPRequestHandle hRequest, SteamAPICall_t *pCallHandle);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamHTTP_DeferHTTPRequest(SELF, HTTPRequestHandle hRequest);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamHTTP_PrioritizeHTTPRequest(SELF, HTTPRequestHandle hRequest);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamHTTP_GetHTTPResponseHeaderSize(SELF, HTTPRequestHandle hRequest, const char *pchHeaderName, uint32 *unResponseHeaderSize);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamHTTP_GetHTTPResponseHeaderValue(SELF, HTTPRequestHandle hRequest, const char *pchHeaderName, uint8 *pHeaderValueBuffer, uint32 unBufferSize);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamHTTP_GetHTTPResponseBodySize(SELF, HTTPRequestHandle hRequest, uint32 *unBodySize);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamHTTP_GetHTTPResponseBodyData(SELF, HTTPRequestHandle hRequest, uint8 *pBodyDataBuffer, uint32 unBufferSize);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamHTTP_GetHTTPStreamingResponseBodyData(SELF, HTTPRequestHandle hRequest, uint32 cOffset, uint8 *pBodyDataBuffer, uint32 unBufferSize);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamHTTP_ReleaseHTTPRequest(SELF, HTTPRequestHandle hRequest);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamHTTP_GetHTTPDownloadProgressPct(SELF, HTTPRequestHandle hRequest, float *pflPercentOut);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamHTTP_SetHTTPRequestRawPostBody(SELF, HTTPRequestHandle hRequest, const char *pchContentType, uint8 *pubBody, uint32 unBodyLen);
S_CLASSAPI HTTPCookieContainerHandle S_CLASSCALLTYPE SteamAPI_ISteamHTTP_CreateCookieContainer(SELF, bool bAllowResponsesToModify);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamHTTP_ReleaseCookieContainer(SELF, HTTPCookieContainerHandle hCookieContainer);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamHTTP_SetCookie(SELF, HTTPCookieContainerHandle hCookieContainer, const char *pchHost, const char *pchUrl, const char *pchCookie);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamHTTP_SetHTTPRequestCookieContainer(SELF, HTTPRequestHandle hRequest, HTTPCookieContainerHandle hCookieContainer);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamHTTP_SetHTTPRequestUserAgentInfo(SELF, HTTPRequestHandle hRequest, const char *pchUserAgentInfo);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamHTTP_SetHTTPRequestRequiresVerifiedCertificate(SELF, HTTPRequestHandle hRequest, bool bRequireVerifiedCertificate);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamHTTP_SetHTTPRequestAbsoluteTimeoutMS(SELF, HTTPRequestHandle hRequest, uint32 unMilliseconds);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_ISteamHTTP_GetHTTPRequestWasTimedOut(SELF, HTTPRequestHandle hRequest, bool *pbWasTimedOut);