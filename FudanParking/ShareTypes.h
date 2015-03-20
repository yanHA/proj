#ifndef ShareTypes_H
#define ShareTypes_H

#include "cxcore.h"
#include "highgui.h"
#include "cv.h"

#include <Windows.h>

#include <stdio.h>
#include <string>
#include <stdlib.h>

// #include "utils\LogWriter.h"

//#define OPENCV2

#define QUEUN_MAX_LENGTH	128

#define CONFIG_FILE_NAME	".\\etc\\conf.ini"
#define CAMERA_FILE_NAME	"etc\\CameraInfo.ini"
#define VLOOP_FILE_NAME0	"etc\\PortConfig0.ini"
#define VLOOP_FILE_NAME1	"etc\\PortConfig1.ini"

#define ANALYSE_LOG_NAME	"log_analyse.txt"
#define LPR_LOG_NAME		"log_lpr0.txt"
#define LPR_LOG_NAME1		"log_lpr1.txt"
#define BUSINESS_LOG_NAME	"log_business.txt"
#define MAIN_LOG_NAME		"log_main.txt"

using namespace std;


struct CarStatus
{     
	vector<int> num;            //车位编号
	vector<int> status;        //车位状态
	char readtime[128];        //修改时间
};

// 缓冲队列视频帧格式
struct VideoImage
{
	IplImage*	frameImg;		// 图像
	long	frameTag;			// 帧号
	//int		Mutex;			// 互斥锁,1表示已锁,0表示无锁
};

// 视频帧缓冲队列
class CVideoBuffer
{
public:
	CVideoBuffer();
	~CVideoBuffer();

public:
	VideoImage*	m_videoBuffer;		   // 视频缓冲队列
	int m_tail;						   // 当前位置,指向即将放入图像的下一个位置
	int m_cur;						  // 当前位置,指向刚刚写入图像的位置

	HANDLE hSemaphore;					// 队列数据可用信号量	
	HANDLE hReadMutex[64];				// 读锁
	HANDLE hWriteMutex;					// 写锁

public:
	int m_length;					// 缓冲队列长度
	int m_imageWidth;				// 保存图像的宽
	int m_imageHeight;				// 保存图像的高

public:
	BOOL CreateBuffer(int length,string configFile,string itemName);	// 创建缓冲队列
	BOOL AddImage(IplImage*	frameImg,long frameTag);				   // 在队尾添加图像 
	BOOL GetImageCurrent(IplImage* dstImg,long &frameTag);			   // 得到刚刚放入队列的图像和帧号
	BOOL GetImageCurrentLow(IplImage* lowImg,long &frameTag,int &pos);	// 得到刚刚放入队列的图像和帧号,缩放为小图像，循环等待读入
	BOOL GetImageCurrentLD(IplImage* smallImg,long &frameTag);		// 得到刚刚放入队列的图像和帧号,缩放为小图像，无等待
	BOOL GetImageCurrentHD(IplImage* dstImg,long &frameTag);		// 得到刚刚放入队列的图像和帧号,大图像，无等待
	BOOL GetImageCurrentLocal(IplImage* localImg,long &frameTag,CvRect roi);		// 得到刚刚放入队列的图像和帧号,剪切局部图像
	BOOL GetImageRecentHD(IplImage* dstImg,long &frameTag,int recentCount);		// 得到前几帧图像和帧号,大图像，无等待
	int GetIndexByFrameNum(long frameTag);							// 根据帧号得到该帧所对应图像在队列中的位置
	BOOL GetImageByIndex(int index,IplImage* dstImg);				// 根据队列位置得到对应图像
	int GetIndexCurrent();											// 获得当前队列位置（上一个位置）	


private:
	void SubImageMemCpy(IplImage* dstImg,IplImage* srcImg);			// 用内存拷贝方式截取子区域图像
};



// 消息队列泛型
template <class Type> class QUEUE{
public:
	Type data[QUEUN_MAX_LENGTH];

	int front;							// 读位置
	int back;							// 写位置

	HANDLE hSemaphore;					// 队列数据可用信号量	
	HANDLE hReadMutex;					// 读锁
	HANDLE hWriteMutex;					// 写锁

	QUEUE()
	{
		hReadMutex = NULL;
		hWriteMutex = NULL;
		hSemaphore = NULL;
	}
	~QUEUE()
	{
		if(hReadMutex != NULL)
			CloseHandle(hReadMutex);
		if(hWriteMutex != NULL)
			CloseHandle(hWriteMutex);
		if(hSemaphore != NULL)
			CloseHandle(hSemaphore);
	}

	void Initialize()
	{
		hSemaphore = CreateSemaphore(NULL, 0, QUEUN_MAX_LENGTH, NULL);
		hReadMutex = CreateMutex(NULL, FALSE, NULL);
		hWriteMutex = CreateMutex(NULL, FALSE, NULL);

		front = 0;
		back = 0;
	}

	bool Push(const Type &newData)
	{
		WaitForSingleObject(hWriteMutex, INFINITE);

		// hack 队列满则不添加
		if((back+1)%QUEUN_MAX_LENGTH == front)
		{
			ReleaseMutex(hWriteMutex);
			return false;
		}
		// end of hack

		data[back++] = newData;
		back %= QUEUN_MAX_LENGTH;

		ReleaseMutex(hWriteMutex);

		if(back == front)
		{
			WaitForSingleObject(hReadMutex, INFINITE);

			front ++;
			front %= QUEUN_MAX_LENGTH;

			ReleaseMutex(hReadMutex);
		}

		// printf("######push %d          front = %d back = %d\n", newData.info, front, back);

		ReleaseSemaphore(hSemaphore, 1, NULL);
		return true;
	}

	bool Pop(Type &retData)
	{
		DWORD retval = WaitForSingleObject(hSemaphore, 50);
		if(retval == WAIT_TIMEOUT )
			return 0;

		WaitForSingleObject(hReadMutex, INFINITE);

		retData = data[front++];
		front %= QUEUN_MAX_LENGTH;

		// printf("@@@@@@pop %d           front = %d back = %d\n", retData.info, front, back);

		ReleaseMutex(hReadMutex);

		return 1;
	}
};

#endif
