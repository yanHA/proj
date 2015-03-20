#include "stdafx.h"
#include "MyThread.h"
#include "resource.h"



CMyThread::CMyThread()
{
	m_showImageSrc = cvLoadImage("./etc/ParkingSpot.jpg");
	m_carImage_1 = cvLoadImage("./etc/FDUcar_1.jpg");
	m_carImage_2 = cvLoadImage("./etc/FDUcar_2.jpg");

	m_testmodel = svm_load_model("./etc/mymodel.model");
	m_markPath = "./etc/mark.txt";
	m_showPicmark = "./etc/ParkingSpotmark.txt";
}

CMyThread::~CMyThread()
{
	cvReleaseImage(&m_showImageSrc);
	cvReleaseImage(&m_carImage_1);
	cvReleaseImage(&m_carImage_2);

	svm_free_model_content(m_testmodel);

}

BOOL CMyThread::Initialize(HDC Pic_hdc, CRect Pic_rect,CVideoBuffer *vBuffer, TQueue<struct CarStatus> *carqueue)
{
	m_Pic_hdc = Pic_hdc;
	m_Pic_rect = Pic_rect;
	m_vBuffer = vBuffer;
	m_carqueue = carqueue;

	return 1;
}

vector<CvRect> CMyThread::ReadText(CString markPath)
{
	vector<CvRect> vr;

	FILE *fp = fopen(markPath, "r");
	assert(fp != NULL);

	char tmp[256];
	fscanf(fp, "%s", tmp);

	int n;
	fscanf(fp, "%d", &n);
	vr.resize(n);
	for (int i = 0; i < n; i++)
	{
		fscanf(fp, "%s", tmp);

		CvRect r;
		fscanf(fp, "%d%d%d%d", &r.x, &r.y, &r.width, &r.height);
		vr[i] = r;
	}

	fclose(fp);

	return vr;
}

void CMyThread::GetCurTime(char *strTime)
{
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	sprintf(
		strTime, 
		"%04d-%02d-%02d %02d:%02d:%02d", 
		sys.wYear, 
		sys.wMonth, 
		sys.wDay, 
		sys.wHour, 
		sys.wMinute, 
		sys.wSecond
	);
}

void CMyThread::copyImage(IplImage *imgSrc, IplImage *patch, CvRect rect)
{
	cvSetImageROI(imgSrc, rect);
	cvResize(patch, imgSrc);
	cvResetImageROI(imgSrc);
}

DWORD CMyThread::ThreadMemberFunc()
{
	//CvCapture *capture = cvCaptureFromAVI(m_filePath);
	//assert(capture != NULL);

	cvNamedWindow("Video", CV_WINDOW_AUTOSIZE);
	int nframe = 0;
	char str[10];
	int fps = 24;
	long tag = 0;
	long pretag = 0;
	CCarDetect *carDetect;
	carDetect = new CCarDetect;
	IplImage *videoImage = cvCreateImage(cvSize(m_vBuffer->m_imageWidth, m_vBuffer->m_imageHeight), 8, 3);
	CvvImage ShowImage;
	IplImage *RoateImage = NULL;
	char time[128];

	HWND hwnd_1 = GetDlgItem(AfxGetApp()->GetMainWnd()->GetSafeHwnd(), IDC_ALLCAR);
	HWND hwnd_2 = GetDlgItem(AfxGetApp()->GetMainWnd()->GetSafeHwnd(), IDC_CARTRUE);
	HWND hwnd_3 = GetDlgItem(AfxGetApp()->GetMainWnd()->GetSafeHwnd(), IDC_FALSECAR);
	

	vector<CvRect> vbox = ReadText(m_markPath);
	vector<CvRect> obox = ReadText(m_showPicmark);
	sprintf(str, "%d", vbox.size());
	SetWindowText(hwnd_1, str);
	BOOL retval = m_vBuffer->GetImageCurrentHD(videoImage,tag);
	
	while(retval)
	{
		cvFlip(videoImage, videoImage);
		IplImage *showImage = cvCreateImage(cvGetSize(m_showImageSrc),m_showImageSrc->depth,m_showImageSrc->nChannels);
		cvCopy(m_showImageSrc, showImage);

		/*
		if (nframe % fps == 0)
		{
			RoateImage = carDetect.Detection(videoImage, m_testmodel, vbox);
		}
		*/
		RoateImage = carDetect->Detection(videoImage, m_testmodel, vbox);
		GetCurTime(time);
		CarStatus m_carstatus;

		strcpy(m_carstatus.readtime, time);

		int truecar = 0;
		for (int i = 0; i < (int)vbox.size(); i++)
		{
			m_carstatus.num.push_back(i);
			m_carstatus.status.push_back(carDetect->result[i]);

			if (vbox[i].width > vbox[i].height)
			{
				if (carDetect->result[i] > 0.5)
				{
					copyImage(showImage, m_carImage_1, obox[i]);
					truecar++;
				}
			}
			else
				if(carDetect->result[i] > 0.5)
				{
					copyImage(showImage, m_carImage_2, obox[i]);
					truecar++;
				}
		}

		m_carqueue->Push(m_carstatus);

		nframe++;
		//printf("***%d***\n", nframe);
		//printf("readtag:%d\n",tag);
		ShowImage.CopyOf(showImage);
		ShowImage.DrawToHDC(m_Pic_hdc, m_Pic_rect);

		sprintf(str,"%d", truecar);
		SetWindowText(hwnd_2, str);
		sprintf(str, "%d", (100 - truecar));
		SetWindowText(hwnd_3, str);

		cvShowImage("Video", RoateImage);
		cvWaitKey(1);
		cvReleaseImage(&showImage);
		cvReleaseImage(&RoateImage);
		retval = m_vBuffer->GetImageCurrentHD(videoImage,tag);
		if(pretag == tag)
			break;
		pretag = tag;
		Sleep(1000);
		
	}

	cvReleaseImage(&videoImage);
	//cvReleaseCapture(&capture);
	cvDestroyAllWindows();

	return 0;
}