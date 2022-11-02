/*

For two separate processes to use a shared memory, they need to know the key.
We assume that the key is pre shared (hardcoded)

Writer creates shared memory with shmget.

Writer process writes 2 integers X and Y

Reader process reads them

*/


#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<errno.h>


#define SHM_KEY 0x1111


int main(int argc, char *argv[]) {
   int shmid;
   void *writer_process_shared_memory;
   int *X, *Y;


   shmid = shmget(SHM_KEY, 2*sizeof(int), 0666|IPC_CREAT);
   if (shmid == -1) {
      perror("Shared memory");
      return 1;
   }
   
   // Attach to the segment to get a pointer to it.
   writer_process_shared_memory = shmat(shmid, NULL, 0);
   if (writer_process_shared_memory == (void *) -1) {
      perror("Shared memory attach");
      return 1;
   }

   printf("Process1 Writer: Shared memory created and attached\n");
   
   printf("Process1 Writer: Writing X = %d and Y = %d\n", 5, 6);

   X = (int *)writer_process_shared_memory;
   Y = (int *)(writer_process_shared_memory + sizeof(int));
   *X = 5;
   *Y = 6;

   printf("Process1 Writer: Reading X = %d and Y = %d\n", *X, *Y);

   for(;;){}

      if (shmdt(writer_process_shared_memory) == -1) {
         perror("shmdt");
         return 1;
      }
   printf("Process1 Writer: Detached shared memory. Exiting..\n");



   return 0;
}
