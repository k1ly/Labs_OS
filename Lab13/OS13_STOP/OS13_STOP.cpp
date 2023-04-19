﻿#include <iostream>
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

			if (!OS13::HT::Snap(h, ht))
				cout << OS13::HT::GetLastErrorMessage(h, ht) << endl;

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