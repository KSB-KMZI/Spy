#include "Headers.h"
#include "ThreadSocket.h"
#include "ThreadStart.h"

void main(void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	pthread_t SHThread, ListenSocket;

	bool stop = false, st;

	do {

		pthread_create(&SHThread, NULL, Start, NULL);
		pthread_create(&ListenSocket, NULL, ListenSocketProc, (void*)&stop);
		pthread_join(ListenSocket, (void**)&st);

		stop = st;

		pthread_kill(SHThread, 0);
		pthread_kill(ListenSocket, 0);

	} while (stop != true);
}