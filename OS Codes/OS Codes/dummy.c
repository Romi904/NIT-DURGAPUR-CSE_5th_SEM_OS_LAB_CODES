#include <stdio.h>
 #include <sys/types.h>
       #include <unistd.h>

int main()
{
    fork() && fork();
    fork() || fork();
    
    printf("Hello World pid=%d ppid=%d \n",getpid(),getppid());
    return 0;
} 