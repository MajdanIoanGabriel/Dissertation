#include "socket/SocketServer.hpp"

int main () 
{
    SocketServer socketServer(3333);
    while(true) {
        if (socketServer.listenForConnections()) {
            socketServer.receiveMessage();
            socketServer.sendMessage("Good, you?");
        }
    }

    return 0;
}