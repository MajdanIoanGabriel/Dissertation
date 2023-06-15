#include <map>
#include <vector>

#include "clients/FileClient.hpp"
#include "clients/MsgQueueClient.hpp"
#include "clients/PipeClient.hpp"
#include "clients/ShmClient.hpp"
#include "clients/SocketClient.hpp"
#include "Defines.hpp"
#include "Json.hpp"
#include "Timer.hpp"

using namespace json;
using namespace timer;

void runSocketClient(int cycles=1) {
    std::map<size_t, std::vector<double>> duration_map;
    SocketClient socketClient(IP_ADDRESS, PORT);

    socketClient.connectToServer();

    for (int i=0; i<cycles; i++) {
        for (size_t size: testedDurations) {
            duration_map[size].push_back(duration(socketClient, &SocketClient::sendMessage, size));
            std::cout << "Message size: " << size << " sent in " << duration_map[size].back() << "us." << std::endl;
        }
    }

    writeToJSON(SOCKET_JSON, duration_map);
}

void runShmClient(int cycles=1) {
    std::map<size_t, std::vector<double>> duration_map;
    ShmClient shmClient;

    for (int i=0; i<cycles; i++) {
        for (size_t size: testedDurations) {
            duration_map[size].push_back(duration(shmClient, &ShmClient::writeToSharedMemory, size));
            std::cout << "Message size: " << size << " sent in " << duration_map[size].back() << "us." << std::endl;
        }
    }

    writeToJSON(SHM_JSON, duration_map);
}

void runPipeClient(int cycles=1) {
    std::map<size_t, std::vector<double>> duration_map;
    PipeClient pipeClient;

    for (int i=0; i<cycles; i++) {
        for (size_t size: testedDurations) {
            duration_map[size].push_back(duration(pipeClient, &PipeClient::sendMessage, size));
            std::cout << "Message size: " << size << " sent in " << duration_map[size].back() << "us." << std::endl;
        }
    }

    writeToJSON(PIPE_JSON, duration_map);
}

void runMsgQueueClient(int cycles=1) {
    std::map<size_t, std::vector<double>> duration_map;
    MsgQueueClient msgQueueClient(1234);
    msgQueueClient.connectToQueue();

    for (int i=0; i<cycles; i++) {
        for (size_t size: testedDurations) {
            duration_map[size].push_back(duration(msgQueueClient, &MsgQueueClient::sendMessage, size));
            std::cout << "Message size: " << size << " sent in " << duration_map[size].back() << "us." << std::endl;
        }
    }

    writeToJSON(MSGQUEUE_JSON, duration_map);
}

void runFileClient(int cycles=1) {
    std::map<size_t, std::vector<double>> duration_map;
    FileClient fileClient("communication.txt");

    for (int i=0; i<cycles; i++) {
        for (size_t size: testedDurations) {
            duration_map[size].push_back(duration(fileClient, &FileClient::sendMessage, size));
            std::cout << "Message size: " << size << " sent in " << duration_map[size].back() << "us." << std::endl;
        }
    }

    writeToJSON(FILE_JSON, duration_map);
}

int main () 
{
    runSocketClient(10);
    // runShmClient(10);
    // runPipeClient(10);
    // runMsgQueueClient(10);
    // runFileClient(10);
    return 0;
}