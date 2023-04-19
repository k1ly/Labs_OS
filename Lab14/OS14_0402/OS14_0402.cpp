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

			LPSTR filename = argv[1];

			ht = OS14::HT::OpenExisting(h, filename);
			if (!ht)
				throw "Open: error!";

			while (ht->Addr)
			{
				int key = rand() % 50 + 1;
				Element* element = OS14::HT::NewElement(h, &key, sizeof(key));
				Element* oldelement = OS14::HT::Get(h, ht, element);
				OS14::HT::Print(h, oldelement ? oldelement : element);
				cout << (OS14::HT::Delete(h, ht, element) ? "Deleted!" : OS14::HT::GetLastErrorMessage(h, ht)) << endl;
				delete element;
				Sleep(1000);
			}
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