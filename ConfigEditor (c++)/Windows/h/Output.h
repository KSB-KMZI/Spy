#pragma once
#include "Headers.h"
void Help(int val);
void InitControl(control &C);
void PrintControl(control &C);
void Save(ofstream &out, control &C, char *filepath);
string Set(control &C);
string Set_Create(control &C);