#include "clients/ShmClient.hpp"
#include "Defines.hpp"

ShmClient::ShmClient() {
    // Generate a unique key
    key_t key = ftok("shared_memory_key", 'R');

    // Get the shared memory segment
    shmid = shmget(key, MEGABYTE, 0666);
    if (shmid == -1) {
        std::cerr << "Failed to access shared memory segment." << std::endl;
        exit(1);
    }

    // Attach to the shared memory segment
    sharedMemory = static_cast<char*>(shmat(shmid, nullptr, 0));
    if (sharedMemory == reinterpret_cast<char*>(-1)) {
        std::cerr << "Failed to attach to shared memory segment." << std::endl;
        exit(1);
    }
    
    // Open server semaphore
    serverSemaphore = sem_open("/server_semaphore", 0);
    if (serverSemaphore == SEM_FAILED) {
        std::cerr << "Failed to open server semaphore." << std::endl;
        exit(1);
    }
    
    // Open client semaphore
    clientSemaphore = sem_open("/client_semaphore", 0);
    if (clientSemaphore == SEM_FAILED) {
        std::cerr << "Failed to open client semaphore." << std::endl;
        exit(1);
    }
}

ShmClient::~ShmClient() {
    // Close semaphores
    sem_close(serverSemaphore);
    sem_close(clientSemaphore);

    // Detach from the shared memory segment
    shmdt(sharedMemory);
}

void ShmClient::writeToSharedMemory(const size_t size) {
    std::string message(size, '0');

    // Write the message to the shared memory
    std::strncpy(sharedMemory, message.c_str(), size+1);

    // Signal the server that the message is ready
    sem_post(clientSemaphore);

    // Wait for the server to read the message
    sem_wait(serverSemaphore);
}
