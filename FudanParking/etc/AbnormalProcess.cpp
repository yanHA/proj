#include "stdafx.h"
#include "AbnormalProcess.h"

CAbnormalProcess::CAbnormalProcess(MsgQueue<LogMsg> *logQueue)
{
	m_logQueue = logQueue;

    NtQuerySystemInformation = (PROCNTQSI)GetProcAddress(GetModuleHandleA("ntdll"), "NtQuerySystemInformation");
	NtQuerySystemInformation(0,
							 &PhSystemBasicInformation,
							 sizeof(SYSTEM_BASIC_INFORMATION),
							 NULL
							 );
	int sz = sizeof(SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION) * PhSystemBasicInformation.NumberOfProcessors;
	PhCpuInformation = (PSYSTEM_PROCESSOR_PERFORMANCE_INFORMATION)malloc(sz);
	memset(PhCpuInformation, 0, sz);
}

CAbnormalProcess::~CAbnormalProcess()
{
    free(PhCpuInformation);
}

bool CAbnormalProcess::Process(int acquireFPS, int runFPS)
{
    int cpu = GetCPUUsage();
    int mem = GetMemoryUsage();

    LogMsg logMsg;
    logMsg.type = SYSTEM;
    logMsg.key  = LOG_STATUS;
    sprintf(logMsg.msg, "acqFPS:%d  runFPS:%d  cpu:%.2f%%  mem:%dM", 
            acquireFPS, 
            runFPS, 
            cpu / 100.0, 
            mem);
    m_logQueue->Push(logMsg);

	if(acquireFPS == 0) return false;

    return true;
}

int CAbnormalProcess::GetMemoryUsage()
{
    int iPid = _getpid();
	PROCESS_MEMORY_COUNTERS pmc;
	pmc.cb = sizeof(PROCESS_MEMORY_COUNTERS);

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, DWORD(iPid));

	GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc));

	return pmc.WorkingSetSize / 1024 / 1024;    
}

int CAbnormalProcess::GetCPUUsage()
{
	SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION PhCpuTotals;

	// Zero the CPU totals.
	memset(&PhCpuTotals, 0, sizeof(SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION));

	NtQuerySystemInformation(8,
		                     PhCpuInformation,
							 sizeof(SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION) * 
							 PhSystemBasicInformation.NumberOfProcessors,
							 NULL); 

	for (int i = 0; i < PhSystemBasicInformation.NumberOfProcessors; i++)
	{
		PSYSTEM_PROCESSOR_PERFORMANCE_INFORMATION cpuInfo = &PhCpuInformation[i];

		// KernelTime includes idle time.
		cpuInfo->KernelTime.QuadPart -= cpuInfo->IdleTime.QuadPart;
		cpuInfo->KernelTime.QuadPart += cpuInfo->DpcTime.QuadPart + cpuInfo->InterruptTime.QuadPart;

		PhCpuTotals.DpcTime.QuadPart += cpuInfo->DpcTime.QuadPart;
		PhCpuTotals.IdleTime.QuadPart += cpuInfo->IdleTime.QuadPart;
		PhCpuTotals.InterruptCount += cpuInfo->InterruptCount;
		PhCpuTotals.InterruptTime.QuadPart += cpuInfo->InterruptTime.QuadPart;
		PhCpuTotals.KernelTime.QuadPart += cpuInfo->KernelTime.QuadPart;
		PhCpuTotals.UserTime.QuadPart += cpuInfo->UserTime.QuadPart;
	}

	PhUpdateDelta(&PhCpuKernelDelta, PhCpuTotals.KernelTime.QuadPart);
	PhUpdateDelta(&PhCpuUserDelta, PhCpuTotals.UserTime.QuadPart);
	PhUpdateDelta(&PhCpuIdleDelta, PhCpuTotals.IdleTime.QuadPart);

	ULONG64 total = PhCpuKernelDelta.Delta + PhCpuUserDelta.Delta + PhCpuIdleDelta.Delta;

	FLOAT uUsage = (FLOAT)PhCpuUserDelta.Delta / total * 10000;

    return (int)uUsage;    
}
