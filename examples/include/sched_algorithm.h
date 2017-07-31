#ifndef _PARALLEL_SCHEDALGORITHM_
#define _PARALLEL_SCHEDALGORITHM_

#include "thread.h"

namespace jampi {

    class SchedAlgorithm {
    public:
        template<class THREAD>
        THREAD *create_thread(int ctx) { return nullptr; }

        template<class TASK>
        void execute(TASK &t, int ctx) {}

        virtual ~SchedAlgorithm() = default;
    };
};

#endif
