#ifndef UTILS_THREAD
#define UTILS_THREAD

#include <thread>

class Thread {
public:
    template<typename Function, typename... Args>
    explicit Thread(Function&& function, Args&&... args) {
        // Create a new thread and run the function with the provided arguments
        thread_ = std::thread(std::forward<Function>(function), std::forward<Args>(args)...);
    }

    // Destructor to join the thread when the object is destroyed
    ~Thread() {
        if (thread_.joinable()) {
            thread_.join();
        }
    }

private:
    std::thread thread_;
};

#endif