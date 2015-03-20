#include "stdafx.h"
#include "VideoAcqAxis.h"

void CVideoAcqAxis::AddImageCallBack(void *imageBuffer,int width,int height,void *pUserData)
{
	CVideoAcqAxis *pAxis = (CVideoAcqAxis*)pUserData;

	if(pAxis->m_nframe % 3 != 0)
	{
		pAxis->m_nframe ++;
		return;
	}

	WaitForSingleObject(pAxis->m_buffer->hWriteMutex, INFINITE);

	IplImage *pImg = cvCreateImageHeader(cvSize(width,height),8,3);
	pImg->imageData = (char*)imageBuffer;

	pAxis->m_buffer->AddImage(pImg,pAxis->m_nframe);

	cvReleaseImageHeader(&pImg);

	pAxis->m_nframe ++;
	pAxis->m_nframe %= MAX_FRAME_TAG;

	ReleaseMutex(pAxis->m_buffer->hWriteMutex);

	ReleaseSemaphore(pAxis->m_buffer->hSemaphore, 1, NULL);

	pAxis->AddFrame();
}

CVideoAcqAxis::CVideoAcqAxis()
{
	pAxisWraper = NULL;
	m_bThreadTerminated = true;
	m_buffer = NULL;
	m_nframe = 0;

	pAxisWraper = new VideoAcqAxisWrapper();
}

CVideoAcqAxis::~CVideoAcqAxis()
{
	if(!m_bThreadTerminated)
		pAxisWraper->AxisStop();

	delete pAxisWraper;
}

BOOL CVideoAcqAxis::Initialize(CVideoBuffer *buffer,AcqParam param)
{
	m_buffer = buffer;

	AcqParamAxis paramAxis;
	paramAxis.ipv4 = param.ipv4;
	paramAxis.user = param.user;
	paramAxis.pass = param.pass;
	paramAxis.port = param.port;

	pAxisWraper->AxisInit(paramAxis);

	return 1;
}

BOOL CVideoAcqAxis::StartAcq()
{
	int retval = pAxisWraper->AxisStart(AddImageCallBack,this);

	m_bThreadTerminated = false;

	return retval;
}

BOOL CVideoAcqAxis::StopAcq()
{
	pAxisWraper->AxisStop();

	m_bThreadTerminated = true;

	return 1;
}

void CVideoAcqAxis::AddFrame()
{
	// emit receiveNewImage();
}
