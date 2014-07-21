#include <Winsock2.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "pthreadVC2.lib")
#include <stdlib.h>
#include <windows.h> 
#include <iostream>
#include <fstream>
#include <vector>
//#include <mutex>
//#include <thread>
//#include <condition_variable>
#include <pthread.h>
using namespace std;
   
vector<SOCKET> vs;
//mutex mtx;
//condition_variable cv;
//bool ready = false;


pthread_t tid1;
pthread_t tid2;
pthread_t tid3;
pthread_mutex_t mutex; 
pthread_mutex_t wmutex;

struct mypara 
{ 
    SOCKET para1;//参数1 
    SOCKET para2;//参数2 
	mypara(SOCKET p1,SOCKET p2):para1(p1),para2(p2){};
};

char* get_username(char* str)
{
	char* id = (char*)malloc(sizeof(char)*100);
	str++;str++;
	int i;
	for(i = 0; *str != '/' ; str++)
		id[i] = *str;
	id[i+1]='\0';
	return id;
}

bool SearchUser(char *ID,char * Filename)
{
	char ch[200];
	bool judge=false;
	fstream in;
	in.open(Filename,ios::in);
  while(in.getline(ch,200))
  {
   if(strstr(ch,ID)!=NULL)
   {
    judge=true;
    printf("%s\n",ch);
	break;
   }
  }
  if(!judge)
   printf("Wrong ID or PSW");
  in.close();
  return judge;
}

bool SearchID(char *ID,char *Filename)
{
	bool judge = false;
	fstream in;
	in.open(Filename,ios::in|ios::out|ios::app);

	char* id = get_username(ID);
	char* ch = (char*)malloc(sizeof(char)*100);
	while(in.getline(ch,100))
	{
		id = get_username(ID);
		ch = get_username(ch);
		if(ch == NULL) break;
		if(strcmp(id,ch) == 0)			//find exist username
		{
			judge = true;
			printf("%s\n",ch);
			break;
		}
	}
	in.sync();
	in.flush();
	in.close();
	if(judge)
		printf("ID exist!");
	else
	{
		fstream in2;
		in2.open(Filename,ios::in|ios::out|ios::app);
		in2<<ID<<endl;
		in2.sync();
		in2.flush();
		in2.close();
	}


	return judge;
}


