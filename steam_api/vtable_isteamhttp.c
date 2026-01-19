#include "steam.h"

#define vtable_ISteamHTTP002 vtable_ISteamHTTP003

static void *vtable_ISteamHTTP003[] = {
    SteamAPI_ISteamHTTP_CreateHTTPRequest,
    SteamAPI_ISteamHTTP_SetHTTPRequestContextValue,
    SteamAPI_ISteamHTTP_SetHTTPRequestNetworkActivityTimeout,
    SteamAPI_ISteamHTTP_SetHTTPRequestHeaderValue,
    SteamAPI_ISteamHTTP_SetHTTPRequestGetOrPostParameter,
    SteamAPI_ISteamHTTP_SendHTTPRequest,
    SteamAPI_ISteamHTTP_SendHTTPRequestAndStreamResponse,
    SteamAPI_ISteamHTTP_DeferHTTPRequest,
    SteamAPI_ISteamHTTP_PrioritizeHTTPRequest,
    SteamAPI_ISteamHTTP_GetHTTPResponseHeaderSize,
    SteamAPI_ISteamHTTP_GetHTTPResponseHeaderValue,
    SteamAPI_ISteamHTTP_GetHTTPResponseBodySize,
    SteamAPI_ISteamHTTP_GetHTTPResponseBodyData,
    SteamAPI_ISteamHTTP_GetHTTPStreamingResponseBodyData,
    SteamAPI_ISteamHTTP_ReleaseHTTPRequest,
    SteamAPI_ISteamHTTP_GetHTTPDownloadProgressPct,
    SteamAPI_ISteamHTTP_SetHTTPRequestRawPostBody,
    SteamAPI_ISteamHTTP_CreateCookieContainer,
    SteamAPI_ISteamHTTP_ReleaseCookieContainer,
    SteamAPI_ISteamHTTP_SetCookie,
    SteamAPI_ISteamHTTP_SetHTTPRequestCookieContainer,
    SteamAPI_ISteamHTTP_SetHTTPRequestUserAgentInfo,
    SteamAPI_ISteamHTTP_SetHTTPRequestRequiresVerifiedCertificate,
    SteamAPI_ISteamHTTP_SetHTTPRequestAbsoluteTimeoutMS,
    SteamAPI_ISteamHTTP_GetHTTPRequestWasTimedOut,
};

VtableEntry vtable_ISteamHTTP[] = {
    {2, vtable_ISteamHTTP002, sizeof(vtable_ISteamHTTP002), 0},
    {3, vtable_ISteamHTTP003, sizeof(vtable_ISteamHTTP003), 0},
    {0, NULL, 0, 0},
};
