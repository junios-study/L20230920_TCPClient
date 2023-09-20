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

	char Message[1024] = { 0, };
	int RecvByte = recv(ServerSocket, Message, sizeof(Message), 0);

	cout << Message << endl;

	char FirstNumberString[100] = { 0, };
	char SecondNumberString[100] = { 0, };
	char Operator = 0;

	memcpy(FirstNumberString, Message, 2);
	memcpy(SecondNumberString, Message + 3, 2);
	Operator = Message[2];

	int FirstNumber = atoi(FirstNumberString);
	int SecondNumber = atoi(SecondNumberString);

	int ResultNumber = FirstNumber + SecondNumber;

	char Result[1024] = { 0, };
	itoa(ResultNumber, Result, 10);

	int SendByte = send(ServerSocket, Result, (int)strlen(Result), 0);

	closesocket(ServerSocket);

	WSACleanup();

	return 0;
}