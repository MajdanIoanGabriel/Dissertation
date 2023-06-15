#include "clients/SocketClient.hpp"

SocketClient::SocketClient(const std::string ipAddress, int port) {
    // Create a socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        std::cerr << "Failed to create socket." << std::endl;
        exit(1);
    }

    // Set up server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    if (inet_pton(AF_INET, ipAddress.c_str(), &serverAddress.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported." << std::endl;
        exit(1);
    }
}

SocketClient::~SocketClient() {
    closeConnection();
}

void SocketClient::connectToServer() {
    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Failed to connect to the server." << std::endl;
        exit(1);
    }

    std::cout << "Connected to the server." << std::endl;
}

void SocketClient::sendMessage(const size_t size, const std::string& message) {
    // Send message to the server
    std::cout << "Sending message to server..." << std::endl;
    send(clientSocket, message.c_str(), size, 0);
}

void SocketClient::closeConnection() {
    // Close the connection and socket
    close(clientSocket);
}
