#include<stdio.h>
#include<stdlib.h>
struct LL 																//linked list node-- for process location
{   int name;
	char *start;
	char *end;
	struct LL *next;
};
struct mm 																 // memory manager -having process "list"
{ char *start_block;
 struct LL *header;
 char *end_block;
 int unused;
};
void insert(struct LL *temp,int index,int size); 						//inesrt a new process 
int first_fit(struct mm *memory_manager,int size,int index);			 //memory scheme used in allocating 
int deallocate(struct mm *memory_manager,int index); 					//remove process from main memory
void output(struct mm *memory_manager); 								// UI for the programmer/user to know what is happening 
void compaction(struct mm *memory_manager); 							//compaction algorithm for solving external fragmentation 
int main()
{   int size,n,choice=1,allocsize,index=1,k,choice2,dealloc;
	printf("enter total size \n");
	scanf("%d",&size);
 	struct mm memory_manager;
	memory_manager.start_block=(char *)malloc(size);
	memory_manager.unused=size;
	memory_manager.header=NULL;
 	memory_manager.end_block=memory_manager.start_block+size-1;
 	while(choice)  														//asking user to allocate process ---can be modified into taking process from  input-queue 
 	{
 		printf("1)allocate size or 2)deallocate  \n");
 		scanf("%d",&choice2);
 		if(choice2==1)
 		{scanf("%d",&allocsize);
 		k=first_fit(&memory_manager,allocsize,index);  
 		if(k)                                      						// allocated on first go
 			{printf("%d index allocated  \n",index);
 			 printf("allocated sequence\n");
 			 output(&memory_manager);
 			  index++;
 			 
 			 }
 		else if(memory_manager.unused>=allocsize)						// checking external fragmentation and allocating new process after doing compaction(if possible)
 		{  compaction(&memory_manager);
 			first_fit(&memory_manager,allocsize,index);
 			printf("%d index allocated  \n",index);
 			 printf("allocated sequence after compaction\n");
 			 output(&memory_manager);	
 			 index++;
 			 
 		}

 		else															// not enough memory
 			printf("not allocated \n");
 		}
 		else if(choice2==2)
 		{  printf("process index to delallocate \n");
 			scanf("%d",&dealloc);
 			if(!deallocate(&memory_manager,dealloc))
 				printf("no process index %d is present\n",dealloc);

 		}
 		printf("enter non-zero to continue or zero to exit \n");
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
				free(temp1);
				printf("allocated	sequence\n");
			output(memory_manager);
				return(1);

			}
			else
			{
				temp=temp->next;
			}
		}

	
	return(0);
}

int first_fit(struct mm *memory_manager,int size,int index)
{ 
	struct LL *temp,*temp1;

		if(memory_manager->unused<size)
			return(0);

		if(memory_manager->header==NULL)
		{
			temp=(struct LL*)malloc(sizeof(struct LL));
			memory_manager->header=temp;
			temp->name=index;
			temp->start=memory_manager->start_block;
			temp->end=temp->start+size-1;
			temp->next=NULL;
			memory_manager->unused-=size;
			return(1);
		}
		temp=memory_manager->header;
		if(temp->start- memory_manager->start_block >= size)
		{temp=(struct LL*)malloc(sizeof(struct LL));
			temp->next=memory_manager->header;
			memory_manager->header=temp;
			temp->name=index;
			temp->start=memory_manager->start_block;
			temp->end=temp->start+size-1;
			memory_manager->unused-=size;
			return(1);

		}
		while(temp!=NULL)
		{  
 			if(temp->next!=NULL)
 			{ if((temp->next->start-temp->end -1)>=size)
 			    {   insert(temp,index,size);
					memory_manager->unused-=size;
						printf("%d\n",memory_manager->unused);
					return(1);
 			    }
 			  else
 			  	temp=temp->next;
 			}
 			 else
 			 {if((memory_manager->end_block-temp->end)>=size)
 			 	{
 			 		insert(temp,index,size);
					memory_manager->unused-=size;
					return(1);
 			 	}
 			 	 temp=NULL;

 			 }
		}
	return(0);
}
void compaction(struct mm *memory_manager)
{ struct LL *temp=memory_manager->header;
	int size;
	if(temp->start- memory_manager->start_block >0)
		{		size=temp->end-temp->start+1;
			temp->start=memory_manager->start_block;
			temp->end=temp->start+size-1;
		}
	while(temp->next!=NULL)
		{  
 		
 			if((temp->next->start-temp->end -1)>0)
 			    { size=temp->next->end-temp->next->start+1;
 			    	 temp->next->start=temp->end+1;
					temp->next->end=temp->next->start+size-1;
 			    }
 			
 			temp=temp->next;

		}

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
void insert(struct LL *temp,int index,int size)
{  
	struct LL *temp1=(struct LL*)malloc(sizeof(struct LL));
 	temp1->name=index;
 	temp1->start=temp->end+1;
	temp1->end=temp1->start+size-1;
	temp1->next=temp->next;
	temp->next=temp1;
					
}