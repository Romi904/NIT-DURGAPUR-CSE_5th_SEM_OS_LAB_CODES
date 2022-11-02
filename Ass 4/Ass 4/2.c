#include <linux/sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>
#include<time.h>
#define _GNU_SOURCE

#define size 8192

int *arr;
int low,hi;
int isPrime(int  n);

 int *prime(){
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
    int n=100;
    printf("Enter n: ");
    scanf("%d",&n);
    int m=7;
    printf("Enter no of process : ");
    scanf("%d",&m);
    int grp = (n / m) + ((n % m) ? 1 : 0);
    printf("\nParent process, ID = %d\n", getpid());

    char *stack=malloc(n);

    for (int i = 0; i < m; i++){
        printf("Process %d\n",i+1);
         low=i*grp+1;
         hi=low+grp;

        if(hi>n){
          hi=n;
        }
        if(clone(&prime,stack+n,CLONE_VM | CLONE_SIGHAND | CLONE_THREAD,NULL)<0){
         i--;
         exit(EXIT_FAILURE);
        }
        sleep(1);
        printf("\n")  ;
    }
}
