#include <Winsock2.h>
#include <stdio.h>
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
  addrServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); // Ŀ��IP (127.0.0.1�Ǳ�����ַ)
  addrServer.sin_family = AF_INET; // Э��������INET
  addrServer.sin_port = htons(6000); // ���Ӷ˿�6000
  // �� sockClient ���ӵ� �����
  connect(sockClient, (SOCKADDR *)&addrServer, sizeof(SOCKADDR)); // �ӷ���˻�ȡ����
  recv(sockClient, recvBuf, 100, 0); // ��ӡ����
  printf("%s\n", recvBuf); message = "��������~"; // �������ݵ������
  send(sockClient, message, strlen(message) + 1, 0); // �ر�socket
  closesocket(sockClient);
  WSACleanup();
  getchar(); // ��ͣ
  return 0;
}
