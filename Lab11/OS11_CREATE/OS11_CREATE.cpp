#include <iostream>
#include "..\\OS11_HTAPI\\OS11_HTAPI.h"

using namespace std;

HT::HTHANDLE* (*Create)(int, int, int, int, const char[]);
BOOL(*Close)(const HT::HTHANDLE*);

int main(int argc, char* argv[])
{
	HT::HTHANDLE* ht = nullptr;
	try
	{
		if (argc < 6)
			throw "Wrong amount of initialization parameters!";

		int capacity = atoi(argv[1]);
		int secSnapshotInterval = atoi(argv[2]);
		int maxKeyLength = atoi(argv[3]);
		int maxPayloadLength = atoi(argv[4]);
		LPSTR filename = argv[5];

		HMODULE htapi_dll = LoadLibraryA("C:\\Users\\Kirill\\Documents\\Labs\\OS\\Lab11\\x64\\Debug\\OS11_HTAPI.dll");
		if (!htapi_dll)
			throw "OS11_HTAPI library load failed!";
		cout << "OS11_HTAPI library loaded successfully!" << endl;

		Create = (HT::HTHANDLE * (*)(int, int, int, int, const char[])) GetProcAddress(htapi_dll, "Create");
		Close = (BOOL(*)(const HT::HTHANDLE*)) GetProcAddress(htapi_dll, "Close");

		ht = Create(capacity, secSnapshotInterval, maxKeyLength, maxPayloadLength, filename);
		if (!ht)
			throw "Create: error!";

		cout << "HT-Storage Created" << endl
			<< "filename = " << ht->FileName << endl
			<< "secSnapshotInterval = " << ht->SecSnapshotInterval << endl
			<< "capacity = " << ht->Capacity << endl
			<< "maxKeyLength = " << ht->MaxKeyLength << endl
			<< "maxPayloadLength = " << ht->MaxPayloadLength << endl;

		if (!Close(ht))
			throw "Close: error!";

		if (!FreeLibrary(htapi_dll))
			throw "OS11_HTAPI library unload failed!";
		cout << "OS11_HTAPI library unloaded successfully!" << endl;
	}
	catch (LPCSTR msg)
	{
		cout << msg << endl;
	}
}
