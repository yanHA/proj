#include "stdafx.h"
#include "ThreadBase.h"

CThreadBase::CThreadBase()
{
	m_bThreadRuning		= false;
	m_bThreadTerminal	= false;
	m_hThread			= NULL;
	m_dwThreadID		= -1;
}

CThreadBase::~CThreadBase()
{
	StopThread();
}

BOOL CThreadBase::StartThread()
{
    printf("StartThread()\n");
	if(!m_bThreadRuning)
	{
		m_hThread = CreateThread(NULL,0,ThreadFunc,(LPVOID)this,0,&m_dwThreadID);
		m_bThreadRuning   = true;
        m_bThreadTerminal = false;
	}
	if(m_hThread)
		return 1;
	else
		return 0;
}

BOOL CThreadBase::StopThread()
{
	int n = 20;		// 0.4s
	while(m_bThreadRuning) 
	{
		Sleep(20);
		if(-- n < 0) break;
	}
	if(n < 0) 
	{
		TerminateThread(m_hThread,0);
	}

	if(m_hThread != NULL) CloseHandle(m_hThread);
	m_bThreadRuning		= false;
    m_bThreadTerminal	= true;
	m_hThread			= NULL;
	return 1;
}

DWORD CThreadBase::Suspend()
{
	return SuspendThread(m_hThread);
}

DWORD CThreadBase::Resume()
{
	return ResumeThread(m_hThread);
}

BOOL CThreadBase::SetPriority(int priority)
{
	return SetThreadPriority(m_hThread,priority);
}

DWORD WINAPI CThreadBase::ThreadFunc(void * param)
{
	CThreadBase *pThread = (CThreadBase *)param;
	for(;(pThread != NULL) && (!pThread->m_bThreadTerminal);)
	{
		int resval;
		if(pThread != NULL)
		{
			resval = pThread ->ThreadMemberFunc();
			if(resval == 0)
				break;
			Sleep(1);
		}
	}

	pThread->m_bThreadRuning	= false;
	pThread->m_bThreadTerminal	= true;

	return 1;
}

