#ifndef __CLIENT_H__
#define __CLIENT_H__
#include <cstdlib>
#include <vector>
#include <Winsock2.h>
#include <stdio.h>
#include <iostream> 
#include "string.h"
#include <fstream>
#include <sstream>
using namespace std; 
#pragma comment(lib, "ws2_32.lib")


class client
{
public:
	SOCKET sockClient;
	char recvBuf[100];
	vector<int> torecv(char* s, char c = '/');
	char* tosend(vector<int> vi, char c = '/');
	client(string str);
	client();
	int start_game();						//return = 1, go first;return = 0, go second
	void draw_card(int a);
	void use_card(int a, int b = -1, int c = 0, int d = 0);
	void attack(int a, int b);
	void end_turn();
	void win(int n = 1);
	void login(string usrn, string pswd, int n);
	bool check_login();
	vector<int> opponent_turn();
};
#endif