#include "Defines.hpp"
#include "servers/FileServer.hpp"
#include "servers/MsgQueueServer.hpp"
#include "servers/PipeServer.hpp"
#include "servers/ShmServer.hpp"
#include "servers/SocketServer.hpp"

void runSocketServer(int cycles=1) {
    SocketServer socketServer(PORT);

    if (socketServer.listenForConnections()) {
        for(int i=0; i<cycles; i++) {
            for (size_t size: testedDurations) {
                socketServer.receiveMessage(size);
            }
        }

        socketServer.closeConnection();
    }
}

void runShmServer(int cycles=1) {
    ShmServer shmServer;

    for(int i=0; i<cycles; i++) {
        for (size_t size: testedDurations) {
            shmServer.readFromSharedMemory(size);
        }
    }
}

void runPipeServer(int cycles=1) {
    PipeServer pipeServer(testedDurations.size()*cycles);
    pipeServer.start();

    while (pipeServer.isRunning()) {
        pipeServer.receiveMessage();
    }
}

void runMsgQueueServer(int cycles=1) {
    MsgQueueServer msgQueueServer(1234);
    msgQueueServer.createQueue();

    for(int i=0; i<cycles; i++) {
        for (size_t size: testedDurations) {
            msgQueueServer.receiveMessage(size);
        }
    }
}

void runFileServer(int cycles=1) {
    FileServer fileServer("communication.txt");

    for(int i=0; i<cycles; i++) {
        for (size_t size: testedDurations) {
            fileServer.receiveMessage();
        }
    }
}

int main () 
{
    runSocketServer(10);
    // runShmServer(10);
    // runPipeServer(10);
    // runMsgQueueServer(10);
    // runFileServer(10);
    return 0;
}