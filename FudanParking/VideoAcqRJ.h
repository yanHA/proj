#ifndef VideoAcqRj_H
#define VideoAcqRj_H

#include "VideoAcq.h"

//#include "VideoAcqAxisWrapper.h"

#include <MulticastRtpSource.h>
#include <Decoder.h>

using namespace FFDecoder;

/** 视频采集派生类，Axis摄像头 */
class CVideoAcqRJ:public CVideoAcq
{
public:
    CVideoAcqRJ();
    ~CVideoAcqRJ();

    BOOL Initialize(CVideoBuffer *buffer,AcqParam param);
    BOOL StartAcq();
    BOOL StopAcq();
    void AddFrame();

	static void AddImageCallBack(void *imageBuffer,int width,int height,void *pUserData);

	CVideoBuffer *m_buffer;

private:
	static int VideoCallbackFun(MirMediaSource *pMediaSource, MediaData *pMediaData, void *pUserData);

private:
	char m_ip[128];
	int m_nPort;

	MulticastRtpSource *m_rtpSource;
	FF_DecodeResult m_result;
	uchar *m_outBuffer;
	FF_PicturePara m_picParam;
	Decoder *m_decoder;
	int m_outLen;
	int m_outSize;

	CvSize m_imgSz;
	IplImage *pImg;
	bool m_bThreadTerminated;
};

#endif