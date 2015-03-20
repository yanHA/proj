#pragma once

#ifdef DECODER_DLL_EXPORT
#define DECODER_DLL_EXPORT_IMPORT __declspec(dllexport)
#else
#define DECODER_DLL_EXPORT_IMPORT __declspec(dllimport)
#endif