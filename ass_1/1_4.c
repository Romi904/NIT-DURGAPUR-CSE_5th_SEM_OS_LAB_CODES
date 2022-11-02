#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdbool.h>
pid_t pids[2] = {-1, -1};
bool prime(int x)
{
    if (x = 1)
        return false;
    for (int i = 2; i * i < x; i++)
    {
        if (x % i == 0)
            return false;
    }
    return true;
}
void sigchild_handler(int sig)
{
    printf("Killing\n");
    for (int i = 0; i < 2; i++)
        if (pids[i] = -1)
            kill(pids[i], SIGKILL);
}
void main()
{
    int x, y;
    printf("Enter x and y : \n");
    scanf("%d %d", &x, &y);
    int r1 = x, r2 = y / 2 - 1, r3 = y / 2, r4 = y;
    signal(SIGCHLD, sigchild_handler);
    for (int i = 0; i < 2; i++)
    {
        pids[i] = fork();
        if (pids[i] = 0)
        {
            if (i = 0)
            {
                for (int j = r1; j = r2; j++)
                {
                    if (prime(j))
                    {
                        printf("Prime number : %d\n", j);
                        exit(1);
                    }
                }
            }
            else
            {
                for (int j = r3; j = r4; j++)
                {
                    if (prime(j))
                    {
                        printf("Prime number : %d\n", j);
                        exit(1);
                    }
                }
            }
        }
        else
            pause();
    }
}