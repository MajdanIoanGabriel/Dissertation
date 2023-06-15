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
            for (size_t size: testedMessageSizes) {
                socketServer.receiveMessage(size);
            }
        }

        socketServer.closeConnection();
    }
}

void runShmServer(int cycles=1) {
    ShmServer shmServer;

    for(int i=0; i<cycles; i++) {
        for (size_t size: testedMessageSizes) {
            shmServer.readFromSharedMemory(size);
        }
    }
}

void runPipeServer(int cycles=1) {
    PipeServer pipeServer(testedMessageSizes.size()*cycles);
    pipeServer.start();

    while (pipeServer.isRunning()) {
        pipeServer.receiveMessage();
    }
}

void runMsgQueueServer(int cycles=1) {
    MsgQueueServer msgQueueServer(1234);
    msgQueueServer.createQueue();

    for(int i=0; i<cycles; i++) {
        for (size_t size: testedMessageSizes) {
            msgQueueServer.receiveMessage(size);
        }
    }
}

void runFileServer(int cycles=1) {
    FileServer fileServer("communication.txt");

    for(int i=0; i<cycles; i++) {
        for (size_t size: testedMessageSizes) {
            fileServer.receiveMessage();
        }
    }
}

int main (int argc, char** argv) 
{
    if (argc != 3)
    {
        std::cout << "Usage: server <ipc_name> <run_cycles>" << std::endl;
        return 1;
    }

    std::string IPCName = argv[1];
    int runCycles = std::atoi(argv[2]);

    if (IPCName == "socket")
        runSocketServer(runCycles);
    else if (IPCName == "shm")
        runShmServer(runCycles);
    else if (IPCName == "pipe")
        runPipeServer(runCycles);
    else if (IPCName == "msgqueue")
        runMsgQueueServer(runCycles);
    else if (IPCName == "file")
        runFileServer(runCycles);
    else std::cout << "Invalid IPC name" << std::endl;

    return 0;
}