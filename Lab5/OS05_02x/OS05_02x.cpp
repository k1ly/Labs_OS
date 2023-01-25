#include <iostream>
#include <Windows.h>
#include <bitset>

using namespace std;

char* GetProcessPriority(HANDLE);
char* GetProcThreadPriority(HANDLE);

int main()
{
	HANDLE hp = GetCurrentProcess();
	HANDLE ht = GetCurrentThread();

	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();
	char* pprior = GetProcessPriority(hp);
	char* tprior = GetProcThreadPriority(ht);
	DWORD pa = NULL, sa = NULL;
	DWORD cpu = SetThreadIdealProcessor(ht, MAXIMUM_PROCESSORS);
	for (int i = 0; i < 1000000; i++)
	{
		if (i % 1000 == 0) {
			Sleep(200);
			cout << "i = " << i << endl;
			cout << "Proccess id: " << pid << endl;
			cout << "Main thread id: " << tid << endl;
			cout << "Process priority class: " << pprior << endl;
			cout << "Main thread priority class: " << tprior << endl;
			if (GetProcessAffinityMask(hp, (PDWORD_PTR)&pa, (PDWORD_PTR)&sa))
				cout << "Process affinity mask: " << bitset<8>(pa) << endl;
			cout << "Thread processor: " << cpu << endl;
		}
	}
	system("pause");
}

char* GetProcessPriority(HANDLE h)
{
	char* priority = NULL;
	DWORD pprior = GetPriorityClass(h);
	switch (pprior)
	{
	case IDLE_PRIORITY_CLASS: priority = (char*)"IDLE_PRIORITY_CLASS"; break;
	case BELOW_NORMAL_PRIORITY_CLASS: priority = (char*)"BELOW_NORMAL_PRIORITY_CLASS"; break;
	case NORMAL_PRIORITY_CLASS: priority = (char*)"NORMAL_PRIORITY_CLASS"; break;
	case ABOVE_NORMAL_PRIORITY_CLASS: priority = (char*)"ABOVE_NORMAL_PRIORITY_CLASS"; break;
	case HIGH_PRIORITY_CLASS: priority = (char*)"HIGH_PRIORITY_CLASS"; break;
	case REALTIME_PRIORITY_CLASS: priority = (char*)"REALTIME_PRIORITY_CLASS"; break;
	}
	return priority;
}

char* GetProcThreadPriority(HANDLE h)
{
	char* priority = NULL;
	DWORD tprior = GetThreadPriority(h);
	switch (tprior)
	{
	case THREAD_PRIORITY_IDLE: priority = (char*)"THREAD_PRIORITY_IDLE"; break;
	case THREAD_PRIORITY_LOWEST: priority = (char*)"THREAD_PRIORITY_LOWEST"; break;
	case THREAD_PRIORITY_BELOW_NORMAL: priority = (char*)"THREAD_PRIORITY_BELOW_NORMAL"; break;
	case THREAD_PRIORITY_NORMAL: priority = (char*)"THREAD_PRIORITY_NORMAL"; break;
	case THREAD_PRIORITY_ABOVE_NORMAL: priority = (char*)"THREAD_PRIORITY_ABOVE_NORMAL"; break;
	case THREAD_PRIORITY_HIGHEST: priority = (char*)"THREAD_PRIORITY_HIGHEST"; break;
	case THREAD_PRIORITY_TIME_CRITICAL: priority = (char*)"THREAD_PRIORITY_TIME_CRITICAL"; break;
	}
	return priority;
}