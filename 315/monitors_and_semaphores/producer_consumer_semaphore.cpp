#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

// Define the buffer size
const int BUFFER_SIZE = 3;

// Define the semaphores
sem_t s_empty, s_full, s_mutex;

// Define the buffer and the number of items
queue<int> buffer;

// Define the producer thread function
void producer_thread(void *arg) {
    while(true) {
        // Produce a new item
        int item = rand() % 100;

        // Wait for an empty slot in the buffer
        sem_wait(&s_empty);

        // Acquire the lock
        sem_wait(&s_mutex);

        sleep(1);

        // Add the item to the buffer
        buffer.push(item);

        // Release the lock
        sem_post(&s_mutex);

        // Signal that the buffer is full
        sem_post(&s_full);

        // Print a message indicating that an item was produced
        cout << "Produced item " << item << endl;
    }
}

// Define the consumer thread function
void consumer_thread(void *arg) {
    while(true) {
        // Wait for a full slot in the buffer
        sem_wait(&s_full);

        // Acquire the lock
        sem_wait(&s_mutex);

        sleep(1);

        // Get the item from the buffer
        int item = buffer.front();
        buffer.pop();

        // Release the lock
        sem_post(&s_mutex);

        // Signal that the buffer is empty
        sem_post(&s_empty);

        // Print a message indicating that an item was consumed
        cout << "Consumed item " << item << endl;
    }
}

int main() {
    // Initialize the semaphores
    sem_init(&s_empty, 0, BUFFER_SIZE);
    sem_init(&s_full, 0, 0);
    sem_init(&s_mutex, 0, 1);

    // Create the producer and consumer threads
    thread producer(producer_thread, nullptr);
    thread consumer(consumer_thread, nullptr);

    // Wait for the threads to finish
    producer.join();
    consumer.join();

    // Destroy the semaphores
    sem_destroy(&s_empty);
    sem_destroy(&s_full);
    sem_destroy(&s_mutex);

    return 0;
}
