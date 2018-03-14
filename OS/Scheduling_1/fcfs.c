#include<stdio.h>
#include<stdlib.h>
typedef struct 
{int at;
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
process_list *dequeuing(Queue *Q,int ct);
int main()
{   Queue Q;
	Q.header=NULL;
	Q.tail=NULL;
	int n,at,bt,pid;
	printf("enter number of process\n");
	scanf("%d",&n);
	printf("enter process id,its arrival time and burst time in s \n");
	for(int i=0;i<n;i++)
	{  scanf("%d%d%d",&pid,&at,&bt);
		enqueue(at,bt,pid,&Q); 
	}
	
	int ct=0,wt=0,tot=0;
	process_list *temp;
	for(int i=0;i<n;i++)
	{ temp=dequeuing(&Q,ct);
	  if(temp->process.ct- temp->process.at != temp->process.bt)
	  {printf("process:%d    waiting time:%ds",temp->process.pid,ct-temp->process.at);
		wt+=ct-temp->process.at;}
	  else
	  {printf("process:%d    waiting time:%ds",temp->process.pid, 0);
		wt+=0;
	  }
	  ct=temp->process.ct;	
	  
 	printf("\tcompletion time:%ds     Turn over time: %ds \n",ct,temp->process.ct -temp->process.at);
 	tot+=temp->process.ct -temp->process.at;
 	free(temp);
	}
	float avg_tot=1.0*tot/n;
	float avg_wt=1.0*wt/n;
	printf("average turn over time=%fs \n average waiting time=%fs\n",avg_tot,avg_wt);


}

void enqueue(int at,int bt,int pid,Queue *Q)
{ process_list *temp=malloc(sizeof(process_list));

  temp->process.at=at;
  temp->process.bt=bt;
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
process_list *dequeuing(Queue *Q,int ct)
{
  process_list *temp=Q->header;
  if(ct >= temp->process.at)
  {temp->process.ct=ct+temp->process.bt;}
  else
  {
  	temp->process.ct=temp->process.at+temp->process.bt;
  }
  Q->header=temp->next;
  
  return temp ;
}
