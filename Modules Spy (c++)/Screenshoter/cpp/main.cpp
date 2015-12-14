#include "Headers.h"
#include "ThreadSocket.h"
#include "ThreadStart.h"
#include "Commonfunctional.h"

void main(void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	pthread_t SHThread, ListenSocket;
	ofstream out;
	control *B = new control, C;
	C.periodic = 1800;
	C.stop = false;
	C.run = true;

	OutTextWithTime("ScreenshooterLog.txt", "Screenshooter is started in ", out);

	do {
		pthread_create(&SHThread, NULL, Start, (void*)&C);
		pthread_create(&ListenSocket, NULL, ListenSocketProc, (void*)&C);
		pthread_join(ListenSocket, (void**)&B);

		if (B == NULL)
		{
			OutTextWithTime("ScreenshooterLog.txt", "Configuration file Sconfig.ksb is not found! Using last succesfull configuration! Time: ", out);
			do {

				pthread_create(&ListenSocket, NULL, ListenSocketProc, (void*)&C);
				pthread_join(ListenSocket, (void**)&B);

			} while (B == NULL);
		}

		C.periodic = B->periodic;
		C.stop = B->stop;
		C.run = B->run;

		pthread_cancel(SHThread);
		OutTextWithTime("ScreenshooterLog.txt", "Screenshooter were restarted in ", out);

	} while (C.stop != true);

	OutTextWithTime("ScreenshooterLog.txt", "Screenshooter was stopped in ", out);
}