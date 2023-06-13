#include "Defines.hpp"
#include "servers/PipeServer.hpp"
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
    ShmServer shmServer;

    for (size_t size: testedDurations) {
        shmServer.readFromSharedMemory(size);
    }
}

void runPipeServer() {
    PipeServer pipeServer(testedDurations.size());
    pipeServer.start();

    while (pipeServer.isRunning()) {
        pipeServer.receiveMessage();
    }

    pipeServer.stop();
}

int main () 
{
    // runSocketServer();
    // runShmServer();
    runPipeServer();
    return 0;
}