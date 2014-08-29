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
	int err;   // �ͻ���Scoket
	SOCKADDR_IN addrServer;// ����˵�ַ
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
		// �������󣬳������
		WSACleanup( );
		return;
	} // �½��ͻ���scoket
	sockClient = socket(AF_INET, SOCK_STREAM, 0); // ����Ҫ���ӵķ���˵�ַ
	addrServer.sin_addr.S_un.S_addr = inet_addr(str.c_str()); // Ŀ��IP (127.0.0.1�Ǳ�����ַ)
	addrServer.sin_family = AF_INET; // Э��������INET
	addrServer.sin_port = htons(6000); // ���Ӷ˿�6000
	// �� sockClient ���ӵ� �����
	connect(sockClient, (SOCKADDR *)&addrServer, sizeof(SOCKADDR)); // �ӷ���˻�ȡ����
}

client::client()
{
	//char buf[1000];
	//getcwd(buf,1000);

	string filename = "ip.txt";
	ifstream file(filename.c_str(),ifstream::in);
	string str;
	getline(file,str);

	int err;   // �ͻ���Scoket
	SOCKADDR_IN addrServer;// ����˵�ַ
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
		// �������󣬳������
		WSACleanup( );
		return;
	} // �½��ͻ���scoket
	sockClient = socket(AF_INET, SOCK_STREAM, 0); // ����Ҫ���ӵķ���˵�ַ
	addrServer.sin_addr.S_un.S_addr = inet_addr(str.c_str()); // Ŀ��IP (127.0.0.1�Ǳ�����ַ)
	addrServer.sin_family = AF_INET; // Э��������INET
	addrServer.sin_port = htons(6000); // ���Ӷ˿�6000
	// �� sockClient ���ӵ� �����
	connect(sockClient, (SOCKADDR *)&addrServer, sizeof(SOCKADDR)); // �ӷ���˻�ȡ����
	recv(sockClient, recvBuf, 100, 0);
}

int client::start_game()
{
	char* message = "3/";
	while(1)
	{
		send(sockClient, message, strlen(message) + 1, 0); // �ر�socket
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

void client::recv_log()
{
	char* buf = new char[1000];
	//memset(buf,0,strlen(buf));
	int n = recv(sockClient, buf, 1000, 0);
	buf[n] = '\0';
	ofstream file("log.txt",ios::out);
	file << buf;
	file.close();
	delete []buf;
}