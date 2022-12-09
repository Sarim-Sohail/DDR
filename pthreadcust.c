#include <pthread.h> // pthread
#include <stdio.h>   // prinftf
#include <stdlib.h>  // random
#include <unistd.h>  // sleep
// you might need more header files
#include<semaphore.h>

#define NUM_CUSTOMERS 5
#define NUM_WORKERS 2
#define SIZE 100000
#define toolong 3
sem_t lock,lock1,lock2;
static int q[SIZE];
int cnt=0;
static int Rear = - 1;
static int Front = - 1;
static void *worker_actions(void *employee_id);
static void *customer_actions(void *personal_id);
static void enqueue(int i)
{  // sem_wait(&lock1);
    if (Rear == SIZE - 1)
        {
            return;
        }
    else
    {
        if (Front == - 1){
		   Front = 0;
    }
        Rear = Rear + 1;
        q[Rear] = i;
        cnt++;
    }
    //sem_post(&lock1);
} 
 
static int dequeue()
{   //sem_wait(&lock2);
    if (Front == - 1 || Front > Rear)
    {
        return -1;
    }
    else
    {
    	
        Front = Front + 1;
        cnt--;
        return 0;
    }
    //sem_post(&lock2);
} 
 

int main(int argc, char **argv) {

    int personal_ids[NUM_CUSTOMERS], employee_ids[NUM_WORKERS];

    pthread_t customers[NUM_CUSTOMERS], workers[NUM_WORKERS];
	sem_init(&lock,0,0);
	sem_init(&lock1,0,0);
	sem_init(&lock2,0,0);
    // create treads
    for (int i = 0; i < NUM_WORKERS; i++) {
        employee_ids[i] = i;
        pthread_create(&workers[i], NULL, worker_actions, (void *)&employee_ids[i]);
    }
    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        personal_ids[i] = i;
        pthread_create(&customers[i], NULL, customer_actions, (void *)&personal_ids[i]);
    }

    // join threads
    for (int i = 0; i < NUM_WORKERS; i++) {
        pthread_join(workers[i], NULL);
    }
    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        pthread_join(customers[i], NULL);
    }

    return 0;
}

static void *worker_actions(void *employee_id) {
    // get the id of this employee
    int id = *(int *)employee_id;
	int val;
    while (1) {
        sem_getvalue(&lock,&val);
    	if(cnt>0){
    		int temp=q[Front];
    		
    		
			
			int time=rand()%10;
            printf("Person %d wakes worker %d\n",temp,id);
			printf("Worker %d is making icecream for person %d .Taking %d seconds\n",id,temp,time);
			dequeue();
			sleep(time);
		
			
			sem_post(&lock);
			printf("Person %d recieved icecream\n",temp);
		}
		else{
		    printf("No customers Worker %d sleeps\n",id);
			int time=rand()%10;
			sleep(time);
			
		}
    }
}

static void *customer_actions(void *personal_id) {
    // get the id of this customer
    int id = *(int *)personal_id;
    int val;
    while(1){
    	sem_getvalue(&lock,&val);
    	if(cnt<toolong){
    	  //  sem_wait(&lock1);
    		enqueue(id);
    		//sem_post(&lock1);
    		
			printf("Customer %d is in queue %d waiting\n",id,cnt-1);
			
			sem_wait(&lock);
    		
    		
		}
		else{
			int time=rand()%10;
			
			printf("Customer %d is relaxing on the beach for %d seconds\n",id,time);
			
			sleep(time);
			
		}
	}
	
}
