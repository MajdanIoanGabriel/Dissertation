#ifndef MSG_QUEUE_SERVER_HPP
#define MSG_QUEUE_SERVER_HPP

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

class MsgQueueServer {
private:
    key_t mKey;
    int mQueueId;

public:
    MsgQueueServer(key_t key);
    ~MsgQueueServer();
    
    void createQueue();
    void receiveMessage(const size_t size);
};

#endif
