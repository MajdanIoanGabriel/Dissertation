#include "Defines.hpp"
#include "Thread.hpp"
#include "socket/SocketServer.hpp"

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

int main () 
{
    Thread socketThread(runSocketServer);
    return 0;
}