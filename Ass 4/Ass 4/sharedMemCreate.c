#include<stdio.h>
#include<sys/ipc.h>    //  Required for shared memory
#include<sys/shm.h>    //  Required for shared memory
#include<sys/types.h>
#include<errno.h>

#define SHM_KEY 0x1111  // global id to the shared resource

int main(int argc, char *argv[]) {
   int   shmid;    // local_id to the shared resource

   void *shared_memory;
   int *X;
   
   // to create the shared memory (if not available) and get the local_id 
   //  through which it can be reffered
   shmid = shmget(SHM_KEY, 2*sizeof(int), 0666|IPC_CREAT);
   
   // Attach to the segment to the current process 
   // use a local pointer to point to it
   shared_memory = shmat(shmid, NULL, 0);
   printf("Process1 Writer: Shared memory created and attached\n");
   
   // cast the shared memory as integer array
   X=(int*) shared_memory;   
   X[0] = 5;  X[1] = 6;   // accessing the shared memory 
   printf("Process1 Writer: Updated value of shared memory X[0] = %d and X[1] = %d\n", X[0], X[1]);

   // Detach the shared segment from the current process
   shmdt(shared_memory);
   printf("Process1 Writer: Detached shared memory. Exiting..\n");

   return 0;
}
