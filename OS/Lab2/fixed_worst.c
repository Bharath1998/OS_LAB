#include<stdio.h>
#include<stdlib.h>
 struct LL
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

void partitioning(struct mm memory_manager[],int n);
int deallocate(struct mm memory_manager[],int index,int n);
 int worst_fit(struct mm memory_manager[],int size,int index,int n);
void output(struct mm memory_manager[],int n);
int main()
{   int size,n,choice=1,allocsize,index=1,k,choice2,dealloc;
	printf("enter total size and no. of partitions\n");
	scanf("%d%d",&size,&n);
 	struct mm memory_manager[n];
	memory_manager[0].start_block=(char *)malloc(size);
 	partitioning(memory_manager,n);
 	while(choice)
 	{
 		printf("1)allocate size or 2)deallocate  \n");
 		scanf("%d",&choice2);
 		if(choice2==1)
 		{scanf("%d",&allocsize);
 		k=worst_fit(memory_manager,allocsize,index,n);
 		if(k)
 			{printf("process index %d allocated in block %d \n",index,k);
 				output(memory_manager,n);
 			  index++;
 			 }

 		else
 			printf("not allocated \n");
 		}
 		else if(choice2==2)
 		{  printf("process index to delallocate \n");
 			scanf("%d",&dealloc);
 			if(!deallocate(memory_manager,dealloc,n))
 				printf("no process index %d is present\n",dealloc);

 		}
 		printf("enter one to continue or zero to exit \n");
 		scanf("%d",&choice);
 	}
}

void partitioning(struct mm memory_manager[],int n)
{   int partition;
	printf("enter partition size \n");
	scanf("%d",&partition);
 	memory_manager[0].end_block=memory_manager[0].start_block+partition-1;
 	memory_manager[0].header=NULL;
	memory_manager[0].unused=partition;
	for(int i=1;i<n;i++)
	{   scanf("%d",&partition);
		memory_manager[i].header=NULL;
		memory_manager[i].unused=partition;
		memory_manager[i].start_block=memory_manager[i-1].end_block+1;
		memory_manager[i].end_block=memory_manager[i].start_block+partition-1;
	}

}
int deallocate(struct mm memory_manager[],int index,int n)
{ struct LL *temp, *temp1;
	for(int i=0;i <n;i++)
	{ temp=memory_manager[i].header;
		if(temp==NULL)
			continue;
		if( temp->name==index)
		{
			memory_manager[i].header=temp->next;
			memory_manager[i].unused+=temp->end-temp->start+1;
			//printf("%d %d \n",temp->name,memory_manager[i].unused );
			output(memory_manager,n);
			free(temp);
			return(1);
		}
		while(temp->next!=NULL)
		{
			if(temp->next->name==index)
			{ temp1=temp->next;
				temp->next=temp1->next;	
				memory_manager[i].unused+=temp1->end-temp1->start+1;
				//printf("%d %d \n",temp1->name,memory_manager[i].unused );
				output(memory_manager,n);
				free(temp1);
				return(1);

			}
			else
			{
				temp=temp->next;
			}
		}

	}
	return(0);
}

int worst_fit(struct mm memory_manager[],int size,int index,int n)
{ int i,j=-1,minmem=size-1,no=-1;
	struct LL *temp,*temp1,*mini=NULL;
	for (int i = 0; i <n; i++)
	{
		/* code */
		if(memory_manager[i].unused<size)
			continue;

		if(memory_manager[i].header==NULL && memory_manager[i].unused > minmem)
		{
			minmem=memory_manager[i].unused;
			mini=memory_manager[i].header;
			no=i;
			j=-1;
		}
		temp=memory_manager[i].header;
		if(temp!=NULL && temp->start -memory_manager[i].start_block>=size && temp->start -memory_manager[i].start_block > minmem)
		{minmem=memory_manager[i].unused;
			mini=memory_manager[i].header;
			no=i;
			j=1;

		}
		while(temp!=NULL)
		{  
 			if(temp->next!=NULL)
 			{ if((temp->next->start-temp->end -1)>=size && (temp->next->start-temp->end -1)>minmem)
 			    {   
 			    	minmem=temp->next->start-temp->end -1;
 			    	mini=temp;
 			    	no=i;
 			    	j=-1;
 			    }
 			  else
 			  	temp=temp->next;
 			}
 			 else
 			 {if((memory_manager[i].end_block-temp->end)>=size && (memory_manager[i].end_block-temp->end) > minmem)
 			 	{  minmem=memory_manager[i].end_block-temp->end;
 			    	mini=temp;
					no=i;
					j=-1;
 			 	}
 			 	 temp=NULL;

 			 }

		}

	}
    if(no!=-1)
    {
    	temp1=(struct LL*)malloc(sizeof(struct LL));
 		temp1->name=index;
 		if(mini!=NULL && j!=1)
 		{temp1->start=mini->end+1;
 		temp1->next=mini->next;
 		mini->next=temp1;
 		}
 		else if(mini==NULL)
 		{temp1->start=memory_manager[no].start_block;
 		 memory_manager[no].header=temp1;
 		 temp1->next=NULL;
 		}
 		else if(j==1)
 		{
 			temp1->start=memory_manager[no].start_block;
 			temp1->next=memory_manager[no].header;
 			memory_manager[no].header=temp1;
 		}

		temp1->end=temp1->start+size-1;
		memory_manager[no].unused-=size;
		//printf("%d\n",memory_manager[no].unused);
		return(no+1);
    }
 return(0);
}

void output(struct mm memory_manager[],int n)
{  for(int i=0;i<n;i++)
	{struct LL *temp=memory_manager[i].header;
	 printf("BLOCK NO: %d\n",i+1);
	while(temp!=NULL)
	 { printf("%d \t %d-%d \n",temp->name,(temp->start-memory_manager[i].start_block),(temp->end-memory_manager[i].start_block));
	  temp=temp->next;
	 }
	}
	printf("\n");
}
