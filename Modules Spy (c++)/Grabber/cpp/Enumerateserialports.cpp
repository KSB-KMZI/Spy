#include "Enumerateserialports.h"

void EnumerateSerialPorts(bool run, char *logfile, unsigned int periodic)
{
	while (run)
	{
		for (int i = periodic; i > 0; i--)
		{
			Sleep(1000);
			if (i == 1)
			{
				ofstream out;
				out.open(logfile, ios::app | ios::out);

				out << "----------------------------------------------------" << endl;
				out << "Serial ports. "; OutFullData(out); out << "   |" << endl;
				out << "----------------------------------------------------" << endl;

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
								out << " Device: " << pszCurrentDevice << endl;
							
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
					for (UINT i = 1; i < 256; i++)
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
							out << " Device: " << sPort << endl;
					} // for (UINT i=1; i<256; i++)
				} // if(bGetVer && (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT))
				out.close();
			}
		}
		pthread_testcancel();
	}
}