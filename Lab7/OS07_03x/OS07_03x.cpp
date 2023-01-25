#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	DWORD pid = GetCurrentProcessId();
	HANDLE mutex = OpenMutex(SYNCHRONIZE, FALSE, L"osMutex");
	if (mutex == NULL)
		cout << "OS07_03x: Mutex Open error!" << endl;
	else cout << "OS07_03x: Mutex Opened" << endl;

	for (int i = 0; i < 90; i++)
	{
		if (i == 30)
			WaitForSingleObject(mutex, INFINITE);
		printf("PID = %d, OS07_03x: %d\n", pid, i);
		Sleep(300);
		if (i == 60) {
			ReleaseMutex(mutex);
			WaitForSingleObject(mutex, INFINITE);
			ReleaseMutex(mutex);
		}
	}

	CloseHandle(mutex);
	system("pause");
}