//ROMIJUL LASKAR
//20CS8065

#include <stdio.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#define SEMAPHORE1 "S1" // semaphores names
#define SEMAPHORE2 "S2"
#define SEMAPHORE3 "S3"
sem_t *pgate, *cgate; // semaphore for letting only one producer and one consumer inside
sem_t *nfill;         // semaphore for letting consumer take a filled resource
typedef struct queue
{ // a linked list
    struct queue *next;
    int data; // resource
} queue;
queue *front = NULL; // linked list as a queue
queue *rear = NULL;
void enque(int val)
{ // add element to queue
    queue *temp;
    temp = (queue *)malloc(sizeof(queue));
    temp->data = val;
    temp->next = NULL;
    if (rear == NULL)
    { // if NULL then initialise queue
        front = temp;
        rear = temp;
        return;
    }
    rear->next = temp;
    rear = temp;
}
int deque()
{ // delete element from queue
    int val;
    queue *temp = front;
    if (front == NULL)
        return -1;
    val = front->data;
    if (front == rear)
        rear = NULL; // if only single element present
    front = front->next;
    free(temp);
    return val;
}
void *Producer(void *arg)
{ // producer func
    int val, count = 0;
    while (1)
    {
        val = rand() % 100; // get randon value
        sem_wait(pgate);    // only one producer at a time
        enque(val);         // add resource
        printf("Producer %d produced item %d\n", *(int *)arg, val);
        sem_post(nfill); // let consumer know
        sem_post(pgate); // let producers know
        if (count++ == 5)
        {
            srand(time(0));
            sleep(1); // sleep for readability
            count = 0;
        }
    }
}
void *Consumer(void *arg)
{ // consumer func
    int val, count = 0;
    while (1)
    {
        sem_wait(cgate); // only one consumer at a time
        sem_wait(nfill); // wait until producer produces at least one resource
        val = deque();   // consume resource
        printf("Consumer %d consumed item %d\n", *(int *)arg, val);
        sem_post(cgate); // let consumers know
        if (count++ == 5)
        {
            sleep(1); // sleep for readability
            count = 0;
            printf("-----------------------------------------------\n\n\n");
        }
    }
}
void destroy(int x)
{
    // destroying semaphores
    sem_unlink(SEMAPHORE1);
    sem_unlink(SEMAPHORE2);
    sem_unlink(SEMAPHORE3);
    // killing process
    signal(SIGINT, SIG_DFL);
    kill(getpid(), SIGINT);
}
int main(void)
{
    signal(SIGINT, destroy);  // SIGINT handler
    int i, np = 5, nc = 5, m; // np->producers, nc->consumers
    pthread_t threads;
    printf("enter No. of producers and no. of consumers: ");
    scanf(" %d %d", &np, &nc);
    srand(time(0));
    int parg[np], carg[nc];
    // initialising semaphores
    pgate = sem_open(SEMAPHORE1, O_CREAT, 0, 1);
    cgate = sem_open(SEMAPHORE2, O_CREAT, 0, 1);
    nfill = sem_open(SEMAPHORE3, O_CREAT, 0, 0);
    m = np > nc ? np : nc;
    for (i = 0; i < m; i++)
    { // creating given number of producers and consumers
        if (i < nc)
        {
            carg[i] = i;
            pthread_create(&threads, NULL, Consumer, carg + i);
        }
        if (i < np)
        {
            parg[i] = i;
            pthread_create(&threads, NULL, Producer, parg + i);
        }
    }
    while (1)
        ; // waiting for signal SIGINT by user
    return 0;
}