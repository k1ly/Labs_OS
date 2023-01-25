#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	DWORD pid = GetCurrentProcessId();
	LPCWSTR an = L"C:\\Users\\Kirill\\Documents\\Labs\\OS\\Lab7\\x64\\Debug\\OS07_05x.exe";
	STARTUPINFO si;
	PROCESS_INFORMATION pi1;
	PROCESS_INFORMATION pi2;
	ZeroMemory(&si, sizeof(STARTUPINFO));

	HANDLE event = CreateEvent(NULL, TRUE, FALSE, L"osEvent");

	si.cb = sizeof(STARTUPINFO);
	if (CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi1))
		cout << "Process OS07_05A created!" << endl;
	else cout << "Process OS07_05A not created" << endl;
	if (CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi2))
		cout << "Process OS07_05B created!" << endl;
	else cout << "Process OS07_05B not created" << endl;

	for (int i = 0; i < 90; i++)
	{
		if (i == 15)
			PulseEvent(event);
		printf("PID = %d, OS07_05: %d\n", pid, i);
		Sleep(300);
	}

	WaitForSingleObject(pi1.hProcess, INFINITE);
	WaitForSingleObject(pi2.hProcess, INFINITE);
	CloseHandle(event);
	CloseHandle(pi1.hProcess);
	CloseHandle(pi2.hProcess);
	system("pause");
}