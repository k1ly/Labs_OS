#include <iostream>
#include "..\\OS11_HTAPI\\OS11_HTAPI.h"

using namespace std;

HT::HTHANDLE* (*OpenExisting)(const char[]);
BOOL(*Delete)(const HT::HTHANDLE*, const HT::Element*);
HT::Element* (*NewElementGet)(const void*, int);
HT::Element* (*Get)(const HT::HTHANDLE*, const HT::Element*);
void(*Print)(const HT::Element*);
BOOL(*Close)(const HT::HTHANDLE*);
char* (*GetLastErrorMessage)(HT::HTHANDLE*);

int main(int argc, char* argv[])
{
	HT::HTHANDLE* ht = nullptr;
	try
	{
		if (argc < 2)
			throw "Wrong amount of initialization parameters!";

		char* filename = argv[1];

		HMODULE htapi_dll = LoadLibraryA("C:\\Users\\Kirill\\Documents\\Labs\\OS\\Lab11\\x64\\Debug\\OS11_HTAPI.dll");
		if (!htapi_dll)
			throw "OS11_HTAPI library load failed!";
		cout << "OS11_HTAPI library loaded successfully!" << endl;

		OpenExisting = (HT::HTHANDLE * (*)(const char[])) GetProcAddress(htapi_dll, "OpenExisting");
		Delete = (BOOL(*)(const HT::HTHANDLE*, const HT::Element*)) GetProcAddress(htapi_dll, "Delete");
		NewElementGet = (HT::Element * (*)(const void*, int)) GetProcAddress(htapi_dll, "NewElementGet");
		Get = (HT::Element * (*)(const HT::HTHANDLE*, const HT::Element*)) GetProcAddress(htapi_dll, "Get");
		Print = (void (*)(const HT::Element*)) GetProcAddress(htapi_dll, "Print");
		Close = (BOOL(*)(const HT::HTHANDLE*)) GetProcAddress(htapi_dll, "Close");
		GetLastErrorMessage = (char* (*)(HT::HTHANDLE*)) GetProcAddress(htapi_dll, "GetLastErrorMessage");

		ht = OpenExisting(filename);
		if (!ht)
			throw "OpenExisting: error!";

		while (ht->Addr)
		{
			int key = rand() % 50 + 1;
			HT::Element* element = NewElementGet(&key, sizeof(key));
			HT::Element* oldelement = Get(ht, element);
			Print(oldelement ? oldelement : element);
			cout << (Delete(ht, element) ? "Deleted!" : GetLastErrorMessage(ht)) << endl;
			delete element;
			Sleep(1000);
		}

		if (!FreeLibrary(htapi_dll))
			throw "OS11_HTAPI library unload failed!";
		cout << "OS11_HTAPI library unloaded successfully!" << endl;
	}
	catch (LPCSTR msg)
	{
		cout << msg << endl;
	}
}
