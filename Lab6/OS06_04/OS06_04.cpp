#include <iostream>
#include <iomanip>
#include <Windows.h>

using namespace std;

void sh(HANDLE pheap);

int main()
{
	HANDLE heap = GetProcessHeap();
	sh(heap);
	int* arr = new int[300000];
	sh(heap);
	system("pause");
}

void sh(HANDLE pheap)
{
	PROCESS_HEAP_ENTRY phe;
	phe.lpData = NULL;
	while (HeapWalk(pheap, &phe))
	{
		cout << " -- address = " << hex << phe.lpData << dec
			<< ", size = " << phe.cbData
			<< (phe.wFlags & PROCESS_HEAP_REGION ? " R" : "")
			<< (phe.wFlags & PROCESS_HEAP_UNCOMMITTED_RANGE ? " U" : "")
			<< (phe.wFlags & PROCESS_HEAP_ENTRY_BUSY ? " B" : "") << endl;
	}
	cout << "---------------------------" << endl;
}