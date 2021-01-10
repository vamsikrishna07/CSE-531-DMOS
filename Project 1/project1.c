#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include "sem.h"
#define _GNU_SOURCE

int a[]={0,0,0};
semaphore_t t1,t2,t3,full,mutex;

void function_1(int *arg)
{
  int threadId = *arg;
  printf("Started child thread %d\n", threadId);

  while (1){
    P(&t1);
    P(&mutex);
    printf("Executing thread %d, Incrementing the array variable\n",threadId);
    a[0]++;
    V(&mutex);
    V(&full);
    sleep(1);
  }
}

void function_2(int *arg)
{
  int threadId = *arg;
  printf("Started child thread %d\n", threadId);

  while (1){
    P(&t2);
    P(&mutex);
    printf("Executing thread %d, Incrementing the array variable\n",threadId);
    a[1]++;
    V(&mutex);
    V(&full);
    sleep(1);
  }
}

void function_3(int *arg)
{
  int threadId = *arg;
  printf("Started child thread %d\n", threadId);

  while (1){
    P(&t3);
    P(&mutex);
    printf("Executing thread %d, Incrementing the array variable\n",threadId);
    a[2]++;
    V(&mutex);
    V(&full);
    sleep(1);
  }
}

int main()
{  int arg;
  int i;
  int id[3] = {0, 1, 2};

  init_sem(&t1, 1);
  init_sem(&t2, 1);
  init_sem(&t3, 1);
  init_sem(&full, 0);
  init_sem(&mutex, 1);

  start_thread(function_1, &id[0]);
  start_thread(function_2, &id[1]); 
  start_thread(function_3, &id[2]);

  while(1) {

    P(&full);
    P(&full);
    P(&full);
    P(&mutex);
    printf("In main thread, Printing array -\t\t [ %d\t %d\t %d ]\t \n",a[0],a[1],a[2]);
    V(&mutex);
    V(&t1);
    V(&t2);
    V(&t3);
    sleep(1);
  } 

  return 0;
}
