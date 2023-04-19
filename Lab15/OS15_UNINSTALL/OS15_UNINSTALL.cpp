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
		schService = OpenServiceA(
			schSCManager,
			SERVICENAME,
			SERVICE_ALL_ACCESS);
		if (!schService)
			throw "Error: OpenService";
		if (!DeleteService(schService))
			throw "Error: DeleteService";
	}
	catch (LPCSTR msg)
	{
		cout << msg << ", error code = " << GetLastError() << endl;
		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		system("pause");
	}
}