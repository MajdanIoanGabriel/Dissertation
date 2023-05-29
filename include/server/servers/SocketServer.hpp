#ifndef SOCKET_SERVER_HPP
#define SOCKET_SERVER_HPP

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

class SocketServer {
private:
    int serverSocket;
    int clientSocket;
    sockaddr_in serverAddress;
    sockaddr_in clientAddress;

public:
    SocketServer(int port);
    ~SocketServer();

    bool listenForConnections();
    void sendMessage(const std::string& message);
    void receiveMessage();
    void closeConnection();
};

#endif
