#include "HT.h"
#include <time.h>
#include <iostream>

namespace HT
{
	int Hash(const HTHANDLE* hthandle, const Element* element, int index);

	HTHANDLE::HTHANDLE()
	{
		this->Capacity = 0;
		this->Size = 0;
		this->SecSnapshotInterval = 0;
		this->MaxKeyLength = 0;
		this->MaxPayloadLength = 0;
	}

	HTHANDLE::HTHANDLE(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const char FileName[512])
	{
		this->Capacity = Capacity;
		this->Size = 0;
		this->SecSnapshotInterval = SecSnapshotInterval;
		this->MaxKeyLength = MaxKeyLength;
		this->MaxPayloadLength = MaxPayloadLength;
		strcpy_s(this->FileName, FileName);
	}

	Element::Element()
	{
		this->keylength = 0;
		this->payloadlength = 0;
	}

	Element::Element(const void* key, int keylength)
	{
		this->key = key;
		this->keylength = keylength;
		this->payloadlength = 0;
	}

	Element::Element(const void* key, int keylength, const void* payload, int payloadlength)
	{
		this->key = key;
		this->keylength = keylength;
		this->payload = payload;
		this->payloadlength = payloadlength;
	}

	Element::Element(Element* oldelement, const void* newpayload, int newpayloadlength)
	{
		this->key = oldelement->key;
		this->keylength = oldelement->keylength;
		this->payload = newpayload;
		this->payloadlength = newpayloadlength;
	}

	HTHANDLE* Create(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const char FileName[512])
	{
		HTHANDLE* ht = nullptr;
		HANDLE file = nullptr;
		HANDLE fm = nullptr;
		LPVOID lp = nullptr;
		try
		{
			if (Capacity < 0 || SecSnapshotInterval < 0 || MaxKeyLength < 0 || MaxPayloadLength < 0)
				throw "Invalid negative parameter!";
			char filename[MAX_PATH];
			GetFullPathNameA(FileName, MAX_PATH, filename, NULL);
			file = CreateFileA(filename,
				GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ | FILE_SHARE_WRITE,
				NULL,
				CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
			if (file == INVALID_HANDLE_VALUE)
				throw "Open file error!";
			fm = CreateFileMappingA(file,
				NULL,
				PAGE_READWRITE,
				0, sizeof(HTHANDLE) + Capacity * (sizeof(Element) + MaxKeyLength + MaxPayloadLength), NULL);
			if (!fm)
				throw "Create file mapping error!";
			lp = MapViewOfFile(fm,
				FILE_MAP_ALL_ACCESS,
				0, 0, 0);
			if (!lp)
				throw "View file mapping error!";
			ht = new(lp) HTHANDLE(Capacity, SecSnapshotInterval, MaxKeyLength, MaxPayloadLength, filename);
			ht->File = file;
			ht->FileMapping = fm;
			ht->Addr = lp;
		}
		catch (LPCSTR exception)
		{
			printf("%s\n", exception);
			UnmapViewOfFile(lp);
			CloseHandle(fm);
			CloseHandle(file);
		}
		return ht;
	}

	HTHANDLE* Open(const char FileName[512])
	{
		HTHANDLE* ht = nullptr;
		HANDLE file = nullptr;
		HANDLE fm = nullptr;
		LPVOID lp = nullptr;
		try
		{
			file = CreateFileA(FileName,
				GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ | FILE_SHARE_WRITE,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
			if (file == INVALID_HANDLE_VALUE)
				throw "Open file error!";
			fm = CreateFileMappingA(file,
				NULL,
				PAGE_READWRITE,
				0, 0, NULL);
			if (!fm)
				throw "Create file mapping error!";
			lp = MapViewOfFile(fm,
				FILE_MAP_ALL_ACCESS,
				0, 0, 0);
			if (!lp)
				throw "View file mapping error!";
			ht = (HTHANDLE*)lp;
			if (GetFileSize(file, NULL) != sizeof(HTHANDLE) + ht->Capacity * (sizeof(Element) + ht->MaxKeyLength + ht->MaxPayloadLength))
				throw "Provided file is not HT structure!";
			ht->File = file;
			ht->FileMapping = fm;
			ht->Addr = lp;
		}
		catch (LPCSTR exception)
		{
			printf("%s\n", exception);
			UnmapViewOfFile(lp);
			CloseHandle(fm);
			CloseHandle(file);
		}
		return ht;
	}

	BOOL Snap(const HTHANDLE* hthandle)
	{
		BOOL b = FALSE;
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
		return b;
	}

	BOOL Close(const HTHANDLE* hthandle)
	{
		BOOL b = TRUE;
		b &= UnmapViewOfFile(hthandle);
		b &= CloseHandle(hthandle->FileMapping);
		b &= CloseHandle(hthandle->File);
		return b;
	}

	BOOL Insert(const HTHANDLE* hthandle, const Element* element)
	{
		BOOL b = FALSE;
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
		return b;
	}

	BOOL Delete(const HTHANDLE* hthandle, const Element* element)
	{
		BOOL b = FALSE;
		try
		{
			Element* elementPtr = Get(hthandle, element);
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
		return b;
	}

	Element* Get(const HTHANDLE* hthandle, const Element* element)
	{
		Element* elementPtr = nullptr;
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
		return elementPtr;
	}

	BOOL Update(const HTHANDLE* hthandle, const Element* oldelement, const void* newpayload, int newpayloadlength)
	{
		BOOL b = FALSE;
		try
		{
			if (newpayloadlength > hthandle->MaxPayloadLength)
				throw "Payload length is greater then maximum payload length!";
			Element* elementPtr = Get(hthandle, oldelement);
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
		return b;
	}

	char* GetLastError(HTHANDLE* ht)
	{
		return ht->LastErrorMessage;
	}

	void Print(const Element* element)
	{
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
}