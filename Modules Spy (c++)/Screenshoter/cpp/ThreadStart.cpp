#include "ThreadStart.h"

void *Start(void *param)
{
	control *CS = (control*)param;
	MakeShots(CS->run, CS->periodic);
	return NULL;
}