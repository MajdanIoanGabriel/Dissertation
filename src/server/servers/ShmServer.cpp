#include "servers/ShmServer.hpp"
#include "Defines.hpp"

ShmServer::ShmServer() {
    // Generate a unique key
    key_t key = ftok("shared_memory_key", 'R');

    // Create the shared memory segment
    shmid = shmget(key, MEGABYTE, IPC_CREAT | 0666);
    if (shmid == -1) {
        std::cerr << "Failed to create shared memory segment." << std::endl;
        exit(1);
    }

    // Attach to the shared memory segment
    sharedMemory = static_cast<char*>(shmat(shmid, nullptr, 0));
    if (sharedMemory == reinterpret_cast<char*>(-1)) {
        std::cerr << "Failed to attach to shared memory segment." << std::endl;
        exit(1);
    }

    // Clear the shared memory
    std::memset(sharedMemory, 0, MEGABYTE);
    
    // Create and initialize server semaphore
    sem_unlink("/server_semaphore");
    serverSemaphore = sem_open("/server_semaphore", O_CREAT | O_EXCL, 0644, 0);
    if (serverSemaphore == SEM_FAILED) {
        std::cerr << "Failed to create server semaphore." << std::endl;
        exit(1);
    }
    
    // Create and initialize client semaphore
    sem_unlink("/client_semaphore");
    clientSemaphore = sem_open("/client_semaphore", O_CREAT | O_EXCL, 0644, 0);
    if (clientSemaphore == SEM_FAILED) {
        std::cerr << "Failed to create client semaphore." << std::endl;
        exit(1);
    }
}

ShmServer::~ShmServer() {
    // Close and unlink server semaphore
    sem_close(serverSemaphore);
    sem_unlink("/server_semaphore");

    // Close and unlink client semaphore
    sem_close(clientSemaphore);
    sem_unlink("/client_semaphore");

    // Detach from the shared memory segment
    shmdt(sharedMemory);

    // Delete the shared memory segment
    shmctl(shmid, IPC_RMID, nullptr);
}

void ShmServer::readFromSharedMemory(size_t size) {
    // Wait for the client to write a message
    sem_wait(clientSemaphore);

    std::cout << "Received message from client (" << std::string(sharedMemory).size() << " bytes). " << std::endl;

    // Signal the client that the message has been read
    sem_post(serverSemaphore);
}
