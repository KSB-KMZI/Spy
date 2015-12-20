#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#pragma warning(disable : 4996)
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