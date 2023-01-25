#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	DWORD pid = GetCurrentProcessId();
	for (int i = 0; i < 50; i++)
	{
		cout << pid << endl;
		Sleep(1000);
	}
}