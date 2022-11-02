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
int *arr;
int low,hi;
int isPrime(int  n);

void *prime(){
   for(int i=low;i<hi;i++){
    if(isPrime(i)){
       printf("%d ",i);
    }
   }
   return 0;
}

int isPrime(int n){
    if(n<2)
      return 0;
    for(int i=2; i*i<=n; i++){
        if(n%i==0)
           return 0;
    }
    return 1;
}



int main(){
    int n;
    printf("Enter n: ");
    scanf("%d",&n);
    int m;
    printf("Enter no of thread : ");
    scanf("%d",&m);
    int grp = (n / m) + ((n % m) ? 1 : 0);
    printf("\nParent process, ID = %d\n", getpid());
    
    pthread_t ths[m];
    int th_arg[m];
    int res_code;
    for(int i=0;i<m;i++){
        th_arg[i]=rand()%(100-1+1)+1;
    }

    for (int i = 0; i < m; i++){
        printf("Thread %d\n",i+1);
         low=i*grp+1;
         hi=low+grp;
        //int j=low;
        if(hi>n){
          hi=n;
        }
        pthread_create(&ths[i],NULL,prime,&th_arg[i]);
        sleep(1);
        printf("\n")  ;
    }
    for(int i=0;i<m;i++){
        res_code=pthread_join(ths[i],NULL);
    }

}