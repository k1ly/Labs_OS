#pragma once
#include <objbase.h>

#define FNAME L"OS14.COM"
#define VINDX L"OS14.1"
#define PRGID L"OS14"

// {4A70BBA3-F0BE-464E-92D9-A30332824833}
static const GUID CLSID_OS14 =
{ 0x4a70bba3, 0xf0be, 0x464e, { 0x92, 0xd9, 0xa3, 0x3, 0x32, 0x82, 0x48, 0x33 } };

// {835DB0DD-4EEC-4251-A55D-FB437057E6D9}
static const GUID IID_HTAPI =
{ 0x835db0dd, 0x4eec, 0x4251, { 0xa5, 0x5d, 0xfb, 0x43, 0x70, 0x57, 0xe6, 0xd9 } };


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
	char	HTUsersGroup[512];
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
	virtual	HRESULT STDMETHODCALLTYPE Create(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const char HTUsersGroup[512], const char FileName[512], HTHANDLE*& ret) = 0;
	virtual	HRESULT STDMETHODCALLTYPE Open(const char FileName[512], HTHANDLE*& ret) = 0;
	virtual	HRESULT STDMETHODCALLTYPE Open(const char HTUser[256], const char HTPassword[256], const char FileName[512], HTHANDLE*& ret) = 0;
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
