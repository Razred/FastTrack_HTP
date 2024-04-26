#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

const int PORT = 8080;
const int BUFFER_SIZE = 1024;

int main() {
    int server_socket, new_socket;
    struct sockaddr_in server_address;
    size_t addrlen = sizeof(server_address);


    if (server_socket = socket(AF_INET, SOCK_STREAM, 0) == 0) {
        std::cerr << "Error: Unable to create socket" << std::endl;
        return 1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        std::cerr << "Error: Unable to bind socket" << std::endl;;
        return 1;
    }

    if (listen(server_socket, 3) < 0) {
        std::cerr << "Error: Unable to listen on socket" << std::endl;;
        return 1;
    }

    std::cout << "Server listening on port " << PORT << std::endl;

    while (true) {
        new_socket = accept(server_socket, (struct sockaddr *)&server_address, (socklen_t *)&addrlen);
        if (new_socket < 0) {
            std::cerr << "Error: Unable to accept connection" << std::endl;
            continue;
        }

        std::cout << "New client connected" << std::endl;

        char buffer[BUFFER_SIZE];
        while (true) {
            int bytes_received = recv(new_socket, buffer, BUFFER_SIZE, 0);
            if (bytes_received < 0) {
                std::cerr << "Error: Unable to receive data" << std::endl;
                break;
            } else if (bytes_received == 0) {
                std::cout << "Client disconnected" << std::endl;
                break;
            }

            buffer[bytes_received] = '\0';
            std::cout << "Received message from client: " << buffer << std::endl;

            const char* response = "Message received";
            int bytes_sent = send(new_socket, response, strlen(response), 0);
            if (bytes_sent < 0) {
                std::cerr << "Error: Unable to send response" << std::endl;
                break;
            }
        }

        close(new_socket);
    }

    close(server_socket);
    return 0;
}
