#include <Winsock2.h>
#include <stdio.h>
#include <iostream> 
using namespace std; 
#pragma comment(lib, "ws2_32.lib")
int main()
{
	int err; char *message; char recvBuf[100]; SOCKET sockClient; // 客户端Scoket
	SOCKADDR_IN addrServer;// 服务端地址
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
		// 启动错误，程序结束
		WSACleanup( );
		return 0;
	} // 新建客户端scoket
	sockClient = socket(AF_INET, SOCK_STREAM, 0); // 定义要连接的服务端地址
	addrServer.sin_addr.S_un.S_addr = inet_addr("192.168.201.26"); // 目标IP (127.0.0.1是本机地址)
	addrServer.sin_family = AF_INET; // 协议类型是INET
	addrServer.sin_port = htons(6000); // 连接端口6000
	// 让 sockClient 连接到 服务端
	connect(sockClient, (SOCKADDR *)&addrServer, sizeof(SOCKADDR)); // 从服务端获取数据
	if(recv(sockClient, recvBuf, 100, 0)>0) // 打印数据
		printf("%s\n", recvBuf); 
	//message = "hello world"; // 发送数据到服务端


	message = (char*) malloc(sizeof(char)*100);
	while(1)
	{
		scanf_s("%s",message,100);
		send(sockClient, message, strlen(message) + 1, 0); // 关闭socket
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
			send(sockClient, message, strlen(message) + 1, 0); // 关闭socket
			if(message[0] == '4' )
				break;
			if(message[0] == '6')
				exit(0);
		}


		while(1)
		{
		if(recv(sockClient, recvBuf, 100, 0)<0 || recvBuf[0]< '1' || recvBuf[0] > '7')
			continue;
		//else if(recv(sockClient, recvBuf, 100, 0)==0)
		//{
		//	exit(0);
		//}
		else
			printf("%s\n", recvBuf);
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
		if(recv(sockClient, recvBuf, 100, 0)<0 || recvBuf[0]< '1' || recvBuf[0] > '7')
			continue;
		//else if(recv(sockClient, recvBuf, 100, 0)==0)
		//{
		//	exit(0);
		//}
		else
			printf("%s\n", recvBuf);
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
			send(sockClient, message, strlen(message) + 1, 0); // 关闭socket
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
	getchar(); // 暂停
	return 0;
}