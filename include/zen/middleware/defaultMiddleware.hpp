#pragma once
#include <functional>
#include "../http/http.hpp"
#include "utils.hpp"

namespace middleware{
    class DefaultMiddleware : public Middleware{
        std::function<void(http::Request& req, http::Response& res)> handler;

        DefaultMiddleware(std::function<void(http::Request& req, http::Response& res)> callback);
    };
}