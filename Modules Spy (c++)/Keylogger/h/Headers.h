#pragma once
#include <Windows.h>
#include <WinUser.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <shlobj.h>
#include <wininet.h>
#include <pthread.h>
#pragma comment(lib, "wininet.lib")
#pragma warning(disable : 4996)
#pragma comment(lib,"wsock32.lib")
#pragma comment (lib, "mswsock.lib")
using namespace std;

#define PORT 65001
#define SERVERADDR "127.0.0.1"