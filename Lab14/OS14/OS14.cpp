#include "pch.h"
#include "framework.h"
#include "OS14.h"

OS14HANDLE OS14::Init()
{
	IUnknown* pIUnknown = nullptr;
	HRESULT rc = CoInitialize(NULL);
	if (FAILED(rc))
		throw rc;
	rc = CoCreateInstance(CLSID_OS14, NULL, CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&pIUnknown);
	if (FAILED(rc))
		throw rc;
	return pIUnknown;
}

void OS14::Dispose(OS14HANDLE h)
{
	((IUnknown*)h)->Release();
	CoFreeUnusedLibraries();
}

Element* OS14::HT::NewElement(OS14HANDLE h)
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

Element* OS14::HT::NewElement(OS14HANDLE h, const void* key, int keylength)
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

Element* OS14::HT::NewElement(OS14HANDLE h, const void* key, int keylength, const void* payload, int payloadlength)
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

Element* OS14::HT::NewElement(OS14HANDLE h, Element* oldelement, const void* newpayload, int newpayloadlength)
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

HTHANDLE* OS14::HT::Create(OS14HANDLE h, int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const char HTUsersGroup[512], const char FileName[512])
{
	HTAPI* pHTAPI = nullptr;
	HRESULT rc = ((IUnknown*)h)->QueryInterface(IID_HTAPI, (void**)&pHTAPI);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	HTHANDLE* ret = nullptr;
	rc = pHTAPI->Create(Capacity, SecSnapshotInterval, MaxKeyLength, MaxPayloadLength, HTUsersGroup, FileName, ret);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	((IUnknown*)h)->Release();
	return ret;
}

HTHANDLE* OS14::HT::Open(OS14HANDLE h, const char FileName[512])
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

HTHANDLE* OS14::HT::Open(OS14HANDLE h, const char HTUser[256], const char HTPassword[256], const char FileName[512])
{
	HTAPI* pHTAPI = nullptr;
	HRESULT rc = ((IUnknown*)h)->QueryInterface(IID_HTAPI, (void**)&pHTAPI);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	HTHANDLE* ret = nullptr;
	rc = pHTAPI->Open(HTUser, HTPassword, FileName, ret);
	if (FAILED(rc))
	{
		((IUnknown*)h)->Release();
		throw rc;
	}
	((IUnknown*)h)->Release();
	return ret;
}

HTHANDLE* OS14::HT::OpenExisting(OS14HANDLE h, const char FileName[512])
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

BOOL OS14::HT::Snap(OS14HANDLE h, const HTHANDLE* hthandle)
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

BOOL OS14::HT::Close(OS14HANDLE h, const HTHANDLE* hthandle)
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

BOOL OS14::HT::Insert(OS14HANDLE h, const HTHANDLE* hthandle, const Element* element)
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

BOOL OS14::HT::Delete(OS14HANDLE h, const HTHANDLE* hthandle, const Element* element)
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

Element* OS14::HT::Get(OS14HANDLE h, const HTHANDLE* hthandle, const Element* element)
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

BOOL OS14::HT::Update(OS14HANDLE h, const HTHANDLE* hthandle, const Element* oldelement, const void* newpayload, int newpayloadlength)
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

char* OS14::HT::GetLastErrorMessage(OS14HANDLE h, HTHANDLE* ht)
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

void OS14::HT::Print(OS14HANDLE h, const Element* element)
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