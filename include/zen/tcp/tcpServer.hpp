#pragma once

#include<iostream>
#include<winsock2.h>

void log(const std::string& message);

void exitWithError(const std::string& errorMessage);

class TcpServer{
private:
    SOCKET main_socket = INVALID_SOCKET;
    sockaddr_in server_addr;
    WSADATA wsaData;
public:
    TcpServer(u_short port);
    ~TcpServer();
    void start();  // contains main loop and shoots a thread for client session handling
    SOCKET& getMainSocket();
};