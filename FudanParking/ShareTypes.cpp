#include "stdafx.h"
#include "ShareTypes.h"

CVideoBuffer::CVideoBuffer()
{
}

CVideoBuffer::~CVideoBuffer()
{
	//释放缓存图像
	for(int i = 0; i < m_length; i ++)
	{
		cvReleaseImage(&m_videoBuffer[i].frameImg);
		m_videoBuffer[i].frameImg = NULL;

		if(hReadMutex[i] != NULL)
			CloseHandle(hReadMutex[i]);
	}

	if(hWriteMutex != NULL)
			CloseHandle(hWriteMutex);
	if(hSemaphore != NULL)
			CloseHandle(hSemaphore);

	delete[] m_videoBuffer;
}

BOOL CVideoBuffer::CreateBuffer(int length,string configFile,string itemName)
{
	//读配置文件,获取缓冲图像大小
	int mode = GetPrivateProfileIntA(itemName.c_str() , "SizeMode", 0, configFile.c_str());
	if(mode == 0)
	{
		//读取配置文件中设置的图片宽高
		m_imageWidth = GetPrivateProfileIntA(itemName.c_str() , "Width", 0, configFile.c_str());
		m_imageHeight = GetPrivateProfileIntA(itemName.c_str() , "Height", 0, configFile.c_str());
	}
	else if(mode == 1)
	{
		//自动获取读入视屏的宽高
		char filePath[256]; 
		GetPrivateProfileStringA(itemName.c_str(), "AcqVideo", "Test.avi", filePath, sizeof(filePath), CONFIG_FILE_NAME);
		CvCapture *capture = cvCaptureFromAVI(filePath);
		IplImage *videoImage = cvQueryFrame(capture);
		m_imageWidth = videoImage->width;
		m_imageHeight = videoImage->height;
		
		cvReleaseCapture(&capture);
		cvReleaseImage(&videoImage);
	}

	m_length = length;
	m_videoBuffer = new VideoImage[m_length];

	int i;
	for(i = 0; i < m_length; i ++)
	{
		m_videoBuffer[i].frameImg = cvCreateImage(cvSize(m_imageWidth,m_imageHeight),8,3);
		m_videoBuffer[i].frameTag = -1;

		hReadMutex[i] = CreateMutex(NULL, FALSE, NULL);
	}

	hSemaphore = CreateSemaphore(NULL, 0, 1, NULL);
	hWriteMutex = CreateMutex(NULL, FALSE, NULL);

	m_tail = 0;
	m_cur = 0;

	return 1;

}

BOOL CVideoBuffer::AddImage(IplImage* frameImg,long frameTag)
{
	int cur = m_tail;
	//WaitForSingleObject(hReadMutex[cur], INFINITE);

	if(frameImg->width * 3 == frameImg->widthStep)
	{
		memcpy(m_videoBuffer[m_tail].frameImg->imageData,frameImg->imageData,frameImg->width * frameImg->height * 3);
	}
	else
	{
		cvCopy(frameImg,m_videoBuffer[m_tail].frameImg);
		//SubImageMemCpy(m_videoBuffer[m_tail].frameImg,frameImg);
	}
	m_videoBuffer[m_tail].frameTag = frameTag;
	
	m_cur = m_tail;
	m_tail ++;
	if(m_tail >= m_length)
		m_tail = 0;

	//ReleaseMutex(hReadMutex[cur]);

	return 1;
}

BOOL CVideoBuffer::GetImageCurrent(IplImage* dstImg,long &frameTag)
{
	DWORD retval = WaitForSingleObject(hSemaphore, 50);
	if(retval == WAIT_TIMEOUT )
		return 0;

	WaitForSingleObject(hWriteMutex, INFINITE);
	int cur = m_cur;

	//WaitForSingleObject(hReadMutex[cur], INFINITE);

	if(dstImg->width * 3 == dstImg->widthStep)
	{
		memcpy(dstImg->imageData,m_videoBuffer[cur].frameImg->imageData,m_videoBuffer[cur].frameImg->width * m_videoBuffer[cur].frameImg->height * 3);
	}
	else
	{
		cvCopy(dstImg,m_videoBuffer[cur].frameImg);
	}
	frameTag = m_videoBuffer[cur].frameTag;

	//ReleaseMutex(hReadMutex[cur]);
	ReleaseMutex(hWriteMutex);

	return 1;
}

BOOL CVideoBuffer::GetImageCurrentLow(IplImage* lowImg,long &frameTag,int &pos)
{
	DWORD retval = WaitForSingleObject(hSemaphore, 50);
	if(retval == WAIT_TIMEOUT )
		return 0;

	WaitForSingleObject(hWriteMutex, INFINITE);
	int cur = m_cur;

	cvResize(m_videoBuffer[cur].frameImg,lowImg);
	frameTag = m_videoBuffer[cur].frameTag;
	pos = cur;

	ReleaseMutex(hWriteMutex);
	return 1;
}

