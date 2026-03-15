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

class Fries{
public:
    virtual void prepare() = 0;
    virtual ~Fries() {};
};

class SaltedFries : public Fries{
public:
    void prepare(){
        cout << "Preparing salted fries!" << endl;
    }
};

class CheesyFries : public Fries{
public:
    void prepare(){
        cout << "Preparing cheesy fries!" << endl;
    }
};

class PeriPeriFries : public Fries{
public:
    void prepare(){
        cout << "Preparing peri peri fries!" << endl;
    }
};

class CheesyPeriPeriFries : public Fries{
public:
    void prepare(){
        cout << "Preparing cheesy peri peri fries!" << endl;
    }
};

class MealFactory{
public:
   virtual Burger* createBurger(string &type) = 0;
   virtual Fries* createFries(string &type) = 0;
};

class BurgerKing : public MealFactory{
public:
     Burger* createBurger(string &type){
        if(type == "basic")
        return new BasicBurger();

        if(type == "standard")
        return new StandardBurger();

        if(type == "premium")
        return new PremiumBurger();
    }

    Fries* createFries(string &type){
        if(type == "salted")
        return new SaltedFries();

        if(type == "cheesy")
        return new CheesyFries();
    }
};

class BurgerSingh : public MealFactory{
public:
     Burger* createBurger(string &type){
        if(type == "basic")
        return new BasicWheatBurger();

        if(type == "standard")
        return new StandardWheatBurger();

        if(type == "premium")
        return new PremiumWheatBurger();
    }

    Fries* createFries(string &type){
        if(type == "salted")
        return new PeriPeriFries();

        if(type == "cheesy")
        return new CheesyPeriPeriFries();
    }
};

int main(){

    string burgerType = "premium";
    string friesType = "cheesy";

    MealFactory* KingFactory = new BurgerKing();
    MealFactory* SinghFactory = new BurgerSingh();
    Burger* KingBurger = KingFactory->createBurger(burgerType);
    Burger* SinghBurger = SinghFactory->createBurger(burgerType);
    Fries* SinghFries = SinghFactory->createFries(friesType);
    Fries* KingFries = KingFactory->createFries(friesType);

    KingBurger->prepare();
    SinghBurger->prepare();
    SinghFries->prepare();
    KingFries->prepare();
}

