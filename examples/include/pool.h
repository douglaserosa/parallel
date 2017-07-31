#include <vector>

#include "sched_algorithm.h"

namespace jampi {

    class ThreadPool : jampi::SchedAlgorithm {
        std::vector<jampi::ThreadInterface*> pool;
        std::vector<jampi::TaskInterface*> task_stack;
        int num_threads;

    public:
        template<class THREAD> THREAD* create_thread(int ctx){
//            if(num_threads < 4) {
                THREAD *thr = new THREAD;
                pool.push_back(thr);
//            }
            return nullptr;
        }

        template<class TASK> void execute(TASK& t, int ctx) {
            if ( num_threads < 4) {
                task_stack.push_back(t);
            } else {
                ThreadInterface* thr =  getBestThread();
                thr->operator()(task_stack.pop_back());

            }
        }

        virtual ~ThreadPool() = default;

    };

}