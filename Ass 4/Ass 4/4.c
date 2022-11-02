#include<pthread.h>
#include<assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>
#include<time.h>

#define size 8192
int ret1,k=0;
void *func(void *a){
  printf("thread %d processing done\n",k);
  
        if(k%2==0)       
          ret1  = rand()%(10-1+1)+1;
          pthread_exit(&ret1);
}

int main(){
    int n=6;
    pthread_t ths[n];
    int th_arg[n];
    int *ptr[n];
    int res_code;
    srand(time(0));
    for(int i=0;i<n;i++){
        th_arg[i]=rand()%(100-1+1)+1;
    }

    for (int i = 0; i <n; i++){
       // printf("Thread %d\n",i+1);
        //pthread_attr_t x;
        pthread_create(&ths[i],NULL,func,&th_arg[i]);
        
        sleep(1);
        k++;
        //printf("\n")  ;
    }
    for(int i=0;i<n;i++){
        if((i)%2==0)
          pthread_join(ths[i],(void**)&ptr[i]);
    }
    
    for(int i=0;i<n;i++){
       if(i%2==0){
        printf("Thread %d exited with returned code %d\n",i,*ptr[i]);
       }
    }

}