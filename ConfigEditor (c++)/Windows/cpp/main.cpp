#include "Headers.h"
#include "Output.h"

int main(void)
{
	string menu;
	ifstream ifst;
	ofstream ofst;
	control C;
	FILE *fp;

	_mkdir("load");
	_mkdir("create");
	_mkdir("save");

	do 
	{
		cout << "Main>> ";
		getline(cin, menu);

		if (menu == "load")
		{
			fp = fopen("load//Config.ksb", "r");
			if (fp == NULL)
			{
				cout << "\n\nConfig.ksb does not exists in //load//\n\n";
				break;
			}
			else
				fclose(fp);

			ifst.open("load//Config.ksb", ios::in);

			ifst >> C.stop;
			for (int i = 0; i < 6; i++)
				ifst >> C.period[i];
			for (int i = 0; i < 6; i++)
				ifst >> C.run[i];

			ifst >> C.keylog;
			ifst >> C.run_s;
			ifst >> C.period_s;

			cout << "\n\nLoad succesfully!\n\n"; PrintControl(C); cout << endl << endl << "Working with loaded file" << endl << endl;

			do
			{ 
				cout << "Load>> ";

				getline(cin, menu);

				if (menu == "set")
				{
					do { menu = Set(C); } while (menu != "no");
					menu = "set";
				}

				if (menu == "save")
				{
					cout << "\n\nsave File //save//Config.ksb will be owerwrite if it does exists!\n";
					do {
						cout << "Continue? yes//no>> ";
						getline(cin, menu);
						cout << endl;
					} while (menu != "yes" && menu != "no");
					Save(ofst, C, "save//Config.ksb");
					menu = "save";
				}

				if (menu == "help")
					Help(1);

				if (menu != "help" && menu != "save" && menu != "set" && menu != "exit")
					cout << "\n\n\aWrong command! Type help for more information.\n\n";

			} while (menu != "exit");
			menu = "load";
		}
		
		if (menu == "create")
		{
			do 
			{
				cout << "Create>> ";

				getline(cin, menu);

				if (menu == "set")
				{
					do { menu = Set_Create(C); } while (menu != "no");
					menu = "set";
				}

				if (menu == "save")
				{
					cout << "\n\nsave File //create//Config.ksb will be owerwrite if it does exists!\n";
					do {
						cout << "Continue? yes//no>> ";
						getline(cin, menu);
						cout << endl;
					} while (menu != "yes" && menu != "no");
					Save(ofst, C, "create//Config.ksb");
					menu = "save";
				}

				if (menu == "help")
					Help(2);

				if (menu != "help" && menu != "save" && menu != "set" && menu != "exit")
					cout << "\n\n\aWrong command! Type help for more information.\n\n";

			} while (menu != "exit");
			menu = "create";
		}

		if (menu == "help")
			Help(0);
		
		if (menu != "help" && menu != "create" && menu != "load" && menu != "exit")
			cout << "\n\n\aWrong command! Type help for more information.\n\n";

	} while (menu != "exit");

	return 0;
}