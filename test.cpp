#include "coro.h"

void coro_test(Coroutine<int> *coro, int a){
	
	printf("on coro 1 - %d \n", a);

	int r = coro->yield(5);

	printf("on coro 2 - %d \n", r);

	coro->yield(0);
}

int main(int argc, char* argv[]){
	
	{
		Coroutine<int> coro( coro_test );

		printf("on main 1\n");

		int r = coro.yield(1);

		printf("on main 2 - %d \n", r);

		coro.yield(2);
	}

	printf("end prog\n");

	return 0;
}
