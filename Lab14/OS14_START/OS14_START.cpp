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
			if (argc < 2)
				throw "Wrong amount of initialization parameters!";
			if (argc < 4)
			{
				LPSTR filename = argv[1];
				ht = OS14::HT::Open(h, filename);
			}
			else
			{
				LPSTR username = argv[1];
				LPSTR password = argv[2];
				LPSTR filename = argv[3];
				ht = OS14::HT::Open(h, username, password, filename);
			}
			if (!ht)
				throw "Open: error!";

			cout << "HT-Storage Start" << endl
				<< "filename = " << ht->FileName << endl
				<< "secSnapshotInterval = " << ht->SecSnapshotInterval << endl
				<< "capacity = " << ht->Capacity << endl
				<< "maxKeyLength = " << ht->MaxKeyLength << endl
				<< "maxPayloadLength = " << ht->MaxPayloadLength << endl;

			while (ht->Addr)
			{
				Sleep(1000);
			}

			if (!OS14::HT::Snap(h, ht))
				cout << OS14::HT::GetLastErrorMessage(h, ht) << endl;

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