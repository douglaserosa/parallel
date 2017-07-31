#ifndef JAMPI_MEMBERCALLABLEIMPL_H
#define JAMPI_MEMBERCALLABLEIMPL_H

#include "callable.h"

namespace jampi {

    template<typename PtrToMember, typename PtrToObject, typename ReturnType, typename ...Args>
    class MemberCallableImpl : public jampi::Callable<ReturnType, Args...> {

    private:
        PtrToMember callable;
        PtrToObject obj;
    public:

        MemberCallableImpl(PtrToMember c, PtrToObject &o) : callable(c), obj(o) {}

        ~MemberCallableImpl() {}

        MemberCallableImpl(const MemberCallableImpl &m) : callable(m.callable), obj(m.obj) {}

        MemberCallableImpl &operator=(const MemberCallableImpl &m) {
            obj = m.obj;
            callable = m.callable;
            return *this;
        }

        MemberCallableImpl(MemberCallableImpl &&other)
                : callable(std::move(other.callable)), obj(std::move(other.obj)) {}

        MemberCallableImpl &operator=(MemberCallableImpl &&other) {
            obj = std::move(other.obj);
            callable = std::move(other.callable);

            return *this;
        }

        virtual jampi::Callable<ReturnType, Args...> *clone() const {
            return new MemberCallableImpl<PtrToMember, PtrToObject, ReturnType, Args...>(*this);
        }

        ReturnType operator()(Args...args) {
            return ((*obj).*callable)(args...);
        }
    };

}

#endif //JAMPI_MEMBERCALLABLEIMPL_H
