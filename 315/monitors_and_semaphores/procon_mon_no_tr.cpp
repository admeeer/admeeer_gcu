#include <iostream>
#include <queue>
#include <unistd.h>

using namespace std;

// Define the buffer size
const int BUFFER_SIZE = 10;

// define custom mutex class
class _mutex{

// overloaded constructor with param or no param
public:
    _mutex(bool init){
        lock = init;
    }

    _mutex(){
        lock = false;
    }
    // try to set lock = true
    int try_lock(){
        if(lock){
            return 0;
        }
        
        lock = true;
        return 1;
    }
    // try to set lock = false
    int try_unlock(){
        if(lock){
            lock = false;
            return 1;
        }
        // this shouldn't happen, so we'll print the issue
        cout << "\n tried to unlock a mutex that was already unlocked ! \n" << endl;
        return 0;
    }


// the lock
bool lock;

};

// custom condition var class
class _condition_variable{

// constructor
public:
    _condition_variable() {
    }

    // wait called, unlock mutex
    void wait(_mutex &m){
        m.try_unlock();
        cout << "condition variable is waiting! " << endl;
    }

    // notify other condition vars
    void notify_all(_mutex &m){
        m.try_unlock();
        //cout << "condition variable has been notified! " << endl;
    }

private:

};

class Monitor {

public:
    // constructor
    Monitor() {
        number_of_items = 0;
    }
    // define the producer method
    void produce(int item) {
        // acquire the lock
        if(m_mutex.try_lock()){

            // check condition
            if(number_of_items == BUFFER_SIZE) {
                producer_cond.wait(m_mutex);
            }
            // push item to buffer
            buffer.push(item);
            cout << "Produced item " << item << endl;
            number_of_items++;
            // notify other condition
            consumer_cond.notify_all(m_mutex);
        }

        return;

    }

    // define the consumer method
    void consume() {
        // acquire the lock
        if(m_mutex.try_lock()){
            // wait until conditon is met
            if(number_of_items == 0){
                consumer_cond.wait(m_mutex);
            }
            // get item, consume it
            int item = buffer.front();
            buffer.pop();
            cout << "Consumed item " << item << endl;
            number_of_items--;
            // notify other condition
            producer_cond.notify_all(m_mutex);

        }

        return;

    }

private:
    // our buffer, size is BUFFER_SIZE
    queue<int> buffer;
    // keep track of number of items
    int number_of_items;
    // mutex
    _mutex m_mutex;
    // condition variables
    _condition_variable producer_cond, consumer_cond; 



};

void producer(Monitor& monitor) {
        // make some item
        int item = rand() % 100;
        // produce item, push to buffer
        sleep(1);
        monitor.produce(item);

}

void consumer(Monitor& monitor) {
        // consume item, copy it
        sleep(1);
        monitor.consume();
}


// Main function
int main() {

    Monitor monitor;

    while(true) {
        int i = rand() % 2;
        if(i){
            producer(monitor);
        }else{
            consumer(monitor);
        }
    }

    return 0;
}
