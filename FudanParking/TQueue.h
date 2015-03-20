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
 * 多线程写，单线程读的循环队列.
 * 多线程互斥写，单线程阻塞读，但读与写不是互斥的.
 * 队列如果满了，则会覆盖最旧的数据.
 */
template <class Type> class TQueue
{
public:
    /**
	 * 构造函数
	 * @param[in] _len 队列长度，尽可能设置长一些
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
	 * 析构函数
	 */
	~TQueue()
	{
		free(data);

		delete pSemaphore;
		delete pMutex;
	}

    /**
     * 向队列中添加数据，如果队列已满，则会覆盖最旧的数据
     * @param[in] d 数据
     */
	void Push(const Type &d)
	{
		WaitForSingleObject(pMutex->m_hObject, INFINITE);

		data[rear++] = d;
		rear %= len;

		// 队列满
		if(rear == front)
		{
			front ++;
			front %= len;
		}

		ReleaseMutex(pMutex->m_hObject);

		ReleaseSemaphore(pSemaphore->m_hObject, 1, NULL);
	}

    /**
     * 弹出数据，一次弹一个
     * @param[out] retData 数据
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
