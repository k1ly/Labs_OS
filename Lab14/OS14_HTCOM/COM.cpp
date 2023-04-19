#include "pch.h"
#include "COM.h"
#include "CFactory.h"
#include "SEQLOG.h"

extern ULONG g_Components;
extern ULONG g_ServerLocks;

STDAPI DllCanUnloadNow()
{
	SEQ;
	HRESULT rc = E_UNEXPECTED;
	if (g_Components == 0 && g_ServerLocks == 0)
		rc = S_OK;
	else rc = S_FALSE;
	LOG("DllCanUnloadNow, rc = ", rc);
	return rc;
}

STDAPI DllGetClassObject(const CLSID& clsid, const IID& iid, void** ppv)
{
	SEQ;
	HRESULT rc = E_UNEXPECTED;
	CFactory* pCF;
	if (clsid != CLSID_OS14)
		rc = CLASS_E_CLASSNOTAVAILABLE;
	else if ((pCF = new CFactory()) == NULL)
		rc = E_OUTOFMEMORY;
	else
	{
		rc = pCF->QueryInterface(iid, ppv);
		pCF->Release();
	}
	LOG("DllGetClassObject, rc = ", rc);
	return S_OK;
}