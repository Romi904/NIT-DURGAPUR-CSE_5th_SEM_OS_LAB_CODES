// Romijul Laskar
// 20CS8065
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>



sem_t *sem; // semahpore pointer
int diff;
int n, m = 10; // threads=>m=10
int count = 0;

int isPrime(int n)
{ // return true id prime
    int sq, i;
    if (n <= 1)
        return 0;
    sq = (int)sqrt((double)n);
    for (i = 2; i <= sq; i++)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

void *search(void *code)
{ // search range got from diiff & r
    int i;
    int r = *(int *)code;
    int s = r * diff + 1;
    int e = (r + 1) * diff;
    if (e > n)
        e = n;
    for (i = s; i <= e; i++)
    {
        if (isPrime(i))
        {
            sem_wait(sem);
            count++; // critical section
            sem_post(sem);
        }
    }
    return NULL;
}


int main(void)
{
    int i;
    int *args;
    pthread_t *threads;
    sem = malloc(sizeof(sem_t)); // allocating space for semaphore(for unnamed semaphore)
    m = 10;                      // 10 threads
    args = (int *)malloc(sizeof(int) * m);
    threads = (pthread_t *)malloc(sizeof(pthread_t) * m);
    printf("Enter limit: ");
    scanf(" %d", &n);
    diff = n / m + ((n % m) ? 1 : 0); // size of each divisions
    sem_init(sem, 0, 1);            // initialising semaphore
    for (i = 0; i < m; i++)
    { // creating 10 threads
        args[i] = i;
        pthread_create(&threads[i], NULL, search, &args[i]);
    }
    for (i = 0; i < m; i++)
    { // waiting for threads to exit
        pthread_join(threads[i], NULL);
    }
    printf("Number of primes in range 1 to %d is: %d\n", n, count);
    free(args); // deallocating space
    free(threads);
    sem_destroy(sem); // destroying semaphore
    return 0;
}
