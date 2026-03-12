#include<bits/stdc++.h>
using namespace std;

class MongoDB{
public:
    void save(){
        cout << "Saving data to MongoDB\n";
    }
};

class SQLDB{
public:
    void save(){
        cout << "Saving data to SQLDB\n";
    }
};

class UserService{
private:
    MongoDB mongo;
    SQLDB sql;

public:
    void saveUser(string dbType){
        if(dbType == "mongo"){
            mongo.save();
        }
        else if(dbType == "sql"){
            sql.save();
        }
    }
};

int main(){
    UserService service;
    service.saveUser("mongo");
    service.saveUser("sql");
}