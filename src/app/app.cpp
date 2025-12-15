#include "../../include/zen/app/app.hpp"

http::Response& Zen::handle(http::Request& req, http::Response& res, int index = 0){
    
    if(index >= pipe.size()) return res;

    middleware::Middleware* mw = pipe[index];

    if(mw->type == middleware::Type::DEFAULT){
        try{
            middleware::DefaultMiddleware* dmw = static_cast<middleware::DefaultMiddleware*>(mw);
            dmw->handler(req, res);
            handle(req, res, ++index);
        } catch (std::runtime_error& err) {

        }
    } else if(mw->type == middleware::Type::PATH) {
        try{
            middleware::PathMiddleware* pmw = static_cast<middleware::PathMiddleware*>(mw);
            if(pmw->method == req.method){
                // parse and match path, if match success execute handler and return res else handle next middleware 
            }
        } catch (std::runtime_error& err){

        }
    }

    return res;
}

// Zen::Zen(int port): server(port){}
Zen::Zen() {}

Zen& Zen::use(std::function<void(http::Request&, http::Response&)> callback){
    middleware::DefaultMiddleware* mw = new middleware::DefaultMiddleware(callback);
    pipe.push_back(mw);
}

Zen& Zen::use(std::string method, std::string path, std::function<void(http::Request&, http::Response&)> callback){
    middleware::PathMiddleware* mw = new middleware::PathMiddleware(method, path, callback);
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