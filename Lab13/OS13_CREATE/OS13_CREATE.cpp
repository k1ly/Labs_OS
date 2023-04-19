#include <iostream>
#include "..\\OS13\\OS13.h"
#pragma comment(lib, "..\\x64\\Debug\\OS13.lib")

using namespace std;

int main(int argc, char* argv[])
{
	OS13HANDLE h = nullptr;
	try
	{
		h = OS13::Init();
		HTHANDLE* ht = nullptr;
		try
		{
			if (argc < 6)
				throw "Wrong amount of initialization parameters!";

			int capacity = atoi(argv[1]);
			int secSnapshotInterval = atoi(argv[2]);
			int maxKeyLength = atoi(argv[3]);
			int maxPayloadLength = atoi(argv[4]);
			LPSTR filename = argv[5];

			ht = OS13::HT::Create(h, capacity, secSnapshotInterval, maxKeyLength, maxPayloadLength, filename);
			if (!ht)
				throw "Create: error!";

			cout << "HT-Storage Created" << endl
				<< "filename = " << ht->FileName << endl
				<< "secSnapshotInterval = " << ht->SecSnapshotInterval << endl
				<< "capacity = " << ht->Capacity << endl
				<< "maxKeyLength = " << ht->MaxKeyLength << endl
				<< "maxPayloadLength = " << ht->MaxPayloadLength << endl;

			if (!OS13::HT::Close(h, ht))
				throw "Close: error!";
		}
		catch (LPCSTR msg)
		{
			cout << msg << endl;
		}
		OS13::Dispose(h);
	}
	catch (int e)
	{
		cout << "OS13: error = " << e << endl;
	}
}