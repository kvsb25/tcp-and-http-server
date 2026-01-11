#include "tester.hpp"

Tester::Tester(std::string &ref_req_str, std::string& ref_res)
{
    // form ref_req and ref_res manually without http::Request and http::Response module
}

Tester::~Tester()
{
    delete ref_req;
    delete ref_res;
}

bool Tester::test(std::string& req_str, std::string& res_str)
{
    // form req with http::Request module
    // match req with ref_req, log false for mismatch
    // form res with http::Response module
    // match res with ref_res, log false for mismatch
}