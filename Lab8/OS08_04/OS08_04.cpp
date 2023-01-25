#include <iostream>
#include <Windows.h>
#define SECOND 10000000

using namespace std;

int main()
{
	LPCWSTR an = L"C:\\Users\\Kirill\\Documents\\Labs\\OS\\Lab8\\x64\\Debug\\OS08_04_X.exe";
	STARTUPINFO si;
	PROCESS_INFORMATION pi1;
	PROCESS_INFORMATION pi2;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	HANDLE timer1 = CreateWaitableTimer(NULL, FALSE, L"osTimer1");
	HANDLE timer2 = CreateWaitableTimer(NULL, FALSE, L"osTimer2");
	long long it1 = -1 * SECOND;
	long long it2 = -2 * SECOND;
	if(!SetWaitableTimer(timer1, (LARGE_INTEGER*)&it1, 0, NULL, NULL, FALSE))
		throw "Error: SetWaitableTimer 1";
	if (CreateProcess(an, (LPWSTR)L"OS08_04_X.exe osTimer1", NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi1))
		cout << "Process OS08_04_1 created!" << endl;
	else cout << "Process OS08_04_1 not created" << endl;
	if (!SetWaitableTimer(timer2, (LARGE_INTEGER*)&it2, 0, NULL, NULL, FALSE))
		throw "Error: SetWaitableTimer 2";
	if (CreateProcess(an, (LPWSTR)L"OS08_04_X.exe osTimer2", NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi2))
		cout << "Process OS08_04_2 created!" << endl;
	else cout << "Process OS08_04_2 not created" << endl;
	WaitForSingleObject(pi1.hProcess, INFINITE);
	WaitForSingleObject(pi2.hProcess, INFINITE);
	CloseHandle(pi1.hProcess);
	CloseHandle(pi2.hProcess);
	system("pause");
}