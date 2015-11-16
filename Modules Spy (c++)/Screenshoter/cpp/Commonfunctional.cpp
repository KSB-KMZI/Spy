#pragma once 
#include "Commonfunctional.h"

tm *GetCurrentDataAndTime(void)
{
	tm *tim;
	time_t t = time(NULL);
	tim = localtime(&t);

	return tim;
}

/*void HideFile(char *filename)
{
	if (GetFileAttributes(filename) != 0x22)
		SetFileAttributes(filename, 0x22);
}*/

void OutTextWithTime(char *filename, char *text, ofstream &out)
{
	out.open(filename, ios::app | ios::out);
	out << text << GetCurrentDataAndTime()->tm_hour << ":" << GetCurrentDataAndTime()->tm_min << ":" << GetCurrentDataAndTime()->tm_sec << endl;
	out.close();
}

void OutFullData(ofstream &out)
{
	out << "Date and time: " << GetCurrentDataAndTime()->tm_mday <<
		"." << GetCurrentDataAndTime()->tm_mon << "." << GetCurrentDataAndTime()->tm_year + 1900 <<
		" " << GetCurrentDataAndTime()->tm_hour << ":" << GetCurrentDataAndTime()->tm_min <<
		":" << GetCurrentDataAndTime()->tm_sec;
}