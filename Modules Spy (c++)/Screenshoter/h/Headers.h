#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <tchar.h>
#include <pthread.h>
#include <ctime>
#include <gdiplus.h>
#pragma warning(disable : 4996)
#pragma comment(lib,"wsock32.lib")
#pragma comment (lib, "mswsock.lib")
#pragma comment(lib, "GdiPlus.lib")
using namespace std;
using namespace Gdiplus;

#define PORT 65002 
#define SERVERADDR "127.0.0.1" 

