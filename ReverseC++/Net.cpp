#include "Net.h"
#pragma comment(lib,"w2_32.lib")

Net::Net(char * addr,int port)
{

	WSAStartup(MAKEWORD(2, 2), &WsaData);

	Socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, NULL, NULL);

	struct hostent* Host;

	Host = gethostbyname(addr);

	strcpy(IpAddress,inet_ntoa(*((struct in_addr *)Host->h_addr)));

	HostInfo.sin_family = AF_INET;

	HostInfo.sin_port = htons(9999);

	HostInfo.sin_addr.s_addr = inet_addr(IpAddress);

	WSAConnect(Socket, (SOCKADDR *)&HostInfo, sizeof(HostInfo), NULL, NULL, NULL, NULL);

}


Net::~Net()
{

	closesocket(Socket);

	WSACleanup();

}

//final
