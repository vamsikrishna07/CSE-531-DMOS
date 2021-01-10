#include <stdlib.h>
#include "sem.h"

#define msg_size 10
#define N 10
#define portsCount 100

struct port{

	Semaphore_t* mutex;
	Semaphore_t* sem_Full;
	Semaphore_t* sem_Empty;
	int in;
	int out;
	int messages[N][msg_size];
};

struct port ports[portsCount];

void initialize_Ports(){
	for(int i = 0; i<100; i++){
		
		ports[i].mutex = CreateSem(1);
		ports[i].sem_Full = CreateSem(0);
		ports[i].sem_Empty = CreateSem(N);
		ports[i].in = 0;
		ports[i].out = 0;
	}
}


int send(int rec_port, int *message){ 
	P(ports[rec_port].sem_Empty);
          P(ports[rec_port].mutex);
                  for(int i=0;i<msg_size;i++) {
                     ports[rec_port].messages[ports[rec_port].in][i] = message[i];
                  }
		  ports[rec_port].in = (ports[rec_port].in+1) % msg_size;
          V(ports[rec_port].mutex);
	V(ports[rec_port].sem_Full);
	return 0;
}



int receive(int send_port, int *message){ 
	P(ports[send_port].sem_Full);
          P(ports[send_port].mutex);
                  for(int i=0;i<msg_size;i++) {
                     message[i] = ports[send_port].messages[ports[send_port].out][i];
                  }
                  ports[send_port].out = (ports[send_port].out+1) % msg_size;
          V(ports[send_port].mutex);
	V(ports[send_port].sem_Empty);
	return 0;
}
