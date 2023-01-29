// By Alexander Peltier

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <iostream>

#define FALSE 0
#define TRUE 1

typedef int bfr;
typedef int ctr;
#define BUFFER_SIZE 3

// mutex lock
pthread_mutex_t mutex;
pthread_mutex_t lmutex;

// semaphores
sem_t full, empty;

// buffer
bfr buffer[BUFFER_SIZE];

// thread id
pthread_t pid;
pthread_t cid;

pthread_attr_t attr; // attributes

// counter for buffer
ctr counter;

// function declarations
void* producer(void *arg);
void* consumer(void *arg);

void init() {

    // mutex lock
    pthread_mutex_init(&mutex, NULL);

    //loop lock
    pthread_mutex_init(&lmutex, NULL);

    // create full semaphore and initalize it to FALSE
    sem_init(&full, 0, 0);

    // create empty semaphore and initialize it to TRUE
    sem_init(&empty, 0, 1);

    // pthread attributes
    pthread_attr_init(&attr);

    counter = 0;

}

void* producer(void *arg) {


    while(TRUE) {
        // create some item, give it a value
        bfr item = 1;
        // wait for empty sempahore to be true
        sem_wait(&empty);
        // lock the mutex
        pthread_mutex_lock(&mutex);
        // produce and throw into stack
        while(counter < BUFFER_SIZE) {
            sleep(1);
            std::cout << "Producer put item in stack at slot " << counter << std::endl;
            buffer[counter] = item;
            counter++;
        }
        // were done producing, unlock mutex
        pthread_mutex_unlock(&mutex);
        // flip full semaphore
        sem_post(&full);


    }

    return NULL;

}

void* consumer(void *arg) {
    // null item
    bfr item;

    while(TRUE){
        // wait for full semaphore to be true
        sem_wait(&full);
        // lock mutex
        pthread_mutex_lock(&mutex);
        // consume stack
        while(counter > 0) {
            sleep(1);
            std::cout << "Consumer consumed item in stack at slot " << counter-1 << std::endl;
            buffer[(counter-1)] = item;
            counter--;
        }
        // we've consumed all the items, unlock mutex
        pthread_mutex_unlock(&mutex);   
        // say that were empty
        sem_post(&empty);


    }

    return NULL;

}

int main() {

// call init function
init();

//create pthreads
pthread_create(&pid, &attr, producer, NULL);
std::cout << "Created producer thread with ID " << pid << std::endl;
pthread_create(&cid, &attr, consumer, NULL);
std::cout << "Created consumer thread with ID " << cid << std::endl;

/*
we never catch the exit of the pthreads because we never close them
so, this is kind of like a while(true)
*/ 
pthread_join(pid, NULL);
pthread_join(cid, NULL);
 
return 0;
}