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
			if (argc < 2)
				throw "Wrong amount of initialization parameters!";

			LPSTR filename = argv[1];

			ht = OS13::HT::OpenExisting(h, filename);
			if (!ht)
				throw "Open: error!";

			while (ht->Addr)
			{
				int key = rand() % 50 + 1;
				Element* element = OS13::HT::NewElement(h, &key, sizeof(key));
				Element* oldelement = OS13::HT::Get(h, ht, element);
				OS13::HT::Print(h, oldelement ? oldelement : element);
				cout << (OS13::HT::Delete(h, ht, element) ? "Deleted!" : OS13::HT::GetLastErrorMessage(h, ht)) << endl;
				delete element;
				Sleep(1000);
			}
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