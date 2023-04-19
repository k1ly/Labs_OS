#include <iostream>
#include <Windows.h>

using namespace std;

BOOL PrintFileText(LPWSTR FileName);
BOOL DelRowFileTxt(LPWSTR FileName, DWORD row);

int main()
{
	setlocale(LC_ALL, "ru");
	LPWSTR fileName = (LPWSTR)L"../os09_01.txt";
	PrintFileText(fileName);
	cout << "---------------------------------" << endl;
	DelRowFileTxt(fileName, 1);
	Sleep(50);
	DelRowFileTxt(fileName, 3);
	Sleep(50);
	DelRowFileTxt(fileName, 8);
	Sleep(50);
	DelRowFileTxt(fileName, 10);
	Sleep(50);
	PrintFileText(fileName);
}

BOOL PrintFileText(LPWSTR FileName)
{
	BOOL b = FALSE;
	try
	{
		WIN32_FIND_DATA data;
		HANDLE file = CreateFile(FileName,
			GENERIC_READ | GENERIC_WRITE,
			NULL,
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
		b = true;
	}
	catch (const char* exception)
	{
		cerr << exception << endl;
	}
	return b;
}

BOOL DelRowFileTxt(LPWSTR FileName, DWORD row)
{
	BOOL b = FALSE;
	try
	{
		if (row < 0)
			throw "Invalid row number";
		WIN32_FIND_DATA data;
		HANDLE file = CreateFile(FileName,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (file == INVALID_HANDLE_VALUE)
			throw "Open file error!";
		LARGE_INTEGER fileSize;
		if (!GetFileSizeEx(file, &fileSize))
			throw "File size error!";
		char* inbuf = new char[((PLARGE_INTEGER)(&fileSize))->QuadPart + 1];
		char* outbuf = new char[((PLARGE_INTEGER)(&fileSize))->QuadPart + 1];
		DWORD n = NULL;
		ZeroMemory(inbuf, ((PLARGE_INTEGER)(&fileSize))->QuadPart + 1);
		ZeroMemory(outbuf, ((PLARGE_INTEGER)(&fileSize))->QuadPart + 1);
		if (!ReadFile(file, inbuf, ((PLARGE_INTEGER)(&fileSize))->QuadPart, &n, NULL))
			throw "Read file error!";
		inbuf[((PLARGE_INTEGER)(&fileSize))->QuadPart] = NULL;
		for (int i = 0, j = 0, line = 1; i < ((PLARGE_INTEGER)(&fileSize))->QuadPart + 1; i++)
		{
			if (line != row)
				outbuf[j++] = inbuf[i];
			if (inbuf[i] == '\n')
				line++;
			if (inbuf[i] == NULL)
			{
				outbuf[j] = NULL;
				break;
			}
		}
		SetFilePointer(file, 0, 0, FILE_BEGIN);
		if (!WriteFile(file, outbuf, strlen(outbuf), &n, NULL))
			throw "Write file error!";
		if (!SetEndOfFile(file))
			throw "End of file error!";
		CloseHandle(file);
		b = TRUE;
	}
	catch (const char* exception)
	{
		cerr << exception << endl;
	}
	return b;
}