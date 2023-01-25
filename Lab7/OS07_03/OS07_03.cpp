#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	DWORD pid = GetCurrentProcessId();
	LPCWSTR an = L"C:\\Users\\Kirill\\Documents\\Labs\\OS\\Lab7\\x64\\Debug\\OS07_03x.exe";
	STARTUPINFO si;
	PROCESS_INFORMATION pi1;
	PROCESS_INFORMATION pi2;
	ZeroMemory(&si, sizeof(STARTUPINFO));

	HANDLE mutex = CreateMutex(NULL, FALSE, L"osMutex");

	si.cb = sizeof(STARTUPINFO);
	if (CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi1))
		cout << "Process OS07_03A created!" << endl;
	else cout << "Process OS07_03A not created" << endl;
	if (CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi2))
		cout << "Process OS07_03B created!" << endl;
	else cout << "Process OS07_03B not created" << endl;

	for (int i = 0; i < 90; i++)
	{
		if (i == 30)
			WaitForSingleObject(mutex, INFINITE);
		printf("PID = %d, OS07_03: %d\n", pid, i);
		Sleep(300);
		if (i == 60) {
			ReleaseMutex(mutex);
			WaitForSingleObject(mutex, INFINITE);
			ReleaseMutex(mutex);
		}
	}

	WaitForSingleObject(pi1.hProcess, INFINITE);
	WaitForSingleObject(pi2.hProcess, INFINITE);
	CloseHandle(mutex);
	CloseHandle(pi1.hProcess);
	CloseHandle(pi2.hProcess);
	system("pause");
}