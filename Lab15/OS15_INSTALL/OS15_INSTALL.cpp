#include <iostream>
#include <Windows.h>

#define SERVICENAME "OS15_HTService"

using namespace std;

int main()
{
	SC_HANDLE schService = NULL, schSCManager = NULL;
	try
	{
		schSCManager = OpenSCManagerA(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
		if (!schSCManager)
			throw "Error: OpenSCManager";
		schService = CreateServiceA(
			schSCManager,
			SERVICENAME,
			SERVICENAME,
			SERVICE_ALL_ACCESS,
			SERVICE_WIN32_OWN_PROCESS,
			SERVICE_AUTO_START,
			SERVICE_ERROR_NORMAL,
			"C:\\Users\\Kirill\\Documents\\Labs\\OS\\Lab15\\x64\\Debug\\OS15_SERVICE.exe",
			NULL, NULL, NULL, NULL, NULL);
		if (!schService)
			throw "Error: CreateService";
	}
	catch (LPCSTR msg)
	{
		cout << msg << ", error code = " << GetLastError() << endl;
		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		system("pause");
	}
}