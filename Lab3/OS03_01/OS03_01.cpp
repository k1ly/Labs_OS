#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	DWORD pid = GetCurrentProcessId();
	for (int i = 0; i < 1000; i++)
	{
		cout << pid << endl;
		Sleep(1000);
	}
	system("pause");
}

// tasklist /fi "imagename eq os03_01.exe" 
// Get-Process os03_01
// perfmon
