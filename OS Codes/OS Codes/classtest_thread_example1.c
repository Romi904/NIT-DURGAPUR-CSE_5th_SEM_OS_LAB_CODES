// To run use 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>

int array[10]={1,2,3,4,5,6,7,8,9,10};
int sum=0,i;

void *thread_code(void *a){
  int index = *((int *)a);
  int s=0;
 /* for(i=index;i<5;i++)
  	s+=array[i];   
  sum+=s;*/
  for(;;){}
}

int main(void) {
  pthread_t threads[100];
  int thread_args[20]={0,5,1,2,3,4,5,6,7,8,9,8,9,9,7,6,5,4,3,2};
  int i;
  int result_code;

  for (i = 0; i < 20; i++)
    {
       pthread_create(&threads[i], NULL, thread_code, &thread_args[i]); // internally it calls clone(....VM|THREAD|SIGHAND...)
       printf("\n\t %d",threads[i]);
    }
  
  for (i = 0; i < 20; i++) {
    result_code = pthread_join(threads[i], NULL);
    printf("In main Thread....child thread %d has ended\n",threads[i]);
  }

  printf("\n\t Total Sum of array elements %d ",sum);
  return 0;
}