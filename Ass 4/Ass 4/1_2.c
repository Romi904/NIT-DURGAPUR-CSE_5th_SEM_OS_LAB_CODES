#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>
#include<time.h>
#include<pthread.h>
#include<assert.h>
// 10k process
int k=0;
void *th_code(void *a){
    printf("Thread %d\n",k+1);
    k++;
}

int main(){
    clock_t t;
    t = clock();
    pthread_t ths[10000];
    int th_arg[10000];
    int res_code;
    for(int i=0;i<10000;i++){
        th_arg[i]=rand()%(100-1+1)+1;
    }
    for(int i=0;i<10000;i++){
       pthread_create(&ths[i],NULL,th_code,&th_arg);
    }
    printf("Created 10k childs");
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    printf("Time taken %f seconds to execute \n", time_taken);
}
// 0.001026s