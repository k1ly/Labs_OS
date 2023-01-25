#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	DWORD pid = GetCurrentProcessId();
	HANDLE event = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"osEvent");
	if (event == NULL)
		cout << "OS07_05x: Event Open error!" << endl;
	else cout << "OS07_05x: Event Opened" << endl;

	WaitForSingleObject(event, INFINITE);
	for (int i = 0; i < 90; i++)
	{
		printf("PID = %d, OS07_05x: %d\n", pid, i);
		Sleep(300);
	}

	CloseHandle(event);
	system("pause");
}