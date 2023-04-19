#pragma once
#include "..\\OS13_HTCOM\\OS13_HTAPI.h"

#define OS13HANDLE void*

namespace OS13
{
	OS13HANDLE Init();

	namespace HT
	{
		Element* NewElement(OS13HANDLE h);
		Element* NewElement(OS13HANDLE h, const void* key, int keylength);
		Element* NewElement(OS13HANDLE h, const void* key, int keylength, const void* payload, int payloadlength);
		Element* NewElement(OS13HANDLE h, Element* oldelement, const void* newpayload, int newpayloadlength);
		HTHANDLE* Create(OS13HANDLE h, int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const char FileName[512]);
		HTHANDLE* Open(OS13HANDLE h, const char FileName[512]);
		HTHANDLE* OpenExisting(OS13HANDLE h, const char FileName[512]);
		BOOL Snap(OS13HANDLE h, const HTHANDLE* hthandle);
		BOOL Close(OS13HANDLE h, const HTHANDLE* hthandle);
		BOOL Insert(OS13HANDLE h, const HTHANDLE* hthandle, const Element* element);
		BOOL Delete(OS13HANDLE h, const HTHANDLE* hthandle, const Element* element);
		Element* Get(OS13HANDLE h, const HTHANDLE* hthandle, const Element* element);
		BOOL Update(OS13HANDLE h, const HTHANDLE* hthandle, const Element* oldelement, const void* newpayload, int newpayloadlength);
		char* GetLastErrorMessage(OS13HANDLE h, HTHANDLE* ht);
		void Print(OS13HANDLE h, const Element* element);
	}

	void Dispose(OS13HANDLE h);
}
