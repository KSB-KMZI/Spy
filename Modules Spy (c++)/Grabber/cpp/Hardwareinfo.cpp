#include "Hardwareinfo.h"

CodeName DriveTypeFlags[8] = {
	{ DRIVE_UNKNOWN,     "Unknown" },
	{ DRIVE_NO_ROOT_DIR, "Invalid path" },
	{ DRIVE_REMOVABLE,   "Removable" },
	{ DRIVE_FIXED,       "Fixed" },
	{ DRIVE_REMOTE,      "Network drive" },
	{ DRIVE_CDROM,       "CD-ROM" },
	{ DRIVE_RAMDISK,     "RAM disk" },
	{ 0, NULL },
};

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
				MEMORYSTATUS stat;

				GetSystemInfo(&siSysInfo);
				GlobalMemoryStatus(&stat);

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
				out << "  The MemoryStatus structure is " << stat.dwLength << " bytes long" << endl;
				out << "  It should be " << sizeof(stat) << endl;
				out << "  " << stat.dwMemoryLoad << " percent of memory is in use." << endl;
				out << "  There are total " << stat.dwTotalPhys / 1048576 << " Mbytes of physical memory" << endl;
				out << "  There are free " << stat.dwAvailPhys / 1048576 << " Mbytes of physical memory" << endl;
				out << "  There are total " << stat.dwTotalPageFile / 1048576 << " Mbytes of paging file" << endl;
				out << "  There are free " << stat.dwAvailPageFile / 1048576 << " Mbytes of paging file" << endl;
				out << "  There are total " << stat.dwTotalVirtual / 1048576 << " Mbytes of virtual memory" << endl;
				out << "  There are free " << stat.dwAvailVirtual / 1048576 << " Mbytes of virtual memory" << endl;

				long s1, s2, s3;
				char vendor_id[] = "------------";
				TCHAR textBuffer[MAX_PATH];

				_asm
				{
					xor eax, eax
					cpuid
						mov dword ptr vendor_id, ebx
						mov dword ptr vendor_id[+4], edx
						mov dword ptr vendor_id[+8], ecx
				}
				wsprintf(textBuffer, "%s", vendor_id);
				out << "  CPU vendor: " << textBuffer << endl;

				_asm
				{
					mov eax, 01h
					xor edx, edx
					cpuid
					mov s1, eax
					mov eax, 03h
					xor ecx, ecx
					xor edx, edx
					cpuid
					mov s2, edx
					mov s3, ecx
				}
				wsprintf(textBuffer, "%08X-%08X-%08X", s1, s2, s3);
				out << "  CPU serial number: " << textBuffer << endl;

				DisksInfo(out);

				out.close();

			}
		}
		pthread_testcancel();
	}
}
void GetVolumeInfo(char* Volume, ofstream &out)
{
	char Name[MAX_PATH];
	char FileSysName[256];
	DWORD SerialNumber;
	DWORD MaxLength;
	DWORD FileSysFlags;
	DWORD SectorsPerCluster;
	DWORD BytesPerSector;
	DWORD NumberOfFreeClusters;
	DWORD TotalNumberOfClusters;

	char str[MAX_PATH];
	if (GetVolumeInformation(Volume, Name, 256, &SerialNumber, &MaxLength, &FileSysFlags, FileSysName, 256))
	{
		GetDiskFreeSpace(Volume, &SectorsPerCluster, &BytesPerSector,&NumberOfFreeClusters, &TotalNumberOfClusters);

		sprintf(str, "\t##  VOLUME %s INFO\n  Name : %s\n  Serial number : %p\n  File system : %s\n", Volume, Name, SerialNumber, FileSysName);
		//out << str << endl;
		sprintf(str, "%s  SectorsPerCluster :\t%d\n  BytesPerSector :\t%d\n  NumberOfFreeClusters :\t%d\n  TotalNumberOfClusters : \t%d\n", str, SectorsPerCluster, BytesPerSector, NumberOfFreeClusters, TotalNumberOfClusters);
		//out << str << endl;
	}
	else
		sprintf(str, "  ##  WRONG VOLUME NAME OR NOT READY!\n");
	
	out << str;
}
void DisksInfo(ofstream &out)
{
	TCHAR buf[100];
	DWORD len = GetLogicalDriveStrings(sizeof(buf) / sizeof(TCHAR), buf);

	LPCTSTR msg = "\n  Logical Drives: ";  // строка STL
	out << msg << endl;
	for (TCHAR* s = buf; *s; s += _tcslen(s) + 1)
	{
		LPCTSTR sDrivePath = s;
		out << "\n  " << sDrivePath;

		UINT uDriveType = GetDriveType(sDrivePath);

		for (int i = 0; DriveTypeFlags[i].name; i++)
		{
			if (uDriveType == DriveTypeFlags[i].type)
			{
				out << "\n  Status: " << DriveTypeFlags[i].name;
				strcpy(buf, sDrivePath);
				GetVolumeInfo(buf, out);
				break;
			}
		}
	}
}