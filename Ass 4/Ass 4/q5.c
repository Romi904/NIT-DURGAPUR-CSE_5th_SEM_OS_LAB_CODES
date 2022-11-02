#include<stdio.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<errno.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

#define SHM_KEY 0x1111

int main(int argc,char** argv){

    int shmid=shmget(SHM_KEY,sizeof(int),0666|IPC_CREAT);

    int m;
    printf("Enter number of processes : ");
    scanf("%d",&m);
    pid_t pid[m];
    void* mem=shmat(shmid,NULL,0);
    *((int*)mem)=1;
    shmdt(mem);
    for(int i=0;i<m;i++){
        pid[i]=fork();
        if(!pid[i]){
            void* memloc=shmat(shmid,NULL,0);
            (*((int*)memloc))++;
            shmdt(memloc);
            exit(0);
        }
    }
    while(wait(NULL)>0);
    mem=shmat(shmid,NULL,0);
    printf("%d\n",*((int*)mem));
    shmdt(mem);

    return 0;
}
