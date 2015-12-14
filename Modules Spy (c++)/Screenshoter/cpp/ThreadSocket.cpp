#include "ThreadSocket.h"
void *ListenSocketProc(void *param)
{
	control *C = (control*)param;
	control *A = new control;
	bool cmp = true;

	ifstream ifst;
	FILE *fp;

	do {

		fp = fopen("Sconfig.ksb", "r");
		if (fp == NULL)
			return NULL;
		else
			fclose(fp);

		ifst.open("Sconfig.ksb", ios::in);

		ifst >> A->stop;
		ifst >> A->run;
		ifst >> A->periodic;

		if (A->stop != C->stop)
			cmp = false;

		if (A->run != C->run)
			cmp = false;

		if (A->periodic != C->periodic)
			cmp = false;

		ifst.close();

	} while (cmp != false);

	return (void*)A;
}