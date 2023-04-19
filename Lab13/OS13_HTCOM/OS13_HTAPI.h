#pragma once
#include <objbase.h>

#define FNAME L"OS13.COM"
#define VINDX L"OS13.1"
#define PRGID L"OS13"

// {85B8159B-26D4-499F-81BF-202EBC09F879}
static const GUID CLSID_OS13 =
{ 0x85b8159b, 0x26d4, 0x499f, { 0x81, 0xbf, 0x20, 0x2e, 0xbc, 0x9, 0xf8, 0x79 } };

// {0A6409DC-771E-4D46-8525-18CA35DAA14F}
static const GUID IID_HTAPI =
{ 0xa6409dc, 0x771e, 0x4d46, { 0x85, 0x25, 0x18, 0xca, 0x35, 0xda, 0xa1, 0x4f } };

struct HTHANDLE    // блок управления HT
{
	HTHANDLE();
	HTHANDLE(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const char FileName[512]);
	int     Capacity;               // емкость хранилища в количестве элементов 
	int     Size;               // размер хранилища в количестве элементов 
	int     SecSnapshotInterval;    // переодичность сохранения в сек. 
	int     MaxKeyLength;           // максимальная длина ключа
	int     MaxPayloadLength;       // максимальная длина данных
	char    FileName[512];          // имя файла 
	HANDLE  File;                   // File HANDLE != 0, если файл открыт
	HANDLE  FileMapping;            // Mapping File HANDLE != 0, если mapping создан  
	LPVOID  Addr;                   // Addr != NULL, если mapview выполнен  
	char    LastErrorMessage[512];  // сообщение об последней ошибке или 0x00  
	time_t  LastSnapTime;           // дата последнего snap'a (time())  
	HANDLE	SnapThread;
	HANDLE	Mutex;
};

struct Element   // элемент 
{
	Element();
	Element(const void* key, int keylength);                                             // for Get
	Element(const void* key, int keylength, const void* payload, int  payloadlength);    // for Insert
	Element(Element* oldelement, const void* newpayload, int  newpayloadlength);         // for update
	const void* key;                 // значение ключа 
	int		keylength;           // рахмер ключа
	const void* payload;             // данные 
	int		payloadlength;       // размер данных
};

interface HTAPI : IUnknown
{
	virtual	HRESULT STDMETHODCALLTYPE NewElement(Element*& ret) = 0;
	virtual	HRESULT STDMETHODCALLTYPE NewElement(const void* key, int keylength, Element*& ret) = 0;
	virtual	HRESULT STDMETHODCALLTYPE NewElement(const void* key, int keylength, const void* payload, int payloadlength, Element*& ret) = 0;
	virtual	HRESULT STDMETHODCALLTYPE NewElement(Element* oldelement, const void* newpayload, int newpayloadlength, Element*& ret) = 0;
	virtual	HRESULT STDMETHODCALLTYPE Create(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const char FileName[512], HTHANDLE*& ret) = 0;
	virtual	HRESULT STDMETHODCALLTYPE Open(const char FileName[512], HTHANDLE*& ret) = 0;
	virtual	HRESULT STDMETHODCALLTYPE OpenExisting(const char FileName[512], HTHANDLE*& ret) = 0;
	virtual	HRESULT STDMETHODCALLTYPE Snap(const HTHANDLE* hthandle, BOOL& ret) = 0;
	virtual	HRESULT STDMETHODCALLTYPE Close(const HTHANDLE* hthandle, BOOL& ret) = 0;
	virtual	HRESULT STDMETHODCALLTYPE Insert(const HTHANDLE* hthandle, const Element* element, BOOL& ret) = 0;
	virtual	HRESULT STDMETHODCALLTYPE Delete(const HTHANDLE* hthandle, const Element* element, BOOL& ret) = 0;
	virtual	HRESULT STDMETHODCALLTYPE Get(const HTHANDLE* hthandle, const Element* element, Element*& ret) = 0;
	virtual	HRESULT STDMETHODCALLTYPE Update(const HTHANDLE* hthandle, const Element* oldelement, const void* newpayload, int newpayloadlength, BOOL& ret) = 0;
	virtual	HRESULT STDMETHODCALLTYPE GetLastErrorMessage(HTHANDLE* ht, char*& ret) = 0;
	virtual	HRESULT STDMETHODCALLTYPE Print(const Element* element) = 0;
};
