#include<iostream>
using namespace std;

class Singleton{
private:
    static Singleton* instance;   // shared pointer for the only object

    Singleton(){
        cout << "Singleton constructor called. New object created!" << endl;
    }

public:
    static Singleton* getInstance(){
        if(!instance){           
            instance = new Singleton();
        }
        return instance;        
    }
};

Singleton* Singleton::instance = new Singleton();

int main(){

    Singleton *s1 = Singleton::getInstance();
    Singleton *s2 = Singleton::getInstance();

    cout << (s1 == s2);
}