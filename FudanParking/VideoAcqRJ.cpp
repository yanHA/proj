#include "stdafx.h"
#include "VideoAcqRJ.h"

void CVideoAcqRJ::AddImageCallBack(void *imageBuffer,int width,int height,void *pUserData)
{
	CVideoAcqRJ *pVideoAcq = (CVideoAcqRJ*)pUserData;

	if(pVideoAcq->m_nframe % 2 == 0)
	{
		pVideoAcq->m_nframe ++;
		return;
	}

	WaitForSingleObject(pVideoAcq->m_buffer->hWriteMutex, INFINITE);

	IplImage *pImg = cvCreateImageHeader(cvSize(width,height),8,3);
	pImg->imageData = (char*)imageBuffer;

	pVideoAcq->m_buffer->AddImage(pImg,pVideoAcq->m_nframe);

	cvReleaseImageHeader(&pImg);

	pVideoAcq->m_nframe ++;
	pVideoAcq->m_nframe %= MAX_FRAME_TAG;

	ReleaseMutex(pVideoAcq->m_buffer->hWriteMutex);

	ReleaseSemaphore(pVideoAcq->m_buffer->hSemaphore, 1, NULL);

	pVideoAcq->AddFrame();
}

CVideoAcqRJ::CVideoAcqRJ()
{
	m_bThreadTerminated = true;
}

CVideoAcqRJ::~CVideoAcqRJ()
{
	delete m_rtpSource;
	free(m_outBuffer);
}

BOOL CVideoAcqRJ::Initialize(CVideoBuffer *buffer,AcqParam param)
{
	m_buffer = buffer;

	strcpy(m_ip,param.ipv4.c_str());
	m_nPort = param.port;

	Decoder::decoderInit();
	m_decoder = Decoder::createDecoder(CODEC_TYPE_H264);

	m_rtpSource = new MulticastRtpSource(m_ip, m_nPort, CODEC_H264_RTP);

	m_imgSz = cvSize(buffer->m_imageWidth,buffer->m_imageHeight);
	m_outBuffer	= (uchar*)malloc(m_imgSz.width * m_imgSz.height * 3);

	printf("RJ inited\n");

	return 1;
}

BOOL CVideoAcqRJ::StartAcq()
{
	m_rtpSource->open(VideoCallbackFun, (void*)this, 96);		// 该函数的返回值无用，不成功为0，成功也为0

	m_bThreadTerminated = false;

	printf("RJ started\n");

	return 1;
}

BOOL CVideoAcqRJ::StopAcq()
{
	m_rtpSource->close();

	m_bThreadTerminated = true;

	return 1;
}

int CVideoAcqRJ::VideoCallbackFun(MirMediaSource *pMediaSource, MediaData *pMediaData, void *pUserData)
{
	CVideoAcqRJ *pCamera = (CVideoAcqRJ*)pUserData;

	if(pMediaData->pData == NULL)
	{
		printf("pMediaData->pData == NULL");
		return 1;
	}

	FF_DecodeResult result = pCamera->m_decoder->decodeFrame(pMediaData->pData, pMediaData->size);
	if((result != SUCCESS) && (result != RESOLUTION_CHANGED))
	{
		printf("(result != SUCCESS) && (result != RESOLUTION_CHANGED)");
		return 1;
	}

	FF_PicturePara picParam;
	result = pCamera->m_decoder->getDecodedResolution(picParam);
	if(result != SUCCESS)
	{
		printf("result != SUCCESS");
		return 1;
	}

	CvSize imgSz = pCamera->m_imgSz;
	if(picParam.width != imgSz.width || picParam.height != imgSz.height)
	{
		printf("picParam.width != imgSz.width || picParam.height != imgSz.height");
		return 1;
	}

	int len = imgSz.width * imgSz.height * 3;
	result = pCamera->m_decoder->getDecodedData(pCamera->m_outBuffer, len);
	if(result != SUCCESS)
	{
		printf("getDecodedData(pCamera->m_outBuffer, len)");
		return 1;
	}

	//pCamera->m_videoBuffer->AddFrame(pCamera->m_outBuffer, pCamera->m_nFrame ++);
	pCamera->AddImageCallBack(pCamera->m_outBuffer,imgSz.width,imgSz.height,pCamera);

	return 1;
}

void CVideoAcqRJ::AddFrame()
{
	//emit receiveNewImage();
}