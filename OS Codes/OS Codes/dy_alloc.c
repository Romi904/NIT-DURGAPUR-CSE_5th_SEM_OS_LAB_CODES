#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>


void main (void)
{
	for(int i=0; i<=20; i++)
		{
			malloc(1024*10);  
			sleep(1);
		}
}