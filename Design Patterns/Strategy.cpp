#include<bits/stdc++.h>
using namespace std;

//Strategy inteface for walk
class WalkableRobot{
public:
    virtual void walk() = 0;
    virtual ~WalkableRobot() {};
};

//Concrete strategies for walk
class NormalWalk : public WalkableRobot{
public:
    void walk() override{
        cout << "Walking normally..." << endl;
    }
};

class NoWalk : public WalkableRobot{
public:
    void walk() override{
        cout << "Cannot walk" << endl;
    }
};

//Strategy inteface for talk
class TalkableRobot{
public:
    virtual void talk() = 0;
    virtual ~TalkableRobot() {};
};

//Concrete strategies for walk
class NormalTalk : public TalkableRobot{
public:
    void talk() override{
        cout << "Talking normally..." << endl;
    }
};

class NoTalk : public TalkableRobot{
public:
    void talk() override{
        cout << "Cannot talk" << endl;
    }
};

//Strategy inteface for fly
class FlyableRobot{
public:
    virtual void fly() = 0;
    virtual ~FlyableRobot() {};
};

//Concrete strategies for fly
class NormalFly : public FlyableRobot{
public:
    void fly() override{
        cout << "Flying normally..." << endl;
    }
};

class NoFly : public FlyableRobot{
public:
    void fly() override{
        cout << "Cannot fly" << endl;
    }
};

class Robot{
protected:
    WalkableRobot* walkBehaviour;
    TalkableRobot* talkBehaviour;
    FlyableRobot* flyBehaviour;

public:
    Robot(WalkableRobot *w, TalkableRobot* t, FlyableRobot* f){
        this->walkBehaviour = w;
        this->talkBehaviour = t;
        this->flyBehaviour = f;
    }

    void walk(){
        walkBehaviour->walk();
    }

    void talk(){
        talkBehaviour->talk();
    }

    void fly(){
        flyBehaviour->fly();
    }

    virtual void projection() = 0; //abstract method to be used by subclasses
};

//Concrete robot types
class CompanionRobot : public Robot{
public: 
    CompanionRobot(WalkableRobot *w, TalkableRobot* t, FlyableRobot* f)
        : Robot(w, t, f) {};

    void projection() override{
        cout << "Displaying friendly companion features..." << endl;
    }
};

class WorkerRobot : public Robot{
public: 
    WorkerRobot(WalkableRobot *w, TalkableRobot* t, FlyableRobot* f)
        : Robot(w, t, f) {};

    void projection() override{
        cout << "Displaying worker efficiency stats..." << endl;
    }
};

int main(){

    Robot* robot1 = new CompanionRobot(new NormalWalk(), new NormalTalk(), new NoFly());
    robot1->walk();
    robot1->talk();
    robot1->fly();
    robot1->projection();

    Robot* robot2 = new CompanionRobot(new NoWalk(), new NoTalk(), new NormalFly());
    robot2->walk();
    robot2->talk();
    robot2->fly();
    robot2->projection();
}
