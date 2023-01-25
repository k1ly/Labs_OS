#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	for (int i = 0; i < 400000; i++)
	{
		cout << i << endl;
		Sleep(1000);
	}
}