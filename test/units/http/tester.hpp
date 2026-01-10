#pragma once
#include "../../../include/zen/http/http.hpp"
#include <sstream>

class Tester{
public:
    http::Request* req;
    http::Request* res;

public:
    Tester(std::string& req_string);
    ~Tester();
    std::string& result();
};