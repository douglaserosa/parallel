#include "sched_algorithm.h"
#include "thread_interface.h"

namespace jampi {

    class UnOptimized : jampi::SchedAlgorithm {
        jampi::ThreadInterface *last_created_thread;
    public:
        UnOptimized() : last_created_thread(nullptr) {}

        template<class THREAD>
        THREAD *create_thread(int ctx) {
            THREAD *thr = new THREAD;
            last_created_thread = thr;
            return thr;
        }

        template<class TASK>
        void execute(TASK &t, int ctx) {
            jampi::Thread <TASK> *curr_thread = dynamic_cast<jampi::Thread<TASK> *>(last_created_thread);
            curr_thread->operator()(t);
        }
    };
}

