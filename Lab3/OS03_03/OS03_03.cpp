#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

using namespace std;

int main()
{
	DWORD pid = GetCurrentProcessId();
	HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
	PROCESSENTRY32 peProcessEntry;
	peProcessEntry.dwSize = sizeof(PROCESSENTRY32);
	cout << "Current PID = " << pid << endl;
	cout << "------------------------" << endl;
	try {
		if (!Process32First(snap, &peProcessEntry))
			throw L"Process32First";
		do
		{
			cout << "Name = " << peProcessEntry.szExeFile << endl
				<< "PID = " << peProcessEntry.th32ProcessID
				<< ", Parent PID = " << peProcessEntry.th32ParentProcessID;
			if (peProcessEntry.th32ProcessID == pid)
				cout << " ---> current process";
			cout << endl << "------------------------" << endl;
		} while (Process32Next(snap, &peProcessEntry));
	}
	catch (char* msg) {
		cout << "ERROR: " << msg << endl;
	}
	system("pause");
}