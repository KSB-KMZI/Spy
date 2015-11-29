#pragma once 
#include "Commonfunctional.h"

tm *GetCurrentDataAndTime(void)
{
	tm *tim;
	time_t t = time(NULL);
	tim = localtime(&t);

	return tim;
}

void HideFile(char *filename)
{
	if (GetFileAttributes(filename) != 0x22)
		SetFileAttributes(filename, 0x22);
}

void OutTextWithTime(char *filename, char *text, control *C, ofstream &out)
{
	out.open(filename, ios::app | ios::out);
	out << text << GetCurrentDataAndTime()->tm_hour << ":" << GetCurrentDataAndTime()->tm_min << ":" << GetCurrentDataAndTime()->tm_sec;

	if (C != NULL)
	{
		out << "-params-" << *C->run;
		for (int i = 0; i < 6; i++)
			out << C->period[i];
		for (int i = 0; i < 6; i++)
			out << C->run[i];
		out << endl;
	}
	else
		out << endl;

	out.close();
}

void OutFullData(ofstream &out)
{
	out << "Date and time: " << GetCurrentDataAndTime()->tm_mday <<
		"." << GetCurrentDataAndTime()->tm_mon + 1 << "." << GetCurrentDataAndTime()->tm_year + 1900 <<
		" " << GetCurrentDataAndTime()->tm_hour << ":" << GetCurrentDataAndTime()->tm_min <<
		":" << GetCurrentDataAndTime()->tm_sec;
}