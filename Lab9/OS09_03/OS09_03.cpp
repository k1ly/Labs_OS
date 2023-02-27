#include <iostream>
#include <Windows.h>

using namespace std;

BOOL PrintFileText(LPWSTR FileName);
BOOL InsRowFileTxt(LPWSTR FileName, LPWSTR str, DWORD row);

int main()
{
	setlocale(LC_ALL, "ru");
	LPWSTR fileName = (LPWSTR)L"../os09_01.txt";
	PrintFileText(fileName);
	cout << "---------------------------------" << endl;
	InsRowFileTxt(fileName, (wchar_t*)L"New line 0", 0);
	Sleep(50);
	InsRowFileTxt(fileName, (wchar_t*)L"New line -1", -1);
	Sleep(50);
	InsRowFileTxt(fileName, (wchar_t*)L"New line 5", 5);
	Sleep(50);
	InsRowFileTxt(fileName, (wchar_t*)L"New line 7", 7);
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

BOOL InsRowFileTxt(LPWSTR FileName, LPWSTR str, DWORD row)
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
		char* outbuf = new char[((PLARGE_INTEGER)(&fileSize))->QuadPart * 2 + 1];
		DWORD n = NULL;
		ZeroMemory(inbuf, ((PLARGE_INTEGER)(&fileSize))->QuadPart + 1);
		ZeroMemory(outbuf, ((PLARGE_INTEGER)(&fileSize))->QuadPart * 2 + 1);
		if (!ReadFile(file, inbuf, ((PLARGE_INTEGER)(&fileSize))->QuadPart, &n, NULL))
			throw "Read file error!";
		inbuf[((PLARGE_INTEGER)(&fileSize))->QuadPart] = NULL;
		for (int i = 0, j = 0, line = 1; i < ((PLARGE_INTEGER)(&fileSize))->QuadPart + 1; i++)
		{
			if (inbuf[i] == '\n') {
				line++;
				if (line == row)
					outbuf[j++] = inbuf[i++];
			}
			if (line == row || (line == 1 && row == 0) || (inbuf[i] == NULL && ((signed)row) < 0))
			{
				if (inbuf[i] == NULL && ((signed)row) < 0) {
					outbuf[j++] = '\r';
					outbuf[j++] = '\n';
				}
				char* cstr = new char(wcslen(str));
				size_t length;
				wcstombs_s(&length, cstr, wcslen(str) * sizeof(wchar_t), str, wcslen(str) * sizeof(wchar_t));
				strcpy_s(&outbuf[j], length, cstr);
				j += strlen(cstr);
				if ((line == row) || (line == 1 && row == 0)) {
					outbuf[j++] = '\r';
					outbuf[j++] = '\n';
					line++;
				}
			}
			outbuf[j++] = inbuf[i];
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