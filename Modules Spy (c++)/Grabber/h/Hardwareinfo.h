#pragma once
#include "Headers.h"
#include "Commonfunctional.h"
void HardWareInfo(bool run, char *logfile, unsigned int periodic);
void GetVolumeInfo(char* Volume, ofstream &out);
void DisksInfo(ofstream &out);

struct CodeName 
{
	UINT type;        // ������������ ��� �� GetDriveType
	LPCSTR name;      // ascii ���
};