#include "stdafx.h"
#include "VideoAcq.h"


/*CVideoBuffer::CVideoBuffer(int length)
{
    m_length = length;
    m_videoBuffer = new VideoImageA[m_length];

    int i;
    for(i = 0; i < m_length; i ++)
    {
        m_videoBuffer[i].frameImg = NULL;
        m_videoBuffer[i].frameTag = -1;
    }
}
CVideoBuffer::~CVideoBuffer()
{
    delete m_videoBuffer;
}*/

// Base
CVideoAcquisition::CVideoAcquisition()
{
}

CVideoAcquisition::~CVideoAcquisition()
{
}

// AVI
CVideoAcqAvi::CVideoAcqAvi()
{
    m_bThreadTerminal = true;

	m_nframe = 0;
}

CVideoAcqAvi::~CVideoAcqAvi()
{
    if(!m_bThreadTerminal)
        StopAcq();
}

BOOL CVideoAcqAvi::Initialize(CVideoBuffer *buffer,AcqParam param)
{
    m_buffer = buffer;
    m_strAviVideoPath = param.fileName;
    m_frameRate = param.frameRate;

    m_Thread = NULL;

    m_qImage = NULL;
	m_pCapture = NULL;

    //if(m_strAviVideoPath.find(".avi") == -1)
    //    return 0;

    m_hRequestExitEvent = FALSE;

	
    return 1;
}

BOOL CVideoAcqAvi::StartAcq()
{
    // 初始化线程标志
    m_hRequestExitEvent = CreateEvent(NULL, TRUE, false, NULL);

    m_Thread = CreateThread(NULL,0,AcqThreadFunc,(LPVOID)this,0,&m_threadID);

    if(m_Thread != NULL)
	{
		// 判断是否已读取视频
		bool retval = 1;
		int i = 10;
		while(i -- > 0)
		{
			if(m_bThreadTerminal == 0)
			{
				retval = 0;
				break;
			}

			Sleep(500);
		}

		if(retval == 0)
			return true;
		else 
			return false;   
	}
    else
        return false;
}

BOOL CVideoAcqAvi::StopAcq()
{
    //if(!TerminateThread(m_Thread,0))
    //        return 0;
    //CloseHandle(m_Thread);

    SetEvent(m_hRequestExitEvent);

    WaitForSingleObject(m_Thread,INFINITE);
    return 1;
}

/*
BOOL CVideoAcqAvi::SetInputFrameRate(double inFrameRate)
{
    m_frameRate = inFrameRate;
    return 1;
}
*/

void CVideoAcqAvi::AddFrame()
{
    //cvCvtColor(m_qImage,m_buffer->m_videoBuffer[0].frameImg,CV_BGR2RGB);
	//m_buffer->m_videoBuffer[0].frameTag = m_nframe;

	WaitForSingleObject(m_buffer->hWriteMutex, INFINITE);

	m_buffer->AddImage(m_qImage,m_nframe);

	m_nframe ++;
	m_nframe %= MAX_FRAME_TAG;

	ReleaseMutex(m_buffer->hWriteMutex);

	ReleaseSemaphore(m_buffer->hSemaphore, 1, NULL);

	//emit receiveNewImage();
}

