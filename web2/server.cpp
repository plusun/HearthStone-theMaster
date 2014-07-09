#include <Winsock2.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")
#include <stdlib.h>
#include <windows.h> 
#include <iostream>
#include <fstream>
using namespace std;
    

int main()
{
	char filename[] = "record.txt"; // �˴�д���ļ��� 

	int err; // ������Ϣ
	int len;
	char sendBuf[100]; // �������ͻ��˵��ַ���
	char recvBuf[100]; // ���ܿͻ��˷��ص��ַ���
	char recvBuf1[100];
	char recvBuf2[100];
	SOCKET sockServer; // �����Socket
	SOCKADDR_IN addrServer;// ����˵�ַ
	SOCKET sockClient1; // �ͻ��� Scoket
	SOCKET sockClient2;
	SOCKADDR_IN addrClient1;// �ͻ��˵�ַ
	SOCKADDR_IN addrClient2;
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
	listen(sockServer, 2); // 5 Ϊ�ȴ�������Ŀ
	printf("������������:\n������...\n");
	len = sizeof(SOCKADDR);

	ofstream fout(filename);

	while (1)
	{
		// accept ���������̣�ֱ���пͻ�����������Ϊֹ
		sockClient1 = accept(sockServer, (SOCKADDR *)&addrClient1, &len); // ���ͻ�����������ʱ, ƴ�������ַ���
		sockClient2 = accept(sockServer, (SOCKADDR *)&addrClient2, &len);
		sprintf_s(sendBuf, "��ӭ ip: %s ���û�����, ������ HearthStone �ķ�����\n", inet_ntoa(addrClient1.sin_addr)); // ��ͻ��˷����ַ���
		send(sockClient1, sendBuf, strlen(sendBuf) + 1, 0); // ��ȡ�ͻ��˷��ص�����
		sprintf_s(sendBuf, "��ӭ ip: %s ���û�����, ������ HearthStone �ķ�����\n", inet_ntoa(addrClient2.sin_addr));
		send(sockClient2, sendBuf, strlen(sendBuf) + 1, 0); 

			while (1)
			{
				char a ,b;
				if(recv(sockClient1, recvBuf1, 100, 0)<=0)
					continue;
				printf("C1:%s\n",recvBuf1);
				fout<<"C1:"<<recvBuf1<<"\n";
				if(recv(sockClient2, recvBuf2, 100, 0)<=0)
					continue;
				printf("C2:%s\n",recvBuf2);
				fout<<"C2:"<<recvBuf1<<"\n";
				a = recvBuf1[0];
				b = recvBuf2[0];
				if(a == b  && b == '3')
				{
					sprintf_s(recvBuf1, "7/1/");
					sprintf_s(recvBuf2, "7/0/");
					send(sockClient1, recvBuf1, strlen(recvBuf) + 1, 0);
					send(sockClient2, recvBuf2, strlen(recvBuf) + 1, 0);

					break;
				}
			}
		while (1)
		{
			while(1)
			{
				if(recv(sockClient1, recvBuf1, 100, 0)<=0)
					continue;
					printf("C1:%s\n",recvBuf1);
					fout<<"C1:"<<recvBuf1<<"\n";
				if(recvBuf1[0] == '6')
				{
					send(sockClient2, recvBuf1, strlen(recvBuf1) + 1, 0);
					closesocket(sockClient1);
					closesocket(sockClient2);
					return 0;
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
				fout<<"C2:"<<recvBuf2<<"\n";
				if(recvBuf2[0] == '6')
				{
					send(sockClient1, recvBuf2, strlen(recvBuf2) + 1, 0);
					closesocket(sockClient1);
					closesocket(sockClient2);
					return 0;
				}
				else if(recvBuf2[0] == '1' || recvBuf2[0] == '2' ||recvBuf2[0] == '5' ||recvBuf1[0] == '8')
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
	// ��ӡ�ͻ��˷��ص�����
	//printf("%s\n", recvBuf);
	// �ر�socket
	}
}

