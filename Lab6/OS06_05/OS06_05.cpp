#include <iostream>
#include <iomanip>
#include <Windows.h>
#define MB (1024*1024)

using namespace std;

void sh(HANDLE pheap);

int main()
{
	HANDLE heap = HeapCreate(HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY, 0, 4 * MB);
	sh(heap);
	int* x = (int*)HeapAlloc(heap, HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY, 300000 * sizeof(int));
	sh(heap);
	HeapFree(heap, HEAP_NO_SERIALIZE, x);
	sh(heap);
	HeapDestroy(heap);
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