#include<stdio.h>
#include<stdlib.h>
typedef struct 
{int at;
 int actual_bt;
 int bt;
 int ct;
 int pid;
 int priority;
}PCB;
typedef struct node
{  PCB process;
   struct node *next;
   struct node *prev;
}process_list;
typedef struct 
{
	process_list *header;
	process_list *tail;
}Queue;
void enqueue(int priority,int at,int bt,int pid,Queue *Q);
process_list *dequeuing(Queue *Q);
void renqueue(process_list *temp,Queue *RQ);
process_list *max_priority(Queue *RQ);
int main()
{   Queue Q,RQ;
	RQ.header=NULL;
	RQ.tail=NULL;
	Q.header=NULL;
	Q.tail=NULL;
	int n,at,bt,pid,priority;
	printf("enter number of process and time quantum\n");
	scanf("%d",&n);
	printf("enter process id,priority,its arrival time and burst time\n");
	for(int i=0;i<n;i++)
	{  scanf("%d%d%d%d",&pid,&priority,&at,&bt);
		enqueue(priority,at,bt,pid,&Q); 
	}
	int ct=0,wt=0,tot=0;
	float totav=0,wtav=0;
	process_list *temp,*temp2,*max;
	temp2=Q.header;
	while(temp2!=NULL && temp2->process.at<=ct)
		{  // printf("hi\n");
			temp2=dequeuing(&Q);
			renqueue(temp2,&RQ);
			temp2=Q.header;
		}
	int context_switch=0;
	temp=RQ.header;
	for(int i=0;i<n;)
	{  
	 	if(RQ.header==NULL )
	 	{ temp2=dequeuing(&Q);
		  renqueue(temp2,&RQ);
		  ct=temp2->process.at;
		  while(temp2!=NULL && temp2->process.at<=ct)
		{  // printf("hi\n");
			temp2=dequeuing(&Q);
			renqueue(temp2,&RQ);
			temp2=Q.header;
		}
		
	 	}

	 	max=max_priority(&RQ);
	 	//printf("%d",max->process.priority);
	    if( temp==NULL || max->process.priority > temp->process.priority )
	 		{ 
	 		  temp=max;
	 		  context_switch++;
	 		}

	   if (temp->process.bt ==1)
	   {ct++ ;   
	   	printf("process: %d\tat: %d\tbt: %d\tcompletion time:%d",temp->process.pid,temp->process.at,temp->process.actual_bt,ct);
	 	 tot=ct-temp->process.at;
 		wt=tot-temp->process.actual_bt;
 		printf("\tTurn over time: %d\twaiting time: %d\n",tot,wt);
 				if( temp!=RQ.header)
 				{  
 		 		temp->prev->next=temp->next;
 		 		if (temp->next!=NULL)
		 		  temp->next->prev=temp->prev;
		 		  free(temp);
		 		  temp=NULL;

 				}
	 				
	 		  else
	 		{   
	 			if(temp->next!=NULL)
	 			temp->next->prev=NULL;
	 			
	 			RQ.header=temp->next;
	 			free(temp);
	 			temp=NULL;
	 		}
 		totav+=tot;
 		wtav+=wt;
	   	i++;
	   		}
	   else 
	   {
	   	ct++;
	   	temp->process.bt-=1;
	   	
	   }
	   while(temp2!=NULL && temp2->process.at<=ct)
		{	//printf("hii\n");
			temp2=dequeuing(&Q);
			renqueue(temp2,&RQ);
			temp2=Q.header;
		}
	 
	}
	totav=totav/n;
	wtav=wtav/n;
	printf("average turn over time=%f \n average waiting time=%f\n",totav,wtav);
	printf("No. of context switch : %d\n",context_switch);

}
void enqueue(int priority,int at,int bt,int pid,Queue *Q)
{ process_list *temp=malloc(sizeof(process_list));
  temp->process.at=at;
  temp->process.bt=bt;
  temp->process.actual_bt=bt;
  temp->process.pid=pid;
  temp->process.priority=priority;
  temp->next=NULL;
  if (Q->header==NULL)
  {
  	Q->header=temp;
  	temp->prev=NULL;
  	Q->tail=temp;
  	
  	return;
  } 
  Q->tail->next=temp;
  temp->prev=Q->tail;
  Q->tail=temp;
}

process_list *dequeuing(Queue *Q)
{
  process_list *temp=Q->header;
  if(temp->next!=NULL)
  Q->header=temp->next;
	else 
	Q->header=NULL;
  return temp ;
}

void renqueue(process_list *temp,Queue *RQ)
{ if (RQ->header==NULL)
  {
  	RQ->header=temp;
	temp->next=NULL;
	temp->prev=NULL;
  	RQ->tail=temp;
  	return;
  } 
  
 RQ->tail->next=temp;
 temp->next=NULL;
 temp->prev=RQ->tail;
 RQ->tail=temp;

}

process_list *max_priority(Queue *RQ)
{ process_list *temp=RQ->header;
 process_list *max=RQ->header;
   while(temp!=NULL)
   {  if(temp->process.priority > max->process.priority)
   		max=temp;

      temp=temp->next;
   }
   return max;

}