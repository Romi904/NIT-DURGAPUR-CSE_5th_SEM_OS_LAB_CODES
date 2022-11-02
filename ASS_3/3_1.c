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
    printf("Enter the value to search :");
    int x;
    scanf("%d", &x);
    for (int i = 0; i < n; i++)
    {
        int stat;
        if (fork() == 0)
        {
            int div = size / n;
            for (int j = i * div; j < div * (i + 1); j++)
            {
                if (arr[j] == x)
                {
                    printf("Child %d found the value \n", i + 1);
                    exit(1);
                }
            }
            exit(0);
        }
        else
        {
            wait(&stat);
            if (WEXITSTATUS(stat) == 1)
            {
                printf("Element found \n");
                return;
            }
        }
    }
    printf("Element not found \n");
}