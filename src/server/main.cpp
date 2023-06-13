#include "Defines.hpp"
#include "servers/MsgQueueServer.hpp"
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

void runMsgQueueServer() {
    MsgQueueServer msgQueueServer(1234);
    msgQueueServer.createQueue();

    for (size_t size: testedDurations) {
        msgQueueServer.receiveMessage(size);
    }
}

int main () 
{
    // runSocketServer();
    // runShmServer();
    // runPipeServer();
    runMsgQueueServer();
    return 0;
}