#include <iostream>
#include "OS10_HTAPI.h"

using namespace std;

int main()
{
	LPCSTR filename = "C:\\Users\\Kirill\\Documents\\Labs\\OS\\Lab10\\HT3.ht";
	HT::HTHANDLE* ht = nullptr;
	try
	{
		if (ht = HT::Open(filename))
			cout << "Open: success!" << endl;
		else
		{
			if (ht = HT::Create(1000, 7, 10, 256, filename))
				cout << "Create: success!" << endl;
			else throw "Create: error";
		}

		if (HT::Insert(ht, new HT::Element("key1", 7, "payload", 8)))
			cout << "Insert: success!" << endl;
		else cout << "Insert: " << HT::GetLastError(ht) << endl;

		if (HT::Insert(ht, new HT::Element("key2", 7, "payload2", 9)))
			cout << "Insert: success!" << endl;
		else cout << "Insert: " << HT::GetLastError(ht) << endl;

		HT::Element* hte1 = HT::Get(ht, new HT::Element("key1", 7));
		if (hte1)
			cout << "Get: success!" << endl;
		else cout << HT::GetLastError(ht) << endl;
		HT::Print(hte1);

		HT::Element* hte2 = HT::Get(ht, new HT::Element("key2", 7));
		if (hte1)
			cout << "Get: success!" << endl;
		else cout << HT::GetLastError(ht) << endl;
		HT::Print(hte2);

		if (HT::Snap(ht))
			cout << "Snap: success!" << endl;
		else cout << "Snap: " << HT::GetLastError(ht) << endl;

		if (HT::Delete(ht, hte2))
			cout << "Delete: success!" << endl;
		else cout << "Delete: " << HT::GetLastError(ht) << endl;

		hte2 = HT::Get(ht, new HT::Element("key2", 7));
		if (hte2)
			cout << "Get: success!" << endl;
		HT::Print(hte2);

		if (HT::Update(ht, hte1, "newpayload", 10))
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
		if (ht != nullptr)
			cout << HT::GetLastError(ht) << endl;
	}
}
