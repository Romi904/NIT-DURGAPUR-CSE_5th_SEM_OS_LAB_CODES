#include<stdio.h>
#include <sys/types.h>


void main (void)
{
	pid_t mypid=getpid();
	pid_t myparpid=getppid();
	printf("\n\t Process Id=%d; Parent Process Id=%d \n", mypid,myppid);

	for(;;) {}
}