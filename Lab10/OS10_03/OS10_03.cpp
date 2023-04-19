#include <iostream>
#include "..\\OS10_HTAPI\\OS10_HTAPI.h"
#pragma comment(lib, "..\\x64\\Debug\\OS10_HTAPI.lib")

using namespace std;

int main()
{
	LPCSTR filename = "..\\HT3.ht";
	HT::HTHANDLE* ht = nullptr;
	try
	{
		char key1[10];
		char key2[10];
		if (ht = HT::Open(filename)) {
			cout << "Open: success!" << endl;
			sprintf_s(key1, "key%d", 2);
		}
		else
		{
			if (ht = HT::Create(1000, 7, 10, 256, filename))
				cout << "Create: success!" << endl;
			else throw "Create: error";
			sprintf_s(key1, "key%d", 1);
		}
		sprintf_s(key2, "%s_2", key1);

		if (HT::Insert(ht, new HT::Element(key1, (int)strlen(key1) + 1, "payload", 8)))
			cout << "Insert: success!" << endl;
		else cout << "Insert: " << HT::GetLastError(ht) << endl;

		if (HT::Insert(ht, new HT::Element(key1, (int)strlen(key1) + 1, "payload", 8)))
			cout << "Insert: success!" << endl;
		else cout << "Insert: " << HT::GetLastError(ht) << endl;

		if (HT::Insert(ht, new HT::Element(key2, (int)strlen(key2) + 1, "payload2", 9)))
			cout << "Insert: success!" << endl;
		else cout << "Insert: " << HT::GetLastError(ht) << endl;

		HT::Element* hte1 = HT::Get(ht, new HT::Element(key1, (int)strlen(key1) + 1));
		if (hte1)
			cout << "Get: success!" << endl;
		HT::Print(hte1);

		HT::Element* hte2 = HT::Get(ht, new HT::Element(key2, (int)strlen(key2) + 1));
		if (hte2)
			cout << "Get: success!" << endl;
		HT::Print(hte2);

		if (HT::Snap(ht))
			cout << "Snap: success!" << endl;
		else cout << "Snap: " << HT::GetLastError(ht) << endl;

		if (HT::Delete(ht, hte2))
			cout << "Delete: success!" << endl;
		else cout << "Delete: " << HT::GetLastError(ht) << endl;

		hte2 = HT::Get(ht, new HT::Element(key2, (int)strlen(key2) + 1));
		if (hte2)
			cout << "Get: success!" << endl;
		HT::Print(hte2);

		if (HT::Update(ht, hte1, "newpayload", 11))
			cout << "Update: success!" << endl;
		else cout << "Update: " << HT::GetLastError(ht) << endl;
		HT::Print(hte1);

		Sleep(10000);

		if (HT::Close(ht))
			cout << "Close: success!" << endl;
		else throw "Close: error";
	}
	catch (LPCSTR msg)
	{
		cout << msg << endl;
	}
}
