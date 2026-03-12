#include<bits/stdc++.h>
using namespace std;

class Account{
public:
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
};

class SavingAccount : public Account{
private:
    double balance;

public:
    SavingAccount(){
        balance = 0;
    }

    void deposit(double amount){
        balance += amount;
        cout << "Deposited in savings account. New balance is: " << balance << endl;
    }

    void withdraw(double amount){
        if(balance >= amount){
            balance -= amount;
            cout << "Withdrawl successfull savings account. New balance is: " << balance << endl;
        }
        else{
            cout << "Insufficient funds" << endl;
        }
    }
};

class CurrentAccount : public Account{
private:
    double balance;

public:
    CurrentAccount(){
        balance = 0;
    }

    void deposit(double amount){
        balance += amount;
        cout << "Deposited in current account. New balance is: " << balance << endl;
    }

    void withdraw(double amount){
        if(balance >= amount){
            balance -= amount;
            cout << "Withdrawl successfull current account. New balance is: " << balance << endl;
        }
        else{
            cout << "Insufficient funds" << endl;
        }
    }
};

class FixedTermAccount : public Account{
private:
    double balance;

public:
    FixedTermAccount(){
        balance = 0;
    }

    void deposit(double amount){
        balance += amount;
        cout << "Deposited in Fixed Term account. New balance is: " << balance << endl;
    }

    void withdraw(double amount){
        throw logic_error("Withdrawl is not allowed in Fixed Term Account");
    }
};

class BankClient{
private:
    vector<Account*> accounts;

public:
    BankClient(vector<Account*> accounts){
        this->accounts = accounts;
    }

    void processTransactions(){
        for (Account* acc: accounts){
            acc->deposit(1000);

            //LSP violation as FixedAccount cannot procees withdraw
            try {
            acc->withdraw(500);
            } catch(const logic_error& e){
                cout << "Exception: " << e.what() << endl;
            }
        }
    }
};

int main(){
    vector<Account*> accounts;
    accounts.push_back(new SavingAccount());
    accounts.push_back(new CurrentAccount());
    accounts.push_back(new FixedTermAccount());

    BankClient* client = new BankClient(accounts);
    client->processTransactions(); // throws exception

    return 0;
}