/*
 * Copyright (C) 2012, Freative, Corporation.
 * All Rights Reserved.
 * Version: V1.0
 * Owner: mqfcu7
 * Data: 2012-12-03
 */

#ifndef ThreadBase_H
#define ThreadBase_H

#include <afxmt.h>
#include <windows.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>

using namespace std;

/**
 * �̻߳���.
 * ���ฺ�𴴽������̡߳������̡߳������߳����ȼ�
 */
class CThreadBase
{
public:
    /**
     * ���캯��
     */
    CThreadBase();

    /**
     * ��������
     */
    virtual ~CThreadBase();

    /**
     * �����߳�
     * @return �߳��Ƿ�ɹ������������߳�
     */
    virtual BOOL StartThread();

    /**
     * �����߳�
     * @return �߳��Ƿ�ɹ���ֹ
     */
    virtual BOOL StopThread();

    /**
     * �����߳�
     */
    virtual DWORD Suspend();

    /**
     * �����߳�
     */
	virtual DWORD Resume();

    /**
     * �����߳����ȼ�
     * @return �����ɹ�ֵ
     */
    BOOL SetPriority(int priority);	

protected:
	virtual DWORD ThreadMemberFunc() = 0;				/**< �������̺߳�����ע������һ�����麯�� */

private:
	static DWORD WINAPI ThreadFunc(LPVOID param);		/**< ��̬�߳���ʼ����*/

public:
	HANDLE m_hThread;									/**< �߳̾�� */
	bool m_bThreadRuning;								/**< �߳��Ƿ����� */
	bool m_bThreadTerminal;								/**< �߳��Ƿ���ֹ */
	DWORD m_dwThreadID;									/**< �߳�ID */
};
#endif
