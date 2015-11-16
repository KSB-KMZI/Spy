#pragma once
#include "Headers.h"
tm *GetCurrentDataAndTime(void);
//void HideFile(char *filename);
void OutTextWithTime(char *filename, char *text, ofstream &out);
void OutFullData(ofstream &out);