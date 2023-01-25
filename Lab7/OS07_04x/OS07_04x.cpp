#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	DWORD pid = GetCurrentProcessId();
	HANDLE semaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"osSem");
	if (semaphore == NULL)
		cout << "OS07_04x: Semaphore Open error!" << endl;
	else cout << "OS07_04x: Semaphore Opened" << endl;

	LONG prevcount = 0;
	for (int i = 0; i < 90; i++)
	{
		if (i == 30)
			WaitForSingleObject(semaphore, INFINITE);
		printf("PID = %d, OS07_04x: %d\n", pid, i);
		Sleep(300);
		if (i == 60) {
			ReleaseSemaphore(semaphore, 1, &prevcount);
			WaitForSingleObject(semaphore, INFINITE);
		}
	}
	ReleaseSemaphore(semaphore, 1, &prevcount);

	CloseHandle(semaphore);
	cout << "OS07_04x: count = " << prevcount << endl;
	system("pause");
}