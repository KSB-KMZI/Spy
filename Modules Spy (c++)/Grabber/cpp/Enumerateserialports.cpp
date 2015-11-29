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
								out << " Device: " << pszCurrentDevice << endl;
							
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
					for (UINT i = 1; i < 256; i++)
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
							out << " Device: " << sPort << endl;
					} // for (UINT i=1; i<256; i++)
				} // if(bGetVer && (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT))
				out.close();
			}
		}
		pthread_testcancel();
	}
}