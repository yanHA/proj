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
 * 线程基类.
 * 该类负责创建开启线程、结束线程、设置线程优先级
 */
class CThreadBase
{
public:
    /**
     * 构造函数
     */
    CThreadBase();

    /**
     * 析构函数
     */
    virtual ~CThreadBase();

    /**
     * 创建线程
     * @return 线程是否成功创建并开启线程
     */
    virtual BOOL StartThread();

    /**
     * 结束线程
     * @return 线程是否成功终止
     */
    virtual BOOL StopThread();

    /**
     * 挂起线程
     */
    virtual DWORD Suspend();

    /**
     * 继续线程
     */
	virtual DWORD Resume();

    /**
     * 设置线程优先级
     * @return 操作成功值
     */
    BOOL SetPriority(int priority);	

protected:
	virtual DWORD ThreadMemberFunc() = 0;				/**< 工作者线程函数，注意这是一个纯虚函数 */

private:
	static DWORD WINAPI ThreadFunc(LPVOID param);		/**< 静态线程起始函数*/

public:
	HANDLE m_hThread;									/**< 线程句柄 */
	bool m_bThreadRuning;								/**< 线程是否运行 */
	bool m_bThreadTerminal;								/**< 线程是否终止 */
	DWORD m_dwThreadID;									/**< 线程ID */
};
#endif
