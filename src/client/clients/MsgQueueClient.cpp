#include "clients/MsgQueueClient.hpp"

MsgQueueClient::MsgQueueClient(key_t key) : mKey(key), mQueueId(-1) {}

void MsgQueueClient::connectToQueue() {
    // Connect to an existing message queue
    mQueueId = msgget(mKey, 0666);
    if (mQueueId == -1) {
        std::cerr << "Failed to connect to message queue." << std::endl;
        exit(1);
    }
    std::cout << "mQueueId = " << mQueueId << std::endl;
}

void MsgQueueClient::sendMessage(const size_t size) {
    std::string message(size, '0');
    Message msg;
    msg.mType = 1;
    strncpy(msg.mData, message.c_str(), size+1);

    // Send the message
    if (msgsnd(mQueueId, &msg, size, 0) == -1) {
        std::cerr << "Failed to send message. Error: " << strerror(errno) << std::endl;
        exit(1);
    }
}
