#pragma once
#include "../../../include/zen/http/http.hpp"
#include <sstream>

class Tester{
public:
    http::Request* ref_req;
    http::Request* ref_res;
    std::string ref_req_str;
    std::string ref_res_str;

public:
    Tester(std::string& ref_req_string, std::string& ref_res);
    ~Tester();
    bool test(std::string& req_str, std::string& res_str);
};