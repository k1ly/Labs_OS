#include <iostream>
#include <Windows.h>

using namespace std;

bool t = false;

DWORD WINAPI ChildThread();

int main(int argc, char* argv[])
{
	clock_t start = clock();
	setlocale(LC_ALL, "ru");
	if (argc < 2)
		throw "Error: No timer name was specified in parameters";
	wchar_t name[20];
	mbstowcs_s(NULL, name, strlen(argv[1]) * sizeof(wchar_t), argv[1], strlen(argv[1]));
	HANDLE timer = OpenWaitableTimer(TIMER_ALL_ACCESS, FALSE, name);
	DWORD ChildId = NULL;
	HANDLE hChild = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread, NULL, 0, &ChildId);
	WaitForSingleObject(timer, INFINITE);
	t = true;
	CloseHandle(timer);
	CloseHandle(hChild);
	cout << "Прошло секунд: " << (float)(clock() - start) / CLK_TCK << endl;
	system("pause");
}

DWORD WINAPI ChildThread()
{
	for (int i = 0, n = 1; ; n++)
	{
		if (t)
			break;
		bool isSimple = true;
		for (int j = 2; j < n; j++)
			if (n % j == 0) {
				isSimple = false;
				break;
			}
		if (isSimple)
			cout << ++i << " - " << n << endl;
	}
	return 0;
}