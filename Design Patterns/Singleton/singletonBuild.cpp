#include<bits/stdc++.h>
using namespace std;

// STEP 0: Normal class
// Anyone can create objects freely → violates Singleton idea
class Singleton{
public:
    Singleton(){
        cout << "Singleton constructor called. New object created!" << endl;
    }
};


// STEP 1: Make constructor private
// Now external code cannot create objects using new or stack allocation
// Problem: now NO object can be created at all
class Singleton{
private:
    Singleton(){
        cout << "Singleton constructor called. New object created!" << endl;
    }
};


// STEP 2: Add a getter function that returns the object
// Idea: instead of creating objects directly, users call this function
// Problem: this function itself needs an object to be called
class Singleton{
private:
    Singleton(){
        cout << "Singleton constructor called. New object created!" << endl;
    }
public:
    Singleton* getInstance(){
        return new Singleton;
    }
};


// STEP 3: Make the getter static
// Static functions belong to the class, not an object
// Now we can call: Singleton::getInstance()
// Problem: every call still creates a new object
class Singleton{
private:
    Singleton(){
        cout << "Singleton constructor called. New object created!" << endl;
    }
public:
    static Singleton* getInstance(){
        return new Singleton();
    }
};


// STEP 4: Store the instance inside the class
// If instance already exists → return it
// If not → create it once and store it
class Singleton{
private:
    static Singleton* instance;   // shared pointer for the only object

    Singleton(){
        cout << "Singleton constructor called. New object created!" << endl;
    }

public:
    static Singleton* getInstance(){
        if(!instance){           // first time call
            instance = new Singleton();
        }
        return instance;         // return the same object every time
    }
};

// Static variables must be defined outside the class
Singleton* Singleton::instance = nullptr;

int main(){

    Singleton *s1 = Singleton::getInstance();
    Singleton *s2 = Singleton::getInstance();

    // if singleton works correctly both pointers should be same
    cout << (s1 == s2);
}