#include "../../include/zen/tcp/clientSession.hpp"

ClientSession::ClientSession(SOCKET& s) : socket(s), buff(DEFAULT_BUFLEN){}

ClientSession::~ClientSession(){
    if(closesocket(socket) == SOCKET_ERROR) {
        std::cout << "Client Socket close failed with error: "
            << WSAGetLastError() 
            << std::endl;
    }

    buff.clear();
}

std::string ClientSession::recvFromClient(){
    int bytesRecv;
    int totalBytesRecv = 0;

    if(buff.empty())
        buff.resize(DEFAULT_BUFLEN);

    while(true){
        if( buff.size() == totalBytesRecv){
            buff.resize(buff.size()*2);
        }

        // call recv(for client's socket, buff starting mem addr, available space that can be filled, remote entity closes the connection)
        bytesRecv = recv( // recv from winsock
            this->socket, 
            buff.data() + totalBytesRecv, 
            buff.size() - totalBytesRecv, 
            0
        );

        // check if all data received 
        if(bytesRecv > 0){
            totalBytesRecv += bytesRecv;
        } else if(bytesRecv == 0) {
            break;
        } else { // error
            std::cerr << "recv failed: " << WSAGetLastError() << std::endl;
            return "";
        }
    }
    
    return std::string(buff.data(), totalBytesRecv);
}

void ClientSession::sendToClient(const std::string& res){
    int totalSent = 0;
    int length = res.length();
    int retry = 5;

    while(totalSent < length){
        int bytesSent = send(
            socket,
            res.data()+totalSent,
            length-totalSent,
            0
        );

        if(bytesSent>0){
            totalSent += bytesSent;
            retry = 5;
        } else if (bytesSent == 0) {
            break;
        } else {
            
            int err = WSAGetLastError();

            // retry sending
            if(err == WSAEWOULDBLOCK || err == WSAEINTR || err == WSAEINVAL){
                if(retry-- > 0){
                    continue;
                }
                break;
            };

        }
    }
}

// apply hard limit protection in recvFromClient