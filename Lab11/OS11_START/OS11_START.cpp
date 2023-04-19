#include <iostream>
#include "..\\OS11_HTAPI\\OS11_HTAPI.h"

using namespace std;

HT::HTHANDLE* (*Open)(const char[]);
BOOL(*Snap)(const HT::HTHANDLE*);
BOOL(*Close)(const HT::HTHANDLE*);
char* (*GetLastErrorMessage)(HT::HTHANDLE*);

int main(int argc, char* argv[])
{
	HT::HTHANDLE* ht = nullptr;
	try
	{
		if (argc < 2)
			throw "Wrong amount of initialization parameters!";

		LPSTR filename = argv[1];

		HMODULE htapi_dll = LoadLibraryA("C:\\Users\\Kirill\\Documents\\Labs\\OS\\Lab11\\x64\\Debug\\OS11_HTAPI.dll");
		if (!htapi_dll)
			throw "OS11_HTAPI library load failed!";
		cout << "OS11_HTAPI library loaded successfully!" << endl;

		Open = (HT::HTHANDLE * (*)(const char[])) GetProcAddress(htapi_dll, "Open");
		Snap = (BOOL(*)(const HT::HTHANDLE*)) GetProcAddress(htapi_dll, "Snap");
		Close = (BOOL(*)(const HT::HTHANDLE*)) GetProcAddress(htapi_dll, "Close");
		GetLastErrorMessage = (char* (*)(HT::HTHANDLE*)) GetProcAddress(htapi_dll, "GetLastErrorMessage");

		ht = Open(filename);
		if (!ht)
			throw "Open: error!";

		cout << "HT-Storage Start" << endl
			<< "filename = " << ht->FileName << endl
			<< "secSnapshotInterval = " << ht->SecSnapshotInterval << endl
			<< "capacity = " << ht->Capacity << endl
			<< "maxKeyLength = " << ht->MaxKeyLength << endl
			<< "maxPayloadLength = " << ht->MaxPayloadLength << endl;

		system("pause");
		if (!Snap(ht))
			cout << GetLastErrorMessage(ht) << endl;

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
