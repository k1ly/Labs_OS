﻿#include <iostream>
#include <Windows.h>

using namespace std;

void Cycle(int k, const char* name) {
	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();
	for (int i = 0; i < k; i++)
	{
		printf("%s: PID = %d, TID = %d\n", name, pid, tid);
		Sleep(1000);
	}
}

DWORD WINAPI ChildThread1() {
	Cycle(50, "OS04_03_T1");
	return 0;
}

DWORD WINAPI ChildThread2() {
	Cycle(125, "OS04_03_T2");
	return 0;
}

int main()
{
	DWORD ChildId1 = NULL;
	HANDLE hChild1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread1, NULL, 0, &ChildId1);
	DWORD ChildId2 = NULL;
	HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread2, NULL, 0, &ChildId2);

	DWORD pid = GetCurrentProcessId();
	for (int i = 0; i < 100; i++)
	{
		if (i == 20) {
			SuspendThread(hChild1);
			printf("\nOS04_03_T1 thread suspended\n\n");
		}
		if (i == 40) {
			SuspendThread(hChild2);
			printf("\nOS04_03_T2 thread suspended\n\n");
		}
		if (i == 60) {
			ResumeThread(hChild1);
			printf("\nOS04_03_T1 thread resumed\n\n");
		}
		printf("Main: PID = %d\n", pid);
		Sleep(1000);
	}
	ResumeThread(hChild2);
	printf("\nOS04_03_T2 thread resumed\n\n");

	WaitForSingleObject(hChild1, INFINITE);
	CloseHandle(hChild1);
	WaitForSingleObject(hChild2, INFINITE);
	CloseHandle(hChild2);
	system("pause");
}