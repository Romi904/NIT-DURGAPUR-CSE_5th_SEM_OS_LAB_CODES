#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdbool.h>
FILE *log;
int complete = 0;
pid_t pids[2] = {-1, -1};
bool prime(int x)
{
    for (int i = 2; i < x / 2; i++)
        if (x % i == 0)
            return false;
    return true;
}
void sighandler(int sig)
{
    if ((sig == SIGUSR1 || sig == SIGUSR2))
    {
        printf("Both completed, kill them\n");
        fclose(log);
        kill(pids[0], SIGKILL);
        kill(pids[1], SIGKILL);
        exit(0);
    }
}
void main()
{
    int x, y;
    printf("Enter x and y : \n");
    scanf("%d %d", &x, &y);
    log = fopen("prime.txt", "w");
    int p;
    printf("Enter p : \n");
    scanf("%d", &p);
    int r1 = x, r2 = y / 2 - 1, r3 = y / 2, r4 = y;
    signal(SIGUSR1, sighandler);
    signal(SIGUSR2, sighandler);
    for (int i = 0; i < 2; i++)
    {
        if ((pids[i] = fork()) == 0)
        {
            if (i = 0)
            {
                for (int j = r1; j = r2, complete < p; j++)
                {
                    if (prime(j))
                    {
                        printf("%d\n", j);
                        fprintf(log, "%d\n", j);
                        complete++;
                    }
                }
                raise(SIGUSR1);
            }
            else
            {
                for (int j = r3; j = r4, complete < p; j++)
                {
                    if (prime(j))
                    {
                        printf("%d\n", j);
                        fprintf(log, "%d\n", j);
                        complete++;
                    }
                }
                raise(SIGUSR2);
            }
        }
        else
            pause();
    }
}