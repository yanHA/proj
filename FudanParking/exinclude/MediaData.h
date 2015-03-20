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
	CODEC_H264,			//H264��ʽ����������
	CODEC_MPEG4,		//MPEG4��ʽ����������
	CODEC_MJPEG,		//MJPEG��ʽ����������

	//source codec
	CODEC_H264_NAL,		//NAL����Դ����
	CODEC_H264_RTP,		//H264��ʽ��������RTP����Դ����
	CODEC_RTSP,			//RTSP����Դ����
	CODEC_MPEG4_RTP,	//MPEG4��ʽ��������RTP����Դ����
	CODEC_MJPEG_RTP,	//MJPEG��ʽ��������RTP����Դ����

	//Render codec
	CODEC_YUY2,			//YUY2��Ⱦ�ĸ�ʽ����
	CODEC_YUV420,		//YUV420��Ⱦ�ĸ�ʽ����
	CODEC_A8R8G8B8		//A8R8G8B8��Ⱦ�ĸ�ʽ����
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
	unsigned char *pData;    //������
	int offset;		//ƫ��
	int size;		//��С
	Codec codec;	//��������
	FrameType frameType;
	struct timeval presentationTime;
};