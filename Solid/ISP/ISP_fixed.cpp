#include<bits/stdc++.h>
using namespace std;

class Shape2D{
public:
    virtual double area() = 0;
};

class Shape3D{
public:
    virtual double area() = 0;
    virtual double volume() = 0;
};

class Circle : public Shape2D{
private:
    double radius;

public:
    Circle(double r){
        radius = r;
    }

    double area(){
        return 3.14 * radius * radius;
    }
};

class Square : public Shape2D{
private:
    double side;

public:
    Square(double s){
        side = s;
    }

    double area(){
        return side * side;
    }
};

class Cube : public Shape3D{
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
    Shape2D* c = new Circle(5);
    Shape2D* s = new Square(4);
    Shape3D* cube = new Cube(3);

    cout << "Circle Area: " << c->area() << endl;
    cout << "Square Area: " << s->area() << endl;
    cout << "Cube Volume: " << cube->volume() << endl;

    return 0;
}