#ifndef JAMPI_CALLABLEIMPL_H
#define JAMPI_CALLABLEIMPL_H

#include "callable.h"

namespace jampi {
    template<typename Function, typename ReturnType, typename ...Args>
    class CallableImpl : public Callable<ReturnType, Args...> {
        Function callable;

    public:
        CallableImpl(Function f) : callable(f) {}

        ~CallableImpl() {}

        // Assumindo q c.callable seja copy constructible
        // Testar esse construtor com um objeto complexo
        //CallableImpl(const CallableImpl& c):callable(c.callable) {}
        CallableImpl(const CallableImpl &c) : callable(c.callable) {}


        // Assuming it is copy asignable
        CallableImpl &operator=(const CallableImpl &c) {

            callable = c.callable;

            return *this;
        }

        CallableImpl(CallableImpl &&other) : callable(std::move(other.callable)) {}

        CallableImpl &operator=(CallableImpl &&other) {
            callable = std::move(other.callable);
            return *this;
        }

        ReturnType operator()(Args... args) {
            return (callable)(args...);
            //return ReturnType();
        }


        virtual Callable<ReturnType, Args...> *clone() const {
            return new CallableImpl<Function, ReturnType, Args...>(*this);
        }


    };
}

#endif //JAMPI_CALLABLEIMPL_H
