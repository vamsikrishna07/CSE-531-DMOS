#include "threads.h"
#include <unistd.h>
int global_counter = 0;

void f1() {
 	int local_counter = 0;
 	while(1) 
	 {
  		local_counter=local_counter+1;
 		global_counter++;
  		printf("Thread 1 local counter : %d - global counter : %d\n",local_counter,global_counter);
  		sleep(1);
  		yield();
 	}
}

void f2() {
 	int local_counter = 0;
 	while(1) 
	 {
  		local_counter=local_counter+2;
 		global_counter++;
  		printf("Thread 2 local counter : %d - global counter : %d\n",local_counter,global_counter);
  		sleep(1);
  		yield();
 	}
}

void f3() {
 	int local_counter = 0;
 	while(1) 
	 {
  		local_counter=local_counter+3;
 		global_counter++;
  		printf("Thread 3 local counter : %d - global counter : %d\n",local_counter,global_counter);
  		sleep(1);
  		yield();
 	}
}

void f4() {
 	int local_counter = 0;
 	while(1) 
	 {
  		local_counter=local_counter+4;
 		global_counter++;
  		printf("Thread 4 local counter : %d - global counter : %d\n",local_counter,global_counter);
  		sleep(1);
  		yield();
 	}
}


int main() {
   Ready_Q = newQueue();
   start_thread(f1);
   start_thread(f2);
   start_thread(f3);
   start_thread(f4);
   run();
   return 0;
}
