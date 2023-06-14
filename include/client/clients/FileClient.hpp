#ifndef FILECLIENT_HPP
#define FILECLIENT_HPP

#include <fstream>
#include <iostream>
#include <semaphore.h>
#include <fcntl.h>

class FileClient {
public:
    FileClient(const std::string& filePath);
    ~FileClient();

    void sendMessage(const size_t size);

private:
    std::string filePath_;
    std::ofstream file;
    sem_t* semaphore;
};

#endif 
