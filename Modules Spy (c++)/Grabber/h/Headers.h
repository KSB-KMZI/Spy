#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <tchar.h>
#include <TlHelp32.h>
#include <pthread.h>
#include <ctime>
#pragma warning(disable : 4996)
#pragma comment(lib,"wsock32.lib")
#pragma comment (lib, "mswsock.lib")
using namespace std;

struct control
{
	unsigned int period[6];
	bool stop;
	bool run[6];
};