BOOL CVideoBuffer::GetImageCurrentLD(IplImage* smallImg,long &frameTag)
{
	//DWORD retval = WaitForSingleObject(hSemaphore, 50);
	//if(retval == WAIT_TIMEOUT )
	//	return 0;

	WaitForSingleObject(hWriteMutex, INFINITE);
	int cur = m_cur;

	cvResize(m_videoBuffer[cur].frameImg,smallImg,0);
	frameTag = m_videoBuffer[cur].frameTag;

	ReleaseMutex(hWriteMutex);
	return 1;
}

BOOL CVideoBuffer::GetImageCurrentHD(IplImage* dstImg,long &frameTag)
{
	//DWORD retval = WaitForSingleObject(hSemaphore, 50);
	//if(retval == WAIT_TIMEOUT )
	//	return 0;

	WaitForSingleObject(hWriteMutex, INFINITE);
	int cur = m_cur;

	if(dstImg->width * 3 == dstImg->widthStep)
	{
		memcpy(dstImg->imageData,m_videoBuffer[cur].frameImg->imageData,m_videoBuffer[cur].frameImg->width * m_videoBuffer[cur].frameImg->height * 3);
	}
	else
	{
		cvCopy(dstImg,m_videoBuffer[cur].frameImg);
	}
	frameTag = m_videoBuffer[cur].frameTag;

	ReleaseMutex(hWriteMutex);

	return 1;
}

BOOL CVideoBuffer::GetImageCurrentLocal(IplImage* localImg,long &frameTag,CvRect roi)
{
	//DWORD retval = WaitForSingleObject(hSemaphore, 50);
	//if(retval == WAIT_TIMEOUT )
	//	return 0;

	WaitForSingleObject(hWriteMutex, INFINITE);
	int cur = m_cur;

	cvSetImageROI(m_videoBuffer[cur].frameImg, roi);
	cvCopyImage(m_videoBuffer[cur].frameImg, localImg);
	cvResetImageROI(m_videoBuffer[cur].frameImg);

	frameTag = m_videoBuffer[cur].frameTag;

	ReleaseMutex(hWriteMutex);
	return 1;
}

BOOL CVideoBuffer::GetImageRecentHD(IplImage* dstImg,long &frameTag,int recentCount)
{
	//DWORD retval = WaitForSingleObject(hSemaphore, 50);
	//if(retval == WAIT_TIMEOUT )
	//	return 0;

	WaitForSingleObject(hWriteMutex, INFINITE);
	int cur = m_cur - recentCount;
	if(cur < 0)
		cur += m_length;

	if(dstImg->width * 3 == dstImg->widthStep)
	{
		memcpy(dstImg->imageData,m_videoBuffer[cur].frameImg->imageData,m_videoBuffer[cur].frameImg->width * m_videoBuffer[cur].frameImg->height * 3);
	}
	else
	{
		cvCopy(dstImg,m_videoBuffer[cur].frameImg);
	}
	frameTag = m_videoBuffer[cur].frameTag;

	ReleaseMutex(hWriteMutex);
	return 1;
}

int CVideoBuffer::GetIndexByFrameNum(long frameTag)
{
	int i;
	for(i = 0;i < m_length;i ++)
	{
		if(m_videoBuffer[i].frameTag == frameTag)
			return i;
	}

	//找不到
	return -1;
}

BOOL CVideoBuffer::GetImageByIndex(int index,IplImage* dstImg)
{
	if(index >= 0 && index < m_length)
	{
		//here lock
		WaitForSingleObject(hWriteMutex, INFINITE);

		memcpy(dstImg->imageData,m_videoBuffer[index].frameImg->imageData,m_videoBuffer[index].frameImg->width * m_videoBuffer[index].frameImg->height * 3);
		
		//here release lock
		ReleaseMutex(hWriteMutex);
		return 1;
	}
	else
	{
		return 0;
	}
}

void CVideoBuffer::SubImageMemCpy(IplImage* dstImg,IplImage* srcImg)
{
	int i;
	int offsetDst = 0;
	int offsetSrc = srcImg->width;
	for(i = 0;i < srcImg->height;i ++)
	{
		memcpy(dstImg->imageData + offsetDst,srcImg->imageData + offsetSrc,dstImg->width * 3);
		offsetDst += dstImg->widthStep;
		offsetSrc += srcImg->widthStep;
	}
}

int CVideoBuffer::GetIndexCurrent()
{
	//int cur = m_tail - 1;
	//if (cur < 0)	
	//	cur += m_length;

	return m_cur;
}