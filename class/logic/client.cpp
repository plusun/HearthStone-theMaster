#include "client.h"

vector<int> client::torecv(char* s, char c)
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

char* client::tosend(vector<int> vi, char c)
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

client::client(string str)
{
	int err;   // 客户端Scoket
	SOCKADDR_IN addrServer;// 服务端地址
	WSADATA wsaData;
	WORD wVersionRequested;
	wVersionRequested = MAKEWORD( 2, 2 );
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 )
	{
		return;
	}
	if ( LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 2 )
	{
		// 启动错误，程序结束
		WSACleanup( );
		return;
	} // 新建客户端scoket
	sockClient = socket(AF_INET, SOCK_STREAM, 0); // 定义要连接的服务端地址
	addrServer.sin_addr.S_un.S_addr = inet_addr(str.c_str()); // 目标IP (127.0.0.1是本机地址)
	addrServer.sin_family = AF_INET; // 协议类型是INET
	addrServer.sin_port = htons(6000); // 连接端口6000
	// 让 sockClient 连接到 服务端
	connect(sockClient, (SOCKADDR *)&addrServer, sizeof(SOCKADDR)); // 从服务端获取数据
}

client::client()
{
	int err;   // 客户端Scoket
	SOCKADDR_IN addrServer;// 服务端地址
	WSADATA wsaData;
	WORD wVersionRequested;
	wVersionRequested = MAKEWORD( 2, 2 );
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 )
	{
		return;
	}
	if ( LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 2 )
	{
		// 启动错误，程序结束
		WSACleanup( );
		return;
	} // 新建客户端scoket
	sockClient = socket(AF_INET, SOCK_STREAM, 0); // 定义要连接的服务端地址
	addrServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); // 目标IP (127.0.0.1是本机地址)
	addrServer.sin_family = AF_INET; // 协议类型是INET
	addrServer.sin_port = htons(6000); // 连接端口6000
	// 让 sockClient 连接到 服务端
	connect(sockClient, (SOCKADDR *)&addrServer, sizeof(SOCKADDR)); // 从服务端获取数据
	recv(sockClient, recvBuf, 100, 0);
}

int client::start_game()
{
	char* message = "3/";
	while(1)
	{
		send(sockClient, message, strlen(message) + 1, 0); // 关闭socket
		printf("send: %s\n", message);

		if(recv(sockClient, recvBuf, 100, 0)>0)
		{
			if (recvBuf[0] !=  '7')
				continue;									//error
			if (recvBuf[2] ==  '1')
				return 1;
			else
			if (recvBuf[2] == '0')
				return 0;
			else
				continue;									//error
		}
	}
}

void client::draw_card(int a)
{
	vector<int> vi;
	vi.push_back(8);
	vi.push_back(a);
	char* message = tosend(vi);
	send(sockClient, message, strlen(message) + 1, 0);
	free(message);
}

void client::use_card(int a, int b, int c, int d)
{
	vector<int> vi;
	vi.push_back(1);
	vi.push_back(a);
	vi.push_back(b);
	vi.push_back(c);
	vi.push_back(d);
	char* message = tosend(vi);
	send(sockClient, message, strlen(message) + 1, 0);
	free(message);
}

void client::attack(int a, int b)
{
	vector<int> vi;
	vi.push_back(2);
	vi.push_back(a);
	vi.push_back(b);
	char* message = tosend(vi);
	send(sockClient, message, strlen(message) + 1, 0);
	free(message);
}

void client::end_turn()
{
	vector<int> vi;
	vi.push_back(4);
	char* message = tosend(vi);
	send(sockClient, message, strlen(message) + 1, 0);
	free(message);
}

void client::win(int n)
{
	vector<int> vi;
	vi.push_back(6);
	vi.push_back(n);
	char* message = tosend(vi);
	send(sockClient, message, strlen(message) + 1, 0);
	free(message);
}

void client::login(string usrn, string pswd, int n)
{
	string str = "";
	if (n == 1)
		str = "9/";
	else
		str = "a/";
	str += usrn;
	str += "/";
	str += pswd;
	str += "/";
	char* message = (char*) malloc(sizeof(char) * 100);
	strcpy_s(message,100,str.c_str());
	send(sockClient, message, strlen(message) + 1, 0);
	free(message);
}

bool client::check_login()
{
	char* message = (char*) malloc(sizeof(char) * 100);
	do
	{
	recv(sockClient, message, 100, 0);
	}
	while (message[0] != '9');
	vector<int> vi = torecv(message);
	free(message);
	if (vi[0] == 9 && vi[1] == 1)
		return true;
	else
		return false;
}

vector<int> client::opponent_turn()
{
	char* message = (char*) malloc(sizeof(char) * 100);
	recv(sockClient, message, 100, 0);
	vector<int> vi = torecv(message);
	free(message);
	return vi;
}