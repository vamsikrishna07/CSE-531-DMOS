#include "TCB.h"

TCB_t* newQueue() {
    TCB_t* head = NULL;
    return head;
}

TCB_t* NewItem() {
	TCB_t *item = (TCB_t *)malloc(sizeof(TCB_t));
	item->previous = NULL;
	item->next = NULL;
	return item; 	
}


void AddQueue(TCB_t** head, TCB_t* item) {
	if((*head)==NULL)
	{
		(*head) = item;
	  	(*head)->next = *head;
	  	(*head)->previous = *head;
	}
	else
	{
        	TCB_t *tail = (*head)->previous;
		item->next = *head;
		item->previous = tail;
		tail->next = item;
		(*head)->previous = item; 
	}
}


TCB_t * DelQueue(TCB_t** head) {
     	TCB_t *del;
     	if((*head) == NULL) 
	{
     		perror("Queue is empty");
     		exit(EXIT_FAILURE);
     	}
     	else
	{
		if((*head)->next ==(*head)) 
		{
     	     		del = (*head);
     	     		(*head) = NULL;
     	   	}
		else
		{
     	    		del = (*head);
     	    		TCB_t *last_item,*next_item;
     	    		last_item = (*head)->previous;
     	    		next_item = (*head)->next;
     	    		last_item->next = next_item;
     	    		next_item->previous = last_item;
     	    		*head = next_item;     	   }
     	}
     	return del;
}

void print_queue(TCB_t* head) 
{
	printf("current Queue -\t");
	if(head == NULL) 
	{
     	   printf("Empty Queue \n");
     	}
     	else
     	{
     	    TCB_t *tail=head;
	    do 
	    {
	    	printf("%d \t ", tail->val);
	    	tail=tail->next;	
	    } while(tail!=head); 
     	}
     	printf("\n\n");
}



