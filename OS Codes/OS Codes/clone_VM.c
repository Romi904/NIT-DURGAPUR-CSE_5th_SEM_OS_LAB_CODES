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

int do_something(){
        printf("Child pid : %d\n", getpid());
        for(;;);
        return 0;
}
int main() {
        void *stack = malloc(STACK);    // Stack for new process
        
        if( clone( &do_something, (char *)stack + STACK, CLONE_VM, 0) < 0 ){
                perror("Clone Failed");
                exit(0);
        }
        printf("Parent pid : %d\n", getpid());
        sleep(3);       // Add sleep so we can see both processes output
        free(stack);
        for(;;);
        return 0;
}