#include <iostream>
#include <Windows.h>
#include <bitset>

using namespace std;

char* GetProcessPriority(HANDLE);
char* GetProcessPriority(unsigned int);
char* GetProcThreadPriority(HANDLE);
char* GetProcThreadPriority(unsigned int);

void TA() {
	HANDLE hp = GetCurrentProcess();
	HANDLE ht = GetCurrentThread();

	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();
	char* pprior = GetProcessPriority(hp);
	char* tprior = GetProcThreadPriority(ht);
	DWORD cpu = SetThreadIdealProcessor(ht, MAXIMUM_PROCESSORS);
	for (int i = 0; i < 1000000; i++)
	{
		if (i % 1000 == 0) {
			Sleep(200);
			printf("i = %d\n", i);
			printf("Proccess id: %d\n", pid);
			printf("Thread id: %d\n", tid);
			printf("Process priority class: %s\n", pprior);
			printf("Thread priority class: %s\n", tprior);
			printf("Thread processor: %d\n", cpu);
		}
	}
}

int main(int argc, char* argv[])
{
	try {
		if (argc == 1)
			throw "P1 parameter is missing";
		if (argc == 2)
			throw "P2 parameter is missing";
		if (argc == 3)
			throw "P3 parameter is missing";
		if (argc == 4)
			throw "P4 parameter is missing";

		unsigned int mask = (unsigned int)atoi(argv[1]);
		unsigned int prior = (unsigned int)atoi(argv[2]);
		unsigned int prior1 = (unsigned int)atoi(argv[3]);
		unsigned int prior2 = (unsigned int)atoi(argv[4]);
		cout << "P1 = " << bitset<8>(mask) << " (" << mask << ")" << endl;
		cout << "P2 = " << GetProcessPriority(prior) << " (" << prior << ")" << endl;
		cout << "P3 = " << GetProcThreadPriority(prior1) << " (" << prior1 << ")" << endl;
		cout << "P4 = " << GetProcThreadPriority(prior2) << " (" << prior2 << ")" << endl;

		HANDLE h = GetCurrentProcess();
		SetProcessAffinityMask(h, mask);
		SetPriorityClass(h, prior);

		DWORD ChildId1 = NULL;
		HANDLE hChild1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TA, NULL, CREATE_SUSPENDED, &ChildId1);
		DWORD ChildId2 = NULL;
		HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TA, NULL, CREATE_SUSPENDED, &ChildId2);
		SetThreadPriority(hChild1, prior1);
		SetThreadPriority(hChild2, prior2);
		ResumeThread(hChild1);
		ResumeThread(hChild2);

		WaitForSingleObject(hChild1, INFINITE);
		CloseHandle(hChild1);
		WaitForSingleObject(hChild2, INFINITE);
		CloseHandle(hChild2);
	}
	catch (const char* error) {
		cout << error << endl;
	}
	system("pause");
}

char* GetProcessPriority(unsigned int p)
{
	char* priority = NULL;
	switch (p)
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

char* GetProcThreadPriority(unsigned int t)
{
	char* priority = NULL;
	switch (t)
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