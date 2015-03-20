#ifndef VideoAcqAxis_H
#define VideoAcqAxis_H

//#include <zmq.hpp>
#include "VideoAcq.h"

#include "VideoAcqAxisWrapper.h"

/** 视频采集派生类，Axis摄像头 */
class CVideoAcqAxis:public CVideoAcq
{
public:
    CVideoAcqAxis();
    ~CVideoAcqAxis();

    BOOL Initialize(CVideoBuffer *buffer,AcqParam param);
    BOOL StartAcq();
    BOOL StopAcq();
    void AddFrame();

	static void AddImageCallBack(void *imageBuffer,int width,int height,void *pUserData);

	CVideoBuffer *m_buffer;

private:
	VideoAcqAxisWrapper *pAxisWraper;

	IplImage *pImg;
	bool m_bThreadTerminated;
};

#endif