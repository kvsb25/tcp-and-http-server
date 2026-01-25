#include "tester.hpp"

ParsedRequest ref_req {
    .method  = "GET",
    .path    = "/api/users?limit=10&page=2",
    .version = "HTTP/1.1",
    .headers = {
        {"Host", " localhost:3000"},
        {"User-Agent", " MicroFrameworkTest/1.0"},
        {"Accept", " application/json"},
        {"Connection", " keep-alive"}
    },
    .body = ""
};

auto iso = []{ auto t=time(nullptr); char b[32]; strftime(b,32,"%Y-%m-%dT%H:%M:%SZ", gmtime(&t)); return std::string(b); }();
ParsedResponse ref_res {
    .version        = "HTTP/1.1",
    .status_code    = 200,
    .status_message = "OK",
    .headers = {
        {"Content-Type", "application/json"},
        {"Connection", "close"},
        {"Content-Length", "38"},
        {"Date", iso}
    },
    .body = "{ \"message\": \"API Framework Working\" }"
};

int main(){
    std::string req =
        "GET /api/users?limit=10&page=2 HTTP/1.1\r\n"
        "Host: localhost:3000\r\n"
        "User-Agent: MicroFrameworkTest/1.0\r\n"
        "Accept: application/json\r\n"
        "Connection: keep-alive\r\n"
        "\r\n";

    std::string res =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: application/json\r\n"
        "Connection: close\r\n"
        "Content-Length: 38\r\n"
        "\r\n"
        "{ \"message\": \"API Framework Working\" }";

    Tester tester(ref_req,ref_res);
    bool result = tester.wireFormatTest(req, res);

    std::cout << "Wire format test result: " << (result ? "PASS" : "FAIL") ;
    return 0;
}