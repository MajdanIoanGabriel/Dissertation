#ifndef PIPE_SERVER_HPP
#define PIPE_SERVER_HPP

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <string>

class PipeServer {
public:
    PipeServer(int expectedMsg);
    ~PipeServer();
    void start();
    void stop();
    void receiveMessage();
    void createPipe();
    bool isRunning();

private:
    int pipefd;
    bool _isRunning;
    std::string pipeName;
    int expectedMessages;
    int receivedMessages;
};


#endif
