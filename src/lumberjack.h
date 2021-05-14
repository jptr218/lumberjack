#pragma once

#pragma comment(lib, "ws2_32.lib")

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <winsock2.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <time.h>
#include <iostream>
#include <mstcpip.h>
using namespace std;

string exec(string cmd);
string extractBytes(char* buf, int bytes);

void write(SOCKET sock, string buf);
void read(SOCKET sock);

string getHost(string email);
void sendMail(SOCKET sock, string host, string from, string to, string subject, string message);