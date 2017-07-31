#ifndef _THREAD_INTERFACE_
#define _THREAD_INTERFACE_

#include <type_traits>
#include <future>

#include "task.h"

namespace jampi {

    class ThreadInterface {
    public:
        virtual ~ThreadInterface() {}
        virtual void join() = 0;

        ThreadInterface() = default;
        ThreadInterface(const ThreadInterface &) = default;
        ThreadInterface(ThreadInterface &&) = default;
        ThreadInterface &operator=(const ThreadInterface &) = default;
        ThreadInterface &operator=(ThreadInterface &&) = default;
    };
}

#endif