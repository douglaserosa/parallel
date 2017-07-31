
/*	
 *	TODO:
 *
 *	1. Melhorar nomes de identificadores
 *	2. Implementar compatibilidade da range com std::begin/end
 *	3. Implementar uma funcao auxiliar para gerar essa range
 *	4. Adicionar PARALLEL a todas as macros guarda
 *	5. Adicionar SIFNAE se possivel
 * */

#ifndef _FOR_
#define _FOR_

#include <type_traits>
#include "task.h"
#include "scheduling_policy.h"
#include "range.h"
#include "context_generator.h"
#include "default_thread.h"
#include "default_algorithm.h"

namespace jampi {

    template<class SCHED, template<typename> class ThreadType, typename Func>
    void for_helper(SCHED &policy, jampi::Range &r, int chunk, Func &f) {

        int size = r.size();

        if ((size / chunk) > 1) {

            int shift = size / 2;

            jampi::Range left_range(r.begin(), r.begin() + shift);
            jampi::Range right_range(r.begin() + shift, r.end());

            jampi::Task<void, SCHED &, jampi::Range &, int, Func &>
                    left(for_helper<SCHED, ThreadType, Func>, policy, left_range, chunk, f);
            jampi::Task<void, SCHED &, jampi::Range &, int, Func &>
                    right(for_helper<SCHED, ThreadType, Func>, policy, right_range, chunk, f);
            int context = generate_context(shift * 7 * 29);

            using TASK = decltype(left);

            policy.template spawn<TASK, ThreadType<TASK> >(left, context);
            policy.template spawn<TASK, ThreadType<TASK> >(right, context);

            policy.template sync(context);

        } else { 
            f(r);
        }
    }

/*
 * Implementar move semantics na classe range e
 * uma versao do for que aceite esse rvalue,
 * (se bem que pode ja ta implementado... (vide default)) 
 *
 * */

/*
 * Para que os padroes pudessem compilar, 
 * houveram modificacoes nos padroes. Isso deve ser limpado;
 *
 *
 * */

// Implementado deducao do parametro que representa invocavel
    template<typename SchedAlg = DefaultAlgorithm, template<typename> class ThreadType = DefaultThread, typename Func>
    void For(jampi::Range &r, int chunk, const Func &f) {

        if (chunk == 0 || chunk >= r.size()) return;

        jampi::SchedulingPolicy<SchedAlg> scheduler;

        for_helper<decltype(scheduler), ThreadType, typename std::remove_cv<Func>::type>
                (scheduler, r, chunk, const_cast<Func &>(f));
    }

// Rvalue adicionado, mas nao testado;
// outro ponto:
// acho que esse for nao funciona com ponteiro para membro de classe; -> arrumar
    template<typename SchedAlg = DefaultAlgorithm, template<typename> class ThreadType = DefaultThread, typename Func>
    void parallel_for(jampi::Range &&r, int chunk, const Func &f) {

        if (chunk == 0 || chunk >= r.size()) return;

        jampi::SchedulingPolicy<SchedAlg> scheduler;

        for_helper<decltype(scheduler), ThreadType, typename std::remove_cv<Func>::type>
                (scheduler, r, chunk, const_cast<Func &>(f));
    }


// rodando teste no valgrind retornou sem erros, porem com isso:
// used_suppression:  1 dl-hack3-cond-1 /usr/lib/valgrind/default.supp:1206

};


#endif
