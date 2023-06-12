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

void runShmClient() {
    ShmClient shmClient;

    for (size_t size: testedDurations) {
        duration_map[size] = duration(shmClient, &ShmClient::writeToSharedMemory, size);
        std::cout << "Message size: " << size << " sent in " << duration_map[size] << "us." << std::endl;
    }
}

int main () 
{
    // runSocketClient();
    runShmClient();
    return 0;
}