#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <linux/sched.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define STACK 8192


static int child_func() {
  printf("Child: sleeping for 20 sec. pid=%d \n",getpid());
  sleep(100);
  for(;;){}
  return 0;
}

int main(int argc, char** argv) {

  
   //system("top > y.txt");

  printf("Parent: my pid is: %ld\n", (long)getpid());

  // Allocate stack for child task.
  const int STACK_SIZE = 65536;
  char* stack = malloc(STACK_SIZE);
  

  // When called with the command-line argument "vm", set the CLONE_VM flag on.
  unsigned long flags = 0;
  // 
  //flags |= CLONE_VM;
  //flags |= CLONE_THREAD;
  
  
  if (clone(&child_func, stack + STACK_SIZE,  CLONE_SIGHAND | CLONE_THREAD | CLONE_VM, NULL) == -1) {
    perror("clone");
    exit(1);
  }

  printf("Parent: Waiting for 25 sec..\n");
  for(;;){}

  printf("Parent: exiting.\n");
  return 0;
}
