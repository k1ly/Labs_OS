#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	LPCWSTR				an1 = L"C:\\Users\\Kirill\\Documents\\Labs\\OS\\Lab3\\x64\\Debug\\OS03_02_1.exe";
	LPCWSTR				an2 = L"C:\\Users\\Kirill\\Documents\\Labs\\OS\\Lab3\\x64\\Debug\\OS03_02_2.exe";
	STARTUPINFO			si;
	PROCESS_INFORMATION	pi1;
	PROCESS_INFORMATION	pi2;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	if (CreateProcess(an1, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi1))
		cout << "Process OS03_02_1 created!" << endl;
	else
		cout << "Process OS03_02_1 is not created!" << endl;
	if (CreateProcess(an2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi2))
		cout << "Process OS03_02_2 created!" << endl;
	else
		cout << "Process OS03_02_2 is not created!" << endl;
	DWORD pid = GetCurrentProcessId();
	for (int i = 0; i < 100; i++)
	{
		cout << pid << endl;
		Sleep(1000);
	}
	WaitForSingleObject(pi1.hProcess, INFINITE);
	CloseHandle(pi1.hProcess);
	WaitForSingleObject(pi2.hProcess, INFINITE);
	CloseHandle(pi2.hProcess);
	system("pause");
}