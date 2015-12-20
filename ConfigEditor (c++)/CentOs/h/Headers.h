#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;

struct control
{
	unsigned int period[6];
	bool stop;
	bool run[6];
	bool keylog;
	bool run_s;
	unsigned int period_s;
};