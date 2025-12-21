#include "../../include/zen/middleware/pathMiddleware.hpp"

namespace middleware
{
    PathMiddleware::PathMiddleware(std::string m, std::string p, std::function<void(http::Request &req, http::Response &res)> callback) : Middleware(Type::PATH), handler(callback), method(m) {
        // extract path segments with delim as '/'
        std::stringstream path;

        path << p;

        std::string path_segment;
        std::vector<std::string> segments;

        while(std::getline(path, path_segment, '/')){
            if(!path_segment.empty()){
                segments.push_back(path_segment);
            }
        }

        path.clear();
        
        // construct regex for each segment. Static and Param segments
        std::stringstream regex_temp;
        for(auto segment : segments){
            // Param segment
            if(segment[0] == ':'){
                regex_temp << "/([^/]+)";
                this->route.params.push_back(segment.substr(1));
            // Static segment 
            } else {
                regex_temp << "/" << segment;
            }
        }

        // full path regex. 
        std::regex r(regex_temp.str());

        // initialize path: Route
        this->route.path_regex = r;
    }

    bool PathMiddleware::match(http::Request& req){
        // return true if the request url and method matches the middleware attributes method and path:Route
        
        bool match = false;
        std::smatch m;
        
        // std::regex_match(stringToBeChecked, std::smatch, regexToBeUsed);
        if(req.method == this->method && std::regex_match(req.path, m, this->route.path_regex)){
            match = true;
            for(int i = 1 ; i < m.size() ; i++){
                req.params.insert({this->route.params[i-1], m[i]});
            }
        }

        return match;
    }
}