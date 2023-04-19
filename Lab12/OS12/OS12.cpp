#include "pch.h"
#include "framework.h"
#include "OS12.h"
#include "..\\OS12_COM\\INTERFACE.h"

OS12HANDLE OS12::Init()
{
	IUnknown* pIUnknown = nullptr;
	HRESULT rc = CoInitialize(NULL);
	if (FAILED(rc))
		throw rc;
	rc = CoCreateInstance(CLSID_OS12, NULL, CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&pIUnknown);
	if (FAILED(rc))
		throw rc;
	return pIUnknown;
}

void OS12::Dispose(OS12HANDLE h)
{
	((IUnknown*)h)->Release();
	CoFreeUnusedLibraries();
}

double OS12::Adder::Add(OS12HANDLE h, double x, double y)
{
	IAdder* pIAdder = nullptr;
	HRESULT rc = ((IUnknown*)h)->QueryInterface(IID_IAdder, (void**)&pIAdder);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	double z = 0.0;
	rc = pIAdder->Add(x, y, z);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	((IUnknown*)h)->Release();
	return z;
}

double OS12::Adder::Sub(OS12HANDLE h, double x, double y)
{
	IAdder* pIAdder = nullptr;
	HRESULT rc = ((IUnknown*)h)->QueryInterface(IID_IAdder, (void**)&pIAdder);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	double z = 0.0;
	rc = pIAdder->Sub(x, y, z);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	((IUnknown*)h)->Release();
	return z;
}

double OS12::Multiplier::Mul(OS12HANDLE h, double x, double y)
{
	IMultiplier* pMultiplier = nullptr;
	HRESULT rc = ((IUnknown*)h)->QueryInterface(IID_IMultiplier, (void**)&pMultiplier);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	double z = 0.0;
	rc = pMultiplier->Mul(x, y, z);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	((IUnknown*)h)->Release();
	return z;
}

double OS12::Multiplier::Div(OS12HANDLE h, double x, double y)
{
	IMultiplier* pMultiplier = nullptr;
	HRESULT rc = ((IUnknown*)h)->QueryInterface(IID_IMultiplier, (void**)&pMultiplier);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	double z = 0.0;
	rc = pMultiplier->Div(x, y, z);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	((IUnknown*)h)->Release();
	return z;
}