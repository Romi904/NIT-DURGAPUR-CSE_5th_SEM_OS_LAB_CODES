#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>
#include<time.h>
// 10k process
int main(){
    clock_t t;
    t = clock();
    pid_t x;
    for(int i=0;i<10000;i++){
        if((x=fork())==0){
        printf("Child[%d] pid %d ppid %d \n",i+1,getpid(),getppid());
        exit(0);
        }
    }
    printf("Created 10k childs");
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    printf("time taken %f seconds to execute \n", time_taken);
}
//Time Taken 0.001248s