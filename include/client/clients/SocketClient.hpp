#ifndef SOCKET_CLIENT_HPP
#define SOCKET_CLIENT_HPP

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class SocketClient {
private:
    int clientSocket;
    sockaddr_in serverAddress;

public:
    SocketClient(const std::string ipAddress, int port);
    ~SocketClient();

    void connectToServer();
    void sendMessage(const size_t size, const std::string& message);
    void closeConnection();
};

#endif