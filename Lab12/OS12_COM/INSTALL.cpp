#include "pch.h"
#include "INSTALL.h"
#include "REGISTRY.h"
#include "SEQLOG.h"

STDAPI DllInstall(BOOL b, PCWSTR s)
{
	SEQ;
	LOG("DllInstall - ", (b ? "install" : "uninstall"));
	return S_OK;
}

STDAPI DllRegisterServer()
{
	SEQ;
	LOG("DllRegisterServer - ", hmodule);
	HRESULT rc = RegisterServer(hmodule, CLSID_OS12, FNAME, VINDX, PRGID);
	LOG("DllRegisterServer, rc = ", rc);
	return S_OK;
}

STDAPI DllUnregisterServer()
{
	SEQ;
	LOG("DllUnregisterServer - ", hmodule);
	HRESULT rc = UnregisterServer(CLSID_OS12, VINDX, PRGID);
	LOG("DllUnregisterServer, rc = ", rc);
	return S_OK;
}

