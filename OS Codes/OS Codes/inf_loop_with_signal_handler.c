#include<stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int n=0;

/////////// different handler codes for SIGSTOP
void f1(int x)
{
	printf("\n\t Recieved Signal %d \n",x);
	printf("\n\t 'Bye'..... I can't sustain the blow.....I am dying...... \n");
	signal(SIGINT,SIG_DFL);
	kill(getpid(),SIGINT);
}
void f2(int x)
{
	printf("\n\t Recieved Signal %d \n",x);
	printf("\n\t Why are you trying to kill me? You can't do this.....\n");
	signal(SIGINT,f1);
}
void f4(int x)
{
	printf("\n\t %d. Recieved Signal %d \n",n+1,x);
	n++;
	if(n>=5)
		signal(SIGINT,SIG_DFL);
}

/////////// handler code for SIGSTOP
void f5(int x)   
{
	printf("\n\t Recieved Signal %d \n",x);
	printf("\n\t Hey!!! you are forcefully suspending me.....\n");
	signal(SIGTSTP,SIG_DFL);
}



void main (void)
{
     //signal(SIGINT,f1);	// custom handler defined for SIGINT signal
     //signal(SIGINT,f2);	// custom handler defined for SIGINT signal
	signal(SIGINT,f4);    // custom handler defined for SIGINT  signal
	signal(SIGTSTP,f5);  // custom handler defined for SIGSTOP signal
	
	for(;;)
	{

        //sleep(20000);

	}

}