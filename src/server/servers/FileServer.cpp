#include "servers/FileServer.hpp"

FileServer::FileServer(const std::string& filePath): filePath_(filePath) {
    semaphore = sem_open("/file_semaphore", O_CREAT, 0666, 0);

    file = std::ifstream(filePath_);

    if (!file) {
        std::cerr << "Error opening file: " << filePath_ << std::endl;
        exit(0);
    }
}

FileServer::~FileServer() {
    file.close();
    sem_unlink("/file_semaphore");
}

void FileServer::receiveMessage() {
    sem_wait(semaphore);

    std::string message;
    file >> message;
    std::cout << "Received message of size: " << message.size() << std::endl;
}
