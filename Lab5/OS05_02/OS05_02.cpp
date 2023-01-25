#include <iostream>
#include <Windows.h>
#include <bitset>

using namespace std;

char* GetProcessPriority(unsigned int);

int main(int argc, char* argv[])
{
	try {
		if (argc == 1)
			throw "P1 parameter is missing";
		if (argc == 2)
			throw "P2 parameter is missing";
		if (argc == 3)
			throw "P3 parameter is missing";

		unsigned int mask = (unsigned int)atoi(argv[1]);
		unsigned int prior1 = (unsigned int)atoi(argv[2]);
		unsigned int prior2 = (unsigned int)atoi(argv[3]);
		cout << "P1 = " << bitset<8>(mask) << " (" << mask << ")" << endl;
		cout << "P2 = " << GetProcessPriority(prior1) << " (" << prior1 << ")" << endl;
		cout << "P3 = " << GetProcessPriority(prior2) << " (" << prior2 << ")" << endl;

		LPCWSTR				an = L"C:\\Users\\Kirill\\Documents\\Labs\\OS\\Lab5\\x64\\Debug\\OS05_02x.exe";
		STARTUPINFO			si;
		PROCESS_INFORMATION	pi1;
		PROCESS_INFORMATION	pi2;
		ZeroMemory(&si, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);
		if (CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | prior1, NULL, NULL, &si, &pi1))
		{
			SetProcessAffinityMask(pi1.hProcess, mask);
			cout << "Process OS05_02x 1 created!" << endl;
		}
		else
			cout << "Process OS05_02x 1 is not created!" << endl;
		if (CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | prior2, NULL, NULL, &si, &pi2)) {
			SetProcessAffinityMask(pi2.hProcess, mask);
			cout << "Process OS05_02x 2 created!" << endl;
		}
		else
			cout << "Process OS05_02x 2 is not created!" << endl;
		WaitForSingleObject(pi1.hProcess, INFINITE);
		CloseHandle(pi1.hProcess);
		WaitForSingleObject(pi2.hProcess, INFINITE);
		CloseHandle(pi2.hProcess);
	}
	catch (const char* error) {
		cout << error << endl;
	}
	system("pause");
}

char* GetProcessPriority(unsigned int p)
{
	char* priority = NULL;
	switch (p)
	{
	case IDLE_PRIORITY_CLASS: priority = (char*)"IDLE_PRIORITY_CLASS"; break;
	case BELOW_NORMAL_PRIORITY_CLASS: priority = (char*)"BELOW_NORMAL_PRIORITY_CLASS"; break;
	case NORMAL_PRIORITY_CLASS: priority = (char*)"NORMAL_PRIORITY_CLASS"; break;
	case ABOVE_NORMAL_PRIORITY_CLASS: priority = (char*)"ABOVE_NORMAL_PRIORITY_CLASS"; break;
	case HIGH_PRIORITY_CLASS: priority = (char*)"HIGH_PRIORITY_CLASS"; break;
	case REALTIME_PRIORITY_CLASS: priority = (char*)"REALTIME_PRIORITY_CLASS"; break;
	}
	return priority;
}