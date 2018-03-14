#include<stdio.h>
#include<stdlib.h>
struct LL //linked list node
{   int name;
	char *start;
	char *end;
	struct LL *next;
};
struct mm 
{ char *start_block;
 struct LL *header;
 char *end_block;
 int unused;
};

int best_fit(struct mm *memory_manager,int size,int index);
int deallocate(struct mm *memory_manager,int index);
void output(struct mm *memory_manager); 
int main()
{   int size,n,choice=1,allocsize,index=1,k,choice2,dealloc;
	printf("enter total size \n");
	scanf("%d",&size);
 	struct mm memory_manager;
	memory_manager.start_block=(char *)malloc(size);
	memory_manager.unused=size;
	memory_manager.header=NULL;
 	memory_manager.end_block=memory_manager.start_block+size-1;
 	while(choice)
 	{
 		printf("1)allocate size or 2)deallocate  \n");
 		scanf("%d",&choice2);
 		if(choice2==1)
 		{scanf("%d",&allocsize);
 		k=best_fit(&memory_manager,allocsize,index);
 		if(k)
 			{printf("%d index allocated  \n",index);
 			 printf("allocated sequence\n");
 			 output(&memory_manager);
 			  index++;
 			 }

 		else
 			printf("not allocated \n");
 		}
 		else if(choice2==2)
 		{  printf("process index to delallocate \n");
 			scanf("%d",&dealloc);
 			if(!deallocate(&memory_manager,dealloc))
 				printf("no process index %d is present\n",dealloc);

 		}
 		printf("enter one to continue or zero to exit \n");
 		scanf("%d",&choice);
 	}
}


int deallocate(struct mm *memory_manager,int index)
{ struct LL *temp, *temp1;
	
	 temp=memory_manager->header;
		if(temp==NULL)
			return(0);
		if( temp->name==index)
		{
			memory_manager->header=temp->next;
			memory_manager->unused+=temp->end-temp->start+1; 
			printf("%d %d \n",temp->name,memory_manager->unused );
			free(temp);
			//printf("%d\n",memory_manager[i].unused);
			printf("allocated	sequence\n");
			output(memory_manager);
			return(1);
		}
		while(temp->next!=NULL)
		{
			if(temp->next->name==index)
			{ temp1=temp->next;
				temp->next=temp1->next;	
				memory_manager->unused+=temp1->end-temp1->start+1;
				//printf("%d %d \n",temp1->name,memory_manager->unused );
				printf("allocated	sequence\n");
				output(memory_manager);
				free(temp1);
				return(1);

			}
			else
			{
				temp=temp->next;
			}
		}

	
	return(0);
}

int best_fit(struct mm *memory_manager,int size,int index)
{ int minmem=10000000,no=-1;
	struct LL *temp,*temp1,*mini=NULL;
		if(memory_manager->unused<size)
			//printf("hi");
			return(0);

		if(memory_manager->header==NULL)
		{
			minmem=memory_manager->unused;
			mini=memory_manager->header;
			
		}
		temp=memory_manager->header;
		if(temp!=NULL && (temp->start-memory_manager->start_block)>=size && (temp->start-memory_manager->start_block) < minmem )
		{minmem=temp->start-memory_manager->start_block;
		 mini=temp;
		 no=1;
		}
		while(temp!=NULL)
		{  
 			if(temp->next!=NULL)
 			{ if((temp->next->start-temp->end -1)>=size && (temp->next->start-temp->end -1)<minmem)
 			    {   
 			    	minmem=temp->next->start-temp->end -1;
 			    	mini=temp;
 			    	no=-1;
 			    }
 			  else
 			  	temp=temp->next;
 			}
 			 else
 			 {if((memory_manager->end_block-temp->end)>=size && (memory_manager->end_block-temp->end) < minmem)
 			 	{  minmem=memory_manager->end_block-temp->end;
 			    	mini=temp;
					no=-1;
 			 	}
 			 	 temp=NULL;

 			 }

		}

	
    if(minmem>=size)
    {
    	temp1=(struct LL*)malloc(sizeof(struct LL)); //insertion 
 		temp1->name=index;
 		if(mini!=NULL && no!=1)
 		{temp1->start=mini->end+1;
 		temp1->next=mini->next;
 		mini->next=temp1;
 		}
 		else if (no==1)
 		{
 			temp1->start=memory_manager->start_block;
 			temp1->next=memory_manager->header;
 			memory_manager->header=temp1;
 		}
 		else if(mini==NULL)
 		{temp1->start=memory_manager->start_block;
 		 memory_manager->header=temp1;
 		 temp1->next=NULL;
 		}
		temp1->end=temp1->start+size-1;
		memory_manager->unused-=size;
		//printf("hi2\n");
		//printf("%d\n",memory_manager->unused);
		return(1);
    }
 return(0);
}
void output(struct mm *memory_manager)
{	printf("pid \t   memory location \n");
	struct LL *temp=memory_manager->header;
	while(temp!=NULL)
	{ printf("%d \t %d-%d \n",temp->name,(temp->start-memory_manager->start_block),(temp->end-memory_manager->start_block));
	  temp=temp->next;
	}
	printf("\n");
}