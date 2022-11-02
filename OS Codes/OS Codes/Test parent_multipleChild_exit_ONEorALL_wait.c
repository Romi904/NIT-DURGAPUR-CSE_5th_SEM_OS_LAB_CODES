#include<stdio.h>        // printf scanf
#include<unistd.h>       // slepp
#include <sys/types.h>   // pid_t
#include<sys/wait.h>     // wait
#include <signal.h>      // signal kill
#include<stdlib.h>       // exit

void main (void)
{   
	pid_t child_pid, wpid;
	int status = 0;

	//Father code (before child processes start)

	for (int id=0; id<2; id++) {
    	if ((child_pid = fork()) == 0) {
        	   sleep(1 + rand() % 10);
        	   exit(id);
    	}
	}

	//wpid = waitpid(child_pid[1],&status,0); // [A] this way parent WAITS for SPECIFIED child process to exit
	//wpid = waitpid(-1,&status,0); // [B] this way parent WAITS for ANY_ONE of the child process to exit
    //wpid = waitpid(child_pid[1],&status,WNOHANG); // [C] this way parent RETURNS IMMEDIATELY if child with specified pid has not terminated
    //wpid = waitpid(-1,&status,WNOHANG); // [D] this way parent RETURNS IMMEDIATELY if none of the child has terminated
    while((waitpid(-1,&status,0)) > 0); // [E] this way parent WAITS for ALL of it's the child process to exit

	sleep(1);
	printf("\n\t Parent %d synchronized with child death (ret Child Id %d ....ret Status %d.... )",getpid(),wpid,status);
	
}