#pragma once
#include <functional>
#include <regex>
#include "../http/http.hpp"
#include "utils.hpp"

namespace middleware{

    struct Route{
        // path's regex
        std::regex path_regex;
        // url params
        std::vector<std::string> params;
    };

    class PathMiddleware : public Middleware{
    public:
        std::string method;
        Route route;
        std::function<void(http::Request& req, http::Response& res)> handler;
    public:
        PathMiddleware(std::string m , std::string p, std::function<void(http::Request& req, http::Response& res)> callback);
        bool match(http::Request& req);
    };
}