#include "../include/zen/app/app.hpp"

int main(){
    Zen app;

    app.use("GET", "/users/:id", [](http::Request& req, http::Response& res){});

    app.listen(8080, [](){std::cout<<"";});
    return 0;
}