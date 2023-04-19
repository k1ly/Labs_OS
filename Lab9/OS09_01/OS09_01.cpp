#include <iostream>
#include <Windows.h>

using namespace std;

BOOL PrintFileInfo(LPWSTR FileName);
BOOL PrintFileText(LPWSTR FileName);

int main()
{
	setlocale(LC_ALL, "ru");
	LPWSTR fileName = (LPWSTR)L"../os09_01.txt";
	PrintFileInfo(fileName);
	cout << "---------------------------------" << endl;
	PrintFileText(fileName);
}

BOOL PrintFileInfo(LPWSTR FileName)
{
	BOOL b = FALSE;
	try
	{
		HANDLE file = CreateFile(FileName,
			GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (file == INVALID_HANDLE_VALUE)
			throw "Open file error!";
		const char* typeName = NULL;
		switch (GetFileType(file))
		{
		case FILE_TYPE_CHAR:typeName = "FILE_TYPE_CHAR"; break;
		case FILE_TYPE_DISK:typeName = "FILE_TYPE_DISK"; break;
		case FILE_TYPE_PIPE:typeName = "FILE_TYPE_PIPE"; break;
		case FILE_TYPE_UNKNOWN:typeName = "FILE_TYPE_UNKNOWN"; break;
		case FILE_TYPE_REMOTE:typeName = "FILE_TYPE_REMOTE"; break;
		}
		WIN32_FIND_DATA data;
		file = FindFirstFile(FileName, &data);
		FILETIME creationFileTime;
		FILETIME lastWriteFileTime;
		FileTimeToLocalFileTime(&data.ftCreationTime, &creationFileTime);
		FileTimeToLocalFileTime(&data.ftLastWriteTime, &lastWriteFileTime);
		_SYSTEMTIME creationTime;
		_SYSTEMTIME  lastWriteTime;
		FileTimeToSystemTime(&creationFileTime, &creationTime);
		FileTimeToSystemTime(&lastWriteFileTime, &lastWriteTime);
		cout << "Имя: "; wcout << data.cFileName << endl;
		cout << "Тип: " << typeName << endl;
		cout << "Размер: "; if (data.nFileSizeHigh > 0) cout << data.nFileSizeHigh; cout << data.nFileSizeLow << endl;
		cout << "Дата создания: " << creationTime.wDay << "." << creationTime.wMonth << "." << creationTime.wYear << " "
			<< creationTime.wHour << ":" << creationTime.wMinute << ":" << creationTime.wSecond << endl;
		cout << "Дата изменения: " << lastWriteTime.wDay << "." << lastWriteTime.wMonth << "." << lastWriteTime.wYear << " "
			<< lastWriteTime.wHour << ":" << lastWriteTime.wMinute << ":" << lastWriteTime.wSecond << endl;
		CloseHandle(file);
		b = TRUE;
	}
	catch (const char* exception)
	{
		cerr << exception << endl;
	}
	return b;
}

BOOL PrintFileText(LPWSTR FileName)
{
	BOOL b = FALSE;
	try
	{
		WIN32_FIND_DATA data;
		HANDLE file = CreateFile(FileName,
			GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (file == INVALID_HANDLE_VALUE)
			throw "Open file error!";
		char buf[1024];
		DWORD n = NULL;
		while (true)
		{
			ZeroMemory(buf, sizeof(buf));
			if (!ReadFile(file, &buf, sizeof(buf), &n, NULL))
				throw "Read file error!";
			if (n == 0)
				break;
			cout << buf << endl;
		}
		CloseHandle(file);
		b = TRUE;
	}
	catch (const char* exception)
	{
		cerr << exception << endl;
	}
	return b;
}