#include "Getsampleserviceconfig.h"

void ErrorExit(char *ErrMsg)
{
	cout << "Error : " << ErrMsg << endl;
}
void GetSampleServiceConfig(bool run, char *logfile, unsigned int periodic)
{
	while (run)
	{
		for (int i = periodic; i > 0; i--)
		{
			Sleep(1000);
			if (i == 1)
			{
				LPQUERY_SERVICE_CONFIG lpqscBuf;
				LPSERVICE_DESCRIPTION lpqscBuf2;
				DWORD dwBytesNeeded;

				// Открываем дескриптор сервиса.
				SC_HANDLE schSCManager = OpenSCManager(NULL, SERVICES_ACTIVE_DATABASE, SERVICE_QUERY_CONFIG);

				SC_HANDLE schService = OpenService(
					schSCManager,           // база данных SCManager
					"Fax",           // имя сервиса
					SERVICE_QUERY_CONFIG);  // нужно только получить

				if (schService == NULL)
				{
					ErrorExit("OpenService");
					return;
				}

				// Выделяем буфер для информации о настройках сервиса.

				lpqscBuf = (LPQUERY_SERVICE_CONFIG)LocalAlloc(LPTR, 4096);
				if (lpqscBuf == NULL)
				{
					ErrorExit("LocalAlloc");
					return;
				}

				lpqscBuf2 = (LPSERVICE_DESCRIPTION)LocalAlloc(LPTR, 4096);
				if (lpqscBuf2 == NULL)
				{
					ErrorExit("LocalAlloc");
					return;
				}

				// Получаем настройки сервиса.

				if (!QueryServiceConfig(schService, lpqscBuf, 4096, &dwBytesNeeded))
				{
					ErrorExit("QueryServiceConfig");
					return;
				}

				// Распечатываем настройки сервиса.

				ofstream out;
				out.open(logfile, ios::app | ios::out);

				out << "-----------------------------------------------------------------" << endl;
				out << "Sample service configuration."; OutFullData(out); out << " |" << endl;
				out << "-----------------------------------------------------------------" << endl;
				out << " Type: 0x" << lpqscBuf->dwServiceType << endl;
				out << " Launch type: 0x" << lpqscBuf->dwStartType << endl;
				out << " Error control: 0x" << lpqscBuf->dwErrorControl << endl;
				out << " Service path: " << lpqscBuf->lpBinaryPathName << endl;

				if (lpqscBuf->lpLoadOrderGroup != NULL)
					out << " Group: " << lpqscBuf->lpLoadOrderGroup << endl;
				if (lpqscBuf->dwTagId != 0)
					out << " ID in group: " << lpqscBuf->dwTagId << endl;
				if (lpqscBuf->lpDependencies != NULL)
					out << " Dependencies: " << lpqscBuf->lpDependencies << endl;
				if (lpqscBuf->lpServiceStartName != NULL)
					out << " Name: " << lpqscBuf->lpServiceStartName << endl;
				if (lpqscBuf2->lpDescription != NULL)
					out << " Description: " << lpqscBuf2->lpDescription << endl;

				LocalFree(lpqscBuf);
				LocalFree(lpqscBuf2);

				out.close();
			}
		}
		pthread_testcancel();
	}
}