import java.util.*;
class paging_LL{

	static int Main[]=new int[1024];
	static int page_size=4;
	static {
		System.out.println("Main memory size: "+Main.length+"bytes\t pagesize= "+page_size+"bytes");
	}
public static void main(String[] args) {
	
	
	Scanner io=new Scanner(System.in);
	System.out.println("enter process memory");
	int mem=io.nextInt();
	int pageno=mem/page_size;
	if( mem % page_size !=0)
		pageno++;
	int page_table[]=new int[pageno];
	paging_LL co=new paging_LL();
	co.alloc(page_table);
	System.out.println("enter page no. to access");
	 pageno=io.nextInt();
	int address=co.access(pageno,page_table);
	if (address==-1)
		System.out.println("invalid access");
	else
	{System.out.print(pageno+"th page address: "+address);
		System.out.println("\tvalue at starting location: "+Main[address]);}
}

void alloc(int page_table[])
{ 
	Random  rand=new Random();

   for(int i=0;i<page_table.length;i++)
   { 
     page_table[i]=rand.nextInt(256);
     while(Main[page_table[i]*page_size]!=0)
     {
     	page_table[i]=rand.nextInt(256);
     }
     Main[page_table[i]*page_size]=i;
   }
}
int access(int pageno,int page_table[])
{

	if (page_table.length-1<pageno)
			return(-1);
	
	return (page_table[pageno]*page_size);
}

}
