#ifndef AbnormalProcess_H
#define AbnormalProcess_H

#include "LogsProcess.h"
#include <windows.h>
#include <Psapi.h>
#include <process.h>
#include <conio.h> 
#include <tlhelp32.h>

using namespace std;

#define PhUpdateDelta(DltMgr, NewValue) \
    ((DltMgr)->Delta = (NewValue) - (DltMgr)->Value, \
    (DltMgr)->Value = (NewValue), (DltMgr)->Delta)

typedef struct _PH_UINT64_DELTA
{
    ULONG64 Value;
    ULONG64 Delta;

	_PH_UINT64_DELTA()
	{
		Value = 0;
		Delta = 0;
	}
} PH_UINT64_DELTA, *PPH_UINT64_DELTA;

typedef struct _SYSTEM_BASIC_INFORMATION
{
    ULONG Reserved;
    ULONG TimerResolution;
    ULONG PageSize;
    ULONG NumberOfPhysicalPages;
    ULONG LowestPhysicalPageNumber;
    ULONG HighestPhysicalPageNumber;
    ULONG AllocationGranularity;
    ULONG_PTR MinimumUserModeAddress;
    ULONG_PTR MaximumUserModeAddress;
    ULONG_PTR ActiveProcessorsAffinityMask;
    CCHAR NumberOfProcessors;
} SYSTEM_BASIC_INFORMATION, *PSYSTEM_BASIC_INFORMATION;

typedef struct _SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION
{
    LARGE_INTEGER IdleTime;
    LARGE_INTEGER KernelTime;
    LARGE_INTEGER UserTime;
    LARGE_INTEGER DpcTime;
    LARGE_INTEGER InterruptTime;
    ULONG InterruptCount;
} SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION, *PSYSTEM_PROCESSOR_PERFORMANCE_INFORMATION;

typedef LONG (WINAPI *PROCNTQSI)(UINT,PVOID,ULONG,PULONG);

class CAbnormalProcess
{
public:

    int GetMemoryUsage();
    int GetCPUUsage();

private:
    MsgQueue<LogMsg> *m_logQueue;

    PROCNTQSI NtQuerySystemInformation;

	SYSTEM_BASIC_INFORMATION PhSystemBasicInformation;
	PSYSTEM_PROCESSOR_PERFORMANCE_INFORMATION PhCpuInformation;
	PH_UINT64_DELTA PhCpuKernelDelta;
	PH_UINT64_DELTA PhCpuUserDelta;
	PH_UINT64_DELTA PhCpuIdleDelta;
};

#endif
