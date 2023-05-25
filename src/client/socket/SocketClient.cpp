#include "socket/SocketClient.hpp"

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

void SocketClient::sendMessage(const std::string& message) {
    size_t size = message.size();

    // Send message size to the server
    std::cout << "Sending message size to server... (" << size << ")" << std::endl;
    send(clientSocket, &size, sizeof(size), 0);

    // Send message to the server
    std::cout << "Sending message to server..." << std::endl;
    send(clientSocket, message.c_str(), size, 0);
}

void SocketClient::receiveMessage() {
    char buffer[1024];

    // Receive message from the server
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead > 0) {
        std::cout << "Received message from server: " << std::string(buffer, bytesRead) << std::endl;
    }
}

void SocketClient::closeConnection() {
    // Close the connection and socket
    close(clientSocket);
}
