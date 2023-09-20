#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32")

using namespace std;

int main()
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN ServerSock;
	memset(&ServerSock, 0, sizeof(ServerSocket));
	ServerSock.sin_family = PF_INET;
	ServerSock.sin_port = htons(7777);
	inet_pton(AF_INET, "127.0.0.1", &(ServerSock.sin_addr.s_addr));

	connect(ServerSocket, (SOCKADDR*)&ServerSock, sizeof(ServerSock));




	closesocket(ServerSocket);

	WSACleanup();

	return 0;
}