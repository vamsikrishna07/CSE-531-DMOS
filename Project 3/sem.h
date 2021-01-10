#include "threads.h" 

typedef struct Semaphore_t {
	int counter;
	TCB_t *q;
} Semaphore_t;

Semaphore_t* CreateSem(int InputValue) {
	Semaphore_t *sem = (Semaphore_t*)malloc(sizeof(Semaphore_t));
	sem->counter = InputValue;
	sem->q = newQueue();
	return sem;
}

void P(Semaphore_t *sem) {
	sem->counter--;
	if(sem->counter<0) {
		AddQueue(&sem->q,Curr_Thread);
		// prev_thread = Curr_thread;
		TCB_t *p = Curr_Thread;
		Curr_Thread = DelQueue(&Ready_Q);
		swapcontext(&(p->context),&(Curr_Thread->context));	
	}
}	

void V(Semaphore_t *sem) {
	sem->counter++;
	if(sem->counter<=0) {
		TCB_t *blockedEarlier = DelQueue(&sem->q);
		AddQueue(&Ready_Q,blockedEarlier);
	}
	yield();
}
