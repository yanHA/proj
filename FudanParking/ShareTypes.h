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
	vector<int> num;            //��λ���
	vector<int> status;        //��λ״̬
	char readtime[128];        //�޸�ʱ��
};

// ���������Ƶ֡��ʽ
struct VideoImage
{
	IplImage*	frameImg;		// ͼ��
	long	frameTag;			// ֡��
	//int		Mutex;			// ������,1��ʾ����,0��ʾ����
};

// ��Ƶ֡�������
class CVideoBuffer
{
public:
	CVideoBuffer();
	~CVideoBuffer();

public:
	VideoImage*	m_videoBuffer;		   // ��Ƶ�������
	int m_tail;						   // ��ǰλ��,ָ�򼴽�����ͼ�����һ��λ��
	int m_cur;						  // ��ǰλ��,ָ��ո�д��ͼ���λ��

	HANDLE hSemaphore;					// �������ݿ����ź���	
	HANDLE hReadMutex[64];				// ����
	HANDLE hWriteMutex;					// д��

public:
	int m_length;					// ������г���
	int m_imageWidth;				// ����ͼ��Ŀ�
	int m_imageHeight;				// ����ͼ��ĸ�

public:
	BOOL CreateBuffer(int length,string configFile,string itemName);	// �����������
	BOOL AddImage(IplImage*	frameImg,long frameTag);				   // �ڶ�β���ͼ�� 
	BOOL GetImageCurrent(IplImage* dstImg,long &frameTag);			   // �õ��ոշ�����е�ͼ���֡��
	BOOL GetImageCurrentLow(IplImage* lowImg,long &frameTag,int &pos);	// �õ��ոշ�����е�ͼ���֡��,����ΪСͼ��ѭ���ȴ�����
	BOOL GetImageCurrentLD(IplImage* smallImg,long &frameTag);		// �õ��ոշ�����е�ͼ���֡��,����ΪСͼ���޵ȴ�
	BOOL GetImageCurrentHD(IplImage* dstImg,long &frameTag);		// �õ��ոշ�����е�ͼ���֡��,��ͼ���޵ȴ�
	BOOL GetImageCurrentLocal(IplImage* localImg,long &frameTag,CvRect roi);		// �õ��ոշ�����е�ͼ���֡��,���оֲ�ͼ��
	BOOL GetImageRecentHD(IplImage* dstImg,long &frameTag,int recentCount);		// �õ�ǰ��֡ͼ���֡��,��ͼ���޵ȴ�
	int GetIndexByFrameNum(long frameTag);							// ����֡�ŵõ���֡����Ӧͼ���ڶ����е�λ��
	BOOL GetImageByIndex(int index,IplImage* dstImg);				// ���ݶ���λ�õõ���Ӧͼ��
	int GetIndexCurrent();											// ��õ�ǰ����λ�ã���һ��λ�ã�	


private:
	void SubImageMemCpy(IplImage* dstImg,IplImage* srcImg);			// ���ڴ濽����ʽ��ȡ������ͼ��
};



// ��Ϣ���з���
template <class Type> class QUEUE{
public:
	Type data[QUEUN_MAX_LENGTH];

	int front;							// ��λ��
	int back;							// дλ��

	HANDLE hSemaphore;					// �������ݿ����ź���	
	HANDLE hReadMutex;					// ����
	HANDLE hWriteMutex;					// д��

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

		// hack �����������
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
