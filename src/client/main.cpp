#include "Defines.hpp"
#include "Timer.hpp"
#include "clients/ShmClient.hpp"
#include "clients/SocketClient.hpp"

double runSocketClient(size_t size) {
    SocketClient socketClient(IP_ADDRESS, PORT);
    Timer timer;
    std::string message(size, '0');

    timer.start();

    socketClient.connectToServer();
    socketClient.sendMessage(message);
    socketClient.receiveMessage();

    timer.stop();
    std::cout << "Message (" << size << " bytes) sent, duration:" << timer.durationInMilliseconds() << "ms."<< std::endl;

    return timer.durationInMilliseconds();
}

double runShmClient(size_t size) {
    ShmClient shmClient(size);
    Timer timer;
    std::string message(size, '0');

    timer.start();

    shmClient.writeToSharedMemory(message);
    shmClient.waitForServer();
    shmClient.readFromSharedMemory();

    timer.stop();
    std::cout << "Message (" << size << " bytes) sent, duration:" << timer.durationInMilliseconds() << "ms."<< std::endl;

    return timer.durationInMilliseconds();
}

int main () 
{
    // (void)runSocketClient(KILOBYTE);
    // (void)runSocketClient(MEGABYTE);
    // (void)runSocketClient(10*MEGABYTE);
    // (void)runSocketClient(20*MEGABYTE);
    // (void)runSocketClient(100*MEGABYTE);
    // (void)runSocketClient(GIGABYTE);

    (void)runShmClient(MEGABYTE);
    return 0;
}