#ifndef JAMPI_TASKINTERFACE_H
#define JAMPI_TASKINTERFACE_H

namespace jampi {

    class TaskInterface {
    public:
        virtual void operator()() = 0;

        virtual ~TaskInterface() {}

        TaskInterface() = default;

        TaskInterface(const TaskInterface &) = default;

        TaskInterface &operator=(const TaskInterface &) = default;

        TaskInterface(TaskInterface &&) = default;

        TaskInterface &operator=(TaskInterface &&) = default;

    };
}

#endif //JAMPI_TASKINTERFACE_H
