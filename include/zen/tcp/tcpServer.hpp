#pragma once

#include<iostream>
#include<winsock2.h>

class TcpServer{
private:
    SOCKET main_socket;
    sockaddr_in server_addr;
public:
    TcpServer(SOCKET& s, sockaddr_in& addr);
    ~TcpServer();
    void start();  // contains main loop and shoots a thread for client session handling
};