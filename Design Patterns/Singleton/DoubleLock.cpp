#include<iostream>
#include<mutex>
using namespace std;

class Singleton{
private:
    static Singleton* instance; 
    static mutex mtx;  

    Singleton(){
        cout << "Singleton constructor called. New object created!" << endl;
    }

public:
    static Singleton* getInstance(){

        // Optimization attempt:
        // Locking a mutex is expensive.
        // In the previous thread-safe version we locked every time getInstance() was called,
        // even when the instance was already created.
        // So we first check if instance is nullptr.
        // If it is already created, we skip locking and return immediately.

        if(!instance){          
            lock_guard<mutex> lock(mtx); // lock only when creation might be needed
            instance = new Singleton();
        }

        return instance;        
    }
};

Singleton* Singleton::instance = nullptr;
mutex Singleton::mtx;


// Problem with the above version:
// Two threads could reach the first if(!instance) at the same time.
// Both would see instance == nullptr and both would enter the block.
// After the first thread creates the object and releases the lock,
// the second thread would still execute the creation line.
// This leads to two objects being created (race condition).


class Singleton{
private:
    static Singleton* instance; 
    static mutex mtx;  

    Singleton(){
        cout << "Singleton constructor called. New object created!" << endl;
    }

public:
    static Singleton* getInstance(){


        if(!instance){          
            lock_guard<mutex> lock(mtx); // acquire lock before creation

            // Second check (inside lock) is necessary because another
            // thread might have created the instance while this thread
            // was waiting to acquire the mutex.

            if(!instance)
                instance = new Singleton();
        }

        return instance;        
    }
};

Singleton* Singleton::instance = nullptr;
mutex Singleton::mtx;


int main(){

    Singleton *s1 = Singleton::getInstance();
    Singleton *s2 = Singleton::getInstance();

    cout << (s1 == s2);
}