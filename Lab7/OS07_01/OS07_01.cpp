#include <iostream>
#include <Windows.h>

using namespace std;

DWORD pid = NULL;

DWORD WINAPI ChildThread();
void EnterCriticalSectionAsm();
void LeaveCriticalSectionAsm();

int critical_section = 0;

int main()
{
	pid = GetCurrentProcessId();
	DWORD ChildId1 = NULL;
	DWORD ChildId2 = NULL;
	HANDLE hChild1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread, NULL, 0, &ChildId1);
	HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread, NULL, 0, &ChildId2);

	WaitForSingleObject(hChild1, INFINITE);
	WaitForSingleObject(hChild2, INFINITE);
	CloseHandle(hChild1);
	CloseHandle(hChild2);
	system("pause");
}

DWORD WINAPI ChildThread()
{
	DWORD tid = GetCurrentThreadId();
	EnterCriticalSectionAsm();
	for (int i = 0; i < 90; i++)
	{
		printf("PID = %d, (Child Thread) tid = %d: %d\n", pid, tid, i);
		Sleep(50);
	}
	LeaveCriticalSectionAsm();
	return 0;
}

void EnterCriticalSectionAsm() {
	_asm {
	CriticalSection:
		lock bts critical_section, 0;
		jc CriticalSection
	}
}

void LeaveCriticalSectionAsm() {
	_asm lock btr critical_section, 0
}