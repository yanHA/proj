#ifndef MyThread_H
#define MyThread_H


#include "stdafx.h"
#include "ThreadBase.h"
#include "CarDetect.h"
#include "CvvImage.h"
#include "VideoRead.h"
#include "DataBaseProc.h"
#include "TQueue.h"


/************************************************************************/
/* 继承实现CThreadBase类，实现用于车辆检测的工作线程                    */
/************************************************************************/


class CMyThread : public CThreadBase
{
public:
	CMyThread();
	~CMyThread();


	BOOL Initialize(HDC Pic_hdc, CRect Pic_rect, CVideoBuffer *vBuffer, TQueue<struct CarStatus> *carstate);
	vector<CvRect> ReadText(CString markPath);
	void copyImage(IplImage *imgSrc, IplImage *patch, CvRect rect);
	void GetCurTime(char *strTime);
	

private:
	DWORD ThreadMemberFunc();

	HDC           m_Pic_hdc;
	CRect         m_Pic_rect;
	CString       m_markPath;
	CString       m_showPicmark;
	IplImage     *m_showImageSrc;
	IplImage     *m_carImage_1;
	IplImage     *m_carImage_2;
	CVideoBuffer *m_vBuffer;
	TQueue<struct CarStatus>  *m_carqueue;
	struct svm_model *m_testmodel;
};

#endif