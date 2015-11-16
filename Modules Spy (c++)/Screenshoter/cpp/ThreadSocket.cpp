#include "ThreadSocket.h"
void *ListenSocketProc(void *param)
{
	//������������ ���������� Winsocks 
	WSADATA WsaData;
	if (WSAStartup(0x0202, &WsaData))
	{
		cout << "Winsock cannot be started\r\n";
		return NULL;
	}

	//�������� ������
	SOCKET my_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (my_sock == INVALID_SOCKET)
	{
		cout << "Socket() error: " << WSAGetLastError() << endl;
		WSACleanup();
		return NULL;
	}

	// ��������� ����������� ������������������ ������ 
	int i = 1;
	if (setsockopt(my_sock, SOL_SOCKET, SO_BROADCAST, (char *)&i, sizeof(i)) == -1)
	{
		cout << "Error setting broadcast socket\n";
		WSACleanup();
		return NULL;
	}
	HOSTENT *hst;
	sockaddr_in dest_addr;
	memset(&dest_addr, 0, sizeof(sockaddr_in));
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(PORT);
	int dasize = sizeof(dest_addr);

	// ����������� IP-������ ���� ����������
	// �������������� IP ������ �� ����������� � ������� ������
	if (inet_addr(SERVERADDR))
		dest_addr.sin_addr.s_addr = inet_addr(SERVERADDR);
	else
		if (hst = gethostbyname(SERVERADDR))  // ������� �������� IP ����� �� ��������� ����� �������
			dest_addr.sin_addr.s_addr = ((unsigned long **)hst->h_addr_list)[0][0]; // hst->h_addr_list �������� �� ������ �������, � ������ ���������� �� ������
		else
		{
			cout << "Unknown host: " << WSAGetLastError() << endl;
			closesocket(my_sock);
			WSACleanup();
			return NULL;
		}

	if (connect(my_sock, (sockaddr *)&dest_addr, dasize))
	{
		cout << "������ ���������� c " << SERVERADDR;
		return NULL;
	}

	bool stop = false;
	char buff[1] = { 0 };
	int bytescountrecv = 0;

	while (true)
	{
		bytescountrecv = recvfrom(my_sock, buff, 36, 0, (sockaddr *)&dest_addr, &dasize);
		if (bytescountrecv == SOCKET_ERROR)
		{
			cout << "Recvfrom() error: " << WSAGetLastError() << endl;
			closesocket(my_sock);
			WSACleanup();
			return NULL;
		}

		stop = buff[0];

		closesocket(my_sock);
		WSACleanup();

		return (void*)&stop;
	}
}