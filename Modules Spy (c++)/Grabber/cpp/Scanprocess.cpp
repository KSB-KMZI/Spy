#include "Scanprocess.h"

void ScanProcess(bool run, char *logfile, unsigned int periodic)
{
	while (run)
	{
		for (int i = periodic; i > 0; i--)
		{
			Sleep(1000);
			if (i == 1)
			{
				HANDLE hSnap;
				PROCESSENTRY32 proc;

				hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

				ofstream out;
				out.open(logfile, ios::app | ios::out);

				if (hSnap == NULL)
				{
					out << "Error load toolhelp. "; 
					OutFullData(out); 
					cout << endl;
				}

				out << "-------------------------------------------------------" << endl;
				out << "Process scenner. "; OutFullData(out); out << "   |"<< endl;
				out << "-------------------------------------------------------" << endl;

				if (Process32First(hSnap, &proc))
				{
					int j = 0;
					while (Process32Next(hSnap, &proc))
					{
						out << "---------Process-¹" << j + 1 << "---"<< endl;
						out << "PID: " << proc.th32ProcessID << endl << "Exe file: " << proc.szExeFile << endl << "Parent's PID: " << proc.th32ParentProcessID << endl;
						out << "----------------------" << endl;
						//cout << proc. << endl;
						j++;
					}
				}

				out.close();
			}
		}
		pthread_testcancel();
	}
}