#include<stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>


void main (void)
{
	pid_t   x;

    printf("\n\t The original parent proc id %d ",getpid());
	for(int i=0;i<=4;i++)
		{
			if((x=fork()))
			   printf("\n \t Created child %d by %d \n",x,getpid());
			else
			   break;	//printf("\n\t We are the child processes %d  par %d",getpid(), getppid());
		}
	//if(x==0)
		//for(;;) ;
}
	