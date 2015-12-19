#include "InitControl.h"
void InitControl(control &C)
{
	C.stop = false;
	C.period[0] = 7200; C.period[1] = 7200; C.period[2] = 7200; C.period[3] = 7200; C.period[4] = 7200; C.period[5] = 7200;
	C.run[0] = true;
	C.run[1] = true;
	C.run[2] = true;
	C.run[3] = true;
	C.run[4] = true;
	C.run[5] = true;
	C.keylog = false;
	C.run_s = true;
	C.period_s = 7200;
}