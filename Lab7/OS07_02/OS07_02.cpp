#include <iostream>
#include <Windows.h>

using namespace std;

DWORD pid = NULL;

DWORD WINAPI ChildThread();

CRITICAL_SECTION sc;

int main()
{
	pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();
	DWORD ChildId1 = NULL;
	DWORD ChildId2 = NULL;
	HANDLE hChild1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread, NULL, 0, &ChildId1);
	HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread, NULL, 0, &ChildId2);

	InitializeCriticalSection(&sc);
	for (int i = 0; i < 90; i++)
	{
		if (i == 30)
			EnterCriticalSection(&sc);
		printf("PID = %d, (Main) tid = %d: %d\n", pid, tid, i);
		Sleep(100);
		if (i == 60) {
			LeaveCriticalSection(&sc);
			EnterCriticalSection(&sc);
			LeaveCriticalSection(&sc);
		}
	}
	DeleteCriticalSection(&sc);

	WaitForSingleObject(hChild1, INFINITE);
	WaitForSingleObject(hChild2, INFINITE);
	CloseHandle(hChild1);
	CloseHandle(hChild2);
	system("pause");
}

DWORD WINAPI ChildThread()
{
	DWORD tid = GetCurrentThreadId();
	EnterCriticalSection(&sc);
	for (int i = 0; i < 90; i++)
	{
		if (i == 30)
			EnterCriticalSection(&sc);
		printf("PID = %d, (Child Thread) tid = %d: %d\n", pid, tid, i);
		Sleep(100);
		if (i == 60) {
			LeaveCriticalSection(&sc);
			EnterCriticalSection(&sc);
			LeaveCriticalSection(&sc);
		}
	}
	return 0;
}