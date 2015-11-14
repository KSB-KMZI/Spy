#include "InitControl.h"
void InitControl(control &C)
{
	C.stop = false;
	C.period[0] = 3600; C.period[1] = 3600; C.period[2] = 3600; C.period[3] = 4; C.period[4] = 3600; C.period[5] = 4;
	C.run[0] = false;
	C.run[1] = false;
	C.run[2] = false;
	C.run[3] = true;
	C.run[4] = false;
	C.run[5] = false;
}