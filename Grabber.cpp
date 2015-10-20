#pragma warning(disable : 4996)
#pragma comment(lib,"wsock32.lib")
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <tchar.h>
#include <TlHelp32.h>
#include <pthread.h>
using namespace std;

#define BUFSIZE 1024

void HardWareInfo(void);
void SystemInfo(void);
void GetSampleServiceConfig(void);
void ErrorExit(char *ErrMsg);
void GetCompIP(void);
void EnumerateSerialPorts(void);
void ScanProcess(void);
void * GetInstruction(void *p);

int instr;

void main(void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	instr = 0x00;
	//pthread_t Instruction;
	//pthread_create(&Instruction, NULL, GetInstruction, NULL);


//	HardWareInfo();
//  GetSampleServiceConfig();
//	SystemInfo();
//	cout << endl;
//	GetCompIP();
//	cout << endl;
//	EnumerateSerialPorts();
//	cout << endl;
//	ScanProcess();

	system("pause");
}
void * GetInstruction(void *p)
{
	ifstream file;
	FILE *fp;
	while (true)
	{
		fp = fopen("Instruction.txt", "r");
		if (fp != NULL)
		{
			file.open("Instruction.txt", ios::in);
			file >> instr;
			file.close();
		}
	}
	return NULL;
}
void SystemInfo(void)
{
	LPTSTR lpszSystemInfo;      // указатель на строку, в которой
								// будет информация о системе.
	DWORD cchBuff = 256;        // длина имени компьютера или
								// пользователя.
	TCHAR tchBuffer[BUFSIZE];   // буфер для строки.

	DWORD dwResult;             // возвращаемое значение функции.

	lpszSystemInfo = tchBuffer;

	// Получаем и отображаем имя компьютера.

	if (GetComputerName(lpszSystemInfo, &cchBuff))
		cout << "Computer name: " << lpszSystemInfo << endl;

	// Получаем и отображаем имя пользователя.

	if (GetUserName(lpszSystemInfo, &cchBuff))
		cout << "Username: " << lpszSystemInfo << endl;

	// Получаем и отображаем системную директорию.

	if (GetSystemDirectory(lpszSystemInfo, MAX_PATH + 1))
		cout << "System directory: " << lpszSystemInfo << endl;

	// Получаем и отображаем директорию Windows.

	if (GetWindowsDirectory(lpszSystemInfo, MAX_PATH + 1))
		cout << "Windows directory: " << lpszSystemInfo << endl;

	cout << "Переменные окружения (partial list): " << endl;

	// Получаем переменную окружения OS.

	dwResult = ExpandEnvironmentStrings(
		"OS=%OS%",
		lpszSystemInfo,
		BUFSIZE);
	if (dwResult <= BUFSIZE)
		cout << lpszSystemInfo << endl;


	// Получаем переменную окружения PATH.

	dwResult = ExpandEnvironmentStrings(
		"PATH=%PATH%",
		lpszSystemInfo,
		BUFSIZE);
	if (dwResult <= BUFSIZE)
		cout << lpszSystemInfo << endl;

	// Получаем переменную окружения TMP.

	dwResult = ExpandEnvironmentStrings(
		"TEMP=%TEMP%",
		lpszSystemInfo,
		BUFSIZE);
	if (dwResult <= BUFSIZE)
		cout << lpszSystemInfo << endl;
}
void HardWareInfo(void)
{
	SYSTEM_INFO siSysInfo;

	GetSystemInfo(&siSysInfo);

	cout << "Hardware information: " << endl;
	cout << "  OEM ID: " << siSysInfo.dwOemId << endl;
	cout << "  Number of processors cores: " << siSysInfo.dwNumberOfProcessors << endl;
	cout << "  Page size: " << siSysInfo.dwPageSize << endl;
	cout << "  Processor type: x" << siSysInfo.dwProcessorType  << endl;
	cout << "  Minimum application address: " << siSysInfo.lpMinimumApplicationAddress << endl;
	cout << "  Maximum application address: " << siSysInfo.lpMaximumApplicationAddress << endl;
	cout << "  Active processor mask: " << siSysInfo.dwActiveProcessorMask << endl;
}
void ErrorExit(char *ErrMsg)
{
	cout << "Error : " << ErrMsg << endl;
}
void GetSampleServiceConfig(void)
{
	LPQUERY_SERVICE_CONFIG lpqscBuf;
	LPSERVICE_DESCRIPTION lpqscBuf2;
	DWORD dwBytesNeeded;

	// Открываем дескриптор сервиса.
	SC_HANDLE schSCManager = OpenSCManager(NULL, SERVICES_ACTIVE_DATABASE, SERVICE_QUERY_CONFIG);

	SC_HANDLE schService = OpenService(
		schSCManager,           // база данных SCManager
		"Факс",           // имя сервиса
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

	cout << "\nSample_Srv configuration: \n";
	cout << " Тип: 0x" << lpqscBuf->dwServiceType << endl;
	cout << " Тип запуска: 0x" << lpqscBuf->dwStartType << endl;
	cout << " Контроль ошибок: 0x" << lpqscBuf->dwErrorControl << endl;
	cout << " Путь сервиса: " << lpqscBuf->lpBinaryPathName << endl;

	if (lpqscBuf->lpLoadOrderGroup != NULL)
		cout << " Группа: " << lpqscBuf->lpLoadOrderGroup << endl;
	if (lpqscBuf->dwTagId != 0)
		cout << " Идентификатор в группе: "<< lpqscBuf->dwTagId << endl;
	if (lpqscBuf->lpDependencies != NULL)
		cout << " Зависимости: " << lpqscBuf->lpDependencies << endl;
	if (lpqscBuf->lpServiceStartName != NULL)
		cout << " Имя: " << lpqscBuf->lpServiceStartName << endl;
	if (lpqscBuf2->lpDescription != NULL)
		cout << " Описание: " << lpqscBuf2->lpDescription << endl;

	LocalFree(lpqscBuf);
	LocalFree(lpqscBuf2);
}
void GetCompIP(void)
{
	WSADATA wsaData;
	if (!WSAStartup(!NULL, &wsaData))
	{
		char chInfo[64];
		if (!gethostname(chInfo, sizeof(chInfo)))
		{
			cout << "Hostname: "<< chInfo << endl;
			hostent *sh;
			sh = gethostbyname((char*)&chInfo);
			if (sh != NULL)
			{
				cout << "Hostname: "<< sh->h_name << endl;
				int nAdapter = 0;
				while (sh->h_addr_list[nAdapter])
				{
					struct sockaddr_in adr;
					memcpy(&adr.sin_addr, sh->h_addr_list[nAdapter], sh->h_length);
					cout << "IP: "<< inet_ntoa(adr.sin_addr) << endl;
					cout << "Port: " << adr.sin_port << endl;
					nAdapter++;
				}
			}
		}
		else
			cout << "Error local host " << endl;
	}
	else
		cout << "Winsock initial Bad !!!!" << endl;
	WSACleanup();
}
void EnumerateSerialPorts(void)
{
	// В какой системе работаем?
	OSVERSIONINFO osvi;
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	BOOL bGetVer = GetVersionEx(&osvi);

	// В NT используем API QueryDosDevice
	if (bGetVer && (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT))
	{

		// Используем QueryDosDevice для просмотра всех устройств похожих на COMx.
		// Это наилучшее решение, так как порты не требуется открывать

		TCHAR szDevices[65535];
		DWORD dwChars = QueryDosDevice(NULL, szDevices, 65535);
		if (dwChars)
		{
			int i = 0;
			for (;;)
			{
				// Получаем текущее имя устройства
				TCHAR* pszCurrentDevice = &szDevices[i];
				// Если похоже на "COMX" выводим на экран
				int nLen = _tcslen(pszCurrentDevice);
				if (nLen > 3 && _tcsnicmp(pszCurrentDevice, _T("COM"), 3) == 0)
				{
					printf(pszCurrentDevice);
					printf("\n");
				}
				// Переходим к следующему символу терминатору
				while (szDevices[i] != _T('\0'))
					i++;
				// Перескакиваем на следующую строку
				i++;
				// Список завершается двойным симмволом терминатором, так что если символ
				// NULL, мы дошли до конца
				if (szDevices[i] == _T('\0'))
					break;
			} // for (;;)
		} // if(dwChars)
	} // if(bGetVer && (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT))
	else
	{
		// В 95/98 открываем каждый порт для определения его существования
		// Поддерживается до 255 COM портов, так что мы проходим пл всему списку
		// Если мы не можем открыть порт, или происходит ошибка при открытии,
		// получаем access denied или общую ошибку все эти случаи указывают на
		// то, что под таким номером есть порт.
		for (UINT i = 1; i<256; i++)
		{
			// Формируем сырое имя устройства
			char sPort[10];
			sprintf(sPort, "\\\\.\\COM%d", i);
			// Пытаемся открыть каждый порт
			BOOL bSuccess = FALSE;
			HANDLE hPort = ::CreateFile(sPort, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
			if (hPort == INVALID_HANDLE_VALUE)
			{
				DWORD dwError = GetLastError();
				// Смотрим что получилось при открытии
				if (dwError == ERROR_ACCESS_DENIED || dwError == ERROR_GEN_FAILURE)
					bSuccess = TRUE;
			}
			else
			{
				// Порт открыт успешно
				bSuccess = TRUE;
				// Не забываем закрывать каждый открытый порт,
				// так как мы не собираемся с ним работать...
				CloseHandle(hPort);
			} // if(hPort == INVALID_HANDLE_VALUE)
			  // Выводим на экран название порта
			if (bSuccess)
			{
				printf(sPort);
				printf("\n");
			}
		} // for (UINT i=1; i<256; i++)
	} // if(bGetVer && (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT))
}
void ScanProcess(void)
{
	HANDLE hSnap;
	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap == NULL)
	{
		MessageBox(NULL, "Error Load ToolHelp", NULL, MB_OK);
	}
	PROCESSENTRY32 proc;
	THREADENTRY32 te32;
	if (Process32First(hSnap, &proc))
	{
		cout << proc.szExeFile << "\r\n";
		//     cout <<  te32.th32ThreadID << " " << te32.th32OwnerProcessID << endl;
		while (Process32Next(hSnap, &proc))
		{
			cout << proc.szExeFile << "\r\n";
			         Thread32Next(hSnap, &te32);
			          cout <<  te32.th32ThreadID << " " << te32.th32OwnerProcessID << endl; 
		}
	}
}