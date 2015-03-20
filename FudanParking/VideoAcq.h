#ifndef VideoAcq_H
#define VideoAcq_H

#define MAX_FRAME_TAG			10000			// 帧标签的最大值

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

// 缓冲队列视频帧格式
/*struct VideoImageA
{
    IplImage*	frameImg;		// 图像
    long	frameTag;			// 帧号
};

// 视频帧缓冲队列
class CVideoBuffer
{
public:
    CVideoBuffer(int length);
    ~CVideoBuffer();

public:
    VideoImageA*	m_videoBuffer;		// 视频缓冲队列
    int m_length;                           // 队列长度
};*/


// 视频采集模块参数
struct AcqParam
{
    string ipv4;                // ip地址
    string fileName;            // 文件名
    double frameRate;           // 帧率
    int MaxExposureTime;        // 最大曝光值
    int channel;                // 通道号，单通道摄像机为0；多通道硬盘录像机为>0
	int port;					// 端口号，一般为8000
	string user;                // 用户名
	string pass;                // 密码
};

// 视频采集模块基类，从某个数据源(例如摄像头、本地文件)中获取连续的视频帧，并插入到视频缓冲中
class CVideoAcquisition//:public QWidget
{
    //Q_OBJECT
public:
    CVideoAcquisition();
    ~CVideoAcquisition();

    virtual BOOL Initialize(CVideoBuffer *buffer,AcqParam param) = 0;	// 初始化操作
    virtual BOOL StartAcq() = 0;                                        // 开始获取，一般会开启一个线程进行视频获取
    virtual BOOL StopAcq() = 0;                                         // 结束获取
    virtual void AddFrame() = 0;                                        // 向buffer中加入新的一帧
    //virtual BOOL SetInputFrameRate(double inFrameRate) = 0;			// 设定输入帧率

//signals:
//    void receiveNewImage();

protected:
    int m_nframe;														// 帧号
    CVideoBuffer *m_buffer;												// 缓冲图像队列
}
typedef CVideoAcq;

// 视频采集模块子类，从本地avi视频文件中获取连续的视频帧
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
    static DWORD WINAPI AcqThreadFunc(LPVOID lpParam);					// 线程工作函数

public:
    HANDLE m_Thread;			// 线程句柄
    DWORD  m_threadID;			// 线程ID
    HANDLE m_hRequestExitEvent;		// 结束事件

    string m_strAviVideoPath;		// 视频文件路径
    double m_frameRate;			// 预设定帧率

    CvCapture* m_pCapture;		// 视频采集指针
    IplImage* m_qImage;			// 当前图像(视频中获取的)
    bool m_bThreadTerminal;             // 线程是否终止
};


#endif
