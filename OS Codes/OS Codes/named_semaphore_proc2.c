// Example for synchronized printing with semaphores.
// The process 2 will print only after process 1 has printed.
// Then the process 1 will print, after process 2 has printed.
// (Interleaved printing synchronized using binary semaphores) 
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
 #include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>

#define SEMAPHORE_NAME1 "/sem-mutex1"
#define SEMAPHORE_NAME2 "/sem-mutex2"

int main (int argc, char **argv)
{
    sem_t *binary_sem1;
    sem_t *binary_sem2;
    //  binary_sem1 with an initial value 1
    binary_sem1 = sem_open (SEMAPHORE_NAME1, O_CREAT, 0660, 1);
    //  binary_sem2 with an initial value 0
    binary_sem2 = sem_open (SEMAPHORE_NAME2, O_CREAT, 0660, 0);
    for (int i = 0; i < 10; i++)
    {
        // semaphore wait
        sem_wait (binary_sem1);
        printf("\nProcess 2 printing.. %d\n", i);
        // semaphore signal
        sem_post (binary_sem1);
        sleep(1);
    }
    // Remove semaphores
    sem_unlink (SEMAPHORE_NAME1);
    sem_unlink (SEMAPHORE_NAME2);
    return 0;
}
