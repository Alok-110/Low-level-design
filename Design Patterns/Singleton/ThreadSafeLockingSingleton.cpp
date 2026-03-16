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
        lock_guard<mutex> lock(mtx); //Lock for thread saftey
        if(!instance){          
            instance = new Singleton();
        }
        return instance;        
    }
};

// Static variables must be defined outside the class
Singleton* Singleton::instance = nullptr;
mutex Singleton::mtx;

int main(){

    Singleton *s1 = Singleton::getInstance();
    Singleton *s2 = Singleton::getInstance();
    cout << (s1 == s2);
}

