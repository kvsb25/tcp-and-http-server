#include "../../include/zen/http/response.hpp"

namespace http
{
    Response::Response()
    {
        status_code = 200;
        status_message = message_for_status[status_code];
    }

    Response& Response::send(std::string &data)
    {
        body << data;
    }

}