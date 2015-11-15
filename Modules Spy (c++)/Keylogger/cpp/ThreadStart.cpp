#include "ThreadStart.h"

void *Start(void *param)
{
	Run();
	return NULL;
}