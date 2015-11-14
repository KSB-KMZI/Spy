#pragma once
#include "Headers.h"
#include "Commonfunctional.h"
#include "InitControl.h"
#include "ThreadStart.h"
#include "ThreadSocket.h"

void main(void)
{
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);

	control *B = new control, C;
	ofstream out;
	pthread_t ModuleStarter, ListenSocket;

	InitControl(C);

	OutTextWithTime("GrabberLog.txt", "Threads were run in ", out);

	do {
	
		pthread_create(&ModuleStarter, NULL, Start, (void*)&C);
		pthread_create(&ListenSocket, NULL, ListenSocketProc, NULL);
		pthread_join(ListenSocket, (void**)&B);

		C.stop = B->stop;
		for (int i = 0; i < 6; i++)
			C.period[i] = B->period[i];
		for (int i = 0; i < 6; i++)
			C.run[i] = B->run[i];

		pthread_kill(ModuleStarter, 0);
		pthread_kill(ListenSocket, 0);

		OutTextWithTime("GrabberLog.txt", "Threads were rerun in ", out);

	} while (C.stop != true);

	OutTextWithTime("GrabberLog.txt", "Threads were stopped in ", out);
}