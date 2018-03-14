#include<stdio.h>
#include<math.h>
int main()
{ long int n=100000,check;
	long int count=0,prime_count=0;
  long int i=1;
  for(i=2;prime_count < n;i++)
  {  check=sqrt(i)+1;
  	 count=0;
  	for(long int j=1;j<check; j++ )
    { if( i%j==0)
    	count++;

    }
    if(count==1)
     {
     	//printf("%d\n",i);
     	prime_count++;
     } 	
  }

}