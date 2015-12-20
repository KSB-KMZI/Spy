#pragma once
#include "Headers.h"
tm *GetCurrentDataAndTime(void);
void HideFile(char *filename);
void HideFile(const char *filename);
void OutTextWithTime(char *filename, char *text, control *C, ofstream &out);
void OutFullData(ofstream &out);
void MakeDataString(string &str);
void CreateHiddenFolders(void);
string GetSymbolic(int val);