#include <Winsock2.h>
#include <stdio.h>
#include <iostream> 
using namespace std; 
#pragma comment(lib, "ws2_32.lib")
int main()
{
	int err; char *message; char recvBuf[100]; SOCKET sockClient; // �ͻ���Scoket
	SOCKADDR_IN addrServer;// ����˵�ַ
	WSADATA wsaData;
	WORD wVersionRequested;
	wVersionRequested = MAKEWORD( 2, 2 );
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 )
	{
		return 0;
	}
	if ( LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 2 )
	{
		// �������󣬳������
		WSACleanup( );
		return 0;
	} // �½��ͻ���scoket
	sockClient = socket(AF_INET, SOCK_STREAM, 0); // ����Ҫ���ӵķ���˵�ַ
	addrServer.sin_addr.S_un.S_addr = inet_addr("192.168.201.28"); // Ŀ��IP (127.0.0.1�Ǳ�����ַ)
	addrServer.sin_family = AF_INET; // Э��������INET
	addrServer.sin_port = htons(6000); // ���Ӷ˿�6000
	// �� sockClient ���ӵ� �����
	connect(sockClient, (SOCKADDR *)&addrServer, sizeof(SOCKADDR)); // �ӷ���˻�ȡ����
	if(recv(sockClient, recvBuf, 100, 0)>0) // ��ӡ����
		printf("%s\n", recvBuf); 
	//message = "hello world"; // �������ݵ������


	message = (char*) malloc(sizeof(char)*100);
	while(1)
	{
		scanf_s("%s",message,100);
		send(sockClient, message, strlen(message) + 1, 0); // �ر�socket
		printf("send: %s\n", message);

		if(message[0] == '3' && recv(sockClient, recvBuf, 100, 0)>0)
			break;
	}

	printf("received: %s\n",recvBuf);

	if(recvBuf[2] == '1')
	{
	while(1)
	{
		while(1)
		{
			scanf_s("%s",message,100);
			send(sockClient, message, strlen(message) + 1, 0); // �ر�socket
			if(message[0] == '4' )
				break;
			if(message[0] == '6')
				exit(0);
		}


		while(1)
		{
		if(recv(sockClient, recvBuf, 100, 0)<0 || recvBuf[0]< '1' || recvBuf[0] > '8')
			continue;
		//else if(recv(sockClient, recvBuf, 100, 0)==0)
		//{
		//	exit(0);
		//}
		else
			printf("recv:%s\n", recvBuf);
		if(recvBuf[0] == '4')
		{
			break;
		}
		if(recvBuf[0] == '6')
			exit(0);
		}
	}
	}
	else if(recvBuf[2] == '0')
	{
	while(1)
	{
		while(1)
		{
		if(recv(sockClient, recvBuf, 100, 0)<0 || recvBuf[0]< '1' || recvBuf[0] > '8')
			continue;
		//else if(recv(sockClient, recvBuf, 100, 0)==0)
		//{
		//	exit(0);
		//}
		else
			printf("recv:%s\n", recvBuf);
		if(recvBuf[0] == '4')
		{
			break;
		}
		if(recvBuf[0] == '6')
			exit(0);
		}
	
		while(1)
		{
			scanf_s("%s",message,100);
			send(sockClient, message, strlen(message) + 1, 0); // �ر�socket
			if(message[0] == '4')
			break;
			if(message[0] == '6')
				exit(0);
		}

	//recv(sockClient, recvBuf, 100, 0);
	//printf("%s\n", recvBuf);
	}
	}


	closesocket(sockClient);
	WSACleanup();
	getchar(); // ��ͣ
	return 0;
}