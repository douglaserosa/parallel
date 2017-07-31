#ifndef _TIMER_H_
#define _TIMER_H_

#include <chrono>

class Timer {
public:
    Timer();
    ~Timer();
    void reset();
    double elapsed() const;
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> clock;
};

#endif // _TIMER_H_
