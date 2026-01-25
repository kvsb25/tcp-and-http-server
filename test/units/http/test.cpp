#include "tester.hpp"
const auto iso = []{ auto t=time(nullptr); char b[32]; strftime(b,32,"%Y-%m-%dT%H:%M:%SZ", gmtime(&t)); return std::string(b); }();

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
    // std::string req =
        // "GET /api/users?limit=10&page=2 HTTP/1.1\r\n"
        // "Host: localhost:3000\r\n"
        // "User-Agent: MicroFrameworkTest/1.0\r\n"
        // "Accept: application/json\r\n"
        // "Connection: keep-alive\r\n"
        // "\r\n";

    // std::string res =
        // "HTTP/1.1 200 OK\r\n"
        // "Content-Type: application/json\r\n"
        // "Connection: close\r\n"
        // "Content-Length: 38\r\n"
        // "\r\n"
        // "{ \"message\": \"API Framework Working\" }";

    // Tester tester(ref_req,ref_res);
    // bool result = tester.wireFormatTest(req, res);

    std::vector<std::string> raw_req = {

        "GET /api/users?limit=10&page=2 HTTP/1.1\r\n"
        "Host: localhost:3000\r\n"
        "User-Agent: MicroFrameworkTest/1.0\r\n"
        "Accept: application/json\r\n"
        "Connection: keep-alive\r\n"
        "\r\n",

        "POST /api/users HTTP/1.1\r\n"
        "Host: localhost:3000\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 30\r\n"
        "Connection: close\r\n"
        "\r\n"
        "{ \"name\": \"Alice\", \"age\": 23 }"
    };

    std::vector<std::string> raw_res = {
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: application/json\r\n"
        "Connection: close\r\n"
        "Content-Length: 38\r\n"
        "\r\n"
        "{ \"message\": \"API Framework Working\" }",

        "HTTP/1.1 201 Created\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 36\r\n"
        "Connection: close\r\n"
        "\r\n"
        "{ \"status\": \"success\", \"id\": 101 }"
    };

    std::vector<ParsedRequest> parsed_req = {
        {
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
        },
        {
            "POST",
            "/api/users",
            "HTTP/1.1",
            {
                {"Host", " localhost:3000"},
                {"Content-Type", " application/json"},
                {"Content-Length", " 30"},
                {"Connection", " close"}
            },
            "{ \"name\": \"Alice\", \"age\": 23 }"
        }
    };

    std::vector<ParsedResponse> parsed_res = {
        {   
            "HTTP/1.1",
            200,
            "OK",
            {
                {"Content-Type", "application/json"},
                {"Connection", "close"},
                {"Content-Length", "38"},
                {"Date", iso}
            },
            "{ \"message\": \"API Framework Working\" }"
        },
        {
            "HTTP/1.1",
            201,
            "Created",
            {
                {"Content-Type", "application/json"},
                {"Connection", "close"},
                {"Content-Length", "36"},
                {"Date", iso}
            },
            "{ \"status\": \"success\", \"id\": 101 }"
        }
    };

    for(int i = 0; i<parsed_res.size(); i++){
        Tester test(parsed_req[i], parsed_res[i]);
        bool result = test.wireFormatTest(raw_req[i], raw_res[i]);
        std::cout << "Wire format test result for "<< i << ": " << (result ? "PASS" : "FAIL") << std::endl << std::endl;
    }

    return 0;
}