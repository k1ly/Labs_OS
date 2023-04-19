#include "pch.h"
#include "OS13.h"
#include "SEQLOG.h"
#include <time.h>
#include <iostream>
#include <LM.h>
#pragma comment(lib, "netapi32.lib")

extern ULONG g_Components;

struct OS13_HTHANDLE
{
	OS13* handle = nullptr;
	HTHANDLE* ht = nullptr;
	OS13_HTHANDLE(OS13* pHandle, HTHANDLE* pHT)
	{
		handle = pHandle;
		ht = pHT;
	}
};

int Hash(const HTHANDLE* hthandle, const Element* element, int index);
void GetFileMappingName(LPSTR fmName, LPCSTR path);
void GetMutexName(LPSTR mutexName, LPCSTR path);
DWORD WINAPI SnapAsync(LPVOID h);

OS13::OS13() : m_Ref(1)
{
	SEQ;
	InterlockedIncrement(&g_Components);
	LOG("OS13::OS13, g_Components = ", g_Components);
}

OS13::~OS13()
{
	SEQ;
	InterlockedDecrement(&g_Components);
	LOG("OS13::~OS13, g_Components = ", g_Components);
}

HRESULT STDMETHODCALLTYPE OS13::QueryInterface(REFIID riid, void** ppv)
{
	SEQ;
	HRESULT rc = S_OK;
	if (riid == IID_IUnknown)
		*ppv = (IUnknown*)this;
	else if (riid == IID_HTAPI)
		*ppv = (HTAPI*)this;
	else rc = E_NOINTERFACE;
	if (rc == S_OK)
		this->AddRef();
	LOG("OS13::QueryInterface, rc = ", rc);
	return rc;
}

ULONG STDMETHODCALLTYPE OS13::AddRef(void)
{
	SEQ;
	InterlockedIncrement(&this->m_Ref);
	LOG("OS13::AddRef, m_Ref = ", this->m_Ref);
	return this->m_Ref;
}

ULONG STDMETHODCALLTYPE OS13::Release(void)
{
	SEQ;
	ULONG m_Ref = this->m_Ref;
	if ((m_Ref = InterlockedDecrement(&this->m_Ref)) == 0)
		delete this;
	LOG("OS13::Release, m_Ref = ", m_Ref);
	return m_Ref;
}

HRESULT STDMETHODCALLTYPE OS13::NewElement(Element*& ret)
{
	SEQ;
	HRESULT rc = S_OK;
	ret = new Element();
	LOG("OS13::NewElement, element = ", ret);
	return rc;
}

HRESULT STDMETHODCALLTYPE OS13::NewElement(const void* key, int keylength, Element*& ret)
{
	SEQ;
	HRESULT rc = S_OK;
	ret = new Element(key, keylength);
	LOG("OS13::NewElementKey, element = ", ret);
	return rc;
}

HRESULT STDMETHODCALLTYPE OS13::NewElement(const void* key, int keylength, const void* payload, int payloadlength, Element*& ret)
{
	SEQ;
	HRESULT rc = S_OK;
	ret = new Element(key, keylength, payload, payloadlength);
	LOG("OS13::NewElementPayload, element = ", ret);
	return rc;
}

HRESULT STDMETHODCALLTYPE OS13::NewElement(Element* oldelement, const void* newpayload, int newpayloadlength, Element*& ret)
{
	SEQ;
	HRESULT rc = S_OK;
	ret = new Element(oldelement, newpayload, newpayloadlength);
	LOG("OS13::NewElementUpdate, element = ", ret);
	return rc;
}

