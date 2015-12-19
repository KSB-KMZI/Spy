#include "ThreadStart.h"
#include "Singlemodulesrun.h"
void *Start(void *param)
{
	control *C = (control*)param;
	SingleModulesRun(C);
	return NULL;
}