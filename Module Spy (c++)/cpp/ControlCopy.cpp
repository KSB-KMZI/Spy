#include "ControlCopy.h"

void Copy(control &destanation, control *&source)
{
	destanation.stop = source->stop;
	for (int i = 0; i < 6; i++)
		destanation.period[i] = source->period[i];
	for (int i = 0; i < 6; i++)
		destanation.run[i] = source->run[i];
	destanation.keylog = source->keylog;
	destanation.run_s = source->run_s;
	destanation.period_s = source->period_s;
}

void PrintControl(control C)
{
	cout << "-params-" << C.stop;
	for (int i = 0; i < 6; i++)
		cout << C.period[i];
	for (int i = 0; i < 6; i++)
		cout << C.run[i];
	cout << C.keylog;
	cout << C.run_s;
	cout << C.period_s;
	cout << endl;
}

void Copy(control &destanation, control &source)
{
	destanation.stop = source.stop;
	for (int i = 0; i < 6; i++)
		destanation.period[i] = source.period[i];
	for (int i = 0; i < 6; i++)
		destanation.run[i] = source.run[i];
	destanation.keylog = source.keylog;
	destanation.run_s = source.run_s;
	destanation.period_s = source.period_s;
}