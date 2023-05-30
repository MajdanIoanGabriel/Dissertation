#ifndef SHM_CLIENT_HPP
#define SHM_CLIENT_HPP

#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>
#include <cstring>

class ShmClient {
private:
    int shmid; // Shared memory ID
    char* sharedMemory; // Pointer to the shared memory
    const size_t sharedMemorySize; // Size of the shared memory in bytes
    sem_t* serverSemaphore; // Semaphore for server synchronization
    sem_t* clientSemaphore; // Semaphore for client synchronization

public:
    ShmClient(size_t size);
    ~ShmClient();

    void waitForServer();
    void readFromSharedMemory();
    void writeToSharedMemory(const std::string& message);
};

#endif
