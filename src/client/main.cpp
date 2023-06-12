#include "Defines.hpp"
#include "Timer.hpp"
#include "clients/ShmClient.hpp"
#include "clients/SocketClient.hpp"
#include <map>

using namespace timer;

std::map<int, double> duration_map;

void runSocketClient() {
    SocketClient socketClient(IP_ADDRESS, PORT);

    socketClient.connectToServer();

    for (size_t size: testedDurations) {
        duration_map[size] = duration(socketClient, &SocketClient::sendMessage, size);
        std::cout << "Message size: " << size << " sent in " << duration_map[size] << "us." << std::endl;
    }
}

// double runShmClient(size_t size) {
//     ShmClient shmClient(size);
//     Timer timer;
//     std::string message(size, '0');

//     timer.start();

//     shmClient.writeToSharedMemory(message);
//     shmClient.waitForServer();
//     shmClient.readFromSharedMemory();

//     timer.stop();
//     std::cout << "Message (" << size << " bytes) sent, duration:" << timer.durationInMilliseconds() << "ms."<< std::endl;

//     return timer.durationInMilliseconds();
// }

int main () 
{
    runSocketClient();

    // (void)runShmClient(MEGABYTE);
    return 0;
}