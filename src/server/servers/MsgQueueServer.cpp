#include "servers/MsgQueueServer.hpp"

MsgQueueServer::MsgQueueServer(key_t key) : mKey(key), mQueueId(-1) {}

MsgQueueServer::~MsgQueueServer() {
    // Delete the message queue
    if (msgctl(mQueueId, IPC_RMID, nullptr) == -1) {
        std::cerr << "Failed to delete message queue." << std::endl;
        return;
    }
}

void MsgQueueServer::createQueue() {
    // Create a new message queue
    mQueueId = msgget(mKey, IPC_CREAT | 0666);
    if (mQueueId == -1) {
        std::cerr << "Failed to create message queue." << std::endl;
        exit(1);
    }

    // Increase the maximum message size
    struct msqid_ds queueInfo;
    if (msgctl(mQueueId, IPC_STAT, &queueInfo) == -1) {
        std::cerr << "Failed to retrieve message queue information." << std::endl;
        exit(1);
    }
    
    if (queueInfo.msg_qbytes != MEGABYTE) {
        queueInfo.msg_qbytes = MEGABYTE; // Set the maximum message size to 1 MB

        if (msgctl(mQueueId, IPC_SET, &queueInfo) == -1) {
            std::cerr << "Failed to set the maximum message size." << std::endl;
            exit(1);
        }
    }
}

void MsgQueueServer::receiveMessage(const size_t size) {
    Message msg;
    // Receive the message
    if (msgrcv(mQueueId, &msg, size + sizeof(long), 1, 0) == -1) {
        std::cerr << "Failed to receive message." << std::endl;
        exit(1);
    }

    std::cout << "Received message of size " << size << "." << std::endl;
}
