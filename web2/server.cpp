#include <Winsock2.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")
#include <stdlib.h>
#include <windows.h> 
    

int main()
{
int err; // 错误信息
int len;
char sendBuf[100]; // 发送至客户端的字符串
char recvBuf[100]; // 接受客户端返回的字符串
char recvBuf1[100];
char recvBuf2[100];
SOCKET sockServer; // 服务端Socket
SOCKADDR_IN addrServer;// 服务端地址
SOCKET sockClient1; // 客户端 Scoket
SOCKET sockClient2;
SOCKADDR_IN addrClient1;// 客户端地址
SOCKADDR_IN addrClient2;
WSADATA wsaData; // winsock 结构体
WORD wVersionRequested;// winsock 的版本
// 配置 Windows Socket版本
wVersionRequested = MAKEWORD( 2, 2 ); // 初始化 Windows Socket
err = WSAStartup( wVersionRequested, &wsaData );
if ( err != 0 )
{
// 启动错误，程序结束
return 0;
}
/*
* 确认WinSock DLL支持2.2
* 请注意如果DLL支持的版本大于2.2至2.2
* 它仍然会返回wVersion2.2的版本
*/
if ( LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 2 )
{
// 启动错误，程序结束
WSACleanup(); // 终止Winsock 2 DLL (Ws2_32.dll) 的使用
return 0;
}
// 定义服务器端
sockServer = socket(AF_INET, SOCK_STREAM, 0);
// 设置服务端
addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY); // 本机IP
addrServer.sin_family = AF_INET; // 协议类型是INET
addrServer.sin_port = htons(6000); // 绑定端口6000
// 将服务器端socket绑定在本地端口
bind(sockServer, (SOCKADDR *)&addrServer, sizeof(SOCKADDR)); // Listen 监听端
listen(sockServer, 2); // 5 为等待连接数目
printf("服务器已启动:\n监听中...\n");
len = sizeof(SOCKADDR);

while (1)
{
// accept 会阻塞进程，直到有客户端连接上来为止
sockClient1 = accept(sockServer, (SOCKADDR *)&addrClient1, &len); // 当客户端连接上来时, 拼接如下字符串
sockClient2 = accept(sockServer, (SOCKADDR *)&addrClient2, &len);
sprintf(sendBuf, "欢迎 ip: %s 的用户连接, 这里是 HearthStone 的服务器\n", inet_ntoa(addrClient1.sin_addr)); // 向客户端发送字符串
send(sockClient1, sendBuf, strlen(sendBuf) + 1, 0); // 获取客户端返回的数据
sprintf(sendBuf, "欢迎 ip: %s 的用户连接, 这里是 HearthStone 的服务器\n", inet_ntoa(addrClient2.sin_addr));
send(sockClient2, sendBuf, strlen(sendBuf) + 1, 0); 

	while (1)
	{
		char a ,b;
		recv(sockClient1, recvBuf1, 100, 0);
		printf("%s\n",recvBuf1);
		recv(sockClient2, recvBuf2, 100, 0);
		printf("%s\n",recvBuf2);
		a = recvBuf1[0];
		b = recvBuf2[0];
		printf("%d,%d\n",a,b);
		if(a == b  && b == '3')
		{
			sprintf(recvBuf1, "7/1/");
			sprintf(recvBuf2, "7/0/");
			send(sockClient1, recvBuf1, strlen(recvBuf) + 1, 0);
			send(sockClient2, recvBuf2, strlen(recvBuf) + 1, 0);

			break;
		}
	}
while (1)
{
	while(1)
	{
		printf("**\n");
		recv(sockClient1, recvBuf1, 100, 0);
			printf("rec:%s\n",recvBuf1);
		if(recvBuf1[0] == '6')
		{
			send(sockClient2, recvBuf1, strlen(recvBuf1) + 1, 0);
			closesocket(sockClient1);
			closesocket(sockClient2);
			exit(0);
		}
		else if(recvBuf1[0] == '1' | recvBuf1[0] == '2' ||recvBuf1[0] == '5')
		{
        send(sockClient2, recvBuf1, strlen(recvBuf1) + 1, 0);
				printf("%s\n",recvBuf1);
		}
		else if(recvBuf1[0] == '4')
		{
		send(sockClient2, recvBuf1, strlen(recvBuf1) + 1, 0);
		break;
		}
	}

	while(1)
	{
		recv(sockClient2, recvBuf2, 100, 0);
		if(recvBuf2[0] == '6')
		{
			send(sockClient1, recvBuf2, strlen(recvBuf2) + 1, 0);
			closesocket(sockClient1);
			closesocket(sockClient2);
			exit(0);
		}
		else if(recvBuf2[0] == '1' || recvBuf2[0] == '2' ||recvBuf2[0] == '5')
		{
        send(sockClient1, recvBuf2, strlen(recvBuf2) + 1, 0);
		}
		else if(recvBuf2[0] == '4')
		{
		send(sockClient1, recvBuf2, strlen(recvBuf2) + 1, 0);
		break;
		}
	}
}
// 打印客户端返回的数据
//printf("%s\n", recvBuf);
// 关闭socket
}
}

