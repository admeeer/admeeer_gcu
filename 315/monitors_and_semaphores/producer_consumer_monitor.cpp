#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h>

using namespace std;

// Define the buffer size
const int BUFFER_SIZE = 10;

// Define the monitor class
class Monitor {
public:
    Monitor() {
        num_items = 0;
    }

    // Define the producer method
    void produce(int item) {
        // Acquire the lock
        unique_lock<mutex> lock(mutex_);

        // Wait until there is space in the buffer
        while (num_items == BUFFER_SIZE) {
            producer_condition.wait(lock);
        }

        // sleep for 1 second
        sleep(1);

        // Add the item to the buffer
        buffer.push(item);
        num_items++;

        // Notify any waiting consumers
        consumer_condition.notify_all();
    }

    // Define the consumer method
    int consume() {
        // Acquire the lock
        unique_lock<mutex> lock(mutex_);

        // Wait until there is an item in the buffer
        while (num_items == 0) {
            consumer_condition.wait(lock);
        }

       // sleep for 1 second
        sleep(1);

        // Get the first item from the buffer
        int item = buffer.front();
        buffer.pop();
        num_items--;

        // Notify any waiting producers
        producer_condition.notify_all();

        // Return the item
        return item;
    }

private:
    // our buffer, size is global var
    queue<int> buffer;
    // track number of items in buffer
    int num_items;
    // mutex
    mutex mutex_;
    // condition variables
    condition_variable producer_condition, consumer_condition;
};

// end of class definition

// Define the producer function
void producer(Monitor& monitor) {

    while(true){
        // make some item
        int item = rand() % 100;
        // 'produce' item, push to buffer
        monitor.produce(item);

        // print item
        cout << "Produced item " << item << endl;
        // sleep for a second
        this_thread::sleep_for(chrono::seconds(1));
    }
}

// Define the consumer function
void consumer(Monitor& monitor) {
    while(true){
        // consume item, copy it
        int item = monitor.consume();
        // print consumed item
        cout << "Consumed item " << item << endl;
        // sleep for a second
        this_thread::sleep_for(chrono::seconds(1));

    }
}

// Main function
int main() {
    // init relevant vars and run
    Monitor monitor;

    thread producer_thread(producer, ref(monitor));
    thread consumer_thread(consumer, ref(monitor));

    producer_thread.join();
    consumer_thread.join();

    return 0;
}
