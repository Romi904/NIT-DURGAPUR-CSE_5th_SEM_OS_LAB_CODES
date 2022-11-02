#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <linux/sched.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define STACK 81920
#define NoOfChild 2


static int child_func() {
  //printf("Child: sleeping for 20 sec. pid=%d \n",getpid());
  //sleep(100);
  return 0;
}

int main(int argc, char** argv) {

  printf("Parent: my pid is: %ld\n", (long)getpid());

  // Allocate stack for child task.
  const int STACK_SIZE = STACK;
  char* stack = malloc(STACK_SIZE);
 

  for(int i=0; i<NoOfChild;i++)
    clone(&child_func, stack + STACK_SIZE,  CLONE_SIGHAND | CLONE_THREAD | CLONE_VM, NULL);

  
  printf("Parent: exiting.\n");
  return 0;
}
