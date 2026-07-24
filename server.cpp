#include "httplib.h"

#include <iostream>

int main() {
    httplib::Server server;

    server.Post("/message",
        [](const httplib::Request& request,
           httplib::Response& response) {

            std::cout << "Received: " << request.body << '\n';

            response.set_content(
                "hello from c++",
                "text/plain"
            );
        }
    );

    std::cout << "C++ server listening on port 8081\n";

    server.listen("0.0.0.0", 8081);
}