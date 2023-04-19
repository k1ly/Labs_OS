#pragma once
#include <objbase.h>

class CFactory : IClassFactory
{
public:
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv);
	virtual ULONG STDMETHODCALLTYPE AddRef(void);
	virtual ULONG STDMETHODCALLTYPE Release(void);

	virtual HRESULT STDMETHODCALLTYPE CreateInstance(IUnknown* pIU, const IID& id, void** ppv);
	virtual HRESULT STDMETHODCALLTYPE LockServer(BOOL b);
	CFactory();
	~CFactory();
private:
	ULONG m_Ref;
};