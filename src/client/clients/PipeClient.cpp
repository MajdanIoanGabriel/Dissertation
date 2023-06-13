#include "clients/PipeClient.hpp"

PipeClient::PipeClient() {
    openPipe();
}

PipeClient::~PipeClient() {
    close(pipefd);
}

void PipeClient::openPipe() {
    pipeName = "/tmp/pipe";  // Specify the same pipe name used by the server

    // Open the pipe for writing
    pipefd = open(pipeName.c_str(), O_WRONLY);
    if (pipefd == -1) {
        std::cerr << "Failed to open the pipe." << std::endl;
        exit(1);
    }
}

void PipeClient::sendMessage(const size_t size) {
    std::string message(size, '0');
    ssize_t bytesWritten = write(pipefd, message.c_str(), message.length());

    if (bytesWritten == -1) {
        std::cerr << "Failed to write to the pipe." << std::endl;
        exit(1);
    }
}
