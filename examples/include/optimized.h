
namespace jampi {

    class Optimized : jampi::SchedAlgorithm {
        jampi::ThreadInterface *last_created_thread;
    public:
        Optimized() : last_created_thread(nullptr) {}

        template<class THREAD>
        THREAD *create_thread(int ctx) {
            if (ctx % 2 != 0) {
                THREAD *thr = new THREAD;
                last_created_thread = thr;
                return thr;
            } else {
                last_created_thread = nullptr;
            }
            return nullptr;
        }

        template<class TASK>
        void execute(TASK &t, int ctx) {
            if (ctx % 2 != 0) {
                jampi::Thread<TASK> *curr_thread = dynamic_cast<jampi::Thread<TASK> *>(last_created_thread);
                curr_thread->operator()(t);
            } else {
                t();
            }
        }
    };
}