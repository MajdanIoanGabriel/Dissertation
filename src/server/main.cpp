#include "socket/SocketServer.hpp"

#define PORT 3333

int main () 
{
    SocketServer socketServer(PORT);
    while(true) {
        if (socketServer.listenForConnections()) {
            socketServer.receiveMessage();
            socketServer.sendMessage("Message received.");
            socketServer.closeConnection();
        }
    }

    return 0;
}