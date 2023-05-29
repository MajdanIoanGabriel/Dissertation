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

    void start() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    void stop() {
        end_time = std::chrono::high_resolution_clock::now();
    }

    double durationInSeconds() const {
        std::chrono::duration<double> duration = end_time - start_time;
        return duration.count();
    }

    double durationInMilliseconds() const {
        std::chrono::duration<double, std::milli> duration = end_time - start_time;
        return duration.count();
    }
};

#endif