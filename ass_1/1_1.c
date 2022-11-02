#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
void f1(int x)
{
    printf("Custom signal handler %d\n", getpid());
    signal(SIGINT, SIG_DFL);
}
int main()
{
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    signal(SIGINT, f1);
    for (int i = 1; i <= n; i++)
    {
        pid_t x = fork();
        if (x == 0)
        {
            signal(SIGINT, SIG_DFL);
printf("Child %d\tProcess ID: %d\tParent
Process ID:%d\n", i, getpid(), getppid());
        }
        else
        {
            break;
        }
    }
    for (;;)
        ;
    return 0;
}