#ifndef UTILS_TIMER
#define UTILS_TIMER

#include <chrono>

class Timer {
private:
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;

public:
    Timer() {}
    ~Timer() {}
    void start();
    void stop();
    double durationInSeconds() const;
    double durationInMilliseconds() const;
};

#endif