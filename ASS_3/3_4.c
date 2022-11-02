#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
bool prime(int x)
{
    if (x <= 1)
        return false;
    for (int i = 2; i * i < x; i++)
    {
        if (x % i == 0)
            return false;
    }
    return true;
}
void main()
{
    int x, y, n;
    printf("Enter x and y : \n");
    scanf("%d %d", &x, &y);
    printf("Enter the number of children : ");
    scanf("%d", &n);
    pid_t *pids = (pid_t *)malloc(n * sizeof(pid_t));
    FILE *log = fopen("prime(q4).txt", "w");
    int div = (y - x) / n;
    for (int i = 0; i < n; i++)
    {
        if (pids[i] = fork() == 0)
        {
            for (int j = x + (i * div); j < x + (div * (i + 1)); j++)
                if (prime(j))
                    fprintf(log, "%d\t", j);
            exit(0);
        }
    }
    for (int i = 0; i < n; i++)
    {
        int stat;
        pid_t child_pid = waitpid(pids[i], &stat, 0);
        if (WIFEXITED(stat))
            printf("Child %d completed \n", i + 1);
    }
    fclose(log);
}