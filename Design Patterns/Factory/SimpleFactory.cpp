#include<bits/stdc++.h>
using namespace std;

class Burger{
public:
    virtual void prepare() = 0;
    virtual ~Burger() {};
};

class BasicBurger : public Burger{
public:
    void prepare(){
        cout << "Preparing basic burger with Bun, Patty and Ketchup!" << endl;
    }
};

class StandardBurger : public Burger{
public:
    void prepare(){
        cout << "Preparing standard burger with Bun, Patty, Lettuce and Cheese!" << endl;
    }
};

class PremiumBurger : public Burger{
public:
    void prepare(){
        cout << "Preparing premium burger with Gourmet Bun, Cheese-Patty, Lettuce and In-House sauce!" << endl;
    }
};

class BurgerFactory{
public:
    Burger* createBurger(string &type){
        if(type == "basic")
        return new BasicBurger();

        if(type == "standard")
        return new StandardBurger();

        if(type == "premium")
        return new PremiumBurger();
    }
};

int main(){

    string type = "premium";

    BurgerFactory* myBurgerFactory = new BurgerFactory();
    Burger* burger = myBurgerFactory->createBurger(type);

    burger->prepare();
}

