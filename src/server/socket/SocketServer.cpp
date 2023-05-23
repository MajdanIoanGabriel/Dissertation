#include "socket/SocketServer.hpp"

SocketServer::SocketServer(int port) {
    // Create a socket
    wVersionRequested = MAKEWORD(2, 2);
    int err = WSAStartup(wVersionRequested, &wsaData);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Failed to create socket." << std::endl;
        exit(1);
    }

    // Set up server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the server address
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Failed to bind socket to address." << std::endl;
        exit(1);
    }
}

SocketServer::~SocketServer() {
    closeConnection();
}

void SocketServer::listenForConnections() {
    // Listen for client connections
    if (listen(serverSocket, 1) < 0) {
        std::cerr << "Failed to listen for connections." << std::endl;
        exit(1);
    }

    std::cout << "Server listening for connections..." << std::endl;

    // Accept client connection
    socklen_t clientAddressSize = sizeof(clientAddress);
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressSize);
    if (clientSocket < 0) {
        std::cerr << "Failed to accept client connection." << std::endl;
        exit(1);
    }

    std::cout << "Client connected." << std::endl;
}

void SocketServer::sendMessage(const std::string& message) {
    // Send message to the client
    send(clientSocket, message.c_str(), message.length(), 0);
}

void SocketServer::receiveMessage() {
    char *buffer;

    // Receive message from the client
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead > 0) {
        std::cout << "Received message from client: " << buffer << std::endl;
    }
}

void SocketServer::closeConnection() {
    // Close the connection and sockets
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
}
