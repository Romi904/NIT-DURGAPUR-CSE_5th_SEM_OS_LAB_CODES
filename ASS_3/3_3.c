#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define size 1000
void main()
{
    int arr[size];
    for (int i = 0; i < size; i++)
        arr[i] = rand() % 1000;
    printf("Enter the number of children : ");
    int n;
    scanf("%d", &n);
    pid_t *pids = (pid_t *)malloc(n * sizeof(pid_t));
    printf("Enter the value to search :");
    int x;
    scanf("%d", &x);
    for (int i = 0; i < n; i++)
    {
        int stat;
        if (pids[i] = fork() == 0)
        {
            int div = size / n;
            for (int j = i * div; j < div * (i + 1); j++)
                if (arr[j] == x)
                    exit(1);
            exit(0);
        }
    }
    for (int i = 0; i < n; i++)
    {
        int stat;
        pid_t child_pid = waitpid(pids[i], &stat, 0);
        if (WEXITSTATUS(stat) == 1)
        {
            printf("Child %d with pid = %d found the value \n", i + 1,
                   child_pid);
            return;
        }
    }
    printf("Element not found \n");
}