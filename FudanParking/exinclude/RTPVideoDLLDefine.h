#pragma once

#ifdef RTPVIDEO_DLL_EXPORT
#define RTPVIDEO_DLL_EXPORT_IMPORT _declspec(dllexport)
#else
#define RTPVIDEO_DLL_EXPORT_IMPORT _declspec(dllimport)
#endif