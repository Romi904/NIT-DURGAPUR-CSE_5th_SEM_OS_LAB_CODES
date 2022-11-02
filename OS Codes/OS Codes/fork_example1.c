#include<stdio.h>
#include <sys/types.h>
#include <stdlib.h>


void main (void)
{
	int i=5;
	pid_t   x;

    x=fork();
   

	if(x>0)  //only for parent
	{  i+=5; sleep(1);
	   printf("\n \t Par Process %d; x=%d",getpid(),i); 
	}
	else    //only for child
	{   i++;
		printf("\n \t Child Process %d its par %d; x=%d",getpid(),getppid(),i); 
	}

    // both for parent and child
	printf("\n\t Hello\n");
}
	