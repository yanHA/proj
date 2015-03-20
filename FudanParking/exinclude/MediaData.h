#pragma once
#include "RTPVideoDLLDefine.h"
#include <stdio.h>
#ifndef RTPVIDEO_DLL_EXPORT
#include <windows.h>
#else
#include <WinSock2.h>
#endif
#include <WinSock.h>

enum Codec
{
	CODEC_UNKOWN = 0,

	//video codec
	CODEC_H264,			//H264格式的码流类型
	CODEC_MPEG4,		//MPEG4格式的码流类型
	CODEC_MJPEG,		//MJPEG格式的码流类型

	//source codec
	CODEC_H264_NAL,		//NAL数据源类型
	CODEC_H264_RTP,		//H264格式的码流、RTP数据源类型
	CODEC_RTSP,			//RTSP数据源类型
	CODEC_MPEG4_RTP,	//MPEG4格式的码流、RTP数据源类型
	CODEC_MJPEG_RTP,	//MJPEG格式的码流、RTP数据源类型

	//Render codec
	CODEC_YUY2,			//YUY2渲染的格式类型
	CODEC_YUV420,		//YUV420渲染的格式类型
	CODEC_A8R8G8B8		//A8R8G8B8渲染的格式类型
};

enum FrameType
{
	Frame_I = 0,
	Frame_P,
	Frame_B
};

struct MediaData
{
	MediaData()
	{
		pData = NULL;
		offset = 0;
		size = 0;
		codec = CODEC_UNKOWN;
	}
	unsigned char *pData;    //数据体
	int offset;		//偏移
	int size;		//大小
	Codec codec;	//编码类型
	FrameType frameType;
	struct timeval presentationTime;
};