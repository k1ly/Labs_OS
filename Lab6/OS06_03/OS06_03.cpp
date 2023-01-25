#include <iostream>
#include <iomanip>
#include <Windows.h>
#define KB (1024)
#define MB (1024*KB)
#define PG (4*KB)

using namespace std;

LPVOID getmem(int, int);
void saymem();

int main()
{
	setlocale(LC_ALL, "ru");
	saymem();
	LPVOID addr = getmem(256, PG);
	saymem();
	int arr_size = 256 * PG / 4;
	int* arr = new(addr) int[arr_size];
	for (int i = 0; i < arr_size; i++)
	{
		arr[i] = i;
	}
	// Л = cb
	// ы = fb
	// с = f1
	// Страница CB = 203, смещение FBF = 4031
	byte* byte_addr = ((byte*)addr + (0xCB * PG) + 0xFBF);
	cout << hex << (int*)byte_addr << dec << " (" << (int)(*byte_addr) << ")" << endl;
	system("pause");
}

void saymem()
{
	MEMORYSTATUS ms;
	GlobalMemoryStatus(&ms);
	cout << " -- Объем физической памяти\t:" << (ms.dwTotalPhys / MB) << "MB" << endl;
	cout << " -- Доступно физической памяти\t:" << (ms.dwAvailPhys / MB) << "MB" << endl;
	cout << " -- Объем виртуальной памяти\t:" << (ms.dwTotalVirtual) << endl;
	cout << " -- Доступно виртуальной памяти\t:" << (ms.dwAvailVirtual) << endl;
	cout << endl;
}

LPVOID getmem(int mem, int unit)
{
	char* unit_name = (char*)"";
	switch (unit)
	{
	case KB:unit_name = (char*)"KB"; break;
	case MB:unit_name = (char*)"MB"; break;
	case PG:unit_name = (char*)"PG"; break;
	}
	LPVOID memaddr = VirtualAlloc(NULL, mem * unit, MEM_COMMIT, PAGE_READWRITE);
	cout << "-- " << mem << unit_name << "(" << mem * unit << ")" << ", VirtualAlloc = " << hex << memaddr << dec << endl;
	cout << endl;
	return memaddr;
}