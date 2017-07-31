#include "timer.h"

Timer::Timer() {
    this->clock = std::chrono::high_resolution_clock::now();
}

Timer::~Timer() {

}

void Timer::reset() {
    this->clock = std::chrono::high_resolution_clock::now();
}

double Timer::elapsed() const {
    return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1>>>(
            std::chrono::high_resolution_clock::now() - this->clock).count();
}
