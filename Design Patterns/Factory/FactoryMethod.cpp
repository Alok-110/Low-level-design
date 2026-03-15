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

class PremiumWheatBurger : public Burger{
public:
    void prepare(){
        cout << "Preparing premium Wheat burger with Gourmet Bun, Cheese-Patty, Lettuce and In-House sauce!" << endl;
    }
};

class BasicWheatBurger : public Burger{
public:
    void prepare(){
        cout << "Preparing basic Wheat burger with Bun, Patty and Ketchup!" << endl;
    }
};

class StandardWheatBurger : public Burger{
public:
    void prepare(){
        cout << "Preparing standard Wheat burger with Bun, Patty, Lettuce and Cheese!" << endl;
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
   virtual Burger* createBurger(string &type) = 0;
};

class BurgerKing : public BurgerFactory{
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

class BurgerSingh : public BurgerFactory{
public:
     Burger* createBurger(string &type){
        if(type == "basic")
        return new BasicWheatBurger();

        if(type == "standard")
        return new StandardWheatBurger();

        if(type == "premium")
        return new PremiumWheatBurger();
    }
};

int main(){

    string type = "premium";

    BurgerFactory* KingFactory = new BurgerKing();
    BurgerFactory* SinghFactory = new BurgerSingh();
    Burger* KingBurger = KingFactory->createBurger(type);
    Burger* SinghBurger = SinghFactory->createBurger(type);

    KingBurger->prepare();
    SinghBurger->prepare();
}

