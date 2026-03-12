#include<bits/stdc++.h>
using namespace std;

class Shape{
public:
    virtual double area() = 0;
    virtual double volume() = 0;
};

class Circle : public Shape{
private:
    double radius;

public:
    Circle(double r){
        radius = r;
    }

    double area(){
        return 3.14 * radius * radius;
    }

    double volume(){
        throw logic_error("Circle does not have volume");
    }
};

class Square : public Shape{
private:
    double side;

public:
    Square(double s){
        side = s;
    }

    double area(){
        return side * side;
    }

    double volume(){
        throw logic_error("Square does not have volume");
    }
};

class Cube : public Shape{
private:
    double side;

public:
    Cube(double s){
        side = s;
    }

    double area(){
        return 6 * side * side;
    }

    double volume(){
        return side * side * side;
    }
};

int main(){
    Shape* c = new Circle(5);
    Shape* s = new Square(4);
    Shape* cube = new Cube(3);

    cout << "Circle Area: " << c->area() << endl;
    cout << "Square Area: " << s->area() << endl;
    cout << "Cube Volume: " << cube->volume() << endl;

    return 0;
}