#include "Defines.hpp"
#include "servers/ShmServer.hpp"
#include "servers/SocketServer.hpp"

void runSocketServer() {
    SocketServer socketServer(PORT);

    if (socketServer.listenForConnections()) {
        for (size_t size: testedDurations) {
            socketServer.receiveMessage(size);
        }

        socketServer.closeConnection();
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
    runSocketServer();
    // runShmServer();
    return 0;
}