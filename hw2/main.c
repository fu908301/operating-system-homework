#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#define N 5
#define LEFT (i+N-1)%N
#define RIGHT (i+1)%N
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define TRUE 1
void* philosopher(void *number);
void take_forks(int i);
void put_forks(int i);
void test(int i);
void think(void);
void eat(void);
void close_thread();
void small_sleep(int a);
typedef int semaphore;
int state[N]={THINKING};
pthread_mutex_t mutex;
semaphore situation[N]={0};
pthread_t th[5];
void small_sleep(int a)
{
	time_t t1,t2;
	t1=time(NULL);
	t2=time(NULL);
	while((t2-t1)*10000<a)
	t2=time(NULL);	
}	
void* philosopher(void *number)
{
  pthread_detach(pthread_self());
	int i=(int)number;
	while(TRUE)
	{
		think();
		take_forks(i);
		eat();
		put_forks(i);
	}
}
void take_forks(int i)
{
	pthread_mutex_lock(&mutex);	
	state[i]=HUNGRY;
	test(i);
	pthread_mutex_unlock(&mutex);
	while(1)
  {
    if(situation[i]==1)
   {
		 situation[i]=0;
     break;
   }	  
  }        

} 
void put_forks(int i)
{
	pthread_mutex_lock(&mutex);
	state[i]=THINKING;
	test(LEFT);
	test(RIGHT);
	pthread_mutex_unlock(&mutex);
}
void test(int i)
{
	if(state[i]==HUNGRY && state[LEFT]!=EATING && state[RIGHT]!=EATING)
	{
		state[i]=EATING;
		situation[i]=1;
	}
}
void think(void)
{
	
}
void eat(void)
{
	
}
void close_thread()
{
        int i;
        printf("Thread is closing...\n");
        for(i=0;i<5;i++)
        {
                printf("Thread %d is finished\n",i);
                pthread_cancel(th[i]);
        }
	exit(0);
}
int main()
{
        int i;
        signal(SIGINT,close_thread);
        for(i=0;i<5;i++)
        {
               printf("Creating %d thread\n",i);
               pthread_create(&th[i],NULL,philosopher,(void*)i);
        }

        while(1)
        {
		            pthread_mutex_lock(&mutex);
                for(i=0;i<5;i++)
                {
                        if(state[i]==THINKING)
                        printf("O ");
                        else if(state[i]==HUNGRY)
                        printf("X ");
                        else if(state[i]==EATING)
                        printf("E ");
                }              
		pthread_mutex_unlock(&mutex);
		printf("\n");
                sleep(1);
        }
        return 0;
}

