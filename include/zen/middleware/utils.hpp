#pragma once

#include <iostream>

namespace middleware{
    enum class Type{
        DEFAULT,
        PATH
    };

    class Middleware {
    public:
        Type type;
    protected:
        Middleware(Type t);
    };
}