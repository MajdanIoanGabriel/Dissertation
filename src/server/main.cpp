#include "socket/SocketServer.hpp"
#include "Defines.hpp"

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