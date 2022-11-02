#include<stdio.h>
#include<sys/ipc.h>   //  Required for shared memory
#include<sys/shm.h>   //  Required for shared memory
#include<sys/types.h>
#include<errno.h>

#define SHM_KEY 0x1234

int main(int argc, char *argv[]) {
   int shmid;
   void *sh_mem;
   int *X;

   // to create the shared memory (if not available) and get the local_id 
   //  through which it can be reffered
   shmid = shmget(SHM_KEY, 2*sizeof(int), 0666|IPC_CREAT);
      
   // Attach to the segment to the current process 
   // use a local pointer to point to it
   sh_mem = shmat(shmid, NULL, 0);
   printf("Process2 Reader: Shared memory  attached\n");
   
   // cast the shared memory as integer array
   X = (int *)sh_mem;
   printf("Process2 Reader: Reading X[0] = %d and X[1] = %d\n", X[0], X[1]);

   //for(;;);
   // Detach the shared segment from the current process
   shmdt(sh_mem);
 
   // Destroy the shared memory resource (make sure that no other proess is using it)
   shmctl(shmid, IPC_RMID, 0);
   printf("Process2 Reader: Detached shared, destroyed shared  memory. Exiting..\n");
   return 0;
}
