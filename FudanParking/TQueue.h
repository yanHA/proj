/* 
 * Copyright (C) 2012, Freative, Corporation.  
 * All Rights Reserved.
 * Version: V1.0
 * Owner: mqfcu7
 * Data: 2012-12-03
 */

#ifndef TQueue_H
#define TQueue_H

#include <afxmt.h>



/**
 * ���߳�д�����̶߳���ѭ������.
 * ���̻߳���д�����߳���������������д���ǻ����.
 * ����������ˣ���Ḳ����ɵ�����.
 */
template <class Type> class TQueue
{
public:
    /**
	 * ���캯��
	 * @param[in] _len ���г��ȣ����������ó�һЩ
	 */
	TQueue(int _len)
	{
		len		= _len;
		int sz	= (len + 1) * sizeof(Type);		// trick
		data	= (Type*)malloc(sz);
		memset(data, 0, sz);

		front	= 0;
		rear	= 0;

		pSemaphore	= new CSemaphore(0, len);
		pMutex	= new CMutex(FALSE);
	}

    /**
	 * ��������
	 */
	~TQueue()
	{
		free(data);

		delete pSemaphore;
		delete pMutex;
	}

    /**
     * �������������ݣ����������������Ḳ����ɵ�����
     * @param[in] d ����
     */
	void Push(const Type &d)
	{
		WaitForSingleObject(pMutex->m_hObject, INFINITE);

		data[rear++] = d;
		rear %= len;

		// ������
		if(rear == front)
		{
			front ++;
			front %= len;
		}

		ReleaseMutex(pMutex->m_hObject);

		ReleaseSemaphore(pSemaphore->m_hObject, 1, NULL);
	}

    /**
     * �������ݣ�һ�ε�һ��
     * @param[out] retData ����
     */
	void Pop(Type &retData)
	{
		WaitForSingleObject(pSemaphore->m_hObject, INFINITE);

		retData = data[front++];
		front %= len;
	}

private:
	Type *data;
	int len;

	int front;
	int rear;

	CSemaphore *pSemaphore;
	CMutex *pMutex;
};

#endif
