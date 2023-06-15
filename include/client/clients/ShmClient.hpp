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
    sem_t* serverSemaphore; // Semaphore for server synchronization
    sem_t* clientSemaphore; // Semaphore for client synchronization

public:
    ShmClient();
    ~ShmClient();

    void writeToSharedMemory(const size_t size, const std::string& message);
};

#endif
