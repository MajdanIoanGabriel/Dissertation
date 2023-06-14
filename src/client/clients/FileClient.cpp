#include "clients/FileClient.hpp"

FileClient::FileClient(const std::string& filePath): filePath_(filePath) {
    semaphore = sem_open("/file_semaphore", O_CREAT, 0666, 0);

    remove(filePath.c_str());
    file = std::ofstream(filePath_, std::ios_base::app);

    if (!file) {
        std::cerr << "Error opening file: " << filePath_ << std::endl;
        exit(0);
    }
}

FileClient::~FileClient() {
    file.close();
}

void FileClient::sendMessage(const size_t size) {
    std::string message(size, '0');

    file << message << std::endl;
    file.flush();
    
    sem_post(semaphore);
}
