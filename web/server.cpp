#include <Winsock2.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")
int main()
{
int err; // ������Ϣ
int len;
char sendBuf[100]; // �������ͻ��˵��ַ���
char recvBuf[100]; // ���ܿͻ��˷��ص��ַ���
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
listen(sockServer, 5); // 5 Ϊ�ȴ�������Ŀ
printf("������������:\n������...\n");
len = sizeof(SOCKADDR);
while (1)
{
// accept ���������̣�ֱ���пͻ�����������Ϊֹ
sockClient = accept(sockServer, (SOCKADDR *)&addrClient, &len); // ���ͻ�����������ʱ, ƴ�������ַ���
sprintf(sendBuf, "��ӭ ip: %s ���û�����, ������ HearthStone �ķ�����\n", inet_ntoa(addrClient.sin_addr)); // ��ͻ��˷����ַ���
send(sockClient, sendBuf, strlen(sendBuf) + 1, 0); // ��ȡ�ͻ��˷��ص�����
recv(sockClient, recvBuf, 100, 0);
// ��ӡ�ͻ��˷��ص�����
printf("%s\n", recvBuf);
// �ر�socket
closesocket(sockClient);
}
}