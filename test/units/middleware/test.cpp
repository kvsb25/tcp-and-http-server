#include "tester.hpp"

int main(){

    middleware::PathMiddleware pm("GET", "/", [](http::Request req, http::Response res){
        std::cout<< "req.method: " << req.method << std::endl 
            << "req.path: " << req.path << std::endl
            << "req.body: " << req.body << std::endl;
            res.json("{\"message\": \"hello\"}");
            return;
    });

    // std::vector<std::unique_ptr<middleware::Middleware>> pipe;
    std::vector<middleware::Middleware> pipe;
    pipe.push_back(pm);

    // for(auto m : pipe){
    //     middleware::Middleware m = 
    // }

    return 0;
}