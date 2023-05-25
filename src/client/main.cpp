#include "socket/SocketClient.hpp"

int main () 
{
    SocketClient socketClient("127.0.0.1", 3333);
    // std::string message{"What's up?"};

    socketClient.connectToServer();
    socketClient.sendMessage("What's up?");
    socketClient.receiveMessage();

    return 0;
}