#include "servers/PipeServer.hpp"
#include "Defines.hpp"

PipeServer::PipeServer(int expectedMsg): expectedMessages(expectedMsg), receivedMessages(0), _isRunning(false) {
    createPipe();
}

PipeServer::~PipeServer() {
    stop();
}

void PipeServer::createPipe() {
    pipeName = "/tmp/pipe";  // Specify a unique pipe name

    // Create the named pipe
    mkfifo(pipeName.c_str(), 0666);

    // Open the pipe for reading
    pipefd = open(pipeName.c_str(), O_RDONLY | O_NONBLOCK);
    if (pipefd == -1) {
        std::cerr << "Failed to open the pipe." << std::endl;
        exit(1);
    }

    std::cout << "Pipe created and opened." << std::endl;
}

void PipeServer::start() {
    _isRunning = true;
}

void PipeServer::stop() {
    _isRunning = false;
    close(pipefd);
    unlink(pipeName.c_str());
}

bool PipeServer::isRunning() {
    return _isRunning;
}

void PipeServer::receiveMessage() {
    size_t size = testedDurations[receivedMessages % (testedDurations.size())];
    char buffer[size];
    ssize_t bytesRead;
    std::string message;

    while ((bytesRead = read(pipefd, buffer, sizeof(buffer))) != 0) {
        if(bytesRead != -1)
            message.append(buffer, bytesRead);

        if (message.size() == size) {
            // Complete message received
            receivedMessages++;
            std::cout << "Received message from client (" << size << " bytes). Remaining messages: " << expectedMessages - receivedMessages << std::endl;

            if (receivedMessages == expectedMessages) {
                std::cout << "Received all messages. Closing the server." << std::endl;
                stop();
            }

            break;
        }
    }
}
