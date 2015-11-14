#include "Getcompip.h"

void GetCompIP(bool run, char *logfile, unsigned int periodic)
{
	while (run)
	{
		for (int i = periodic; i > 0; i--)
		{
			Sleep(1000);
			if (i == 1)
			{
				ofstream out;
				out.open(logfile, ios::app | ios::out);

				out << "-----------------------------------------------------------" << endl;
				out << "Network information. "; OutFullData(out); out << "   |" << endl;
				out << "-----------------------------------------------------------" << endl;

				WSADATA wsaData;
				if (!WSAStartup(!NULL, &wsaData))
				{
					char chInfo[64];
					if (!gethostname(chInfo, sizeof(chInfo)))
					{
						out << " Hostname: " << chInfo << endl;
						hostent *sh;
						sh = gethostbyname((char*)&chInfo);
						if (sh != NULL)
						{
							out << " Hostname via DNS: " << sh->h_name << endl;
							int nAdapter = 0;
							while (sh->h_addr_list[nAdapter])
							{
								struct sockaddr_in adr;
								memcpy(&adr.sin_addr, sh->h_addr_list[nAdapter], sh->h_length);
								out << " IP: " << inet_ntoa(adr.sin_addr) << endl;
								out << " Port: " << adr.sin_port << endl;
								nAdapter++;
							}
						}
					}
					else
						out << " Error local host " << endl;
				}
				else
					out << " Winsock initial Bad" << endl;
				WSACleanup();
				out.close();

				//system("ping 192.168.0.1 > out.txt");
			}
		}
	}
}