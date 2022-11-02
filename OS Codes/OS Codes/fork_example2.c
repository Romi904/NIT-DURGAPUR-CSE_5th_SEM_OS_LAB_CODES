#include<stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>


void main (void)
{
	int i=5;
	pid_t   x;

    fork();
    fork();
    fork() && fork();
    fork() || fork();

	
	printf("\n\t Hello\n");
}
	