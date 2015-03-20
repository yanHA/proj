#ifndef VideoAcq_H
#define VideoAcq_H

#define MAX_FRAME_TAG			10000			// ֡��ǩ�����ֵ

//#include <QtGui>
//#include <QtCore>

#include "cxcore.h"
#include "highgui.h"
#include "cv.h"

#include "io.h"

#include <stdio.h>
#include <string>
#include <stdlib.h>

#include "assert.h"

#include "ShareTypes.h"

using namespace std;

// ���������Ƶ֡��ʽ
/*struct VideoImageA
{
    IplImage*	frameImg;		// ͼ��
    long	frameTag;			// ֡��
};

// ��Ƶ֡�������
class CVideoBuffer
{
public:
    CVideoBuffer(int length);
    ~CVideoBuffer();

public:
    VideoImageA*	m_videoBuffer;		// ��Ƶ�������
    int m_length;                           // ���г���
};*/


// ��Ƶ�ɼ�ģ�����
struct AcqParam
{
    string ipv4;                // ip��ַ
    string fileName;            // �ļ���
    double frameRate;           // ֡��
    int MaxExposureTime;        // ����ع�ֵ
    int channel;                // ͨ���ţ���ͨ�������Ϊ0����ͨ��Ӳ��¼���Ϊ>0
	int port;					// �˿ںţ�һ��Ϊ8000
	string user;                // �û���
	string pass;                // ����
};

// ��Ƶ�ɼ�ģ����࣬��ĳ������Դ(��������ͷ�������ļ�)�л�ȡ��������Ƶ֡�������뵽��Ƶ������
class CVideoAcquisition//:public QWidget
{
    //Q_OBJECT
public:
    CVideoAcquisition();
    ~CVideoAcquisition();

    virtual BOOL Initialize(CVideoBuffer *buffer,AcqParam param) = 0;	// ��ʼ������
    virtual BOOL StartAcq() = 0;                                        // ��ʼ��ȡ��һ��Ὺ��һ���߳̽�����Ƶ��ȡ
    virtual BOOL StopAcq() = 0;                                         // ������ȡ
    virtual void AddFrame() = 0;                                        // ��buffer�м����µ�һ֡
    //virtual BOOL SetInputFrameRate(double inFrameRate) = 0;			// �趨����֡��

//signals:
//    void receiveNewImage();

protected:
    int m_nframe;														// ֡��
    CVideoBuffer *m_buffer;												// ����ͼ�����
}
typedef CVideoAcq;

// ��Ƶ�ɼ�ģ�����࣬�ӱ���avi��Ƶ�ļ��л�ȡ��������Ƶ֡
class CVideoAcqAvi:public CVideoAcq
{
public:
    CVideoAcqAvi();
    ~CVideoAcqAvi();

    BOOL Initialize(CVideoBuffer *buffer,AcqParam param);
    BOOL StartAcq();
    BOOL StopAcq();
    void AddFrame();
    //BOOL SetInputFrameRate(double inFrameRate);


private:
    static DWORD WINAPI AcqThreadFunc(LPVOID lpParam);					// �̹߳�������

public:
    HANDLE m_Thread;			// �߳̾��
    DWORD  m_threadID;			// �߳�ID
    HANDLE m_hRequestExitEvent;		// �����¼�

    string m_strAviVideoPath;		// ��Ƶ�ļ�·��
    double m_frameRate;			// Ԥ�趨֡��

    CvCapture* m_pCapture;		// ��Ƶ�ɼ�ָ��
    IplImage* m_qImage;			// ��ǰͼ��(��Ƶ�л�ȡ��)
    bool m_bThreadTerminal;             // �߳��Ƿ���ֹ
};


#endif
