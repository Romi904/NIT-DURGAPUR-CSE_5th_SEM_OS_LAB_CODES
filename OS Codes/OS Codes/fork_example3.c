#include<stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>


void main (void)
{
	FILE  *f1, *f2;
	char  c;
	pid_t x;


    f1=fopen("xx.txt","r");
    f2=fopen("xx_copy.txt","w");

    x=fork();
   
    if(x>0) // exclusive parent process
	{  

        while(!feof(f1))
        {
		c=fgetc(f1);
		sleep(4);
		printf("\n\t %c %d %d \n",c,getpid(),getppid());
		fputc(c,f2);
		}
	}
	else // exclusive to the child process
	{
		while(!feof(f1))
		{
		c=fgetc(f1);
		printf("\n\t %c %d %d \n",c,getpid(),getppid());
		fputc(c,f2);
		//sleep(1);
		}
	}
	
	//sleep(4);
	fclose(f1);
	fclose(f2);
}
	