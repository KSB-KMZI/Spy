#include "Hardwareinfo.h"

void HardWareInfo(bool run, char *logfile, unsigned int periodic)
{
	while (run)
	{
		for (int i = periodic; i > 0; i--)
		{
			Sleep(1000);
			if (i == 1)
			{
				SYSTEM_INFO siSysInfo;

				GetSystemInfo(&siSysInfo);

				ofstream out;
				out.open(logfile, ios::app | ios::out);

				out << "-----------------------------------------------------------" << endl;
				out << "Hardware information. "; OutFullData(out); out << " |" << endl;
				out << "-----------------------------------------------------------" << endl;
				out << "  OEM ID: " << siSysInfo.dwOemId << endl;
				out << "  Number of processors cores: " << siSysInfo.dwNumberOfProcessors << endl;
				out << "  Page size: " << siSysInfo.dwPageSize << endl;
				out << "  Processor type: x" << siSysInfo.dwProcessorType << endl;
				out << "  Minimum application address: " << siSysInfo.lpMinimumApplicationAddress << endl;
				out << "  Maximum application address: " << siSysInfo.lpMaximumApplicationAddress << endl;
				out << "  Active processor mask: " << siSysInfo.dwActiveProcessorMask << endl;

				out.close();
			}
		}
	}
}