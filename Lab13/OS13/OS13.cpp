#include "pch.h"
#include "framework.h"
#include "OS13.h"

OS13HANDLE OS13::Init()
{
	IUnknown* pIUnknown = nullptr;
	HRESULT rc = CoInitialize(NULL);
	if (FAILED(rc))
		throw rc;
	rc = CoCreateInstance(CLSID_OS13, NULL, CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&pIUnknown);
	if (FAILED(rc))
		throw rc;
	return pIUnknown;
}

void OS13::Dispose(OS13HANDLE h)
{
	((IUnknown*)h)->Release();
	CoFreeUnusedLibraries();
}

Element* OS13::HT::NewElement(OS13HANDLE h)
{
	HTAPI* pHTAPI = nullptr;
	HRESULT rc = ((IUnknown*)h)->QueryInterface(IID_HTAPI, (void**)&pHTAPI);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	Element* ret = nullptr;
	rc = pHTAPI->NewElement(ret);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	((IUnknown*)h)->Release();
	return ret;
}

Element* OS13::HT::NewElement(OS13HANDLE h, const void* key, int keylength)
{
	HTAPI* pHTAPI = nullptr;
	HRESULT rc = ((IUnknown*)h)->QueryInterface(IID_HTAPI, (void**)&pHTAPI);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	Element* ret = nullptr;
	rc = pHTAPI->NewElement(key, keylength, ret);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	((IUnknown*)h)->Release();
	return ret;
}

Element* OS13::HT::NewElement(OS13HANDLE h, const void* key, int keylength, const void* payload, int payloadlength)
{
	HTAPI* pHTAPI = nullptr;
	HRESULT rc = ((IUnknown*)h)->QueryInterface(IID_HTAPI, (void**)&pHTAPI);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	Element* ret = nullptr;
	rc = pHTAPI->NewElement(key, keylength, payload, payloadlength, ret);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	((IUnknown*)h)->Release();
	return ret;
}

Element* OS13::HT::NewElement(OS13HANDLE h, Element* oldelement, const void* newpayload, int newpayloadlength)
{
	HTAPI* pHTAPI = nullptr;
	HRESULT rc = ((IUnknown*)h)->QueryInterface(IID_HTAPI, (void**)&pHTAPI);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	Element* ret = nullptr;
	rc = pHTAPI->NewElement(oldelement, newpayload, newpayloadlength, ret);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	((IUnknown*)h)->Release();
	return ret;
}

HTHANDLE* OS13::HT::Create(OS13HANDLE h, int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const char FileName[512])
{
	HTAPI* pHTAPI = nullptr;
	HRESULT rc = ((IUnknown*)h)->QueryInterface(IID_HTAPI, (void**)&pHTAPI);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	HTHANDLE* ret = nullptr;
	rc = pHTAPI->Create(Capacity, SecSnapshotInterval, MaxKeyLength, MaxPayloadLength, FileName, ret);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	((IUnknown*)h)->Release();
	return ret;
}

HTHANDLE* OS13::HT::Open(OS13HANDLE h, const char FileName[512])
{
	HTAPI* pHTAPI = nullptr;
	HRESULT rc = ((IUnknown*)h)->QueryInterface(IID_HTAPI, (void**)&pHTAPI);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	HTHANDLE* ret = nullptr;
	rc = pHTAPI->Open(FileName, ret);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	((IUnknown*)h)->Release();
	return ret;
}

HTHANDLE* OS13::HT::OpenExisting(OS13HANDLE h, const char FileName[512])
{
	HTAPI* pHTAPI = nullptr;
	HRESULT rc = ((IUnknown*)h)->QueryInterface(IID_HTAPI, (void**)&pHTAPI);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	HTHANDLE* ret = nullptr;
	rc = pHTAPI->OpenExisting(FileName, ret);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	((IUnknown*)h)->Release();
	return ret;
}

BOOL OS13::HT::Snap(OS13HANDLE h, const HTHANDLE* hthandle)
{
	HTAPI* pHTAPI = nullptr;
	HRESULT rc = ((IUnknown*)h)->QueryInterface(IID_HTAPI, (void**)&pHTAPI);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	BOOL ret = FALSE;
	rc = pHTAPI->Snap(hthandle, ret);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	((IUnknown*)h)->Release();
	return ret;
}

BOOL OS13::HT::Close(OS13HANDLE h, const HTHANDLE* hthandle)
{
	HTAPI* pHTAPI = nullptr;
	HRESULT rc = ((IUnknown*)h)->QueryInterface(IID_HTAPI, (void**)&pHTAPI);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	BOOL ret = FALSE;
	rc = pHTAPI->Close(hthandle, ret);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	((IUnknown*)h)->Release();
	return ret;
}

BOOL OS13::HT::Insert(OS13HANDLE h, const HTHANDLE* hthandle, const Element* element)
{
	HTAPI* pHTAPI = nullptr;
	HRESULT rc = ((IUnknown*)h)->QueryInterface(IID_HTAPI, (void**)&pHTAPI);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	BOOL ret = FALSE;
	rc = pHTAPI->Insert(hthandle, element, ret);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	((IUnknown*)h)->Release();
	return ret;
}

BOOL OS13::HT::Delete(OS13HANDLE h, const HTHANDLE* hthandle, const Element* element)
{
	HTAPI* pHTAPI = nullptr;
	HRESULT rc = ((IUnknown*)h)->QueryInterface(IID_HTAPI, (void**)&pHTAPI);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	BOOL ret = FALSE;
	rc = pHTAPI->Delete(hthandle, element, ret);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	((IUnknown*)h)->Release();
	return ret;
}

Element* OS13::HT::Get(OS13HANDLE h, const HTHANDLE* hthandle, const Element* element)
{
	HTAPI* pHTAPI = nullptr;
	HRESULT rc = ((IUnknown*)h)->QueryInterface(IID_HTAPI, (void**)&pHTAPI);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	Element* ret = nullptr;
	rc = pHTAPI->Get(hthandle, element, ret);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	((IUnknown*)h)->Release();
	return ret;
}

BOOL OS13::HT::Update(OS13HANDLE h, const HTHANDLE* hthandle, const Element* oldelement, const void* newpayload, int newpayloadlength)
{
	HTAPI* pHTAPI = nullptr;
	HRESULT rc = ((IUnknown*)h)->QueryInterface(IID_HTAPI, (void**)&pHTAPI);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	BOOL ret = FALSE;
	rc = pHTAPI->Update(hthandle, oldelement, newpayload, newpayloadlength, ret);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	((IUnknown*)h)->Release();
	return ret;
}

char* OS13::HT::GetLastErrorMessage(OS13HANDLE h, HTHANDLE* ht)
{
	HTAPI* pHTAPI = nullptr;
	HRESULT rc = ((IUnknown*)h)->QueryInterface(IID_HTAPI, (void**)&pHTAPI);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	char* ret = nullptr;
	rc = pHTAPI->GetLastErrorMessage(ht, ret);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	((IUnknown*)h)->Release();
	return ret;
}

void OS13::HT::Print(OS13HANDLE h, const Element* element)
{
	HTAPI* pHTAPI = nullptr;
	HRESULT rc = ((IUnknown*)h)->QueryInterface(IID_HTAPI, (void**)&pHTAPI);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	pHTAPI->Print(element);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	((IUnknown*)h)->Release();
}