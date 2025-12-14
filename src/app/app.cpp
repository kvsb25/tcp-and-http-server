#include "../../include/zen/app/app.hpp"

http::Response& Zen::handle(const http::Request& req, http::Response& res){
    
}

// Zen::Zen(int port): server(port){}
Zen::Zen() {}

Zen& Zen::use(std::function<void(http::Request&, http::Response&)> callback){
    middleware::DefaultMiddleware mw(callback);
    pipe.push_back(mw);
}

Zen& Zen::use(std::string method, std::string path, std::function<void(http::Request&, http::Response&)> callback){
    middleware::PathMiddleware mw(method, path, callback);
    pipe.push_back(mw);
}

void Zen::listen(u_short& port, std::function<void(void)> callback){
    TcpServer server(port);
    callback();

    while(true){
        SOCKET client_socket = INVALID_SOCKET;
        client_socket = accept(server.getMainSocket(), NULL, NULL);

        ClientSession cs(client_socket);

        std::string data = cs.recvFromClient();

        http::Request* req = new http::Request(data);
        http::Response* res = new http::Response();

        this->handle(*req, *res);
    }
}