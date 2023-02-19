#include <iostream>
#include <queue>
#include <unistd.h>

using namespace std;

// Define the buffer size
const int BUFFER_SIZE = 10;

// buffer
queue<int> buffer;

int number_of_items = 0;

class _semaphore{

public:
    // constructor
    _semaphore(int c){
        counter = c;
    }
    _semaphore(){
        counter = 0;
    }
    // try to acquire lock, if > 0, we got it
    int wait(){
        if(counter > 0){
            counter--;
            return 1;
        }
    return 0;
    }
    // were done here, unlock
    void post(){
        counter++;
    }

private:

int counter;

};

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

// define our semaphores and mutex
_semaphore full_sem;
_semaphore empty_sem(BUFFER_SIZE);
_mutex m_mutex;

void producer() {
    while(number_of_items != BUFFER_SIZE){
        // sleep for 1 second
        sleep(1);
        // wait for empty slot in buffer, decrement semaphore internal counter
        if(empty_sem.wait()){
            // make some item
            int item = rand() % 100;
            // acquire the mutex lock
            if(m_mutex.try_lock()){
                // push item
                buffer.push(item);
                cout << "Produced item " << item << endl;
                number_of_items++;
                // unlock the mutex
                m_mutex.try_unlock();
                // let the consumer know the buffer isnt empty
                full_sem.post();
            }
        }
    }
}

void consumer() {

    while(number_of_items != 0){
        
        // sleep for 1 second
        sleep(1);
        // wait for buffer to be full
        if(full_sem.wait()){

            // acquire the mutex lock
            if(m_mutex.try_lock()){
                // get item
                int item = buffer.front();
                // pop item, print
                buffer.pop();
                cout << "Consumed item " << item << endl;
                // decrement counter
                number_of_items--;
                // unlock the mutex
                m_mutex.try_unlock();

                empty_sem.post();
            }
        }
        
    }

}


// Main function
int main() {

    // randomly choose between calling producer or consumer
    while(true) {
        int i = rand() % 2;
        if(i){
            producer();
        }else{
            consumer();
        }
    }

    return 0;
}
