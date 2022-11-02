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
    FILE *log = fopen("prime(q2).txt", "w");
    int div = (y - x) / n;
    for (int i = 0; i < n; i++)
    {
        int stat;
        if (fork() == 0)
        {
            for (int j = x + (i * div); j < x + (div * (i + 1)); j++)
                if (prime(j))
                    fprintf(log, "%d\n", j);
            exit(0);
        }
        else
            wait(NULL);
    }
    fclose(log);
    printf("Done\n");
}