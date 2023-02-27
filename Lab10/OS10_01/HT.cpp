#include "HT.h"
#include <time.h>
#include <iostream>

namespace HT
{
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
			DWORD HTSize = sizeof(HTHANDLE) + Capacity * (sizeof(Element) + MaxKeyLength + MaxPayloadLength);
			file = CreateFileA(FileName,
				GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ | FILE_SHARE_WRITE,
				NULL,
				OPEN_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
			if (file == INVALID_HANDLE_VALUE)
				throw "Open file error!";
			fm = CreateFileMappingA(file,
				NULL,
				PAGE_READWRITE,
				0, HTSize, NULL);
			if (!fm)
				throw "Create file mapping error!";
			lp = MapViewOfFile(fm,
				FILE_MAP_ALL_ACCESS,
				0, 0, HTSize);
			if (!lp)
				throw "View file mapping error!";
			ht = new(lp) HTHANDLE(Capacity, SecSnapshotInterval, MaxKeyLength, MaxPayloadLength, FileName);
			ht->File = file;
			ht->FileMapping = fm;
			ht->Addr = (LPVOID)((LONG_PTR)lp + sizeof(HTHANDLE));
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
				OPEN_ALWAYS,
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
			ht->File = file;
			ht->FileMapping = fm;
			ht->Addr = (LPVOID)((LONG_PTR)lp + sizeof(HTHANDLE));
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
			DWORD HTSize = sizeof(HTHANDLE) + hthandle->Capacity * (sizeof(Element) + hthandle->MaxKeyLength + hthandle->MaxPayloadLength);
			if (!FlushViewOfFile(hthandle, HTSize))
				throw "Flush file mapping error!";
			time((time_t*)&hthandle->LastSnapTime);
			tm tm_info;
			localtime_s(&tm_info, &hthandle->LastSnapTime);
			CHAR date[50];
			strftime(date, 50, "%Y-%m-%d_%H-%M-%S", &tm_info);
			SIZE_T index = 0;
			for (SIZE_T i = 0; i < strlen(hthandle->FileName); i++)
				if (hthandle->FileName[i] == '\\')
					index = i + 1;
			LPSTR fileName = new CHAR[strlen(hthandle->FileName) + sizeof(date)];
			memcpy(fileName, hthandle->FileName, index);
			memcpy(fileName + index, date, strlen(date));
			memcpy(fileName + index + strlen(date), hthandle->FileName + index, strlen(hthandle->FileName) + 1 - index);
			HANDLE file = CreateFileA(fileName,
				GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ | FILE_SHARE_WRITE,
				NULL,
				OPEN_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
			delete[] fileName;
			if (file == INVALID_HANDLE_VALUE)
				throw "Open file error!";
			WriteFile(file, hthandle, HTSize, NULL, NULL);
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
		BOOL b = FALSE;
		if (CloseHandle(hthandle->FileMapping) &&
			CloseHandle(hthandle->File) &&
			UnmapViewOfFile(hthandle))
			b = TRUE;
		return b;
	}

	BOOL Insert(const HTHANDLE* hthandle, const Element* element)
	{
		BOOL b = FALSE;
		try
		{
			if (hthandle->Size >= hthandle->Capacity)
				throw "Maximum capacity storage size reached!";
			if (element->keylength >= hthandle->MaxKeyLength)
				throw "Key length is greater then maximum key length!";
			if (element->payloadlength >= hthandle->MaxPayloadLength)
				throw "Payload length is greater then maximum payload length!";
			Element* elementPtr = (Element*)((LONG_PTR)hthandle->Addr + hthandle->Size * (sizeof(Element) + hthandle->MaxKeyLength + hthandle->MaxPayloadLength));
			elementPtr->key = (LPVOID)((LONG_PTR)elementPtr + sizeof(Element));
			elementPtr->keylength = element->keylength;
			elementPtr->payload = (LPVOID)((LONG_PTR)elementPtr + sizeof(Element) + hthandle->MaxKeyLength);
			elementPtr->payloadlength = element->payloadlength;
			memcpy((LPVOID)elementPtr->key, element->key, element->keylength);
			memcpy((LPVOID)elementPtr->payload, element->payload, element->payloadlength);
			((HTHANDLE*)hthandle)->Size++;
			b = TRUE;
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
			if (elementPtr == nullptr)
				throw "Element not found";
			memset(elementPtr, 0, (sizeof(Element) + hthandle->MaxKeyLength + hthandle->MaxPayloadLength));
			for (SIZE_T i = ((LONG_PTR)elementPtr - (LONG_PTR)hthandle->Addr) / (sizeof(Element) + hthandle->MaxKeyLength + hthandle->MaxPayloadLength);
				i < hthandle->Size; i++)
			{
				Element* current = (Element*)((LONG_PTR)hthandle->Addr + i * (sizeof(Element) + hthandle->MaxKeyLength + hthandle->MaxPayloadLength));
				if (i == hthandle->Size - 1)
				{
					memset(current, 0, (sizeof(Element) + hthandle->MaxKeyLength + hthandle->MaxPayloadLength));
					((HTHANDLE*)hthandle)->Size--;
					break;
				}
				Element* next = (Element*)((LONG_PTR)current + (sizeof(Element) + hthandle->MaxKeyLength + hthandle->MaxPayloadLength));
				memcpy(current, next, (sizeof(Element) + hthandle->MaxKeyLength + hthandle->MaxPayloadLength));
			}
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
			for (SIZE_T i = 0; i < hthandle->Size; i++)
			{
				Element* current = (Element*)((LONG_PTR)hthandle->Addr + i * (sizeof(Element) + hthandle->MaxKeyLength + hthandle->MaxPayloadLength));
				current->key = (LPVOID)((LONG_PTR)current + sizeof(Element));
				current->payload = (LPVOID)((LONG_PTR)current + sizeof(Element) + hthandle->MaxKeyLength);
				if (current->keylength == element->keylength &&
					strcmp((LPCSTR)current->key, (LPSTR)element->key) == 0)
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
			if (newpayloadlength >= hthandle->MaxPayloadLength)
				throw "Payload length is greater then maximum payload length!";
			Element* elementPtr = Get(hthandle, oldelement);
			if (elementPtr == nullptr)
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
			printf_s("Element = {%s: %s}\n", (LPSTR)element->key, (LPSTR)element->payload);
	}
}