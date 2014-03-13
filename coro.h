#pragma once


#include <Windows.h>
#include <functional>

template <typename T>
class Coroutine{
public:
	Coroutine(std::function<void(Coroutine<T>*,T)> _coro){
		fiber[0] = ConvertThreadToFiber(0);
		fiber[1] = CreateFiberEx(
			0,0, FIBER_FLAG_FLOAT_SWITCH, fiber_func, this);

		coro = _coro;

		now = 0;
	}
	virtual ~Coroutine(){
		DeleteFiber( fiber[1] );
		ConvertFiberToThread();
	}

	static void WINAPI fiber_func(void *_this){
		Coroutine *inst = (Coroutine*)_this;

		inst->coro( inst, inst->in );
	}

	T yield(T _in){
		now ^= 1;
		in = _in;

		SwitchToFiber( fiber[now] );

		return in;
	}

protected:
	std::function<void(Coroutine<T> *,T)> coro;

	void *fiber[2];
	int now;

	T in;
};
