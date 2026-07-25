#include <httplib.h>

#include <iostream>

int main() {
    httplib::Server server;

    server.Post("/message",
        [](const httplib::Request& request,
           httplib::Response& response) {

            std::cout << "Received: " << request.body << std::endl;

            std::string scramble = request.body;
            
            std::string message = "Recieved scramble: " + scramble;

            response.set_content(
                message,
                "text/plain"
            );
        }
    );

    std::cout << "C++ server listening on port 8081" << std::endl;

    server.listen("0.0.0.0", 8081);
}
