#include "ThreadSocket.h"
void *ListenSocketProc(void *param)
{
	control *C = (control*)param;
	control *A = new control;
	bool cmp = true;

	ifstream ifst;
	FILE *fp;

	do {

		fp = fopen("Gconfig.ksb", "r");
		if (fp == NULL)
			return NULL;
		else
			fclose(fp);

		ifst.open("Gconfig.ksb", ios::in);

		ifst >> A->stop;
		for (int i = 0; i < 6; i++)
			ifst >> A->period[i];
		for (int i = 0; i < 6; i++)
			ifst >> A->run[i];

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

		ifst.close();

	} while (cmp != false);

	return (void*)A;
}