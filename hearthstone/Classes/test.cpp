#include <cstdlib>
#include <vector>
#include <Winsock2.h>
#include <stdio.h>
#include <iostream> 
#include "string.h"
using namespace std; 
#pragma comment(lib, "ws2_32.lib")


vector<int> torecv(char* s, char c = '/')
{
	vector<int> vi;
	vi.clear();
	char buf[100];
	char str[100];
	memset(str,0,sizeof(str)); 
	memset(buf,0,sizeof(buf)); 
	int head = 0;
	int tail = 0;
	for (int i = 0; i < strlen(s); i++)
	{
		if (s[i] == c)
		{
			vi.push_back(atoi(str));
			memset(str,0,sizeof(str)); 
		}
		else
		{
			sprintf_s(buf,"%c",s[i],1);
			strcat_s(str, 100, buf);
		}
	}
	return vi;
}

char* tosend(vector<int> vi, char c = '/')
{
	char* message = (char*) malloc(sizeof(char)* 100);
	string str = "";
	char buf[100];
	for (int i = 0; i < vi.size(); i++)
	{
		sprintf_s(buf,100,"%d%c",vi[i],c);
		str += buf;
	}
	strcpy_s(message,100,str.c_str());
	return message;
}

void foo(int a,int b,int c,int d)
{

	int _card = a;
	int _position = b;
	int _side = c;
	int _target = d;
	vector<int> vi;
	vi.push_back(1);
	vi.push_back(_card);
	vi.push_back(_position);
	vi.push_back(_side);
	vi.push_back(_target);
	char* message = tosend(vi);
//	send(sockClient, message, strlen(message) + 1, 0);
	printf("%s",message);
	free(message);
}



void bar()
{
	char* message = message = "4/";
//	send(sockClient, message, strlen(message) + 1, 0);


	while (1)
	{

//		recv(sockClient, message, 100, 0);
		vector<int> vi = torecv(message);

		if (message[0] == '4')				//回合结束
		{
			//TODO
		}
		else
		if (message[0] == '6')				//游戏结束，1表失败，0表胜利
		{
			char tmp = message[2];
			if (tmp == '1')
				exit(1);
			else
				exit(2);
		}
		else
		if (message[0] == '1')
		{
			vector<int> vi = torecv(message);
			int _card = vi[0];
			int _position = vi[1];
			int _side = vi[2];
			int _target = vi[3];

			//TODO
		}
		else
		if (message[0] == '1')				//敌方_minion1 attack 我方_minion2
		{
			vector<int> vi = torecv(message);
			int _minion1 = vi[0];
			int _minion2 = vi[1];


			//TODO
		}
		else
			continue;
	}

}


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




	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	//scanf_s("%d%d%d%d",&a,&b,&c,&d);
	vector<int> vi;
	vi.clear();
	vi.push_back(a);
	vi.push_back(b);
	vi.push_back(c);
	vi.push_back(d);
	foo(a,b,c,d);


	/*
	char* message = (char*) malloc(sizeof(char)* 100);
	message = "1/1/2/3/4/";
	vi = torecv(message);
	for (int i = 0; i < vi.size(); i++)
		printf_s("%d ",vi[i]);
		*/
	return 0;
}