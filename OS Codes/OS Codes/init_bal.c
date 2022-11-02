#include<stdio.h>
#include <sys/types.h>


void main (void)
{
	FILE  *f1;

    int x=2000;

	f1=fopen("acc_balance.txt","w+");
	fprintf(f1,"bal:%d",x);
	//printf("\n\t Balance : %d",x);
	fclose(f1);
}
	