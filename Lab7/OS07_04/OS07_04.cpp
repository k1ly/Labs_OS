#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	DWORD pid = GetCurrentProcessId();
	LPCWSTR an = L"C:\\Users\\Kirill\\Documents\\Labs\\OS\\Lab7\\x64\\Debug\\OS07_04x.exe";
	STARTUPINFO si;
	PROCESS_INFORMATION pi1;
	PROCESS_INFORMATION pi2;
	ZeroMemory(&si, sizeof(STARTUPINFO));

	HANDLE semaphore = CreateSemaphore(NULL, 2, 2, L"osSem");

	si.cb = sizeof(STARTUPINFO);
	if (CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi1))
		cout << "Process OS07_04A created!" << endl;
	else cout << "Process OS07_04A not created" << endl;
	if (CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi2))
		cout << "Process OS07_04B created!" << endl;
	else cout << "Process OS07_04B not created" << endl;

	LONG prevcount = 0;
	for (int i = 0; i < 90; i++)
	{
		if (i == 30)
			WaitForSingleObject(semaphore, INFINITE);
		printf("PID = %d, OS07_04: %d\n", pid, i);
		Sleep(300);
		if (i == 60) {
			ReleaseSemaphore(semaphore, 1, &prevcount);
			WaitForSingleObject(semaphore, INFINITE);
		}
	}
	ReleaseSemaphore(semaphore, 1, &prevcount);

	WaitForSingleObject(pi1.hProcess, INFINITE);
	WaitForSingleObject(pi2.hProcess, INFINITE);
	CloseHandle(semaphore);
	cout << "OS07_04: count = " << prevcount << endl;
	CloseHandle(pi1.hProcess);
	CloseHandle(pi2.hProcess);
	system("pause");
}