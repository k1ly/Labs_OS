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