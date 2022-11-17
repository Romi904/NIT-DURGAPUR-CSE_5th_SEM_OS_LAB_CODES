//Romijul Laskar
//20CS8065

#include <math.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#define SEM_NAME "sem" // semaphore name
sem_t *sem;
int *count;
int m, n, diff;
int isPrime(int n)
{ // return if prime
    int sq, i;
    if (n <= 1)
        return 0;
    sq = sqrt(n);
    for (i = 2; i <= sq; i++)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}
void search(int r)
{ // search range calculated from diff & r
    int i;
    int s = r * diff + 1;
    int e = (r + 1) * diff;
    if (e > n)
        e = n;
    FILE *file;
    for (i = s; i <= e; i++)
    {
        if (isPrime(i))
        {
            sem_wait(sem);       // P
            *count = *count + 1; // critical section
            sem_post(sem);       // V
        }
    }
}
int main(void)
{
    int i, shmid;
    FILE *file;
    file = fopen("count.txt", "w");
    fprintf(file, "0");
    fclose(file);
    m = 10; // 10 childs
    printf("Enter limit: ");
    scanf(" %d", &n);
    diff = n / m + (n % m ? 0 : 1);                        // size of single divided unit
    sem = sem_open(SEM_NAME, O_CREAT, 0660, 1);            // initialising semaphore
    shmid = shmget(0x1234, sizeof(int), 0666 | IPC_CREAT); // creating shared memory
    count = (int *)shmat(shmid, NULL, 0);                  // getting shared memory address
    for (i = 0; i < m; i++)
    { // creating m childs and searching
        if (!fork())
        {
            search(i);
            return 0;
        }
    }
    while (wait(0) > 0)
        ; // waiting for all childs to die
    printf("Number of primes in range 1 to %d is: %d\n", n, *count);
    sem_unlink(SEM_NAME);       // unlinking semaphore
    shmdt(count);               // detaching shared memory
    shmctl(shmid, IPC_RMID, 0); // destroying shared memory
    return 0;
}