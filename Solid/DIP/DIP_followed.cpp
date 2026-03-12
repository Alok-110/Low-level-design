#include<bits/stdc++.h>
using namespace std;

class Database{
public:
    virtual void save() = 0;
};

class MongoDB : public Database{
public:
    void save(){
        cout << "Saving data to MongoDB\n";
    }
};

class SQLDB : public Database{
public:
    void save(){
        cout << "Saving data to SQLDB\n";
    }
};

class UserService{
private:
    Database* db;

public:
    UserService(Database* db){
        this->db = db;
    }

    void saveUser(){
        db->save();
    }
};

int main(){
    Database* db;

    db = new MongoDB();
    UserService service1(db);
    service1.saveUser();

    db = new SQLDB();
    UserService service2(db);
    service2.saveUser();
}