/*  Implementation of Reader Writer Problem with 5 Reader and 2 Writer. There is a shared variable X with the initial value 5, with 2 semaphore and 
both the semaphores are initialized to 1.  
Writer Process 1 increments the value of X by 5 and Writer Process 2 increments the value of X by 10. 
The order in which the processes are trying to access the shared variable is as follows: R1 R2 W1 R3 R4 W2 W1 R5 W2 R1.

*/



#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex,writeblock;
int data = 5,rcount = 0;    // shared variable data intialized with 5

void *reader(void *arg)  
{
  int f;
  f = ((int)arg);
//  printf("%d", f);

  sem_wait(&mutex);    // semaphore wait -> value decremented
  rcount = rcount + 1;
  if(rcount==1)
   sem_wait(&writeblock);   
  sem_post(&mutex);    // semaphprore signal -> value incremented
  printf("Data read by the reader%d is %d\n",f,data);
  sleep(1);
  sem_wait(&mutex);
  rcount = rcount - 1;
  if(rcount==0)
   sem_post(&writeblock);
  sem_post(&mutex);
}

void *writer(void *arg)
{
  int f;
  f = ((int) arg);
  sem_wait(&writeblock);
  if(f == 0){        // for writer1, shared varable incremented with 5
  	data += 5;
  }
  else if(f == 1){   // for writer2, shared variable incremented with 10
  	data += 10;
  } 
  printf("Data writen by the writer%d is %d\n",f,data);
  sleep(1);
  sem_post(&writeblock);
}

int main()
{
  int i; 
  pthread_t rtid[5],wtid[2];
  sem_init(&mutex,0,1);   // initialization of semaphore variable mutex
  sem_init(&writeblock,0,1);  // initialization of writeblock variable
	
//	to create the threads
    pthread_create(&rtid[0],NULL,reader,(void *)0);
    pthread_create(&rtid[1],NULL,reader,(void *)1);
    pthread_create(&wtid[0],NULL,writer,(void *)0);

    pthread_create(&rtid[2],NULL,reader,(void *)2);
    pthread_create(&rtid[3],NULL,reader,(void *)3);
	pthread_create(&wtid[1],NULL,writer,(void *)1);
	pthread_create(&wtid[0],NULL,writer,(void *)0);
	
	pthread_create(&rtid[4],NULL,reader,(void *)4);
    pthread_create(&wtid[1],NULL,writer,(void *)1);
	pthread_create(&rtid[0],NULL,reader,(void *)0);


// to terminate the thread
    pthread_join(rtid[0],NULL);
    pthread_join(rtid[1],NULL);
    pthread_join(wtid[0],NULL);
    pthread_join(rtid[2],NULL);
    pthread_join(rtid[3],NULL);
    pthread_join(wtid[1],NULL);
    pthread_join(wtid[0],NULL);
    pthread_join(rtid[4],NULL);
    pthread_join(wtid[1],NULL);
    pthread_join(rtid[0],NULL);

  return 0;
}
