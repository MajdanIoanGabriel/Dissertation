#include "Defines.hpp"
#include "Thread.hpp"
#include "servers/ShmServer.hpp"
#include "servers/SocketServer.hpp"

void runSocketServer() {
    SocketServer socketServer(PORT);
    while(true) {
        if (socketServer.listenForConnections()) {
            socketServer.receiveMessage();
            socketServer.sendMessage("Message received.");
            socketServer.closeConnection();
        }
    }
}

void runShmServer() {
    ShmServer shmServer(MEGABYTE);
    while (true) {
        shmServer.waitForClient();
        shmServer.readFromSharedMemory();
        shmServer.writeToSharedMemory("Message received.");
    }
}

int main () 
{
    // Thread socketThread(runSocketServer);
    Thread shmThread(runShmServer);
    return 0;
}