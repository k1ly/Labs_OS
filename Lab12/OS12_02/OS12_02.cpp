﻿#include <iostream>
#include "..\\OS12_COM\\INTERFACE.h"

#define IERR(s)    std::cout << "Error: " << s << std::endl
#define IRES(s,r)  std::cout << s << r << std::endl

int main()
{
	IUnknown* pIUnknown = nullptr;
	IAdder* pIAdder = nullptr;
	IMultiplier* pMultiplier = nullptr;
	if (SUCCEEDED(CoInitialize(NULL)))
	{
		if (SUCCEEDED(CoCreateInstance(CLSID_OS12, NULL, CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&pIUnknown)))
		{
			if (SUCCEEDED(pIUnknown->QueryInterface(IID_IAdder, (void**)&pIAdder)))
			{
				{
					double z = 0.0;
					if (!SUCCEEDED(pIAdder->Add(2.0, 3.0, z)))
						IERR("IAdder::Add");
					else IRES("IAdder::Add = ", z);
				}
				{
					double z = 0.0;
					if (!SUCCEEDED(pIAdder->Sub(2.0, 3.0, z)))
						IERR("IAdder::Sub");
					else IRES("IAdder::Sub = ", z);
				}
				if (SUCCEEDED(pIAdder->QueryInterface(IID_IMultiplier, (void**)&pMultiplier)))
				{
					{
						double z = 0.0;
						if (!SUCCEEDED(pMultiplier->Mul(2.0, 3.0, z)))
							IERR("IMultiplier::Mul");
						else IRES("Multiplier::Mul = ", z);
					}
					{
						double z = 0.0;
						if (!SUCCEEDED(pMultiplier->Div(2.0, 3.0, z)))
							IERR("IMultiplier::Div");
						else IRES("IMultiplier::Div = ", z);
					}
					if (SUCCEEDED(pMultiplier->QueryInterface(IID_IAdder, (void**)&pIAdder)))
					{
						double z = 0.0;
						if (!SUCCEEDED(pIAdder->Add(2.0, 3.0, z)))
							IERR("IAdder::Add");
						else IRES("IAdder::Add = ", z);
						pIAdder->Release();
					}
					else IERR("IMultiplier->IAdder");
					pMultiplier->Release();
				}
				else IERR("IAdder->IMultiplier");
				pIAdder->Release();
			}
			else IERR("IAdder");
			pIUnknown->Release();
		}
		else std::cout << "CoCreateInstance error" << std::endl;
		CoFreeUnusedLibraries();
	}
	return 0;
}


