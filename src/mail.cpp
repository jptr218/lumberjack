#include "lumberjack.h"

string getHost(string email) {
    string domain = email.substr(email.find_last_of('@') + 1);
    string nslookup = exec("nslookup -type=mx " + domain);
    string h = nslookup.substr(nslookup.find_last_of(' ') + 1);
    return h.erase(h.find_last_of('\n'));
}

void sendMail(SOCKET sock, string host, string from, string to, string subject, string message){
    read(sock);
    write(sock, string("EHLO " + host + "\r\n"));
    read(sock);
    write(sock, string("MAIL FROM: <" + from + ">\r\n"));
    read(sock);
    write(sock, string("VRFY " + from + "\r\n"));
    read(sock);
    write(sock, string("RCPT TO: <" + to + ">\r\n"));
    read(sock);
    write(sock, string("DATA\r\nFrom: " + from + "\r\nSubject: " + subject));
    read(sock);
    write(sock, message + ".\r\n");
    read(sock);
    write(sock, "QUIT\r\n");
    read(sock);
}