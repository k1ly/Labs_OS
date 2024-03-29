#include "pch.h"
#include "CFactory.h"
#include "OS12.h"
#include "SEQLOG.h"

extern ULONG g_ServerLocks;

CFactory::CFactory() : m_Ref(1)
{
	SEQ;
	LOG("CFactory::CFactory", "");
}

CFactory::~CFactory()
{
	SEQ;
	LOG("CFactory::~CFactory", "");
}

HRESULT STDMETHODCALLTYPE CFactory::QueryInterface(REFIID riid, void** ppv)
{
	SEQ;
	HRESULT rc = S_OK;
	if (riid == IID_IUnknown)
		*ppv = (IUnknown*)this;
	else if (riid == IID_IClassFactory)
		*ppv = (IClassFactory*)this;
	else rc = E_NOINTERFACE;
	if (rc == S_OK)
		this->AddRef();
	LOG("CFactory::QueryInterface, rc = ", rc);
	return rc;
}

ULONG STDMETHODCALLTYPE CFactory::AddRef(void)
{
	SEQ;
	InterlockedIncrement(&this->m_Ref);
	LOG("CFactory::AddRef, m_Ref = ", this->m_Ref);
	return this->m_Ref;
}

ULONG STDMETHODCALLTYPE CFactory::Release(void)
{
	SEQ;
	ULONG m_Ref = this->m_Ref;
	if ((m_Ref = InterlockedDecrement(&this->m_Ref)) == 0)
		delete this;
	LOG("CFactory::Release, m_Ref = ", m_Ref);
	return m_Ref;
}

HRESULT STDMETHODCALLTYPE CFactory::CreateInstance(IUnknown* pIU, const IID& id, void** ppv)
{
	SEQ;
	HRESULT rc = E_UNEXPECTED;
	OS12* pOS12;
	if (pIU != NULL)
		rc = CLASS_E_NOAGGREGATION;
	else if ((pOS12 = new OS12()) == NULL)
		rc = E_OUTOFMEMORY;
	else
	{
		rc = pOS12->QueryInterface(id, ppv);
		pOS12->Release();
	}
	LOG("CFactory::CreateInstance, rc = ", rc);
	return rc;
}

HRESULT STDMETHODCALLTYPE CFactory::LockServer(BOOL b)
{
	SEQ;
	HRESULT rc = S_OK;
	if (b)
		InterlockedIncrement(&g_ServerLocks);
	else
		InterlockedDecrement(&g_ServerLocks);
	LOG("CFactory::LockServer, rc = ", rc);
	return rc;
}