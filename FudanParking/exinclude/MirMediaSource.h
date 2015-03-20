//#pragma once
#ifndef _MY_DEDIASOURCE_
#define _MY_DEDIASOURCE_

#include "MediaData.h"
class MirMediaSource;
typedef int (*MediaSourceCallbackFun)(MirMediaSource *pMediaSource,MediaData* pMediaData,void *pUserData);

class RTPVIDEO_DLL_EXPORT_IMPORT MirMediaSource
{
public:
	MirMediaSource();
	virtual ~MirMediaSource();

	virtual int open(MediaSourceCallbackFun callbackFun,
		void *pUserData,unsigned char rtpPayloadFormat) = 0;

	virtual void close() = 0;

	Codec getCodec();
protected:
	MediaSourceCallbackFun m_pCallbackFun;
	//int (*m_pCallbackFun)(Mirror::Media::MirMediaSource *pMediaSource,MediaSample* pMediaSample,void *pUserData);
	void *m_pUserData;

	Codec m_codec;

	bool  m_bIsRuning;
};
#endif