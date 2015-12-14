#pragma once 
#include "Commonfunctional.h"

tm *GetCurrentDataAndTime(void)
{
	tm *tim;
	time_t t = time(NULL);
	tim = localtime(&t);

	return tim;
}

string GetSymbolic(int val)
{
	string num[61] = {"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16",
	"17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35",
	"36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54",
	"55","56","57","58","59","60"};

	if (val > 60)
		return "0";

	return num[val];
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
		"." << GetCurrentDataAndTime()->tm_mon + 1 << "." << GetCurrentDataAndTime()->tm_year + 1900 <<
		" " << GetCurrentDataAndTime()->tm_hour << ":" << GetCurrentDataAndTime()->tm_min <<
		":" << GetCurrentDataAndTime()->tm_sec;
}

void MakeDataString(string &str)
{
	str = "ScreenShoot" + GetSymbolic(GetCurrentDataAndTime()->tm_mday) + "." +
		GetSymbolic(GetCurrentDataAndTime()->tm_mon + 1) + "." + GetSymbolic(GetCurrentDataAndTime()->tm_year - 100) +
	    "+" + GetSymbolic(GetCurrentDataAndTime()->tm_hour) + "-" + GetSymbolic(GetCurrentDataAndTime()->tm_min) + 
		"-" + GetSymbolic(GetCurrentDataAndTime()->tm_sec) + ".png";
}