#include "steam.h"

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_vr_void_GetWindowBounds(SELF, int32_t *pnX, int32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight)
{
	xlogf("%s(self = %p, pnX = %p, pnY = %p, pnWidth = %p, pnHeight = %p)\n", __func__, self, pnX, pnY, pnWidth, pnHeight);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_vr_void_GetRecommendedRenderTargetSize(SELF, uint32_t *pnWidth, uint32_t *pnHeight)
{
	xlogf("%s(self = %p, pnWidth = %p, pnHeight = %p)\n", __func__, self, pnWidth, pnHeight);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_vr_void_GetEyeOutputViewport(SELF, Hmd_Eye eEye, uint32_t *pnX, uint32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight)
{
	xlogf("%s(self = %p, eEye = %d, pnX = %p, pnY = %p, pnWidth = %p, pnHeight = %p)\n", __func__, self, eEye, pnX, pnY, pnWidth, pnHeight);
}

S_CLASSAPI HmdMatrix44_t S_CLASSCALLTYPE
SteamAPI_vr_void_GetProjectionMatrix(SELF, Hmd_Eye eEye, float fNearZ, float fFarZ, EGraphicsAPIConvention eProjType)
{
	HmdMatrix44_t m = {0};
	printf("%s(self = %p, eEye = %d, fNearZ = %f, fFarZ = %f, eProjType = %d)\n", __func__, self, eEye, fNearZ, fFarZ, eProjType);
	return m;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_vr_void_GetProjectionRaw(SELF, Hmd_Eye eEye, float *pfLeft, float *pfRight, float *pfTop, float *pfBottom)
{
	xlogf("%s(self = %p, eEye = %d, pfLeft = %p, pfRight = %p, pfTop = %p, pfBottom = %p)\n", __func__, self, eEye, pfLeft, pfRight, pfTop, pfBottom);
}

S_CLASSAPI DistortionCoordinates_t S_CLASSCALLTYPE
SteamAPI_vr_void_ComputeDistortion(SELF, Hmd_Eye eEye, float fU, float fV)
{
	DistortionCoordinates_t m = {0};
	xlogf("%s(self = %p, eEye = %d, fU = %f, fV = %f\n", __func__, self, eEye, fU, fV);
	return m;
}

S_CLASSAPI HmdMatrix34_t S_CLASSCALLTYPE
SteamAPI_vr_void_GetEyeToHeadTransform(SELF, Hmd_Eye eEye)
{
	HmdMatrix34_t m = {0};
	xlogf("%s(self = %p, eEye = %d)\n", __func__, self, eEye);
	return m;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_vr_void_GetTimeSinceLastVsync(SELF, float *pfSecondsSinceLastVsync, uint64_t *pulFrameCounter)
{
	xlogf("%s(self = %p, pfSecondsSinceLastVsync = %p, pulFrameCounter = %p)\n", __func__, self, pfSecondsSinceLastVsync, pulFrameCounter);
	return true;
}

S_CLASSAPI int32_t S_CLASSCALLTYPE
SteamAPI_vr_void_GetD3D9AdapterIndex(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_vr_void_GetDXGIOutputInfo(SELF, int32_t *pnAdapterIndex, int32_t *pnAdapterOutputIndex)
{
	xlogf("%s(self = %p, pnAdapterIndex = %p, pnAdapterOutputIndex = %p)\n", __func__, self, pnAdapterIndex, pnAdapterOutputIndex);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_vr_void_AttachToWindow(SELF, void *hWnd)
{
	xlogf("%s(self = %p, hWnd = %p)\n", __func__, self, hWnd);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_vr_void_GetDeviceToAbsoluteTrackingPose(SELF, TrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, TrackedDevicePose_t *pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount)
{
	xlogf("%s(self = %p, eOrigin = %d, fPredictedSecondsToPhotonsFromNow = %f, pTrackedDevicePoseArray = %p, unTrackedDevicePoseArrayCount = %d)\n", __func__, self, eOrigin, fPredictedSecondsToPhotonsFromNow, pTrackedDevicePoseArray, unTrackedDevicePoseArrayCount);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_vr_void_ResetSeatedZeroPose(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI HmdMatrix34_t S_CLASSCALLTYPE
SteamAPI_vr_void_GetSeatedZeroPoseToStandingAbsoluteTrackingPose(SELF)
{
	HmdMatrix34_t m = {0};
	xlogf("%s(self = %p)\n", __func__, self);
	return m;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_vr_void_LoadRenderModel(SELF, const char *pchRenderModelName, RenderModel_t *pRenderModel)
{
	xlogf("%s(self = %p, pchRenderModelName = %s, pRenderModel = %p)\n", __func__, self, pchRenderModelName, pRenderModel);
	return true;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_vr_void_FreeRenderModel(SELF, struct RenderModel_t *pRenderModel)
{
	xlogf("%s(self = %p, pRenderModel = %p)\n", __func__, self, pRenderModel);
}

S_CLASSAPI TrackedDeviceClass S_CLASSCALLTYPE
SteamAPI_vr_void_GetTrackedDeviceClass(SELF, TrackedDeviceIndex_t unDeviceIndex)
{
	xlogf("%s(self = %p, unDeviceIndex = %d)\n", __func__, self, unDeviceIndex);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_vr_void_IsTrackedDeviceConnected(SELF, TrackedDeviceIndex_t unDeviceIndex)
{
	xlogf("%s(self = %p, unDeviceIndex = %d)\n", __func__, self, unDeviceIndex);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_vr_void_GetBoolTrackedDeviceProperty(SELF, TrackedDeviceIndex_t unDeviceIndex, TrackedDeviceProperty prop, TrackedPropertyError *pError)
{
	xlogf("%s(self = %p, unDeviceIndex = %d, prop = %d, pError = %p)\n", __func__, self, unDeviceIndex, prop, pError);
	return true;
}

S_CLASSAPI float S_CLASSCALLTYPE
SteamAPI_vr_void_GetFloatTrackedDeviceProperty(SELF, TrackedDeviceIndex_t unDeviceIndex, TrackedDeviceProperty prop, TrackedPropertyError *pError)
{
	xlogf("%s(self = %p, unDeviceIndex = %d, prop = %d, pError = %p)\n", __func__, self, unDeviceIndex, prop, pError);
	return 0;
}

S_CLASSAPI int32_t S_CLASSCALLTYPE
SteamAPI_vr_void_GetInt32TrackedDeviceProperty(SELF, TrackedDeviceIndex_t unDeviceIndex, TrackedDeviceProperty prop, TrackedPropertyError *pError)
{
	xlogf("%s(self = %p, unDeviceIndex = %d, prop = %d, pError = %p)\n", __func__, self, unDeviceIndex, prop, pError);
	return 0;
}

S_CLASSAPI uint64_t S_CLASSCALLTYPE
SteamAPI_vr_void_GetUint64TrackedDeviceProperty(SELF, TrackedDeviceIndex_t unDeviceIndex, TrackedDeviceProperty prop, TrackedPropertyError *pError)
{
	xlogf("%s(self = %p, unDeviceIndex = %d, prop = %d, pError = %p)\n", __func__, self, unDeviceIndex, prop, pError);
	return 0;
}

S_CLASSAPI HmdMatrix34_t S_CLASSCALLTYPE
SteamAPI_vr_void_GetMatrix34TrackedDeviceProperty(SELF, TrackedDeviceIndex_t unDeviceIndex, TrackedDeviceProperty prop, TrackedPropertyError *pError)
{
	HmdMatrix34_t m = {0};
	xlogf("%s(self = %p, unDeviceIndex = %d, prop = %d, pError = %p)\n", __func__, self, unDeviceIndex, prop, pError);
	return m;
}

S_CLASSAPI uint32_t S_CLASSCALLTYPE
SteamAPI_vr_void_GetStringTrackedDeviceProperty(SELF, TrackedDeviceIndex_t unDeviceIndex, TrackedDeviceProperty prop, char *pchValue, uint32_t unBufferSize, TrackedPropertyError *pError)
{
	xlogf("%s(self = %p, unDeviceIndex = %d, prop = %d, pchValue = %p, unBufferSize = %d, pError = %p)\n", __func__, self, unDeviceIndex, prop, pchValue, unBufferSize, pError);
	return 0;
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_vr_void_GetPropErrorNameFromEnum(SELF, TrackedPropertyError error)
{
	xlogf("%s(self = %p, error = %d)\n", __func__, self, error);
	return "";
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_vr_void_PollNextEvent(SELF, VREvent_t *pEvent)
{
	xlogf("%s(self = %p, pEvent = %p)\n", __func__, self, pEvent);
	return false;
}

S_CLASSAPI const char *S_CLASSCALLTYPE
SteamAPI_vr_void_GetEventTypeNameFromEnum(SELF, EVREventType eType)
{
	xlogf("%s(self = %p, eType = %d)\n", __func__, self, eType);
	return "";
}

S_CLASSAPI HiddenAreaMesh_t S_CLASSCALLTYPE
SteamAPI_vr_void_GetHiddenAreaMesh(SELF, Hmd_Eye eEye)
{
	HiddenAreaMesh_t m = {0};
	xlogf("%s(self = %p, eEye = %d)\n", __func__, self, eEye);
	return m;
}

S_CLASSAPI ChaperoneCalibrationState S_CLASSCALLTYPE
SteamAPI_vr_IVRChaperone_GetCalibrationState(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_vr_IVRChaperone_GetSoftBoundsInfo(SELF, ChaperoneSoftBoundsInfo_t *pInfo)
{
	xlogf("%s(self = %p, pInfo = %p)\n", __func__, self, pInfo);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_vr_IVRChaperone_GetHardBoundsInfo(SELF, HmdQuad_t *pQuadsBuffer, uint32_t *punQuadsCount)
{
	xlogf("%s(self = %p, punQuadsCount = %p, punQuadsCount = %p)\n", __func__, self, pQuadsBuffer, punQuadsCount);
	return true;
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_vr_IVRChaperone_GetSeatedBoundsInfo(SELF, ChaperoneSeatedBoundsInfo_t *pInfo)
{
	xlogf("%s(self = %p, pInfo = %p)\n", __func__, self, pInfo);
	return true;
}

S_CLASSAPI uint32_t S_CLASSCALLTYPE
SteamAPI_vr_IVRCompositor_GetLastError(SELF, char *pchBuffer, uint32_t unBufferSize)
{
	xlogf("%s(self = %p, pchBuffer = %p, unBufferSize = %d)\n", __func__, self, pchBuffer, unBufferSize);
	return 0;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_vr_IVRCompositor_SetVSync(SELF, bool bVSync)
{
	xlogf("%s(self = %p, bVSync = %d)\n", __func__, self, bVSync);
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_vr_IVRCompositor_GetVSync(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return true;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_vr_IVRCompositor_SetGamma(SELF, float fGamma)
{
	xlogf("%s(self = %p, fGamma = %f)\n", __func__, self, fGamma);
}

S_CLASSAPI float S_CLASSCALLTYPE
SteamAPI_vr_IVRCompositor_GetGamma(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_vr_IVRCompositor_SetGraphicsDevice(SELF, Compositor_DeviceType eType, void *pDevice)
{
	xlogf("%s(self = %p, eType = %d, pDevice = %p)\n", __func__, self, eType, pDevice);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_vr_IVRCompositor_WaitGetPoses(SELF, TrackedDevicePose_t *pPoseArray, uint32_t unPoseArrayCount)
{
	xlogf("%s(self = %p, pPoseArray = %p, unPoseArrayCount = %d)\n", __func__, self, pPoseArray, unPoseArrayCount);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_vr_IVRCompositor_Submit(SELF, Hmd_Eye eEye, void *pTexture, Compositor_TextureBounds *pBounds)
{
	xlogf("%s(self = %p, eEye = %d, pTexture = %p, pBounds = %p)\n", __func__, self, eEye, pTexture, pBounds);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_vr_IVRCompositor_ClearLastSubmittedFrame(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_vr_IVRCompositor_GetOverlayDefaults(SELF, Compositor_OverlaySettings *pSettings)
{
	xlogf("%s(self = %p, pSettings = %p)\n", __func__, self, pSettings);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_vr_IVRCompositor_SetOverlay(SELF, void *pTexture, Compositor_OverlaySettings *pSettings)
{
	xlogf("%s(self = %p, pTexture = %p, pSettings = %p)\n", __func__, self, pTexture, pSettings);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_vr_IVRCompositor_SetOverlayRaw(SELF, void *buffer, uint32_t width, uint32_t height, uint32_t depth, Compositor_OverlaySettings *pSettings)
{
	xlogf("%s(self = %p, buffer = %p, width = %d, height = %d, depth = %d, pSettings = %p)\n", __func__, self, buffer, width, height, depth, pSettings);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_vr_IVRCompositor_SetOverlayFromFile(SELF, const char *pchFilePath, Compositor_OverlaySettings *pSettings)
{
	xlogf("%s(self = %p, pchFilePath = %s, pSettings = %p)\n", __func__, self, pchFilePath, pSettings);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_vr_IVRCompositor_ClearOverlay(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_vr_IVRCompositor_GetFrameTiming(SELF, struct Compositor_FrameTiming *pTiming, uint32_t unFramesAgo)
{
	xlogf("%s(self = %p, pTiming = %p, unFramesAgo = %d)\n", __func__, self, pTiming, unFramesAgo);
	return true;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_vr_IVRCompositor_FadeToColor(SELF, float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground)
{
	xlogf("%s(self = %p, fSeconds = %f, fRed = %f, fGreen = %f, fBlue = %f, fAlpha = %f, bBackground = %d)\n", __func__, self, fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_vr_IVRCompositor_FadeGrid(SELF, float fSeconds, bool bFadeIn)
{
	xlogf("%s(self = %p, fSeconds = %f, bFadeIn = %d)\n", __func__, self, fSeconds, bFadeIn);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_vr_IVRCompositor_CompositorBringToFront(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_vr_IVRCompositor_CompositorGoToBack(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_vr_IVRCompositor_CompositorQuit(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
}

S_CLASSAPI bool S_CLASSCALLTYPE
SteamAPI_vr_IVRCompositor_IsFullscreen(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return false;
}

S_CLASSAPI uint32_t S_CLASSCALLTYPE
SteamAPI_vr_IVRControlPanel_GetDriverCount(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI uint32_t S_CLASSCALLTYPE
SteamAPI_vr_IVRControlPanel_GetDriverId(SELF, uint32_t unDriverIndex, char *pchBuffer, uint32_t unBufferLen)
{
	xlogf("%s(self = %p, unDriverIndex = %d, pchBuffer = %p, unBufferLen = %d)\n", __func__, self, unDriverIndex, pchBuffer, unBufferLen);
	return 0;
}

S_CLASSAPI uint32_t S_CLASSCALLTYPE
SteamAPI_vr_IVRControlPanel_GetDriverDisplayCount(SELF, const char *pchDriverId)
{
	xlogf("%s(self = %p, pchDriverId = %s)\n", __func__, self, pchDriverId);
	return 0;
}

S_CLASSAPI uint32_t S_CLASSCALLTYPE
SteamAPI_vr_IVRControlPanel_GetDriverDisplayId(SELF, const char *pchDriverId, uint32_t unDisplayIndex, char *pchBuffer, uint32_t unBufferLen)
{
	xlogf("%s(self = %p, pchDriverId = %s, unDisplayIndex = %d, pchBuffer = %p, unBufferLen = %d)\n", __func__, self, pchDriverId, unDisplayIndex, pchBuffer, unBufferLen);
	return 0;
}

S_CLASSAPI uint32_t S_CLASSCALLTYPE
SteamAPI_vr_IVRControlPanel_GetDriverDisplayModelNumber(SELF, const char *pchDriverId, const char *pchDisplayId, char *pchBuffer, uint32_t unBufferLen)
{
	xlogf("%s(self = %p, pchDriverId = %s, pchDisplayId = %s, pchBuffer = %p, unBufferLen = %d)\n", __func__, self, pchDriverId, pchDisplayId, pchBuffer, unBufferLen);
	return 0;
}

S_CLASSAPI uint32_t S_CLASSCALLTYPE
SteamAPI_vr_IVRControlPanel_GetDriverDisplaySerialNumber(SELF, const char *pchDriverId, const char *pchDisplayId, char *pchBuffer, uint32_t unBufferLen)
{
	xlogf("%s(self = %p, pchDriverId = %s, pchDisplayId = %s, pchBuffer = %p, unBufferLen = %d)\n", __func__, self, pchDriverId, pchDisplayId, pchBuffer, unBufferLen);
	return 0;
}

S_CLASSAPI uint32_t S_CLASSCALLTYPE
SteamAPI_vr_IVRControlPanel_LoadSharedResource(SELF, const char *pchResourceName, char *pchBuffer, uint32_t unBufferLen)
{
	xlogf("%s(self = %p, pchResourceName = %s, pchBuffer = %p, unBufferLen = %d)\n", __func__, self, pchResourceName, pchBuffer, unBufferLen);
	return 0;
}

S_CLASSAPI float S_CLASSCALLTYPE
SteamAPI_vr_IVRControlPanel_GetIPD(SELF)
{
	xlogf("%s(self = %p)\n", __func__, self);
	return 0;
}

S_CLASSAPI void S_CLASSCALLTYPE
SteamAPI_vr_IVRControlPanel_SetIPD(SELF, float fIPD)
{
	xlogf("%s(self = %p, fIPD = %f)\n", __func__, self, fIPD);
}
