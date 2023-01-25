#include <iostream>
#include <ctime>
#include <Windows.h>

using namespace std;

int main()
{
	time_t t1 = time(&t1);
	tm ttm;
	localtime_s(&ttm, &t1);
	cout << "Time:\n"
		<< ttm.tm_mday << "."
		<< (ttm.tm_mon + 1) << "."
		<< (ttm.tm_year + 1900) << " "
		<< ttm.tm_hour << ":"
		<< ttm.tm_min << ":"
		<< ttm.tm_sec << endl;
	system("pause");
}