#pragma once
#include "Headers.h"
#include "Commonfunctional.h"
void GetSampleServiceConfig(bool run, char *logfile, unsigned int periodic);
void WriteService(ofstream &out, const char *servicename);
map <int, string> GetServiceList();
void ErrorExit(char *ErrMsg, ofstream &out);