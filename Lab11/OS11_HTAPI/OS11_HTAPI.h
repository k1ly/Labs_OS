#pragma once
#include <Windows.h>

#ifdef OS11HTAPI_EXPORTS
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT __declspec(dllimport)
#endif

namespace HT    // HT API
{
	// API HT - ����������� ��������� ��� ������� � ��-��������� 
	//          ��-��������� ������������� ��� �������� ������ � �� � ������� ����/��������
	//          ���������������� (�����������) ������ �������������� � ������� snapshot-���������� 
	//          Create - �������  � ������� HT-��������� ��� �������������   
	//          Open   - ������� HT-��������� ��� �������������
	//          Insert - ������� ������� ������
	//          Delete - ������� ������� ������    
	//          Get    - ������  ������� ������
	//          Update - �������� ������� ������
	//          Snap   - �������� snapshot
	//          Close  - ��������� Snap � ������� HT-��������� ��� �������������
	//          GetLastError - �������� ��������� � ��������� ������


	struct HTHANDLE    // ���� ���������� HT
	{
		HTHANDLE();
		HTHANDLE(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const char FileName[512]);
		int     Capacity;               // ������� ��������� � ���������� ��������� 
		int     Size;               // ������ ��������� � ���������� ��������� 
		int     SecSnapshotInterval;    // ������������� ���������� � ���. 
		int     MaxKeyLength;           // ������������ ����� �����
		int     MaxPayloadLength;       // ������������ ����� ������
		char    FileName[512];          // ��� ����� 
		HANDLE  File;                   // File HANDLE != 0, ���� ���� ������
		HANDLE  FileMapping;            // Mapping File HANDLE != 0, ���� mapping ������  
		LPVOID  Addr;                   // Addr != NULL, ���� mapview ��������  
		char    LastErrorMessage[512];  // ��������� �� ��������� ������ ��� 0x00  
		time_t  LastSnapTime;           // ���� ���������� snap'a (time())  
		HANDLE	SnapThread;
		HANDLE	Mutex;
	};

	struct Element   // ������� 
	{
		Element();
		Element(const void* key, int keylength);                                             // for Get
		Element(const void* key, int keylength, const void* payload, int  payloadlength);    // for Insert
		Element(Element* oldelement, const void* newpayload, int  newpayloadlength);         // for update
		const void* key;                 // �������� ����� 
		int		keylength;           // ������ �����
		const void* payload;             // ������ 
		int		payloadlength;       // ������ ������
	};

	extern "C" DLLEXPORT Element * NewElement();

	extern "C" DLLEXPORT Element * NewElementGet(const void* key, int keylength);

	extern "C" DLLEXPORT Element * NewElementInsert(const void* key, int keylength, const void* payload, int  payloadlength);

	extern "C" DLLEXPORT Element * NewElementUpdate(Element * oldelement, const void* newpayload, int  newpayloadlength);

	extern "C" DLLEXPORT HTHANDLE * Create   //  ������� HT             
	(
		int	  Capacity,					   // ������� ���������
		int   SecSnapshotInterval,		   // ������������� ���������� � ���.
		int   MaxKeyLength,                // ������������ ������ �����
		int   MaxPayloadLength,            // ������������ ������ ������
		const char  FileName[512]          // ��� ����� 
	); 	// != NULL �������� ����������  

	extern "C" DLLEXPORT HTHANDLE * Open     //  ������� HT             
	(
		const char    FileName[512]         // ��� ����� 
	); 	// != NULL �������� ����������  

	extern "C" DLLEXPORT HTHANDLE * OpenExisting   //  ������� ������������ HT  
	(
		const char    FileName[512]         // ��� ����� 
	); 	// != NULL �������� ����������

	extern "C" DLLEXPORT BOOL Snap         // ��������� Snapshot
	(
		const HTHANDLE * hthandle           // ���������� HT (File, FileMapping)
	);

	extern "C" DLLEXPORT BOOL Close        // Snap � ������� HT  �  �������� HTHANDLE
	(
		const HTHANDLE * hthandle           // ���������� HT (File, FileMapping)
	);	//  == TRUE �������� ����������   

	extern "C" DLLEXPORT BOOL Insert      // �������� ������� � ���������
	(
		const HTHANDLE * hthandle,            // ���������� HT
		const Element * element              // �������
	);	//  == TRUE �������� ���������� 

	extern "C" DLLEXPORT BOOL Delete      // ������� ������� � ���������
	(
		const HTHANDLE * hthandle,            // ���������� HT (����)
		const Element * element              // ������� 
	);	//  == TRUE �������� ���������� 

	extern "C" DLLEXPORT Element * Get     //  ������ ������� � ���������
	(
		const HTHANDLE * hthandle,            // ���������� HT
		const Element * element              // ������� 
	); 	//  != NULL �������� ���������� 

	extern "C" DLLEXPORT BOOL Update     //  ������� ������� � ���������
	(
		const HTHANDLE * hthandle,            // ���������� HT
		const Element * oldelement,          // ������ ������� (����, ������ �����)
		const void* newpayload,          // ����� ������  
		int             newpayloadlength     // ������ ����� ������
	); 	//  != NULL �������� ���������� 

	extern "C" DLLEXPORT char* GetLastErrorMessage  // �������� ��������� � ��������� ������
	(
		HTHANDLE * ht                         // ���������� HT
	);

	extern "C" DLLEXPORT void Print                               // ����������� ������� 
	(
		const Element * element              // ������� 
	);
};
