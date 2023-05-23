#include "socket/SocketServer.hpp"

int main () 
{
    SocketServer socketServer(3333);
    while(true) {
        socketServer.listenForConnections();
    }

    return 0;
}