import java.util.*;
class page
{ int page_num;
int frame_num;

}
class paging_LL{

	static int Main[]=new int[1024];
	static int page_size=4;
	static {
		System.out.println("Main memory size: "+Main.length+"\t pagesize= "+page_size);
	}
public static void main(String[] args) {
	
	
	Scanner io=new Scanner(System.in);
	System.out.println("enter process memory");
	int mem=io.nextInt();
	
	LinkedList<page> LL =new LinkedList<page>();
	paging_LL co=new paging_LL();
	co.alloc(LL,mem);
	System.out.println("enter page no. to access");
	int pageno=io.nextInt();
	int address=co.access(LL,pageno);
	if (address==-1)
		System.out.println("invalid access");
	else
	{System.out.print(pageno+"th page address: "+address);
		System.out.println("\tvalue at starting location: "+Main[address]);}
}

void alloc(LinkedList<page> LL,int mem)
{ int pageno=mem/page_size;
	Random  rand=new Random();
	if( mem % page_size !=0)
		pageno++;
   for(int i=0;i<pageno;i++)
   { page temp=new page();
   	temp.page_num=i;
     temp.frame_num=rand.nextInt(256);
     while(Main[temp.frame_num*page_size]!=0)
     {
     	temp.frame_num=rand.nextInt(256);
     }
     Main[temp.frame_num*page_size]=i;
     LL.add(temp);
   }
}
int access(LinkedList<page> LL,int pageno)
{
	Iterator<page> it=LL.iterator();
	page i;
	i=null;
	if (LL.size()-1<pageno)
			return(-1);
	while (it.hasNext())
	{ i=it.next();
		if(i.page_num!=pageno)
		System.out.println("accesing page no. "+i.page_num+"\t address: "+i.frame_num*page_size);
 	    else
 	    	break;
	}
	return ( i.frame_num*page_size);
}

}