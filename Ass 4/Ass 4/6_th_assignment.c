#include<stdio.h>
#include<sys/shm.h>
#include<errno.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<time.h>
// #include<sys/ipc.h>

#define SHM_KEY 0x1112

int main(int argc,char** argv){

    int shmid=shmget(SHM_KEY,10*sizeof(int),0666|IPC_CREAT);
    void* temp;
    temp=shmat(shmid,NULL,0);
    int* arr=(int*)temp;
    srand(time(NULL));
    printf("The original array is: \n");
    for(int i=0;i<10;i++){
        if(i%2!=0) arr[i]=0;
        else arr[i]=(rand()%100+1);
        printf("%d ",arr[i]);
    }
    printf("\n");

    shmdt(temp);

    pid_t x=fork();
    if(!x){
        void* temp;
        temp=shmat(shmid,NULL,0);
        int* v=(int*)temp;
        int sum=0;
        for(int i=0;i<10;i+=2){
            sum+=v[i];
            if(i%2==0){
                v[i+1]=(v[i]?(v[i]+2):0);
            }
        }
        printf("\nThe Actual Array is : ");
        for (int  i = 0; i < 10; i++)
        {
            printf(" %d",v[i]);
        }
        printf("\n");
        
        shmdt(temp);
        int avg=(sum/5);
        printf("The sum of odd-indexes : %d\n",sum);
        printf("The average of odd-indexes : %d\n",avg);
    }else{
        while(wait(NULL)>0);
        void* temp;
        temp=shmat(shmid,NULL,0);
        int* v=(int*)temp;
        int sum=0;
        for(int i=1;i<10;i+=2){
            sum+=v[i];
        }
        int avg=(sum/5);
        printf("The sum of even-indexes : %d\n",sum);
        printf("The average of even-indexes : %d\n",avg);
        shmdt(temp);
    }    
    return 0;
}