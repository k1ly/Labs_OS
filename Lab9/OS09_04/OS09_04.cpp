#include <iostream>
#include <Windows.h>

using namespace std;

BOOL PrintWatchRowFileTxt(LPWSTR FileName, DWORD mlsec);

int main()
{
	setlocale(LC_ALL, "ru");
	LPWSTR fileName = (LPWSTR)L"../os09_01.txt";
	PrintWatchRowFileTxt(fileName, 600 * 1000);
}

BOOL PrintWatchRowFileTxt(LPWSTR FileName, DWORD mlsec)
{
	BOOL b = FALSE;
	try
	{
		if (mlsec < 0)
			throw "Invalid millisecond number";
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
		wchar_t path[MAX_PATH];
		GetFinalPathNameByHandle(file, path, MAX_PATH, VOLUME_NAME_DOS);
		CloseHandle(file);
		auto getFileRowCount = [](LPWSTR FileName)
		{
			int rowCount = 0;
			HANDLE file = NULL;
			try
			{
				Sleep(10);
				file = CreateFile(FileName,
					GENERIC_READ,
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
				char* buf = new char[((PLARGE_INTEGER)(&fileSize))->QuadPart + 1];
				DWORD n = NULL;
				ZeroMemory(buf, ((PLARGE_INTEGER)(&fileSize))->QuadPart + 1);
				if (!ReadFile(file, buf, ((PLARGE_INTEGER)(&fileSize))->QuadPart, &n, NULL))
					throw "Read file error!";
				buf[((PLARGE_INTEGER)(&fileSize))->QuadPart] = NULL;
				if (strlen(buf) > 0)
					rowCount = 1;
				for (int i = 0; i < ((PLARGE_INTEGER)(&fileSize))->QuadPart + 1; i++)
				{
					if (buf[i] == '\n')
						rowCount++;
					if (buf[i] == NULL)
						break;
				}
				CloseHandle(file);
			}
			catch (const char* exception)
			{
				cerr << exception << endl;
				if (file != NULL)
					CloseHandle(file);
			}
			return rowCount;
		};
		int fileState = getFileRowCount(FileName);
		wchar_t fdir[_MAX_PATH];
		_wsplitpath_s(path, NULL, 0, fdir, _MAX_PATH, NULL, 0, NULL, 0);
		cout << "Путь к каталогу: "; wcout << fdir << endl;
		HANDLE changeNotif = FindFirstChangeNotification(fdir, FALSE, FILE_NOTIFY_CHANGE_SIZE);
		if (changeNotif == NULL)
			throw "Directory change notification error!";
		clock_t start = clock();
		while (true)
		{
			cout << "Наблюдение за каталогом ..." << endl;
			if (WaitForSingleObject(changeNotif, mlsec) == WAIT_OBJECT_0)
			{
				if (FindNextChangeNotification(changeNotif) == FALSE)
					break;
				else
				{
					int rowCount = getFileRowCount(FileName);
					if (rowCount == 0)
					{
						cout << "Ошибка подсчета строк файла!" << endl;
						break;
					}
					if (fileState < rowCount)
						cout << "Количество строк в файле увеличилось на " << (rowCount - fileState) << endl;
					if (fileState > rowCount)
						cout << "Количество строк в файле уменьшилось на " << (fileState - rowCount) << endl;
					fileState = rowCount;
					cout << "Всего строк: " << fileState << endl;
				}
			}
			if (clock() - start > mlsec)
				break;
		}
		CloseHandle(changeNotif);
		b = TRUE;
	}
	catch (const char* exception)
	{
		cerr << exception << endl;
	}
	return b;
}