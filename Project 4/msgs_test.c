#include "msgs.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Semaphore_t *mutex;
int curr_port = 0;
int server_cnt = 0;
int client_cnt = 0;
int serverPorts[50]={0};
int clientPorts[100]={0};

void server ()
{
	 		
	int portNum;
	int replyTo=0;
	int message[msg_size]={0,0,0,0,0,0,0,0,0,0};
	int received[msg_size];
	int serverNo;
	int count=0;
	P(mutex);
		portNum=curr_port++;
		serverPorts[server_cnt]=portNum;
		serverNo=server_cnt++;
	V(mutex);
	if((portNum+1)>portsCount)
	{
		printf("\nAll ports are busy");
	}else {
	        int incr = 1;
	        int mul = 3;
		while(1)
		{
			receive(portNum,received);
			printf("\nServer %d received data from client %d",serverNo,received[0]);
			printf("\n Received data: \t%d", received[0]);
			count=1;
			while(count<msg_size)
			{
				printf("\t %d ",received[count]);
				++count;
			}
			printf("\n");
			replyTo=clientPorts[received[0]];
			sleep(1);
			count=1;
			message[0]=received[0];
			while(count<msg_size)
			{
				message[count]=(received[count]*mul + incr);
				++count;
			}
			send(replyTo,message);
			printf("\nServer %d sent message to client %d",serverNo,received[0]);
		}
	}
}


void client ()
{

	int portNo;
	int clientNo;
	int serverPortNo=serverPorts[rand() % server_cnt];
	int message[msg_size]={1,1,1,1,1,1,1,1,1,1};
	int received[msg_size];
	int count=0;
	P(mutex);
		portNo=curr_port++;
		clientPorts[client_cnt]=portNo;
		clientNo=client_cnt++;
	V(mutex);
	if((portNo+1)>portsCount)
	{
	  printf("\nAll ports are busy");
	} else {
		while(1) {
			message[0]=clientNo;
			send(serverPortNo,message);
			printf("\nClient %d sent message to server %d",clientNo,serverPortNo);
			count=0;
			while(count<msg_size)
			{
				message[count]*=3;
				count++;
			}
			sleep(1);
			receive(portNo,received);
			printf("\nClient %d received data from server %d",clientNo,serverPortNo);
			printf("\n Received data: \t");
			count=0;
			while(count<msg_size)
			{
				printf("%d \t",received[count]);
				count++;
			}
			printf("\n");
		}
	}	
}


int main(){
	Ready_Q = (TCB_t *) malloc(sizeof(TCB_t)); 
    	Ready_Q=newQueue();
	initialize_Ports();
	mutex = CreateSem(1);
	start_thread(server);
	start_thread(server);
	start_thread(server);
        start_thread(client);
	start_thread(client);
	start_thread(client);
	start_thread(client);
	start_thread(client);
	start_thread(client);
   	run();
	while(1){
		sleep(1);
	}
}
