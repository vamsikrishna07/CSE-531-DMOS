#include "q.h"

TCB_t *Ready_Q;
TCB_t *Curr_Thread;
int tidcounter = 0;

void start_thread(void (*function)(void))
{ 	
    void *stack =  (void*)malloc(8192);
	TCB_t *newtcb = NewItem();
	init_TCB(newtcb, function, stack, 8192);
	tidcounter++;
	newtcb->val = tidcounter;
	AddQueue(&Ready_Q, newtcb);
}

void run()
{   
    Curr_Thread = DelQueue(&Ready_Q);
    ucontext_t parent;     // get a place to store the main context, for faking
    getcontext(&parent);   // magic sauce
    swapcontext(&parent, &(Curr_Thread->context));  // start the first thread
}

 

void yield() // similar to run
{  
//	print_queue(Ready_Q);
   	TCB_t * Prev_Thread;
   	AddQueue(&Ready_Q, Curr_Thread);
   	Prev_Thread = Curr_Thread;
   	Curr_Thread = DelQueue(&Ready_Q);
   	swapcontext(&(Prev_Thread->context), &(Curr_Thread->context));
}

