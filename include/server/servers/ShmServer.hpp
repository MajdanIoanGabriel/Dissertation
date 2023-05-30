#ifndef SHM_SERVER_HPP
#define SHM_SERVER_HPP

#include <iostream>
#include <cstring>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>

class ShmServer {
private:
    int shmid; // Shared memory ID
    char* sharedMemory; // Pointer to the shared memory
    const size_t sharedMemorySize; // Size of the shared memory in bytes
    sem_t* serverSemaphore; // Semaphore for server synchronization
    sem_t* clientSemaphore; // Semaphore for client synchronization

public:
    ShmServer(size_t size);
    ~ShmServer();

    void waitForClient();
    void readFromSharedMemory();
    void writeToSharedMemory(const std::string& message);
};

#endif
