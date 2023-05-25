#include "socket/SocketServer.hpp"

SocketServer::SocketServer(int port) {
    // Create a socket
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
    if (clientSocket < 0) {
        close(clientSocket);
    }
    close(serverSocket);
}

bool SocketServer::listenForConnections() {
    // Listen for client connections
    if (listen(serverSocket, 1) < 0) {
        std::cerr << "Failed to listen for connections." << std::endl;
        return false;
    }

    std::cout << "Server listening for connections..." << std::endl;

    // Accept client connection
    socklen_t clientAddressSize = sizeof(clientAddress);
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressSize);
    if (clientSocket < 0) {
        std::cerr << "Failed to accept client connection." << std::endl;
        return false;
    }

    std::cout << "Client connected." << std::endl;
    return true;
}

void SocketServer::sendMessage(const std::string& message) {
    // Send message to the client
    std::cout << "Sending message to client: " << message << std::endl;
    send(clientSocket, message.c_str(), message.size(), 0);
}

void SocketServer::receiveMessage() {
    size_t remainingBytes{0}, msgSize{0};

    // Receive message size from the client
    int bytesRead = recv(clientSocket, &msgSize, sizeof(msgSize), 0);
    char *buffer = new char[msgSize];
    remainingBytes = msgSize;

    // Receive message from the client
    while (remainingBytes > 0) {
        bytesRead = recv(clientSocket, buffer, msgSize, 0);
        if (bytesRead <= 0) {
            break;
        }

        remainingBytes -= bytesRead;
    }

    std::cout << "Received message from client (" << msgSize << " bytes). " << std::endl;

    delete[] buffer;
}

void SocketServer::closeConnection() {
    // Close the client connection
    close(clientSocket);
    std::cout << "Closed connection to client." << std::endl;
}
