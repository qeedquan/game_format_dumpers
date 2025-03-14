#include "steam.h"

S_CLASSAPI HTTPRequestHandle S_CLASSCALLTYPE
SteamAPI_ISteamHTTP_CreateHTTPRequest(SELF, EHTTPMethod eHTTPRequestMethod, const char *pchAbsoluteURL)
{
	xlogf("%s(self = %p, eHTTPRequestMethod = %d, pchAbsoluteURL = %s)\n", __func__, self, eHTTPRequestMethod, pchAbsoluteURL);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamHTTP_SetHTTPRequestContextValue(SELF, HTTPRequestHandle hRequest, uint64 ulContextValue)
{
	xlogf("%s(self = %p, hRequest = %d, ulContextValue = %lld)\n", __func__, self, hRequest, ulContextValue);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamHTTP_SetHTTPRequestNetworkActivityTimeout(SELF, HTTPRequestHandle hRequest, uint32 unTimeoutSeconds)
{
	xlogf("%s(self = %p, hRequest = %d, unTimeoutSecond = %d)\n", __func__, self, hRequest, unTimeoutSeconds);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamHTTP_SetHTTPRequestHeaderValue(SELF, HTTPRequestHandle hRequest, const char *pchHeaderName, const char *pchHeaderValue)
{
	xlogf("%s(self = %p, hRequest = %d, pchHeaderName = %s, pchHeaderValue = %s)\n", __func__, self, hRequest, pchHeaderName, pchHeaderValue);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamHTTP_SetHTTPRequestGetOrPostParameter(SELF, HTTPRequestHandle hRequest, const char *pchParamName, const char *pchParamValue)
{
	xlogf("%s(self = %p, hRequest = %d, pchParamName = %s, pchParamValue = %s)\n", __func__, self, hRequest, pchParamName, pchParamValue);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamHTTP_SendHTTPRequestAndStreamResponse(SELF, HTTPRequestHandle hRequest, SteamAPICall_t *pCallHandle)
{
	xlogf("%s(self = %p, hRequest = %d, pCallHandle = %p)\n", __func__, self, hRequest, pCallHandle);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamHTTP_SendHTTPRequest(SELF, HTTPRequestHandle hRequest, SteamAPICall_t *pCallHandle)
{
	xlogf("%s(self = %p, hRequest = %d, pCallHandle = %p)\n", __func__, self, hRequest, pCallHandle);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamHTTP_DeferHTTPRequest(SELF, HTTPRequestHandle hRequest)
{
	xlogf("%s(self = %p, hRequest = %d)\n", __func__, self, hRequest);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamHTTP_PrioritizeHTTPRequest(SELF, HTTPRequestHandle hRequest)
{
	xlogf("%s(self = %p, hRequest = %d)\n", __func__, self, hRequest);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamHTTP_GetHTTPResponseHeaderSize(SELF, HTTPRequestHandle hRequest, const char *pchHeaderName, uint32 *unResponseHeaderSize)
{
	xlogf("%s(self = %p, hRequest = %d, pchHeaderName = %s, unResponseHeaderSize = %p)\n", __func__, self, hRequest, pchHeaderName, unResponseHeaderSize);
	*unResponseHeaderSize = 0;
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamHTTP_GetHTTPResponseHeaderValue(SELF, HTTPRequestHandle hRequest, const char *pchHeaderName, uint8 *pHeaderValueBuffer, uint32 unBufferSize)
{
	xlogf("%s(self = %p, hRequest = %d, pchHeaderName = %s, pHeaderValueBuffer = %p, unBufferSize = %d)\n", __func__, self, hRequest, pchHeaderName, pHeaderValueBuffer, unBufferSize);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamHTTP_GetHTTPResponseBodySize(SELF, HTTPRequestHandle hRequest, uint32 *unBodySize)
{
	xlogf("%s(self = %p, hRequest = %d, unBodySize = %p)\n", __func__, self, hRequest, unBodySize);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamHTTP_GetHTTPResponseBodyData(SELF, HTTPRequestHandle hRequest, uint8 *pBodyDataBuffer, uint32 unBufferSize)
{
	xlogf("%s(self = %p, hRequest = %d, pBodyDataBuffer = %p, unBufferSize = %d)\n", __func__, self, hRequest, pBodyDataBuffer, unBufferSize);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamHTTP_GetHTTPStreamingResponseBodyData(SELF, HTTPRequestHandle hRequest, uint32 cOffset, uint8 *pBodyDataBuffer, uint32 unBufferSize)
{
	xlogf("%s(self = %p, hRequest = %d, cOffset = %u, pBodyDataBuffer = %p, unBufferSize = %d)\n", __func__, self, hRequest, cOffset, pBodyDataBuffer, unBufferSize);
	return false;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamHTTP_ReleaseHTTPRequest(SELF, HTTPRequestHandle hRequest)
{
	xlogf("%s(self = %p, hRequest = %d)\n", __func__, self, hRequest);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamHTTP_GetHTTPDownloadProgressPct(SELF, HTTPRequestHandle hRequest, float *pflPercentOut)
{
	xlogf("%s(self = %p, hRequest = %d, pflPercentOut = %p)\n", __func__, self, hRequest, pflPercentOut);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamHTTP_SetHTTPRequestRawPostBody(SELF, HTTPRequestHandle hRequest, const char *pchContentType, uint8 *pubBody, uint32 unBodyLen)
{
	xlogf("%s(self = %p, hRequest = %d, pchContentType = %s, pubBody = %p, unBodyLen = %d)\n", __func__, self, hRequest, pchContentType, pubBody, unBodyLen);
	return true;
}

S_CLASSAPI HTTPCookieContainerHandle S_CLASSCALLTYPE
SteamAPI_ISteamHTTP_CreateCookieContainer(SELF, bool bAllowResponsesToModify)
{
	xlogf("%s(self = %p, bAllowResponsesToModify = %d)\n", __func__, self, bAllowResponsesToModify);
	return 1;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamHTTP_ReleaseCookieContainer(SELF, HTTPCookieContainerHandle hCookieContainer)
{
	xlogf("%s(self = %p, hCookieContainer = %d)\n", __func__, self, hCookieContainer);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamHTTP_SetCookie(SELF, HTTPCookieContainerHandle hCookieContainer, const char *pchHost, const char *pchUrl, const char *pchCookie)
{
	xlogf("%s(self = %p, hCookieContainer = %d, pchHost = %s, pchUrl = %s, pchCookie = %s)\n", __func__, self, hCookieContainer, pchHost, pchUrl, pchCookie);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamHTTP_SetHTTPRequestCookieContainer(SELF, HTTPRequestHandle hRequest, HTTPCookieContainerHandle hCookieContainer)
{
	xlogf("%s(self = %p, hRequest = %d, hCookieContainer = %d)", __func__, self, hRequest, hCookieContainer);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamHTTP_SetHTTPRequestUserAgentInfo(SELF, HTTPRequestHandle hRequest, const char *pchUserAgentInfo)
{
	xlogf("%s(self = %p, hRequest = %d, pchUserAgentInfo = %s)", __func__, self, hRequest, pchUserAgentInfo);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamHTTP_SetHTTPRequestRequiresVerifiedCertificate(SELF, HTTPRequestHandle hRequest, bool bRequireVerifiedCertificate)
{
	xlogf("%s(self = %p, hRequest = %d, bRequireVerifiedCertificate = %d)", __func__, self, hRequest, bRequireVerifiedCertificate);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamHTTP_SetHTTPRequestAbsoluteTimeoutMS(SELF, HTTPRequestHandle hRequest, uint32 unMilliseconds)
{
	xlogf("%s(self = %p, hRequest = %d, unMilliseconds = %d)", __func__, self, hRequest, unMilliseconds);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_ISteamHTTP_GetHTTPRequestWasTimedOut(SELF, HTTPRequestHandle hRequest, bool *pbWasTimedOut)
{
	xlogf("%s(self = %p, hRequest = %d, pbWasTimedOut = %p)", __func__, self, hRequest, pbWasTimedOut);
	return true;
}
