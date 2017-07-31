#ifndef _TASK_
#define _TASK_

#include <memory>
#include <tuple>
#include <utility>
#include <future>

#include "Callable.h"



namespace parallel {

/*
 *  Uma feature potencialmente util para esta classe seria a capacidade
 *  de se converter/retornar no callable que a mesma 'gerencia' 
 *  ( parece nao ser algo tao simples de fazer.) 
 * */


/* NOTE: Thu 13 Oct 2016 11:26:59 AM BRT
 *	
 *	(1) Seria legal ter uma forma de passar os parametros do invocavel
 *	em um outro momento no tempo e nao apenas na construcao de uma tarefa.
 *
 *	Algo do tipo: set_args(Args ....args) {  tuple = args;  }
 *
 *
 *
 * */

// Meta template necessaria para "desempacotar" (google template parameter packing/unpacking)
// uma tupla de modo a ser compativel com C++11 ( no c++14 ja tem um type trait chamado integer_sequence
// porem nao serve em C++11, foco do trabalho).
template<int ...> struct seq {};

template<int N, int ...S> struct gens : gens<N-1, N-1, S...> {};

template<int ...S> struct gens<0, S...>{ typedef seq<S...> type; };


class TaskInterface {
public:
	virtual void operator()() = 0;
	virtual ~TaskInterface(){}
	
	TaskInterface() = default;
	TaskInterface(const TaskInterface&) = default;
	TaskInterface& operator = (const TaskInterface&) = default;

	TaskInterface(TaskInterface&&) = default;
	TaskInterface& operator = (TaskInterface&&) = default;
		
};


// Tag para especializar um tipo de decidir entre uma implementacao (geral) ou outra
// (void, especifico).
template<class T>
class overload_tag { typedef T type; };


template
<
	typename ReturnType,
	typename ...Args
>
class Task : public virtual TaskInterface {
	
	std::unique_ptr< Callable<ReturnType, Args...> > function;
	
	std::tuple<Args...> arguments;

	std::promise<ReturnType> return_channel;


	template<int ...index, class T>
	void apply(seq<index...>, overload_tag<T>) { 
	       if(function) return_channel.set_value( (*function)(std::get<index>(arguments)...) ) ;
	}	

	template<int ...index>
	void apply(seq<index...>, overload_tag<void>) {
	       if (function) { 
	       	    (*function)(std::get<index>(arguments)...);
		     return_channel.set_value(); 
	       }
	}	

	public: 


		typedef ReturnType returnType_; 
		
		Task():function(nullptr), arguments(), return_channel() { }
		
		Task(const Task& t):arguments(t.arguments) {
	      
			Task& other = const_cast<Task&>(t);
			function = std::move(other.function);
			return_channel = std::move(other.return_channel); 
		}
		
		Task& operator=(const Task& t) {
	       		
			Task& other = const_cast<Task&>(t); 
			arguments = std::move(t.arguments);
			function = std::move(other.function);
			return_channel = std::move(other.return_channel); 
			return *this; 
		}

	
		Task( Task&& other):
			function(std::move(other.function)),
			arguments( std::move(other.arguments)),
		     	return_channel( std::move(other.return_channel)){ }

		Task& operator = (Task&& other) {
			
			function  = std::move(other.function);
			arguments = std::move(other.arguments);
			return_channel = std::move(other.return_channel);

			return *this;
		}

		template<class Fn>
		Task(Fn f, Args...args);

		template<class PtrToMember, class PtrToObject>
		Task(PtrToMember m, PtrToObject o, Args...args);

		void operator () () {
			apply(typename gens<sizeof...(Args)>::type(), overload_tag<ReturnType>{});
		}

		std::future<ReturnType> getTaskFuture() { return return_channel.get_future(); }

};

template
<
	typename ReturnType,
	typename ...Args

>
template<class Fn>
Task<ReturnType, Args...>::Task(Fn f, Args...args):
function( new CallableImpl<Fn, ReturnType, Args...>(f) ),arguments(std::tie(args...))
{}


template
<
	typename ReturnType,
	typename ...Args
>
template<class PtrToMember, class PtrToObject>
Task<ReturnType, Args...>::Task(PtrToMember m, PtrToObject o, Args...args):
function( new MemberCallableImpl<PtrToMember, PtrToObject, ReturnType, Args...>(m, o) ),
arguments(std::tie(args...))
{}


}
#endif
