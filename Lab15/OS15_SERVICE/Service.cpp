#include "SERVICE.h"

SERVICE_STATUS ServiceStatus;
SERVICE_STATUS_HANDLE hServiceStatus;

void trace(const char* msg, int mode)
{
	std::ofstream out;
	out.open(TRACEPATH, mode);
	out << msg << std::endl;
	out.close();
}

VOID WINAPI ServiceMain(DWORD dwArgc, LPSTR* lpszArgv)
{
	ServiceStatus.dwServiceType = SERVICE_WIN32;
	ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
	ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN | SERVICE_ACCEPT_PAUSE_CONTINUE;
	ServiceStatus.dwWin32ExitCode = 0;
	ServiceStatus.dwServiceSpecificExitCode = 0;
	ServiceStatus.dwCheckPoint = 0;
	ServiceStatus.dwWaitHint = 0;
	char temp[100];
	if (!(hServiceStatus = RegisterServiceCtrlHandlerA(SERVICENAME, ServiceHandler)))
	{
		sprintf_s(temp, "RegisterServiceCtrlHandler failed, error code = %d", GetLastError());
		trace(temp);
	}
	else
	{
		ServiceStatus.dwCurrentState = SERVICE_RUNNING;
		ServiceStatus.dwCheckPoint = 0;
		ServiceStatus.dwWaitHint = 0;
		if (!SetServiceStatus(hServiceStatus, &ServiceStatus))
		{
			sprintf_s(temp, "SetServiceStatus failed, error code = %d", GetLastError());
			trace(temp);
		}
		else
		{
			trace("Start service", std::ofstream::out);
			STARTUPINFOA si;
			PROCESS_INFORMATION pi;
			ZeroMemory(&pi, sizeof(pi));
			ZeroMemory(&si, sizeof(si));
			si.cb = sizeof(si);
			if (!CreateProcessA("C:\\Users\\Kirill\\Documents\\Labs\\OS\\Lab14\\x64\\Debug\\OS14_START.exe",
				(LPSTR)"OS14_START.exe HTUser01 12345 C:\\Users\\Kirill\\Documents\\Labs\\OS\\Lab14\\x64\\Debug\\HT.ht",
				NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
			{
				sprintf_s(temp, "CreateProcess OS14_START.exe failed, error code = %d", GetLastError());
				trace(temp);
			}
			WaitForSingleObject(pi.hProcess, INFINITE);
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
		}
	}
}

VOID WINAPI ServiceHandler(DWORD fdwControl)
{
	char temp[100];
	switch (fdwControl)
	{
	case SERVICE_CONTROL_STOP:
	case SERVICE_CONTROL_SHUTDOWN:
		STARTUPINFOA si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&pi, sizeof(pi));
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		if (!CreateProcessA("C:\\Users\\Kirill\\Documents\\Labs\\OS\\Lab14\\x64\\Debug\\OS14_STOP.exe",
			(LPSTR)"OS14_STOP.exe C:\\Users\\Kirill\\Documents\\Labs\\OS\\Lab14\\x64\\Debug\\HT.ht",
			NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
		{
			sprintf_s(temp, "CreateProcess OS14_STOP.exe failed, error code = %d", GetLastError());
			trace(temp);
		}
		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		ServiceStatus.dwWin32ExitCode = 0;
		ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		ServiceStatus.dwCheckPoint = 0;
		ServiceStatus.dwWaitHint = 0;
		break;
	case SERVICE_CONTROL_PAUSE:
		ServiceStatus.dwCurrentState = SERVICE_PAUSED;
		break;
	case SERVICE_CONTROL_CONTINUE:
		ServiceStatus.dwCurrentState = SERVICE_CONTROL_CONTINUE;
		break;
	case SERVICE_CONTROL_INTERROGATE:
		break;
	default:
		sprintf_s(temp, "Unrecognized control command %d", fdwControl);
		trace(temp);
	}
	if (!SetServiceStatus(hServiceStatus, &ServiceStatus))
	{
		sprintf_s(temp, "SetServiceStatus failed, error code = %d", GetLastError());
		trace(temp);
	}
}