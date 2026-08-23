#pragma once

#include<iostream>
#include "utils.hpp"

class TcpServer{
private:
    SOCKET main_socket = INVALID_SOCKET;
    sockaddr_in server_addr;
    WSADATA wsaData;
public:
    TcpServer(u_short port);
    ~TcpServer();
    SOCKET& getMainSocket();
};