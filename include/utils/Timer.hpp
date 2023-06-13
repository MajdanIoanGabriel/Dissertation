#ifndef UTILS_TIMER
#define UTILS_TIMER

#include <chrono>
#include <functional>

namespace timer {

    template <typename Obj, typename Func, typename... Args>
    double duration(Obj& obj, Func&& func, Args&&... args)
    {
        auto start = std::chrono::high_resolution_clock::now();
        std::invoke(func, obj, std::forward<Args>(args)...);  // Execute the member function on the given object with arguments
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::micro> duration = end - start;
        return duration.count();
    }

}

#endif