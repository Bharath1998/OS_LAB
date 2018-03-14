#include<stdio.h>
#include<stdlib.h>
typedef struct 
{int at;
 int actual_bt;
 int bt;
 int ct;
 int pid;
}PCB;
typedef struct node
{  PCB process;
   struct node *next;
}process_list;
typedef struct 
{
	process_list *header;
	process_list *tail;
}Queue;
void enqueue(int at,int bt,int pid,Queue *Q);
process_list *dequeuing(Queue *Q);
void renqueue(process_list *temp,Queue *RQ);
int main()
{   Queue Q,RQ;
	RQ.header=NULL;
	RQ.tail=NULL;
	Q.header=NULL;
	Q.tail=NULL;
	int n,at,bt,pid,TQ;
	printf("enter number of process and time quantum\n");
	scanf("%d%d",&n,&TQ);
	printf("enter process id,its arrival time and burst time \n");
	for(int i=0;i<n;i++)
	{  scanf("%d%d%d",&pid,&at,&bt);
		enqueue(at,bt,pid,&Q); 
	}
	int ct=0,wt=0,tot=0;
	float totav=0,wtav=0;
	process_list *temp,*temp2;
	temp2=dequeuing(&Q);
	renqueue(temp2,&RQ);
	temp2=Q.header;
	int context_switch=0;
	for(int i=0;i<n;context_switch++)
	{  

	 	temp=dequeuing(&RQ);
	 	if(temp==NULL)
	 	{ temp2=dequeuing(&Q);
		  renqueue(temp2,&RQ);

		  ct=temp2->process.at;
			temp2=Q.header;
	 	}

	   if (temp->process.bt <=TQ)
	   {ct=ct+temp->process.bt ;   
	   	printf("process: %d\tat: %d\tbt: %d\tcompletion time:%d",temp->process.pid,temp->process.at,temp->process.actual_bt,ct);
	 	 tot=ct-temp->process.at;
 		wt=tot-temp->process.actual_bt;
	  	printf("\tTurn over time: %d\twaiting time: %d\n",tot,wt);
	  	while(temp2!=NULL && temp2->process.at<=ct)
		{  // printf("hi\n");
			temp2=dequeuing(&Q);
			renqueue(temp2,&RQ);
			temp2=Q.header;
		}
 		totav+=tot;
 		wtav+=wt;
	   	i++;
	   }
	   else if(temp->process.bt > TQ)
	   {
	   	ct=ct+TQ;
	   	temp->process.bt-=TQ;
	   	while(temp2!=NULL && temp2->process.at<=ct)
		{	//printf("hii\n");
			temp2=dequeuing(&Q);
			renqueue(temp2,&RQ);
			temp2=Q.header;
		}
	   	renqueue(temp,&RQ);
	   }
	 
	}
	totav=totav/n;
	wtav=wtav/n;
	printf("average turn over time=%f \n average waiting time=%f\n",totav,wtav);
	printf("No. of context switch : %d\n",context_switch);

}

void enqueue(int at,int bt,int pid,Queue *Q)
{ process_list *temp=malloc(sizeof(process_list));
  temp->process.at=at;
  temp->process.bt=bt;
  temp->process.actual_bt=bt;
  temp->process.pid=pid;
  temp->next=NULL;
  if (Q->header==NULL)
  {
  	Q->header=temp;
  	
  	Q->tail=temp;
  	
  	return;
  } 
  Q->tail->next=temp;
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
  	
  	RQ->tail=temp;
  	return;
  } 
  
 RQ->tail->next=temp;
 temp->next=NULL;
 RQ->tail=temp;

}