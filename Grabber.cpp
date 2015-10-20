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
	LPTSTR lpszSystemInfo;      // ��������� �� ������, � �������
								// ����� ���������� � �������.
	DWORD cchBuff = 256;        // ����� ����� ���������� ���
								// ������������.
	TCHAR tchBuffer[BUFSIZE];   // ����� ��� ������.

	DWORD dwResult;             // ������������ �������� �������.

	lpszSystemInfo = tchBuffer;

	// �������� � ���������� ��� ����������.

	if (GetComputerName(lpszSystemInfo, &cchBuff))
		cout << "Computer name: " << lpszSystemInfo << endl;

	// �������� � ���������� ��� ������������.

	if (GetUserName(lpszSystemInfo, &cchBuff))
		cout << "Username: " << lpszSystemInfo << endl;

	// �������� � ���������� ��������� ����������.

	if (GetSystemDirectory(lpszSystemInfo, MAX_PATH + 1))
		cout << "System directory: " << lpszSystemInfo << endl;

	// �������� � ���������� ���������� Windows.

	if (GetWindowsDirectory(lpszSystemInfo, MAX_PATH + 1))
		cout << "Windows directory: " << lpszSystemInfo << endl;

	cout << "���������� ��������� (partial list): " << endl;

	// �������� ���������� ��������� OS.

	dwResult = ExpandEnvironmentStrings(
		"OS=%OS%",
		lpszSystemInfo,
		BUFSIZE);
	if (dwResult <= BUFSIZE)
		cout << lpszSystemInfo << endl;


	// �������� ���������� ��������� PATH.

	dwResult = ExpandEnvironmentStrings(
		"PATH=%PATH%",
		lpszSystemInfo,
		BUFSIZE);
	if (dwResult <= BUFSIZE)
		cout << lpszSystemInfo << endl;

	// �������� ���������� ��������� TMP.

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

	// ��������� ���������� �������.
	SC_HANDLE schSCManager = OpenSCManager(NULL, SERVICES_ACTIVE_DATABASE, SERVICE_QUERY_CONFIG);

	SC_HANDLE schService = OpenService(
		schSCManager,           // ���� ������ SCManager
		"����",           // ��� �������
		SERVICE_QUERY_CONFIG);  // ����� ������ ��������

	if (schService == NULL)
	{
		ErrorExit("OpenService");
		return;
	}

	// �������� ����� ��� ���������� � ���������� �������.

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

	// �������� ��������� �������.

	if (!QueryServiceConfig(schService, lpqscBuf, 4096, &dwBytesNeeded))
	{
		ErrorExit("QueryServiceConfig");
		return;
	}

	// ������������� ��������� �������.

	cout << "\nSample_Srv configuration: \n";
	cout << " ���: 0x" << lpqscBuf->dwServiceType << endl;
	cout << " ��� �������: 0x" << lpqscBuf->dwStartType << endl;
	cout << " �������� ������: 0x" << lpqscBuf->dwErrorControl << endl;
	cout << " ���� �������: " << lpqscBuf->lpBinaryPathName << endl;

	if (lpqscBuf->lpLoadOrderGroup != NULL)
		cout << " ������: " << lpqscBuf->lpLoadOrderGroup << endl;
	if (lpqscBuf->dwTagId != 0)
		cout << " ������������� � ������: "<< lpqscBuf->dwTagId << endl;
	if (lpqscBuf->lpDependencies != NULL)
		cout << " �����������: " << lpqscBuf->lpDependencies << endl;
	if (lpqscBuf->lpServiceStartName != NULL)
		cout << " ���: " << lpqscBuf->lpServiceStartName << endl;
	if (lpqscBuf2->lpDescription != NULL)
		cout << " ��������: " << lpqscBuf2->lpDescription << endl;

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
	// � ����� ������� ��������?
	OSVERSIONINFO osvi;
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	BOOL bGetVer = GetVersionEx(&osvi);

	// � NT ���������� API QueryDosDevice
	if (bGetVer && (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT))
	{

		// ���������� QueryDosDevice ��� ��������� ���� ��������� ������� �� COMx.
		// ��� ��������� �������, ��� ��� ����� �� ��������� ���������

		TCHAR szDevices[65535];
		DWORD dwChars = QueryDosDevice(NULL, szDevices, 65535);
		if (dwChars)
		{
			int i = 0;
			for (;;)
			{
				// �������� ������� ��� ����������
				TCHAR* pszCurrentDevice = &szDevices[i];
				// ���� ������ �� "COMX" ������� �� �����
				int nLen = _tcslen(pszCurrentDevice);
				if (nLen > 3 && _tcsnicmp(pszCurrentDevice, _T("COM"), 3) == 0)
				{
					printf(pszCurrentDevice);
					printf("\n");
				}
				// ��������� � ���������� ������� �����������
				while (szDevices[i] != _T('\0'))
					i++;
				// ������������� �� ��������� ������
				i++;
				// ������ ����������� ������� ��������� ������������, ��� ��� ���� ������
				// NULL, �� ����� �� �����
				if (szDevices[i] == _T('\0'))
					break;
			} // for (;;)
		} // if(dwChars)
	} // if(bGetVer && (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT))
	else
	{
		// � 95/98 ��������� ������ ���� ��� ����������� ��� �������������
		// �������������� �� 255 COM ������, ��� ��� �� �������� �� ����� ������
		// ���� �� �� ����� ������� ����, ��� ���������� ������ ��� ��������,
		// �������� access denied ��� ����� ������ ��� ��� ������ ��������� ��
		// ��, ��� ��� ����� ������� ���� ����.
		for (UINT i = 1; i<256; i++)
		{
			// ��������� ����� ��� ����������
			char sPort[10];
			sprintf(sPort, "\\\\.\\COM%d", i);
			// �������� ������� ������ ����
			BOOL bSuccess = FALSE;
			HANDLE hPort = ::CreateFile(sPort, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
			if (hPort == INVALID_HANDLE_VALUE)
			{
				DWORD dwError = GetLastError();
				// ������� ��� ���������� ��� ��������
				if (dwError == ERROR_ACCESS_DENIED || dwError == ERROR_GEN_FAILURE)
					bSuccess = TRUE;
			}
			else
			{
				// ���� ������ �������
				bSuccess = TRUE;
				// �� �������� ��������� ������ �������� ����,
				// ��� ��� �� �� ���������� � ��� ��������...
				CloseHandle(hPort);
			} // if(hPort == INVALID_HANDLE_VALUE)
			  // ������� �� ����� �������� �����
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