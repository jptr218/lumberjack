#include "lumberjack.h"

int main(int argc, char* argv[])
{
    if (argc < 5) {
        cout << "Usage:" << endl << "lumberjack [from] [to] [subject] [message]" << endl;
        return 1;
    }

    WSADATA wd;
    SOCKET sock;
    sockaddr_in server;
    hostent* hp;

    string from = argv[1];
    string to = argv[2];
    string subject = argv[3] + string("\r\n");
    string message = argv[4] + string("\r\n");
    string host = getHost(to);

    if (WSAStartup(MAKEWORD(2, 2), &wd) != 0) {
        cout << "Error initialising Winsock. Code " << WSAGetLastError() << endl;
        return 0;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET)
    {
        cout << "Error creating socket." << endl;
        return 0;
    }

    server.sin_family = AF_INET;
    hp = gethostbyname(host.c_str());
    if (hp == (struct hostent*)0)
    {
        cout << "Error resolving SMTP hostname. Are you sure you've typed the source email right?" << endl;
        return 0;
    }

    memcpy((char*)&server.sin_addr, (char*)hp->h_addr, hp->h_length);
    server.sin_port = htons(25);
    if (connect(sock, (struct sockaddr*)&server, sizeof server) == -1)
    {
        cout << "Error connecting to SMTP server." << endl;
        return 0;
    }

    sendMail(sock, host, from, to, subject, message);

    closesocket(sock);
    return 1;
}