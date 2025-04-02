//
// Created by thomas on 01/04/25.
//

#ifndef GROUP3ENGINE_NETWORKING_HPP
#define GROUP3ENGINE_NETWORKING_HPP
#include <iostream>
#include <thread>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <vector>

#define PORT 9999
#define BUFFER_SIZE 1024

class Networking {
public:
    Networking();
    ~Networking() {
        close(my_socket);
        listen_thread.join();

    }
    std::vector<std::tuple<std::array<char, BUFFER_SIZE>, size_t, sockaddr_in*>> GetMessages() {
        // copy the messages to a new vector and return it
        // and clear the original vector
        std::vector<std::tuple<std::array<char, BUFFER_SIZE>, size_t, sockaddr_in*>> temp = messages;
        messages.clear();
        return temp;
    }
    sockaddr_in GetServerAddress() { return server_addr; }
    int GetSocket() { return my_socket; }
private:
    [[noreturn]] [[noreturn]] void Listen();
private:
    int my_socket;
    struct sockaddr_in server_addr, client_addr;
    std::array<char, BUFFER_SIZE> buffer;
    std::vector<std::tuple<std::array<char, BUFFER_SIZE>, size_t, sockaddr_in*>> messages;
    std::thread listen_thread;

    // list of clients
    std::vector<struct sockaddr_in> clients;

};


#endif //GROUP3ENGINE_NETWORKING_HPP
