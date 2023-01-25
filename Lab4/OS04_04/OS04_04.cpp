#include <iostream>
#include <Windows.h>

using namespace std;

void Cycle(int k, const char* name, int si, int st) {
	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();
	for (int i = 0; i < k; i++)
	{
		printf("%s: PID = %d, TID = %d\n", name, pid, tid);
		Sleep(1000);
		if (i == si) {
			printf("\n%s thread is sleeping\n\n", name);
			Sleep(st * 1000);
			printf("\n%s thread is waking up\n\n", name);
		}
	}
}

DWORD WINAPI ChildThread1() {
	Cycle(50, "OS04_04_T1", 25, 10);
	return 0;
}

DWORD WINAPI ChildThread2() {
	Cycle(125, "OS04_04_T2", 80, 15);
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
		printf("Main: PID = %d\n", pid);
		Sleep(1000);
		if (i == 30) {
			printf("\nMain thread is sleeping\n\n");
			Sleep(10 * 1000);
			printf("\nMain thread is waking up\n\n");
		}
	}

	WaitForSingleObject(hChild1, INFINITE);
	CloseHandle(hChild1);
	WaitForSingleObject(hChild2, INFINITE);
	CloseHandle(hChild2);
	system("pause");
}