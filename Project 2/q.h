#include "TCB.h"

TCB_t* newQueue() {
    TCB_t* head = NULL;
    return head;
}

TCB_t* NewItem() {
	TCB_t *x = (TCB_t *)malloc(sizeof(TCB_t));
	x->previous = NULL;
	x->next = NULL;
	return x; 	
}


void AddQueue(TCB_t** head, TCB_t* item) {
	if((*head)==NULL)
	{
		(*head) = item;
	  	item->previous = (*head);
	  	item->next = (*head);
	}
	else
	{       
	 TCB_t *tail=(*head);
		  do
		  {
		  tail=tail->next;	
		  }while(tail->next!=(* head));
		  tail->next=item; 	
		  (*head)->previous=item;
		  item->next=(*head);
		  item->previous=tail;
	}
}


TCB_t * DelQueue(TCB_t** head) {
     	TCB_t * item=NULL;
     	if((*head) == NULL) 
		{
     	   printf("Empty Queue\n");
     	}
     	else
		{
			if((*head)->next == (*head)) 
			{       
				item = (*head);
     	    			(*head) = NULL;
     	    			item->next = NULL;
     	    			item->previous = NULL;
     	   		}
			else
			{
     	    	TCB_t *tail=(*head);
	     		do
	     		{
	      			tail=tail->next;	
	     		} while(tail->next!=(*head));
	     		item = (*head);
	     		(*head) = (*head)->next;
	     		tail->next = (*head);
			(*head)->previous = tail;
     	     		item->next = NULL;
     	    		item->previous = NULL;
     	   }
     	}
     	return item;
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



