#include <iostream>

#include "task.h"
#include "default_algorithm.h"
#include "scheduling_policy.h"
#include "default_thread.h"
#include "context_generator.h"

#include "optimized.h"

#include "timer.h"

using TASK = jampi::Task<int, int>;
jampi::SchedulingPolicy <jampi::Optimized, jampi::DefaultThread<TASK>> scheduler;

int fib(int x) {
    if (x > 2) {
        TASK left(fib, x - 1);
        TASK right(fib, x - 2);
        int context = jampi::generate_context(33 * 7 * x);
        auto rl = scheduler.spawn(left, context);
        auto rr = scheduler.spawn(right, 2);
        scheduler.sync(context);
        return rl + rr;
    }
    return 1;
}

int main() {
    Timer timer = Timer();
    fib(22);
    std::cout << timer.elapsed() << std::endl;
}
