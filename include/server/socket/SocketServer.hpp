#ifndef SOCKET_SERVER_HPP
#define SOCKET_SERVER_HPP

#include <iostream>
#include <ws2tcpip.h>
#include <winsock.h>

class SocketServer {
private:
    int serverSocket;
    int clientSocket;
    sockaddr_in serverAddress;
    sockaddr_in clientAddress;
    WORD wVersionRequested;
    WSADATA wsaData;

public:
    SocketServer(int port);
    ~SocketServer();

    void listenForConnections();
    void sendMessage(const std::string& message);
    void receiveMessage();
    void closeConnection();
};

#endif
