#include "lumberjack.h"

string extractBytes(char* buf, int bytes) {
    string result;
    for (int i = 0; i < bytes; i++) {
        result += buf[i];
    }
    return result;
}

void write(SOCKET sock, string buf) {
    if (send(sock, buf.c_str(), buf.length(), NULL) == SOCKET_ERROR) {
        cout << "Error sending to server." << endl;
    }
    else {
        cout << "SENT: " << endl << buf;
    }
}

void read(SOCKET sock) {
    char buf[500];
    DWORD bytes = recv(sock, buf, 500, NULL);
    if (bytes > 0) {
        cout << "RECIEVED: " << endl << extractBytes(buf, bytes);
    }
    else {
        cout << "Error recieving from server." << endl;
    }
}