#pragma once
#include "utils.hpp"

namespace http{
    class ContentNegotiator{
    public:
        ContentNegotiator() = delete; // as i don't want any objects to be created of this class
        static FormatPriority parse(const std::string& header_val);
        static std::string match(const FormatHandlerMap& handler_map, FormatPriority& accepted_val);
    };
}