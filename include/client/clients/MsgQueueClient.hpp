#ifndef MSG_QUEUE_CLIENT_HPP
#define MSG_QUEUE_CLIENT_HPP

#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include "Defines.hpp"

// Structure for message queue
struct Message {
    long mType;
    char mData[MEGABYTE];
};

class MsgQueueClient {
private:
    key_t mKey;
    int mQueueId;

public:
    MsgQueueClient(key_t key);
    void connectToQueue();
    void sendMessage(const size_t size, const std::string& message);
};

#endif
