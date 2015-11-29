#pragma once
#include "Headers.h"
#include "Commonfunctional.h"
#include "InitControl.h"
#include "ThreadStart.h"
#include "ThreadSocket.h"
#include "Singlemodulesrun.h"

void main(void)
{
	control *B = new control, C;
	ofstream out;
	pthread_t ModuleStarter, ListenSocket;

	InitControl(C);

	OutTextWithTime("GrabberLog.txt", "Threads were run in ", &C, out);

	do {
	
		pthread_create(&ModuleStarter, NULL, Start, (void*)&C);
		pthread_create(&ListenSocket, NULL, ListenSocketProc, (void*)&C);
		pthread_join(ListenSocket, (void**)&B);

		if (B == NULL)
		{
			OutTextWithTime("GrabberLog.txt", "Instruction file IG.txt is not found! ", NULL, out);
			return;
		}

		C.stop = B->stop;
		for (int i = 0; i < 6; i++)
			C.period[i] = B->period[i];
		for (int i = 0; i < 6; i++)
			C.run[i] = B->run[i];

		KillModules();
		pthread_cancel(ModuleStarter);
		pthread_cancel(ListenSocket);

		OutTextWithTime("GrabberLog.txt", "Threads were rerun in ", &C, out);

	} while (C.stop != true);

	OutTextWithTime("GrabberLog.txt", "Threads were stopped in ", NULL, out);
}