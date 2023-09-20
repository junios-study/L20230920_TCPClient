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
	int First = 0;
	int Second = 0;
	char Operator = 0;

	memcpy(&First, Message, 4);
	memcpy(&Second, Message + 5, 4);
	Operator = Message[4];
	int Result = 0;

	switch (Operator)
	{
	case '+':
		Result = First + Second;
		break;
	case '-':
		Result = First - Second;
		break;
	case '/':
		Result = First / Second;
		break;
	case '*':
		Result = First * Second;
		break;
	case '%':
	default:
		Result = First % Second;
		break;
	}

	cout << First;
	cout << Message[4];
	cout << Second;
	cout << "=";
	cout << Result << endl;

	char ResultMessaage[1024] = { 0, };
	memcpy(ResultMessaage, &Result, sizeof(Result));

	int SendByte = send(ServerSocket, ResultMessaage, 4, 0);
	closesocket(ServerSocket);

	WSACleanup();

	return 0;
}