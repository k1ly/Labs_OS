#pragma once
#include "..\\OS14_HTCOM\\OS14_HTAPI.h"

#define OS14HANDLE void*

namespace OS14
{
	OS14HANDLE Init();

	namespace HT
	{
		Element* NewElement(OS14HANDLE h);
		Element* NewElement(OS14HANDLE h, const void* key, int keylength);
		Element* NewElement(OS14HANDLE h, const void* key, int keylength, const void* payload, int payloadlength);
		Element* NewElement(OS14HANDLE h, Element* oldelement, const void* newpayload, int newpayloadlength);
		HTHANDLE* Create(OS14HANDLE h, int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const char HTUsersGroup[512], const char FileName[512]);
		HTHANDLE* Open(OS14HANDLE h, const char FileName[512]);
		HTHANDLE* Open(OS14HANDLE h, const char HTUser[256], const char HTPassword[256], const char FileName[512]);
		HTHANDLE* OpenExisting(OS14HANDLE h, const char FileName[512]);
		BOOL Snap(OS14HANDLE h, const HTHANDLE* hthandle);
		BOOL Close(OS14HANDLE h, const HTHANDLE* hthandle);
		BOOL Insert(OS14HANDLE h, const HTHANDLE* hthandle, const Element* element);
		BOOL Delete(OS14HANDLE h, const HTHANDLE* hthandle, const Element* element);
		Element* Get(OS14HANDLE h, const HTHANDLE* hthandle, const Element* element);
		BOOL Update(OS14HANDLE h, const HTHANDLE* hthandle, const Element* oldelement, const void* newpayload, int newpayloadlength);
		char* GetLastErrorMessage(OS14HANDLE h, HTHANDLE* ht);
		void Print(OS14HANDLE h, const Element* element);
	}

	void Dispose(OS14HANDLE h);
}
