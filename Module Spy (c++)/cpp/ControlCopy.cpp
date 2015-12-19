#include "ControlCopy.h"

void Copy(control &C, control *&B)
{
	C.stop = B->stop;
	for (int i = 0; i < 6; i++)
		C.period[i] = B->period[i];
	for (int i = 0; i < 6; i++)
		C.run[i] = B->run[i];
	C.keylog = B->keylog;
	C.run_s = B->run_s;
	C.period_s = B->period_s;
}