HRESULT STDMETHODCALLTYPE OS13::Create(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const char FileName[512], HTHANDLE*& ret)
{
	SEQ;
	HRESULT rc = S_OK;
	HTHANDLE* ht = nullptr;
	HANDLE file = nullptr;
	HANDLE fm = nullptr;
	LPVOID lp = nullptr;
	try
	{
		if (Capacity < 0 || SecSnapshotInterval < 0 || MaxKeyLength < 0 || MaxPayloadLength < 0)
			throw "Invalid negative parameter!";
		char path[MAX_PATH];
		char name[MAX_PATH];
		GetFullPathNameA(FileName, MAX_PATH, path, NULL);
		file = CreateFileA(path,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (file == INVALID_HANDLE_VALUE)
			throw "Create file error!";
		GetFileMappingName(name, path);
		fm = CreateFileMappingA(file,
			NULL,
			PAGE_READWRITE,
			0, sizeof(HTHANDLE) + Capacity * (sizeof(Element) + MaxKeyLength + MaxPayloadLength), name);
		if (!fm)
			throw "Create file mapping error!";
		lp = MapViewOfFile(fm,
			FILE_MAP_ALL_ACCESS,
			0, 0, 0);
		if (!lp)
			throw "Map file view error!";
		ht = new(lp) HTHANDLE(Capacity, SecSnapshotInterval, MaxKeyLength, MaxPayloadLength, path);
		ht->File = file;
		ht->FileMapping = fm;
		ht->Addr = lp;
		GetMutexName(name, path);
		ht->Mutex = CreateMutexA(NULL, FALSE, name);
		if (!ht->Mutex)
			throw "Create mutex error!";
		OS13_HTHANDLE* h = new OS13_HTHANDLE(this, ht);
		ht->SnapThread = CreateThread(NULL, 0, SnapAsync, h, 0, NULL);
		if (!ht->SnapThread)
			throw "Create snap thread error!";
	}
	catch (LPCSTR exception)
	{
		printf("%s\n", exception);
		UnmapViewOfFile(lp);
		CloseHandle(fm);
		CloseHandle(file);
	}
	ret = ht;
	LOG("OS13::Create, ht = ", ret);
	return rc;
}

HRESULT STDMETHODCALLTYPE OS13::Open(const char FileName[512], HTHANDLE*& ret)
{
	SEQ;
	HRESULT rc = S_OK;
	HTHANDLE* ht = nullptr;
	HANDLE file = nullptr;
	HANDLE fm = nullptr;
	LPVOID lp = nullptr;
	try
	{
		char path[MAX_PATH];
		char name[MAX_PATH];
		GetFullPathNameA(FileName, MAX_PATH, path, NULL);
		file = CreateFileA(path,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (file == INVALID_HANDLE_VALUE)
			throw "Create file error!";
		GetFileMappingName(name, path);
		fm = CreateFileMappingA(file,
			NULL,
			PAGE_READWRITE,
			0, 0, name);
		if (!fm)
			throw "Create file mapping error!";
		lp = MapViewOfFile(fm,
			FILE_MAP_ALL_ACCESS,
			0, 0, 0);
		if (!lp)
			throw "Map file view error!";
		ht = (HTHANDLE*)lp;
		if (GetFileSize(file, NULL) != sizeof(HTHANDLE) + ht->Capacity * (sizeof(Element) + ht->MaxKeyLength + ht->MaxPayloadLength))
			throw "Provided file is not HT structure!";
		ht->File = file;
		ht->FileMapping = fm;
		ht->Addr = lp;
		GetMutexName(name, path);
		ht->Mutex = CreateMutexA(NULL, FALSE, name);
		if (!ht->Mutex)
			throw "Create mutex error!";
		OS13_HTHANDLE* h = new OS13_HTHANDLE(this, ht);
		ht->SnapThread = CreateThread(NULL, 0, SnapAsync, h, 0, NULL);
		if (!ht->SnapThread)
			throw "Create snap thread error!";
	}
	catch (LPCSTR exception)
	{
		printf("%s\n", exception);
		UnmapViewOfFile(lp);
		CloseHandle(fm);
		CloseHandle(file);
	}
	ret = ht;
	LOG("OS13::Open, ht = ", ret);
	return rc;
}

HRESULT STDMETHODCALLTYPE OS13::OpenExisting(const char FileName[512], HTHANDLE*& ret)
{
	SEQ;
	HRESULT rc = S_OK;
	HTHANDLE* ht = nullptr;
	HANDLE fm = nullptr;
	LPVOID lp = nullptr;
	char path[MAX_PATH];
	char name[MAX_PATH];
	GetFullPathNameA(FileName, MAX_PATH, path, NULL);
	GetMutexName(name, path);
	HANDLE mutex = OpenMutexA(SYNCHRONIZE, FALSE, name);
	if (mutex)
		WaitForSingleObject(mutex, INFINITE);
	try
	{
		GetFileMappingName(name, path);
		fm = OpenFileMappingA(FILE_MAP_ALL_ACCESS,
			FALSE,
			name);
		if (!fm)
			throw "Open file mapping error!";
		lp = MapViewOfFile(fm,
			FILE_MAP_ALL_ACCESS,
			0, 0, 0);
		if (!lp)
			throw "Map file view error!";
		ht = (HTHANDLE*)lp;
		CloseHandle(fm);
	}
	catch (LPCSTR exception)
	{
		printf("%s\n", exception);
		UnmapViewOfFile(lp);
		CloseHandle(fm);
	}
	if (mutex)
		ReleaseMutex(mutex);
	ret = ht;
	LOG("OS13::OpenExisting, ht = ", ret);
	return rc;
}

HRESULT STDMETHODCALLTYPE OS13::Snap(const HTHANDLE* hthandle, BOOL& ret)
{
	SEQ;
	HRESULT rc = S_OK;
	BOOL b = FALSE;
	WaitForSingleObject(hthandle->Mutex, INFINITE);
	try
	{
		time((time_t*)&hthandle->LastSnapTime);
		if (!FlushViewOfFile(hthandle, 0))
			throw "Flush file mapping error!";
		b = TRUE;
	}
	catch (LPCSTR exception)
	{
		strcpy_s((LPSTR)hthandle->LastErrorMessage, strlen(exception) + 1, exception);
	}
	ReleaseMutex(hthandle->Mutex);
	ret = b;
	LOG("OS13::Snap, b = ", (ret ? "true" : "false"));
	return rc;
}

HRESULT STDMETHODCALLTYPE OS13::Close(const HTHANDLE* hthandle, BOOL& ret)
{
	SEQ;
	HRESULT rc = S_OK;
	BOOL b = TRUE;
	WaitForSingleObject(hthandle->Mutex, INFINITE);
	if (TerminateThread(hthandle->SnapThread, 0))
	{
		b &= CloseHandle(hthandle->SnapThread);
		HANDLE fm = hthandle->FileMapping;
		HANDLE file = hthandle->File;
		HANDLE mutex = hthandle->Mutex;
		memset((LPVOID)&hthandle->SnapThread, 0, sizeof(HANDLE));
		memset((LPVOID)&hthandle->FileMapping, 0, sizeof(HANDLE));
		memset((LPVOID)&hthandle->File, 0, sizeof(HANDLE));
		memset((LPVOID)&hthandle->Mutex, 0, sizeof(HANDLE));
		b &= CloseHandle(fm);
		b &= CloseHandle(file);
		b &= CloseHandle(mutex);
	}
	memset((LPVOID)&hthandle->Addr, 0, sizeof(LPVOID));
	b &= UnmapViewOfFile(hthandle);
	ret = b;
	LOG("OS13::Close, b = ", (ret ? "true" : "false"));
	return rc;
}

HRESULT STDMETHODCALLTYPE OS13::Insert(const HTHANDLE* hthandle, const Element* element, BOOL& ret)
{
	SEQ;
	HRESULT rc = S_OK;
	BOOL b = FALSE;
	WaitForSingleObject(hthandle->Mutex, INFINITE);
	try
	{
		if (hthandle->Size >= hthandle->Capacity)
			throw "Maximum capacity storage size reached!";
		if (element->keylength > hthandle->MaxKeyLength)
			throw "Key length is greater then maximum key length!";
		if (element->payloadlength > hthandle->MaxPayloadLength)
			throw "Payload length is greater then maximum payload length!";
		for (size_t i = 0; i < hthandle->Capacity; i++)
		{
			int hash = Hash(hthandle, element, (int)i);
			Element* elementPtr = (Element*)((LONG_PTR)hthandle + sizeof(HTHANDLE) + hash * (sizeof(Element) + hthandle->MaxKeyLength + hthandle->MaxPayloadLength));
			elementPtr->key = (LPVOID)((LONG_PTR)elementPtr + sizeof(Element));
			if (*(LPSTR)elementPtr->key == NULL)
			{
				elementPtr->keylength = element->keylength;
				elementPtr->payload = (LPVOID)((LONG_PTR)elementPtr + sizeof(Element) + hthandle->MaxKeyLength);
				elementPtr->payloadlength = element->payloadlength;
				memcpy((LPVOID)elementPtr->key, element->key, element->keylength);
				memcpy((LPVOID)elementPtr->payload, element->payload, element->payloadlength);
				((HTHANDLE*)hthandle)->Size++;
				b = TRUE;
				break;
			}
			else
			{
				if (elementPtr->keylength == element->keylength &&
					memcmp(elementPtr->key, element->key, element->keylength) == 0)
					throw "Key already exists!";
			}
		}
	}
	catch (LPCSTR exception)
	{
		strcpy_s((LPSTR)hthandle->LastErrorMessage, strlen(exception) + 1, exception);
	}
	ReleaseMutex(hthandle->Mutex);
	ret = b;
	LOG("OS13::Insert, b = ", (ret ? "true" : "false"));
	return rc;
}

HRESULT STDMETHODCALLTYPE OS13::Delete(const HTHANDLE* hthandle, const Element* element, BOOL& ret)
{
	SEQ;
	HRESULT rc = S_OK;
	BOOL b = FALSE;
	WaitForSingleObject(hthandle->Mutex, INFINITE);
	try
	{
		Element* elementPtr = nullptr;
		Get(hthandle, element, elementPtr);
		if (!elementPtr)
			throw "Element not found";
		memset(elementPtr, 0, (sizeof(Element) + hthandle->MaxKeyLength + hthandle->MaxPayloadLength));
		((HTHANDLE*)hthandle)->Size--;
		b = TRUE;
	}
	catch (LPCSTR exception)
	{
		strcpy_s((LPSTR)hthandle->LastErrorMessage, strlen(exception) + 1, exception);
	}
	ret = b;
	ReleaseMutex(hthandle->Mutex);
	LOG("OS13::Delete, b = ", (ret ? "true" : "false"));
	return rc;
}

HRESULT STDMETHODCALLTYPE OS13::Get(const HTHANDLE* hthandle, const Element* element, Element*& ret)
{
	SEQ;
	HRESULT rc = S_OK;
	Element* elementPtr = nullptr;
	WaitForSingleObject(hthandle->Mutex, INFINITE);
	if (element)
	{
		for (size_t i = 0; i < hthandle->Capacity; i++)
		{
			int hash = Hash(hthandle, element, (int)i);
			Element* current = (Element*)((LONG_PTR)hthandle + sizeof(HTHANDLE) + hash * (sizeof(Element) + hthandle->MaxKeyLength + hthandle->MaxPayloadLength));
			current->key = (LPVOID)((LONG_PTR)current + sizeof(Element));
			current->payload = (LPVOID)((LONG_PTR)current + sizeof(Element) + hthandle->MaxKeyLength);
			if (!current->key)
				break;
			else if (current->keylength == element->keylength &&
				memcmp(current->key, element->key, element->keylength) == 0)
			{
				elementPtr = current;
				break;
			}
		}
	}
	ReleaseMutex(hthandle->Mutex);
	ret = elementPtr;
	LOG("OS13::Get, element = ", ret);
	return rc;
}

HRESULT STDMETHODCALLTYPE OS13::Update(const HTHANDLE* hthandle, const Element* oldelement, const void* newpayload, int newpayloadlength, BOOL& ret)
{
	SEQ;
	HRESULT rc = S_OK;
	BOOL b = FALSE;
	WaitForSingleObject(hthandle->Mutex, INFINITE);
	try
	{
		if (newpayloadlength > hthandle->MaxPayloadLength)
			throw "Payload length is greater then maximum payload length!";
		Element* elementPtr = nullptr;
		Get(hthandle, oldelement, elementPtr);
		if (!elementPtr)
			throw  "Element not found";
		elementPtr->payloadlength = newpayloadlength;
		memcpy((LPVOID)elementPtr->payload, newpayload, newpayloadlength);
		b = TRUE;
	}
	catch (LPCSTR exception)
	{
		strcpy_s((LPSTR)hthandle->LastErrorMessage, strlen(exception) + 1, exception);
	}
	ReleaseMutex(hthandle->Mutex);
	ret = b;
	LOG("OS13::Update, b = ", (ret ? "true" : "false"));
	return rc;
}

HRESULT STDMETHODCALLTYPE OS13::GetLastErrorMessage(HTHANDLE* ht, char*& ret)
{
	SEQ;
	HRESULT rc = S_OK;
	ret = ht->LastErrorMessage;
	LOG("OS13::GetLastErrorMessage, rc = ", rc);
	return rc;
}

HRESULT STDMETHODCALLTYPE OS13::Print(const Element* element)
{
	SEQ;
	HRESULT rc = S_OK;
	if (element)
	{
		printf("Key = [ ");
		for (size_t i = 0; i < element->keylength; i++)
		{
			printf("%02X ", ((PBYTE)element->key)[i]);
		}
		printf("], Value = [ ");
		for (size_t i = 0; i < element->payloadlength; i++)
		{
			printf("%02X ", ((PBYTE)element->payload)[i]);
		}
		printf("]\n");
	}
	LOG("OS13::Print, rc = ", rc);
	return rc;
}

int Hash(const HTHANDLE* hthandle, const Element* element, int index)
{
	int hash = 0;
	for (size_t i = 0; i < element->keylength; i++)
	{
		hash += ((LPSTR)element->key)[i];
	}
	return (hash + index) % hthandle->Capacity;
}

void GetFileMappingName(LPSTR fmName, LPCSTR path)
{
	for (size_t i = 0, j = 0; i < MAX_PATH; i++)
	{
		if (path[i] != '\\' && path[i] != ':')
			fmName[j++] = path[i];
		if (path[i] == '\0')
			break;
	}
}

void GetMutexName(LPSTR mutexName, LPCSTR path)
{
	for (size_t i = 0, j = 0; i < MAX_PATH; i++)
	{
		if (path[i] != '\\')
			mutexName[j++] = path[i];
		if (path[i] == '\0')
			break;
	}
}

DWORD WINAPI SnapAsync(LPVOID h)
{
	OS13* handle = ((OS13_HTHANDLE*)h)->handle;
	HTHANDLE* ht = ((OS13_HTHANDLE*)h)->ht;
	while (ht->Addr)
	{
		Sleep(ht->SecSnapshotInterval * 1000);
		BOOL b = FALSE;
		handle->Snap(ht, b);
	}
	return 0;
}