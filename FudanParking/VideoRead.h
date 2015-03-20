#ifndef VideoRead_H
#define VideoRead_H

#include <string>
#include <stdlib.h>

#include "VideoAcq.h"
#include "VideoAcqAxis.h"
#include "VideoAcqRJ.h"

using namespace std;


class CVideoRead
{
public:
	CVideoRead();
	~CVideoRead();

	void VideoInitialize();
	CVideoBuffer *vBuffer;                                         //�����������

private:

	AcqParam param;                                                //�����ɼ�ģ�����
	CVideoAcq *pAcqThread;                                         //�����ɼ��߳�
	char m_filePath[256];
	char m_tmpStr1[256];
	char m_tmpStr2[256];
	char m_tmpStr3[256];
	char *m_itemName;
};


#endif