#ifndef FILESERVER_HPP
#define FILESERVER_HPP

#include <fstream>
#include <iostream>
#include <semaphore.h>
#include <fcntl.h>

class FileServer {
public:
    FileServer(const std::string& filePath);
    ~FileServer();

    void receiveMessage();

private:
    std::string filePath_;
    std::ifstream file;
    sem_t* semaphore;
};

#endif
