#include "../../include/zen/middleware/defaultMiddleware.hpp"

namespace middleware{
    DefaultMiddleware::DefaultMiddleware(Handler callback) : Middleware(Type::DEFAULT), handler(callback){};
}