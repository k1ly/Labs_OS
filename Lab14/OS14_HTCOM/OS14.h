#pragma once
#include "OS14_HTAPI.h"

class OS14 : IUnknown, HTAPI
{
public:
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv);
	virtual ULONG STDMETHODCALLTYPE AddRef(void);
	virtual ULONG STDMETHODCALLTYPE Release(void);

	virtual	HRESULT STDMETHODCALLTYPE NewElement(Element*& ret);
	virtual	HRESULT STDMETHODCALLTYPE NewElement(const void* key, int keylength, Element*& ret);
	virtual	HRESULT STDMETHODCALLTYPE NewElement(const void* key, int keylength, const void* payload, int payloadlength, Element*& ret);
	virtual	HRESULT STDMETHODCALLTYPE NewElement(Element* oldelement, const void* newpayload, int newpayloadlength, Element*& ret);
	virtual	HRESULT STDMETHODCALLTYPE Create(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const char HTUsersGroup[512], const char FileName[512], HTHANDLE*& ret);
	virtual	HRESULT STDMETHODCALLTYPE Open(const char FileName[512], HTHANDLE*& ret);
	virtual	HRESULT STDMETHODCALLTYPE Open(const char HTUser[256], const char HTPassword[256], const char FileName[512], HTHANDLE*& ret);
	virtual	HRESULT STDMETHODCALLTYPE OpenExisting(const char FileName[512], HTHANDLE*& ret);
	virtual	HRESULT STDMETHODCALLTYPE Snap(const HTHANDLE* hthandle, BOOL& ret);
	virtual	HRESULT STDMETHODCALLTYPE Close(const HTHANDLE* hthandle, BOOL& ret);
	virtual	HRESULT STDMETHODCALLTYPE Insert(const HTHANDLE* hthandle, const Element* element, BOOL& ret);
	virtual	HRESULT STDMETHODCALLTYPE Delete(const HTHANDLE* hthandle, const Element* element, BOOL& ret);
	virtual	HRESULT STDMETHODCALLTYPE Get(const HTHANDLE* hthandle, const Element* element, Element*& ret);
	virtual	HRESULT STDMETHODCALLTYPE Update(const HTHANDLE* hthandle, const Element* oldelement, const void* newpayload, int newpayloadlength, BOOL& ret);
	virtual	HRESULT STDMETHODCALLTYPE GetLastErrorMessage(HTHANDLE* ht, char*& ret);
	virtual	HRESULT STDMETHODCALLTYPE Print(const Element* element);
	OS14();
	~OS14();
private:
	volatile ULONG m_Ref;
};