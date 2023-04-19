#include <iostream>
#include "SERVICE.h"

int main()
{
	SERVICE_TABLE_ENTRYA ServiceStartTable[] = { {(LPSTR)SERVICENAME,ServiceMain},{NULL,NULL} };
	if (!StartServiceCtrlDispatcherA(ServiceStartTable))
		trace("StartServiceCtrlDispatcher", std::ofstream::out);
}