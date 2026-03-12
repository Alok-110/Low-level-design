#include<bits/stdc++.h>
using namespace std;

class Product{
public:
    string name;
    double price;

    Product(string name, double price){
        this->name = name;
        this->price = price;
    }
};

//ShoppingCart class only repsonsible for cart related logic
class ShoppingCart{
private:
    vector<Product> products;

public:
    void addProducts(Product p){
        products.push_back(p);
    }

    vector<Product> getProducts(){
        return products;
    }

    double calculateTotal(){
        double total = 0;
        for(auto p: products)
        total += p.price;

        return total;
    }
};

//only responsible for printing invoice
class ShoppingCartPrinter{
private:
    ShoppingCart cart;

public:
    ShoppingCartPrinter(ShoppingCart cart){
        this->cart = cart;
    }

    void printInvoice(){
        cout<< "Shopping cart invoice:"<<endl;
        for(auto p: cart.getProducts()){
             cout << p.name << " - $" << p.price << endl;
        }
        cout << "Total: $" << cart.calculateTotal() << endl;

    }
};

//only resposnible for storing to database
class Persistence{
public:
    virtual void save(ShoppingCart cart) = 0;
};

class MongoPersistence : public Persistence{
public:
    void save(ShoppingCart cart) override{
        cout << "Saving cart to Mongo" << endl;
    }
};

class SQLPersistence : public Persistence{
public:
    void save(ShoppingCart cart) override{
        cout << "Saving cart to SQL" << endl;
    }
};

class RedisPersistence : public Persistence{
public:
    void save(ShoppingCart cart) override{
        cout << "Saving cart to Redis" << endl;
    }
};

int main(){

    ShoppingCart cart;
    cart.addProducts(Product("Antimatter", 10056000000));
    cart.addProducts(Product("Plutonium", 100490000));

    ShoppingCartPrinter printer(cart);
    printer.printInvoice();

    Persistence* SQL = new SQLPersistence;
    Persistence* Mongo = new MongoPersistence;
    Persistence* Redis = new RedisPersistence;

    SQL->save(cart);
    Mongo->save(cart);
    Redis->save(cart);
    return 0;
}