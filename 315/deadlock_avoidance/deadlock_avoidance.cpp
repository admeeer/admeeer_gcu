#include <iostream>
#include <pthread.h>
#include <unistd.h>

// Global variables
bool resource = true;
pthread_mutex_t resourceMutex = PTHREAD_MUTEX_INITIALIZER;

// Simulate a process
void* process(void* arg) {

    // id of process
    int id = *((int*) arg);
    // timer
    int timeout = id * 5;

    while (true) {
        // sleep for 1 second
        sleep(1);

        if (resource) {

            // Try to acquire the resource
            std::cout << "Process " << id << " is trying to access the resource" << std::endl;
            pthread_mutex_lock(&resourceMutex);

            // Resource is available, acquire it
            std::cout << "Process " << id << " has acquired the resource" << std::endl;

            // Do some work
            resource = false;

            // Sleep for 1 second
            sleep(1);

            // Release the resource
            pthread_mutex_unlock(&resourceMutex);

            std::cout << "Process " << id << " has released the resource" << std::endl;

            resource = true;

            // Wait for a while before trying to acquire the resource again
            sleep(1);

        } else {
            
            // Resource is not available
            std::cout << "Process " << id << " is waiting for the resource" << std::endl;
            // Sleep for a second
            sleep(1);

        }
        // Check if the process has been starved
        timeout--;
        if (timeout == 0) {
            std::cout << "Process " << id << " has been terminated due to starvation" << std::endl;
            pthread_exit(NULL);
        }
        // Check if the thread has been interrupted
        pthread_testcancel();
    }
}

int main() {
    // Create four processes
    pthread_t p1, p2, p3, p4;
    int id1 = 1, id2 = 2, id3 = 3, id4 = 4;
    pthread_create(&p1, NULL, process, &id1);
    pthread_create(&p2, NULL, process, &id2);
    pthread_create(&p3, NULL, process, &id3);
    pthread_create(&p4, NULL, process, &id4);
    // Wait for the processes to finish
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);
    return 0;
}
