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
    sem_t* serverSemaphore; // Semaphore for server synchronization
    sem_t* clientSemaphore; // Semaphore for client synchronization

public:
    ShmServer();
    ~ShmServer();

    void readFromSharedMemory(size_t size);
};

#endif
