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
pthread_cond_t cond;
pthread_attr_t a;

struct mypara 
{ 
    SOCKET para1;//����1 
    SOCKET para2;//����2 
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
	pthread_mutex_lock(&wmutex);
	char ch[200];
	bool judge=false;
	fstream in;
	in.open(Filename,ios::in);
  while(in.getline(ch,200))
  {
   if(strstr(ch,ID)!=NULL)
   {
    judge=true;
    std::printf("%s\n",ch);
	break;
   }
  }
  if(!judge)
   std::printf("Wrong ID or PSW");
  in.close();
  pthread_mutex_unlock(&wmutex);
  return judge;
}

bool SearchID(char *ID,char *Filename)
{
	pthread_mutex_lock(&wmutex);
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
			std::printf("%s\n",ch);
			break;
		}
	}
	in.sync();
	in.flush();
	in.close();
	if(judge)
		std::printf("ID exist!");
	else
	{
		fstream in2;
		in2.open(Filename,ios::in|ios::out|ios::app);
		in2<<ID<<endl;
		in2.sync();
		in2.flush();
		in2.close();

	}

	pthread_mutex_unlock(&wmutex);
	return judge;
}


void* start_game(void* arg)
{
	SOCKET sockClient1 = ((struct mypara *) arg)->para1;
	SOCKET sockClient2 = ((struct mypara *) arg)->para2;
	char recvBuf1[100];
	char recvBuf2[100];
	//char filename[] = "record.log"; // �˴�д���ļ��� 
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
				{
					if (WSAGetLastError() == WSAECONNRESET)
						return NULL;
					continue;
				}
				std::printf("C1:%s\n",recvBuf1);
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
				{
					if (WSAGetLastError() == WSAECONNRESET)
						return NULL;
					continue;
				}
				std::printf("C2:%s\n",recvBuf2);
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
		pthread_cond_wait(&cond, &mutex);

		while (vs.size() >= 2)
		{
			SOCKET s1 = vs[0];
			SOCKET s2 = vs[1];
			vs.erase(vs.begin());
			vs.erase(vs.begin());
			pthread_create(&tid3, &a, start_game, &mypara(s1,s2)); 
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
	sprintf_s(sendBuf, "��ӭ�û�����, ������ HearthStone �ķ�����\n"); // ��ͻ��˷����ַ���
	send(client, sendBuf, strlen(sendBuf) + 1, 0); // ��ȡ�ͻ��˷��ص�����

	while (1)
	{

		char recvBuf[100];
		while (1)
		{
			if (recv(client, recvBuf, 100, 0) < 0)
			{
				if (WSAGetLastError() == WSAECONNRESET)
					return NULL;
				continue;
			}

			if (recvBuf[0] == '9')
				break;
			if (recvBuf[0] == 'a')
				{
					recvBuf[0] = '9';
					if(!SearchID(recvBuf,"user.log"))
					{
						//send(client,"9/1/",5,0);
						break;
					}
					else
					{
						send(client,"9/2/",5,0);
						continue;
					}
				}
		}
		std::printf("recv:%s\n",recvBuf);

		if( SearchUser(recvBuf,"user.log"))  
		{
			//login successfully
			send(client, "9/1/", 5, 0);
			while (1)
			{
				if (recv(client, recvBuf, 100, 0) < 0 || recvBuf[0] != '3')
				{
					if (WSAGetLastError() == WSAECONNRESET)
						return NULL;
					continue;
				}
				pthread_cond_signal(&cond); 
				vs.push_back(client);
				return NULL;
			}
		}
		else
		{
			send(client,"9/2/",5,0);
			continue;
		}

	}
}

int main()
{
	int err; // ������Ϣ
	int len;
	SOCKET sockServer; // �����Socket
	SOCKADDR_IN addrServer;// ����˵�ַ
	SOCKET sockClient; // �ͻ��� Scoket
	SOCKADDR_IN addrClient;// �ͻ��˵�ַ
	WSADATA wsaData; // winsock �ṹ��
	WORD wVersionRequested;// winsock �İ汾
	// ���� Windows Socket�汾
	wVersionRequested = MAKEWORD( 2, 2 ); // ��ʼ�� Windows Socket
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 )
	{
		// �������󣬳������
		return 0;
	}
	/*
	* ȷ��WinSock DLL֧��2.2
	* ��ע�����DLL֧�ֵİ汾����2.2��2.2
	* ����Ȼ�᷵��wVersion2.2�İ汾
	*/
	if ( LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 2 )
	{
		// �������󣬳������
		WSACleanup(); // ��ֹWinsock 2 DLL (Ws2_32.dll) ��ʹ��
		return 0;
	}
	// �����������
	sockServer = socket(AF_INET, SOCK_STREAM, 0);
	// ���÷����
	addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY); // ����IP
	addrServer.sin_family = AF_INET; // Э��������INET
	addrServer.sin_port = htons(6000); // �󶨶˿�6000
	// ����������socket���ڱ��ض˿�
	bind(sockServer, (SOCKADDR *)&addrServer, sizeof(SOCKADDR)); // Listen ������
	listen(sockServer, 10); // 5 Ϊ�ȴ�������Ŀ
	std::printf("������������:\n������...\n");
	len = sizeof(SOCKADDR);

	pthread_mutex_init(&mutex, NULL); 
	pthread_mutex_init(&wmutex, NULL); 
	pthread_cond_init(&cond, NULL);
	pthread_attr_init(&a);  //��ʼ���߳�����
	pthread_attr_setdetachstate(&a, PTHREAD_CREATE_DETACHED);      //�����߳�����

	pthread_create(&tid1, &a, find_game, NULL); 

	while (1)
	{
		// accept ���������̣�ֱ���пͻ�����������Ϊֹ
		sockClient = accept(sockServer, (SOCKADDR *)&addrClient, &len); // ���ͻ�����������ʱ, ƴ�������ַ���
		if (sockClient != -1) 
		{
			pthread_create(&tid2, &a, login, (void*)sockClient); 
		}
	}

	//should never reach here
	pthread_mutex_destroy(&mutex); 
	pthread_mutex_destroy(&wmutex);

	// ��ӡ�ͻ��˷��ص�����
	//printf("%s\n", recvBuf);
	// �ر�socket
}

