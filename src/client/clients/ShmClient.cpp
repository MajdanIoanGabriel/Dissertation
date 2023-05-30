#include "clients/ShmClient.hpp"

ShmClient::ShmClient(size_t size) : sharedMemorySize(size) {
    // Generate a unique key
    key_t key = ftok("shared_memory_key", 'R');

    // Get the shared memory segment
    shmid = shmget(key, sharedMemorySize, 0666);
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

void ShmClient::waitForServer() {
    // Wait for the server to write the message
    sem_wait(serverSemaphore);
}

void ShmClient::readFromSharedMemory() {
    // Read the confirmation message from the shared memory
    std::cout << "Received message from server: " << std::string(sharedMemory) << std::endl;
}

void ShmClient::writeToSharedMemory(const std::string& message) {
    // Write the message to the shared memory
    std::strncpy(sharedMemory, message.c_str(), sharedMemorySize);

    // Signal the server that the message is ready
    sem_post(clientSemaphore);
}
