#pragma once

#include "steamtypes.h"
#include "openvr.h"

typedef void IVRSystem;

typedef struct CVRSystem CVRSystem;

struct CVRSystem {
	CSteamBase base;
};

S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_vr_void_GetWindowBounds(SELF, int32_t *pnX, int32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_vr_void_GetRecommendedRenderTargetSize(SELF, uint32_t *pnWidth, uint32_t *pnHeight);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_vr_void_GetEyeOutputViewport(SELF, Hmd_Eye eEye, uint32_t *pnX, uint32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight);
S_CLASSAPI struct HmdMatrix44_t S_CLASSCALLTYPE SteamAPI_vr_void_GetProjectionMatrix(SELF, Hmd_Eye eEye, float fNearZ, float fFarZ, EGraphicsAPIConvention eProjType);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_vr_void_GetProjectionRaw(SELF, Hmd_Eye eEye, float *pfLeft, float *pfRight, float *pfTop, float *pfBottom);
S_CLASSAPI struct DistortionCoordinates_t S_CLASSCALLTYPE SteamAPI_vr_void_ComputeDistortion(SELF, Hmd_Eye eEye, float fU, float fV);
S_CLASSAPI struct HmdMatrix34_t S_CLASSCALLTYPE SteamAPI_vr_void_GetEyeToHeadTransform(SELF, Hmd_Eye eEye);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_vr_void_GetTimeSinceLastVsync(SELF, float *pfSecondsSinceLastVsync, uint64_t *pulFrameCounter);
S_CLASSAPI int32_t S_CLASSCALLTYPE SteamAPI_vr_void_GetD3D9AdapterIndex(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_vr_void_GetDXGIOutputInfo(SELF, int32_t *pnAdapterIndex, int32_t *pnAdapterOutputIndex);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_vr_void_AttachToWindow(SELF, void *hWnd);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_vr_void_GetDeviceToAbsoluteTrackingPose(SELF, TrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, TrackedDevicePose_t *pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_vr_void_ResetSeatedZeroPose(SELF);
S_CLASSAPI struct HmdMatrix34_t S_CLASSCALLTYPE SteamAPI_vr_void_GetSeatedZeroPoseToStandingAbsoluteTrackingPose(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_vr_void_LoadRenderModel(SELF, const char *pchRenderModelName, RenderModel_t *pRenderModel);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_vr_void_FreeRenderModel(SELF, struct RenderModel_t *pRenderModel);
S_CLASSAPI TrackedDeviceClass S_CLASSCALLTYPE SteamAPI_vr_void_GetTrackedDeviceClass(SELF, TrackedDeviceIndex_t unDeviceIndex);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_vr_void_IsTrackedDeviceConnected(SELF, TrackedDeviceIndex_t unDeviceIndex);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_vr_void_GetBoolTrackedDeviceProperty(SELF, TrackedDeviceIndex_t unDeviceIndex, TrackedDeviceProperty prop, TrackedPropertyError *pError);
S_CLASSAPI float S_CLASSCALLTYPE SteamAPI_vr_void_GetFloatTrackedDeviceProperty(SELF, TrackedDeviceIndex_t unDeviceIndex, TrackedDeviceProperty prop, TrackedPropertyError *pError);
S_CLASSAPI int32_t S_CLASSCALLTYPE SteamAPI_vr_void_GetInt32TrackedDeviceProperty(SELF, TrackedDeviceIndex_t unDeviceIndex, TrackedDeviceProperty prop, TrackedPropertyError *pError);
S_CLASSAPI uint64_t S_CLASSCALLTYPE SteamAPI_vr_void_GetUint64TrackedDeviceProperty(SELF, TrackedDeviceIndex_t unDeviceIndex, TrackedDeviceProperty prop, TrackedPropertyError *pError);
S_CLASSAPI struct HmdMatrix34_t S_CLASSCALLTYPE SteamAPI_vr_void_GetMatrix34TrackedDeviceProperty(SELF, TrackedDeviceIndex_t unDeviceIndex, TrackedDeviceProperty prop, TrackedPropertyError *pError);
S_CLASSAPI uint32_t S_CLASSCALLTYPE SteamAPI_vr_void_GetStringTrackedDeviceProperty(SELF, TrackedDeviceIndex_t unDeviceIndex, TrackedDeviceProperty prop, char *pchValue, uint32_t unBufferSize, TrackedPropertyError *pError);
S_CLASSAPI const char *S_CLASSCALLTYPE SteamAPI_vr_void_GetPropErrorNameFromEnum(SELF, TrackedPropertyError error);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_vr_void_PollNextEvent(SELF, VREvent_t *pEvent);
S_CLASSAPI const char *S_CLASSCALLTYPE SteamAPI_vr_void_GetEventTypeNameFromEnum(SELF, EVREventType eType);
S_CLASSAPI struct HiddenAreaMesh_t S_CLASSCALLTYPE SteamAPI_vr_void_GetHiddenAreaMesh(SELF, Hmd_Eye eEye);
S_CLASSAPI ChaperoneCalibrationState S_CLASSCALLTYPE SteamAPI_vr_IVRChaperone_GetCalibrationState(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_vr_IVRChaperone_GetSoftBoundsInfo(SELF, ChaperoneSoftBoundsInfo_t *pInfo);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_vr_IVRChaperone_GetHardBoundsInfo(SELF, HmdQuad_t *pQuadsBuffer, uint32_t *punQuadsCount);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_vr_IVRChaperone_GetSeatedBoundsInfo(SELF, ChaperoneSeatedBoundsInfo_t *pInfo);
S_CLASSAPI uint32_t S_CLASSCALLTYPE SteamAPI_vr_IVRCompositor_GetLastError(SELF, char *pchBuffer, uint32_t unBufferSize);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_vr_IVRCompositor_SetVSync(SELF, bool bVSync);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_vr_IVRCompositor_GetVSync(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_vr_IVRCompositor_SetGamma(SELF, float fGamma);
S_CLASSAPI float S_CLASSCALLTYPE SteamAPI_vr_IVRCompositor_GetGamma(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_vr_IVRCompositor_SetGraphicsDevice(SELF, Compositor_DeviceType eType, void *pDevice);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_vr_IVRCompositor_WaitGetPoses(SELF, struct TrackedDevicePose_t *pPoseArray, uint32_t unPoseArrayCount);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_vr_IVRCompositor_Submit(SELF, Hmd_Eye eEye, void *pTexture, Compositor_TextureBounds *pBounds);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_vr_IVRCompositor_ClearLastSubmittedFrame(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_vr_IVRCompositor_GetOverlayDefaults(SELF, struct Compositor_OverlaySettings *pSettings);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_vr_IVRCompositor_SetOverlay(SELF, void *pTexture, struct Compositor_OverlaySettings *pSettings);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_vr_IVRCompositor_SetOverlayRaw(SELF, void *buffer, uint32_t width, uint32_t height, uint32_t depth, struct Compositor_OverlaySettings *pSettings);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_vr_IVRCompositor_SetOverlayFromFile(SELF, const char *pchFilePath, struct Compositor_OverlaySettings *pSettings);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_vr_IVRCompositor_ClearOverlay(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_vr_IVRCompositor_GetFrameTiming(SELF, struct Compositor_FrameTiming *pTiming, uint32_t unFramesAgo);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_vr_IVRCompositor_FadeToColor(SELF, float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_vr_IVRCompositor_FadeGrid(SELF, float fSeconds, bool bFadeIn);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_vr_IVRCompositor_CompositorBringToFront(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_vr_IVRCompositor_CompositorGoToBack(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_vr_IVRCompositor_CompositorQuit(SELF);
S_CLASSAPI bool S_CLASSCALLTYPE SteamAPI_vr_IVRCompositor_IsFullscreen(SELF);
S_CLASSAPI uint32_t S_CLASSCALLTYPE SteamAPI_vr_IVRControlPanel_GetDriverCount(SELF);
S_CLASSAPI uint32_t S_CLASSCALLTYPE SteamAPI_vr_IVRControlPanel_GetDriverId(SELF, uint32_t unDriverIndex, char *pchBuffer, uint32_t unBufferLen);
S_CLASSAPI uint32_t S_CLASSCALLTYPE SteamAPI_vr_IVRControlPanel_GetDriverDisplayCount(SELF, const char *pchDriverId);
S_CLASSAPI uint32_t S_CLASSCALLTYPE SteamAPI_vr_IVRControlPanel_GetDriverDisplayId(SELF, const char *pchDriverId, uint32_t unDisplayIndex, char *pchBuffer, uint32_t unBufferLen);
S_CLASSAPI uint32_t S_CLASSCALLTYPE SteamAPI_vr_IVRControlPanel_GetDriverDisplayModelNumber(SELF, const char *pchDriverId, const char *pchDisplayId, char *pchBuffer, uint32_t unBufferLen);
S_CLASSAPI uint32_t S_CLASSCALLTYPE SteamAPI_vr_IVRControlPanel_GetDriverDisplaySerialNumber(SELF, const char *pchDriverId, const char *pchDisplayId, char *pchBuffer, uint32_t unBufferLen);
S_CLASSAPI uint32_t S_CLASSCALLTYPE SteamAPI_vr_IVRControlPanel_LoadSharedResource(SELF, const char *pchResourceName, char *pchBuffer, uint32_t unBufferLen);
S_CLASSAPI float S_CLASSCALLTYPE SteamAPI_vr_IVRControlPanel_GetIPD(SELF);
S_CLASSAPI void S_CLASSCALLTYPE SteamAPI_vr_IVRControlPanel_SetIPD(SELF, float fIPD);
