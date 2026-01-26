#pragma once
#include <functional>
#include "../http/http.hpp"
#include "utils.hpp"

namespace middleware{
    class DefaultMiddleware : public Middleware{
    public:
        Handler handler;
        DefaultMiddleware(Handler callback);
    };
}