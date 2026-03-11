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

//Violating SRP: Shopping cart is handling multiple responsibilities
class ShoppingCart{
private:
    vector<Product*> products;

public:
    void addProduct(Product* p){
        products.push_back(p);
    }

    //Calculate total price of items in cart
    double calculateTotal(){
        double total = 0;
        for(auto p: products)
        total += p->price;

        return total;
    }

    //SRP violation - prints invoice (should be in separte class)
    void printInvoice(){
        cout<< "Shopping cart invoice:"<<endl;
        for(auto p: products){
            cout << p->name << " - $" << p->price << endl;
        }

        cout << "Total: $" << calculateTotal() << endl;
    }

    //SRP violation - save to DB (should be in separte class)
    void saveToDatabase(){
        cout << "Saving shopping cart to database..." << endl;
    }
};

int main(){

    ShoppingCart* cart = new ShoppingCart();

    cart->addProduct(new Product("Antimatter", 100000000000));
    cart->addProduct(new Product("Uranium", 6900000));

    cart->printInvoice();
    cart->saveToDatabase();

    return 0;
}