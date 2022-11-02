// Illustration of a parent process spwaning/creating its child process
// and then both executing an infinite loop
// Compile and run it as daemon process; Observe the following
//(a) if parent is killed child becomes orphan; init(1) becomes its parent
//(b) if child is killed its status becomes dyfunct (Zobmie) process

#include<stdio.h>
#include<sys/types.h>
#include <unistd.h>

void main (void)
{
    int i=0;  i++;
    
	if(fork())  // creates a child process
	{
		//  code executed by original parent
		for(;;) {} 
	}
	else
	{
		//  code executed by new child
		for(;;) {}
	}

}