#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <iostream>
#define N 5
#define LEFT (i+N-1)%N
#define RIGHT (i+1)%N
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define TRUE 1
using namespace std;
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
pthread_cond_t cond[5];
semaphore situation[N]={0};
pthread_t th[5];
void* philosopher(void *number);
void close_thread();
 
class monitor{
  public:
	void take_forks(int i)
	{
		pthread_mutex_lock(&mutex);	
		state[i]=HUNGRY;  
		test(i);
  		if(state[i]!=EATING)
  		{
     			pthread_cond_wait(&cond[i],&mutex);
  		}
  		pthread_mutex_unlock(&mutex);
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
			pthread_cond_signal(&cond[i]);
		}
	}	
	void think(void)
	{
		
	}
	void eat(void)
	{
		
	} 
};
monitor m;
void* philosopher(void *number)	
{	
 	pthread_detach(pthread_self());
	int i=(int)number;
	while(TRUE)
	{
		m.think();
		m.take_forks(i);
		m.eat();
		m.put_forks(i);
	}
}
void close_thread(int signal)
{
     	int i;
     	cout<<"Thread is closing..."<<endl;
       	for(i=0;i<5;i++)
       	{
       	        cout<<"Thread "<<i<<" is finished"<<endl;
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
              pthread_cond_init(&cond[i],NULL);
              cout<<"Creating "<<i<<"thread"<<endl;
              pthread_create(&th[i],NULL,philosopher,(void*)i);
        }

        while(1)
        {
                pthread_mutex_lock(&mutex);
                for(i=0;i<5;i++)
                {
                        if(state[i]==THINKING)
                        cout<<"O ";
                        else if(state[i]==HUNGRY)
                        cout<<"X ";
                        else if(state[i]==EATING)
                        cout<<"E ";                  
                }
                pthread_mutex_unlock(&mutex);
		            cout<<endl;		
                sleep(1);
        }
        return 0;
}

