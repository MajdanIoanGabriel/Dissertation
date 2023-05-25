#include "socket/SocketClient.hpp"
#include "utils/Timer.hpp"

int main () 
{
    SocketClient socketClient("127.0.0.1", 3333);
    Timer socketTimer;

    socketTimer.start();

    socketClient.connectToServer();
    socketClient.sendMessage("What's up?");
    socketClient.receiveMessage();

    socketTimer.stop();

    std::cout << "Timer value: " << socketTimer.durationInSeconds() << "s, or " << socketTimer.durationInMilliseconds() << "ms." << std::endl;

    return 0;
}