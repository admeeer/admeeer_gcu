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
#define BUFFER_SIZE 10

// mutex lock
pthread_mutex_t mutex;
pthread_mutex_t lmutex;

// semaphores
sem_t full, empty;

// buffer
bfr buffer[BUFFER_SIZE];

pthread_t tid; // thread id
pthread_attr_t attr; // attributes

ctr counter;

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

    pthread_attr_init(&attr);

    counter = 0;

}

void* producer(void *arg) {


    while(TRUE) {

        bfr item = 1;

        sem_wait(&empty);

        pthread_mutex_lock(&mutex);

        while(counter < BUFFER_SIZE) {
            sleep(1);
            std::cout << "Producer put item in stack at slot " << counter << std::endl;
            buffer[counter] = item;
            counter++;
        }

        pthread_mutex_unlock(&mutex);

        sem_post(&full);


    }

}

void* consumer(void *arg) {

    bfr item;

    while(TRUE){

        sem_wait(&full);

        pthread_mutex_lock(&mutex);

        while(counter > 0) {
            sleep(1);
            std::cout << "Consumer consumed item in stack at slot " << counter-1 << std::endl;
            buffer[(counter-1)] = item;
            counter--;
        }


    }

}

int main() {
std::cout << "Hello, World" << std::endl;
init();

pthread_create(&tid, &attr, producer, NULL);
std::cout << "Created producer thread with ID " << tid << std::endl;
pthread_create(&tid, &attr, consumer, NULL);
std::cout << "Created consumer thread with ID " << tid << std::endl;


return 0;
}