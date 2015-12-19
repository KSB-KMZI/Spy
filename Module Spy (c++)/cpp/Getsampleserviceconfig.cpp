#include "Getsampleserviceconfig.h"

void ErrorExit(char *ErrMsg, ofstream &out)
{
	out << "Error : " << ErrMsg << endl;
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
				ofstream out;
				map <int, string> srv = GetServiceList();

				out.open(logfile, ios::app | ios::out);
				HideFile(logfile);

				for (int i = 0; i < srv.size(); i++)
					WriteService(out, srv[i].c_str());

				out << "\n--------------------------------------------------------------------------------------------------------------------------------\n";

				out.close();
			}
		}
		pthread_testcancel();
	}
}
map <int, string> GetServiceList()
{
	map<int, string> lstResult;
	SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE);
	if (hSCM == NULL)
	{
		return lstResult;
	}
	BYTE bBuffer[2048] = { 0 };
	DWORD dwResumeHandle = 0;
	DWORD cbNeeded;
	DWORD cServices;
	BOOL bContinue;
	DWORD dwError;
	LPENUM_SERVICE_STATUS pStatus;
	do
	{
		bContinue = FALSE;
		pStatus = (LPENUM_SERVICE_STATUS)bBuffer;
		
		if (!EnumServicesStatus(hSCM, SERVICE_WIN32, SERVICE_STATE_ALL, pStatus, sizeof(bBuffer), &cbNeeded, &cServices, &dwResumeHandle))
		{
			dwError = GetLastError();
			if (dwError != ERROR_MORE_DATA)
				break;
			bContinue = TRUE;
		}
		for (DWORD i = 0; i < cServices; i++)
		{
			lstResult[i] = pStatus->lpServiceName;

			pStatus++;
		}
	} while (bContinue);
	CloseServiceHandle(hSCM);

	return lstResult;
}
void WriteService(ofstream &out, const char *servicename)
{
	LPQUERY_SERVICE_CONFIG lpqscBuf;
	LPSERVICE_DESCRIPTION lpqscBuf2;
	DWORD dwBytesNeeded;

	// Открываем дескриптор сервиса.
	SC_HANDLE schSCManager = OpenSCManager(NULL, SERVICES_ACTIVE_DATABASE, SERVICE_QUERY_CONFIG);

	SC_HANDLE schService = OpenService(
		schSCManager,           // база данных SCManager
		servicename,           // имя сервиса
		SERVICE_QUERY_CONFIG);  // нужно только получить

	if (schService == NULL)
	{
		ErrorExit("OpenService", out);
		return;
	}

	// Выделяем буфер для информации о настройках сервиса.

	lpqscBuf = (LPQUERY_SERVICE_CONFIG)LocalAlloc(LPTR, 4096);
	if (lpqscBuf == NULL)
	{
		ErrorExit("LocalAlloc", out);
		return;
	}

	lpqscBuf2 = (LPSERVICE_DESCRIPTION)LocalAlloc(LPTR, 4096);
	if (lpqscBuf2 == NULL)
	{
		ErrorExit("LocalAlloc", out);
		return;
	}

	// Получаем настройки сервиса.

	if (!QueryServiceConfig(schService, lpqscBuf, 4096, &dwBytesNeeded))
	{
		ErrorExit("QueryServiceConfig", out);
		return;
	}

	out << "-----------------------------------------------------------------" << endl;
	out << "Service: " << servicename << ". Inforamtion."; OutFullData(out); out << " |" << endl;
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
}