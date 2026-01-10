#include "tester.hpp"

Tester::Tester(std::string &req_string)
{
    req = new http::Request(req_string);
}

Tester::~Tester()
{
    delete req;
    delete res;
}

std::string &Tester::result()
{
    std::stringstream result;

    result << "Constructed Request:" << std::endl
           << "req.method: " << req->method << std::endl
           << "req.path: " << req->path << std::endl
           << "req.version: " << req->version << std::endl
           << "req.body: " << req->body << std::endl;

    // query 
}