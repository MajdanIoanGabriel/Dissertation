#include "Timer.hpp"

void Timer::start() {
    start_time = std::chrono::high_resolution_clock::now();
}

void Timer::stop() {
    end_time = std::chrono::high_resolution_clock::now();
}

double Timer::durationInSeconds() const {
    std::chrono::duration<double> duration = end_time - start_time;
    return duration.count();
}

double Timer::durationInMilliseconds() const {
    std::chrono::duration<double, std::milli> duration = end_time - start_time;
    return duration.count();
}
