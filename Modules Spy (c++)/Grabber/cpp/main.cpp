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

	OutTextWithTime("GrabberLog.txt", "Threads were started in ", &C, out);

	do {
	
		pthread_create(&ModuleStarter, NULL, Start, (void*)&C);
		pthread_create(&ListenSocket, NULL, ListenSocketProc, (void*)&C);
		pthread_join(ListenSocket, (void**)&B);

		if (B == NULL)
		{
			OutTextWithTime("GrabberLog.txt", "Configuration file Gconfig.ksb is not found! Using last successfull configuration! Time: ", &C, out);
			B = new control;
			do {

				pthread_create(&ListenSocket, NULL, ListenSocketProc, (void*)&C);
				pthread_join(ListenSocket, (void**)&B);

			} while (B == NULL);
		}

		C.stop = B->stop;
		for (int i = 0; i < 6; i++)
			C.period[i] = B->period[i];
		for (int i = 0; i < 6; i++)
			C.run[i] = B->run[i];

		KillModules();
		OutTextWithTime("GrabberLog.txt", "Threads were restarted in ", &C, out);

	} while (C.stop != true);

	OutTextWithTime("GrabberLog.txt", "Threads were stopped in ", NULL, out);
}