#ifndef _CALLABLE_
#define _CALLABLE_

/*
 *	TODO:
 *	
 *	2. Implementar move semantica na task
 *	3. Finalizar classe task
 *	5. Testar
 *
 *
 * */

namespace jampi {

    template<typename ReturnType, typename ...Args>
    class Callable {
    public:

        Callable(const Callable &) = default;

        Callable &operator=(const Callable &) = default;

        Callable() = default;

        Callable(Callable &&) = default;

        Callable &operator=(Callable &&) = default;


        virtual ReturnType operator()(Args... args) = 0;

        virtual Callable<ReturnType, Args...> *clone() const = 0;

        virtual ~Callable() {}
    };

};

#endif
