#include <iostream>
#include "..\\OS14\\OS14.h"
#pragma comment(lib, "..\\x64\\Debug\\OS14.lib")

using namespace std;

int main(int argc, char* argv[])
{
	OS14HANDLE h = nullptr;
	try
	{
		h = OS14::Init();
		HTHANDLE* ht = nullptr;
		try
		{
			if (argc < 7)
				throw "Wrong amount of initialization parameters!";

			int capacity = atoi(argv[1]);
			int secSnapshotInterval = atoi(argv[2]);
			int maxKeyLength = atoi(argv[3]);
			int maxPayloadLength = atoi(argv[4]);
			LPSTR groupname = argv[5];
			LPSTR filename = argv[6];

			ht = OS14::HT::Create(h, capacity, secSnapshotInterval, maxKeyLength, maxPayloadLength, groupname, filename);
			if (!ht)
				throw "Create: error!";

			cout << "HT-Storage Created" << endl
				<< "filename = " << ht->FileName << endl
				<< "secSnapshotInterval = " << ht->SecSnapshotInterval << endl
				<< "capacity = " << ht->Capacity << endl
				<< "maxKeyLength = " << ht->MaxKeyLength << endl
				<< "maxPayloadLength = " << ht->MaxPayloadLength << endl;

			if (!OS14::HT::Close(h, ht))
				throw "Close: error!";
		}
		catch (LPCSTR msg)
		{
			cout << msg << endl;
		}
		OS14::Dispose(h);
	}
	catch (int e)
	{
		cout << "OS14: error = " << e << endl;
	}
}