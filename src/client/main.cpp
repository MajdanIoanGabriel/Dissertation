#include "socket/SocketClient.hpp"
#include "utils/Timer.hpp"
#include "utils/Defines.hpp"

double sendClientMessage(size_t size) {
    SocketClient socketClient(IP_ADDRESS, PORT);
    Timer socketTimer;
    std::string message(size, '0');

    socketTimer.start();

    socketClient.connectToServer();
    socketClient.sendMessage(message);
    socketClient.receiveMessage();

    socketTimer.stop();
    std::cout << "Message (" << size << " bytes) sent, duration:" << socketTimer.durationInMilliseconds() << "ms."<< std::endl;

    return socketTimer.durationInMilliseconds();
}

int main () 
{
    (void)sendClientMessage(KILOBYTE);
    (void)sendClientMessage(MEGABYTE);
    (void)sendClientMessage(10*MEGABYTE);
    (void)sendClientMessage(20*MEGABYTE);
    (void)sendClientMessage(100*MEGABYTE);
    (void)sendClientMessage(GIGABYTE);
    return 0;
}