void* start_game(void* arg)
{
	SOCKET sockClient1 = ((struct mypara *) arg)->para1;
	SOCKET sockClient2 = ((struct mypara *) arg)->para2;
	char recvBuf1[100];
	char recvBuf2[100];
	//char filename[] = "record.log"; // 此处写入文件名 
	//ofstream fout(filename);

	sprintf_s(recvBuf1, "7/1/");
	sprintf_s(recvBuf2, "7/0/");
	send(sockClient1, recvBuf1, strlen(recvBuf1) + 1, 0);
	send(sockClient2, recvBuf2, strlen(recvBuf2) + 1, 0);

	while (1)
		{
			while(1)
			{
				if(recv(sockClient1, recvBuf1, 100, 0)<=0)
					continue;
					printf("C1:%s\n",recvBuf1);
					//fout<<"C1:"<<recvBuf1<<"\n";
				if(recvBuf1[0] == '6')
				{
					send(sockClient2, recvBuf1, strlen(recvBuf1) + 1, 0);
					closesocket(sockClient1);
					closesocket(sockClient2);
					return NULL;
				}
				else if(recvBuf1[0] == '1' || recvBuf1[0] == '2' ||recvBuf1[0] == '5' ||recvBuf1[0] == '8')
				{
					send(sockClient2, recvBuf1, strlen(recvBuf1) + 1, 0);
				}
				else if(recvBuf1[0] == '4')
				{
					send(sockClient2, recvBuf1, strlen(recvBuf1) + 1, 0);
					break;
				}
			}

			while(1)
			{
				if(recv(sockClient2, recvBuf2, 100, 0)<=0)
					continue;
				printf("C2:%s\n",recvBuf2);
				//fout<<"C2:"<<recvBuf2<<"\n";
				if(recvBuf2[0] == '6')
				{
					send(sockClient1, recvBuf2, strlen(recvBuf2) + 1, 0);
					closesocket(sockClient1);
					closesocket(sockClient2);
					return NULL;
				}
				else if(recvBuf2[0] == '1' || recvBuf2[0] == '2' ||recvBuf2[0] == '5' ||recvBuf2[0] == '8')
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

}


void* find_game(void* arg)
{
	while (1)
	{
		pthread_mutex_lock(&mutex);
		//unique_lock <mutex> lck(mtx);
		//while (!ready) cv.wait(lck);
		//ready = false;
		while (vs.size() >= 2)
		{
			SOCKET s1 = vs[0];
			SOCKET s2 = vs[1];
			vs.erase(vs.begin());
			vs.erase(vs.begin());
			pthread_create(&tid3, NULL, start_game, &mypara(s1,s2)); 
			//std::thread t0(start_game,s1,s2);
		}
		pthread_mutex_unlock(&mutex);
	}
}

void* login(void* arg)
{
	pthread_detach(pthread_self());
	SOCKET client = (SOCKET)arg;
	char sendBuf[100];
	sprintf_s(sendBuf, "欢迎用户连接, 这里是 HearthStone 的服务器\n"); // 向客户端发送字符串
	send(client, sendBuf, strlen(sendBuf) + 1, 0); // 获取客户端返回的数据

	char recvBuf[100];
	while (1)
	{

		if (recv(client, recvBuf, 100, 0) <= 0)
			continue;
		if (recvBuf[0] == '9')
			break;
		if (recvBuf[0] == 'a')
			{
				recvBuf[0] = '9';
				if(!SearchID(recvBuf,"user.log"))
				{
					break;
				}
				else
				{
					send(client,"9/2/",5,0);
					continue;
				}
			}
	}
	printf("recv:%s\n",recvBuf);

	if( SearchUser(recvBuf,"user.log"))  
	{
		//login successfully
		char* buf = "9/1/";
		send(client, buf, 10, 0);
		while (1)
		{
			if (recv(client, recvBuf, 100, 0) <= 0 || recvBuf[0] != '3')
				continue;
			//std::unique_lock <std::mutex> lck(mtx);
			vs.push_back(client);
			//ready = true;
			//cv.notify_all();
			return NULL;
		}
	}
}

void _accept(SOCKET sockServer)
{
	int len;
	SOCKET sockClient;
	SOCKADDR_IN addrClient;

}


int main()
{
	int err; // 错误信息
	int len;
	SOCKET sockServer; // 服务端Socket
	SOCKADDR_IN addrServer;// 服务端地址
	SOCKET sockClient; // 客户端 Scoket
	SOCKADDR_IN addrClient;// 客户端地址
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
	listen(sockServer, 10); // 5 为等待连接数目
	printf("服务器已启动:\n监听中...\n");
	len = sizeof(SOCKADDR);

	pthread_mutex_init(&mutex, NULL); 
	pthread_mutex_init(&wmutex, NULL); 
	
	pthread_create(&tid1, NULL, find_game, NULL); 
	//std::thread t1(find_game);
	//t1.detach();
	//
	//std::thread t2(_accept,sockServer);
	//t2.detach();

	while (1)
	{
		// accept 会阻塞进程，直到有客户端连接上来为止
		sockClient = accept(sockServer, (SOCKADDR *)&addrClient, &len); // 当客户端连接上来时, 拼接如下字符串
		//printf("%d",WSAGetLastError());
		//printf("%d",sockClient);
		if (sockClient != -1) 
		{
			pthread_create(&tid2, NULL, login, (void*)sockClient); 
		}
	}

	//should never reach here
	pthread_mutex_destroy(&mutex); 
	pthread_mutex_destroy(&wmutex);

	// 打印客户端返回的数据
	//printf("%s\n", recvBuf);
	// 关闭socket
}

