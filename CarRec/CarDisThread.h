#ifndef   CarDisThread_H
#define   CarDisThread_H



#include "ThreadBase.h"
#include "CvvImage.h"
#include <FrParkingState.h>
#include <io.h>

/************************************************************************/
/* 继承CThreadBase类，主要实现车辆检测线程                              */
/************************************************************************/


class CCarDisThread : public CThreadBase
{
public:
	CCarDisThread();
	~CCarDisThread();

	bool InitalizeCar(CString pathSrc, HDC hdc, CRect rect, CProgressCtrl *ProgCtrl, CEdit *EditCtrl, CEdit *EditInput, CEdit *EditControlTime, CButton *open, CButton *proc, CStatic *text, CStatic *textfilecount, CStatic *textcorrect, CStatic *textalreadcount, CStatic *textcorrectcount);
	void Run(string dir); 
	void ProgressBatch(string Src);
	IplImage *imgSrc;


private:
	DWORD ThreadMemberFunc();
	void CountPicBatch(string src);  //统计图片数目，此函数用于预先统计
	void ProgressOne(string Src, string ImageName);

	void *param;
	int picCount;                    //统计图片数目
	int picCountCorrect;             //判别正确的图片数目
	int procCount;                   //实时运行的图片数目
	int m_nMin;
	int m_nMax;
	int nLength;
	int m_pertime;
	char *m_model;
	bool m_ret;
	bool m_correct;
	CvSize imgSize;
	CString m_pathSrc;
	//CString m_editshow;
	HDC hdc_pic;
	HDC hdc_edit;
	CRect m_rectImage;
	CvvImage DrawImage;
	CProgressCtrl *m_ProgCtrl;
	CEdit *m_editCtrl;
	CEdit *m_editInput;
	CEdit *m_editControlTime;
	CButton *m_open;
	CButton *m_proc;
	CStatic *m_text;
	CStatic *m_textfilecount;
	CStatic *m_textcorrect;
	CStatic *m_textalreadcount;
	CStatic *m_textcorrectcount;
	time_t begin;
	time_t end;
	int totalTime;
};

#endif