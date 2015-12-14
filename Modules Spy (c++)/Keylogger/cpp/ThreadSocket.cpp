#include "ThreadSocket.h"
void *ListenSocketProc(void *param)
{
	int st;

	ifstream ifst;
	FILE *fp;

	do {

		fp = fopen("Kconfig.ksb", "r");
		if (fp == NULL)
			return (void*)2;
		else
			fclose(fp);

		ifst.open("Kconfig.ksb", ios::in);

		ifst >> st;

		ifst.close();

	} while (st != 1);

	return (void*)st;
}