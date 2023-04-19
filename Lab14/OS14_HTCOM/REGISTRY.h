#pragma once
#include <objbase.h>

HRESULT RegisterServer(HMODULE hModule,	// DLL module handle
	const CLSID& clsid,					// Class ID
	const WCHAR* szFriendlyName,		// Friendly Name
	const WCHAR* szVerIndProgID,		// Programmatic
	const WCHAR* szProgID);				// IDs

HRESULT UnregisterServer(const CLSID& clsid,	// Class ID
	const WCHAR* szVerIndProgID,				// Programmatic
	const WCHAR* szProgID);						// IDs