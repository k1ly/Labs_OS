#pragma once
#include <Windows.h>
#include <fstream>

#define SERVICENAME "OS15_HTService"
#define TRACEPATH "C:\\Users\\Kirill\\Documents\\Labs\\OS\\Lab15\\x64\\Debug\\service.trace"

VOID WINAPI ServiceMain(DWORD dwArgc, LPSTR* lpszArgv);
VOID WINAPI ServiceHandler(DWORD fdwControl);

void trace(const char* msg, int mode = std::ofstream::app);