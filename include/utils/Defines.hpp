#ifndef UTILS_DEFINES
#define UTILS_DEFINES

#include <vector>

#define IP_ADDRESS "127.0.0.1"
#define PORT 3333

#define PIPENAME "build/named_pipe"

#define SOCKET_JSON "json/socket.json"
#define SHM_JSON "json/shm.json"
#define PIPE_JSON "json/pipe.json"
#define MSGQUEUE_JSON "json/msgqueue.json"
#define FILE_JSON "json/file.json"

#define KILOBYTE 1024
#define MEGABYTE 1024*1024
#define GIGABYTE 1024*1024*1024

static std::vector<unsigned long> testedDurations = {1, 4, 16, 64, 256, 1*KILOBYTE, 4*KILOBYTE, 16*KILOBYTE, 64*KILOBYTE, 256*KILOBYTE};

#endif