DWORD WINAPI CVideoAcqAvi::AcqThreadFunc(LPVOID lpParam)
{
	// COM初始化,用于多线程读写视频
	CoInitialize(NULL);

    // 读取文件路径及预设定帧率
    CVideoAcqAvi* pThis = (CVideoAcqAvi *)lpParam;


    // 是否批量处理
    bool batchProcess = false;
    if(pThis->m_strAviVideoPath.find(".avi") != -1)
        batchProcess = false;
    else
        batchProcess = true;

    int sleepTime = 0;
    int sleepPeriod = 0;

    // 记录时间调整帧率start
    int time1 = GetTickCount();

    if(!batchProcess)
    {
        pThis->m_pCapture = cvCaptureFromFile(pThis->m_strAviVideoPath.c_str());

		// 获取帧率调整sleepPeriod
		pThis->m_frameRate = cvGetCaptureProperty(pThis->m_pCapture,CV_CAP_PROP_FPS);
		sleepPeriod = 1000 / pThis->m_frameRate;

        while((pThis->m_qImage = cvQueryFrame(pThis->m_pCapture))&&
            (WaitForSingleObject(pThis->m_hRequestExitEvent, 0) == WAIT_TIMEOUT))
        {
			pThis->m_bThreadTerminal = false;
			// 帧率降低一半
			//if(!(pThis->m_qImage = cvQueryFrame(pThis->m_pCapture)))
			//	break;

            sleepPeriod = 1000 / pThis->m_frameRate;

#ifndef OPENCV2
			// 翻转
			cvFlip(pThis->m_qImage, pThis->m_qImage);
			pThis->m_qImage->origin = 0;
#endif

            //向缓冲中添加
            pThis->AddFrame();

            // 记录时间调整帧率end
            int time2 = GetTickCount();
            if(sleepPeriod > (time2 - time1))
                    sleepTime=sleepPeriod - (time2 - time1);
            else
                    sleepTime=0;
            Sleep(sleepTime);

            int time3 = GetTickCount();
            //printf("%d,%d,%d\n",time2-time1,sleepTime,time3-time1);
            time1 = time3;
        }
    }
	else if(batchProcess && !access(pThis->m_strAviVideoPath.c_str(),0))
	{
		WIN32_FIND_DATAA FindFileData;
		HANDLE hFind;
		string str = pThis->m_strAviVideoPath+"\\*.*";
		hFind = FindFirstFileA(str.c_str(),&FindFileData);

		do
		{
			string aviname = FindFileData.cFileName;
			if(aviname.find(".avi") == -1)	
			{
				continue;
			}

			aviname = pThis->m_strAviVideoPath + "\\" + FindFileData.cFileName;

			pThis->m_pCapture = cvCaptureFromFile(aviname.c_str());
			// 获取帧率调整sleepPeriod
			pThis->m_frameRate = cvGetCaptureProperty(pThis->m_pCapture,CV_CAP_PROP_FPS);
			sleepPeriod = 1000 / pThis->m_frameRate;

			while((pThis->m_qImage = cvQueryFrame(pThis->m_pCapture)) &&
				(WaitForSingleObject(pThis->m_hRequestExitEvent, 0) == WAIT_TIMEOUT))
			{
				pThis->m_bThreadTerminal = false;
#ifndef OPENCV2
				// 翻转
				cvFlip(pThis->m_qImage, pThis->m_qImage);
				pThis->m_qImage->origin = 0;
#endif
				// 放大
				//cvResize(pThis->m_curImage,pThis->m_curHighImage,CV_INTER_LINEAR);

				//向缓冲中添加
				pThis->AddFrame();

				// 记录时间调整帧率end
				int time2 = GetTickCount();
				if(sleepPeriod > (time2 - time1))
						sleepTime=sleepPeriod - (time2 - time1);
				else
						sleepTime=0;
				Sleep(sleepTime);

				int time3 = GetTickCount();
				//printf("%d,%d,%d\n",time2-time1,sleepTime,time3-time1);
				time1 = time3;
			}

			cvReleaseCapture(&pThis->m_pCapture);

		}while(FindNextFileA(hFind,&FindFileData) != 0 && (WaitForSingleObject(pThis->m_hRequestExitEvent, 0) == WAIT_TIMEOUT));
		FindClose(hFind);
	}

    pThis->m_bThreadTerminal = true;

	if(pThis->m_pCapture != NULL)
		cvReleaseCapture(&pThis->m_pCapture);
    // no need to release m_qImage
    //if(pThis->m_qImage != NULL)
    //    cvReleaseImage(&pThis->m_qImage);
    //pThis->m_qImage = NULL;

    CloseHandle(pThis->m_Thread);
	pThis->m_Thread = NULL;

    return 1;
}