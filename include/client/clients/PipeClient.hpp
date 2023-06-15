#ifndef PIPE_CLIENT_HPP
#define PIPE_CLIENT_HPP

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <string>

class PipeClient {
public:
    PipeClient();
    ~PipeClient();
    void sendMessage(const size_t size, const std::string& message);

private:
    int pipefd;
    std::string pipeName;

    void openPipe();
};


#endif
