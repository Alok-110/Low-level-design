#include<bits/stdc++.h>
using namespace std;

class Account{

};

class DepositableAccount : public Account{
public:
    virtual void deposit(double amount) = 0;
};

class WithdrawableAccount : public Account{
public:
    virtual void withdraw(double amount) = 0;
};


class SavingAccount : public DepositableAccount, public WithdrawableAccount{
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

class CurrentAccount : public DepositableAccount, public WithdrawableAccount{
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

class FixedTermAccount : public DepositableAccount{
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
};

class BankClient{
private:
    vector<WithdrawableAccount*> withdrawableAccounts;
    vector<DepositableAccount*> depositableAccounts;

public:
    BankClient(vector<WithdrawableAccount*> withdrawableAccounts, vector<DepositableAccount*> depositableAccounts){
        this->withdrawableAccounts = withdrawableAccounts;
        this->depositableAccounts = depositableAccounts;
    }

    void processTransactions(){
        for (WithdrawableAccount* acc: withdrawableAccounts)
            acc->withdraw(1000);
        
        for (DepositableAccount* acc: depositableAccounts)
            acc->deposit(1000);
    }
};

int main(){
    vector<WithdrawableAccount*> withdrawableAccounts;
    vector<DepositableAccount*> depositableAccounts;

    withdrawableAccounts.push_back(new SavingAccount());
    withdrawableAccounts.push_back(new CurrentAccount());
    depositableAccounts.push_back(new CurrentAccount());
    depositableAccounts.push_back(new CurrentAccount());
    depositableAccounts.push_back(new FixedTermAccount());

    BankClient* client = new BankClient(withdrawableAccounts, depositableAccounts);
    client->processTransactions();

    return 0;
}