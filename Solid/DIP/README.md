# Dependency Inversion Principle (DIP)

## Definition

The **Dependency Inversion Principle** states:

> High-level modules should not depend on low-level modules.
> Both should depend on abstractions.

> Abstractions should not depend on details.
> Details should depend on abstractions.

---

# Core Idea

Traditional design creates dependencies like this:

```id="o6s4xe"
High-Level Logic
       ↓
Low-Level Implementation
```

Example:

```id="l6qjjs"
UserService
     ↓
MongoDB
```

Here, the business logic (`UserService`) directly depends on a concrete database.

This creates **tight coupling**.

---

# Problem with This Design

If we later want to change the database:

```id="c6pjqg"
MongoDB → SQLDB → CassandraDB
```

We must modify the `UserService` class.

Problems:

```id="7u6n0o"
• Tight coupling
• Hard to extend
• Hard to test
• Violates Open/Closed Principle
```

---

# Applying Dependency Inversion

Introduce an abstraction between the high-level and low-level modules.

```id="p04j3r"
UserService
     ↓
   Database (interface)
     ↑
MongoDB   SQLDB
```

Now both depend on the **abstraction**.

---

# Example Design

## Abstraction

```cpp id="92edww"
class Database{
public:
    virtual void save() = 0;
};
```

---

## Low-Level Implementations

```cpp id="v1mra3"
class MongoDB : public Database{
public:
    void save(){
        cout << "Saving data to MongoDB\n";
    }
};
```

```cpp id="m09r9i"
class SQLDB : public Database{
public:
    void save(){
        cout << "Saving data to SQLDB\n";
    }
};
```

---

## High-Level Module

```cpp id="t11n7v"
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
```

---

## Usage

```cpp id="h7qk2f"
int main(){
    Database* db = new MongoDB();

    UserService service(db);
    service.saveUser();
}
```

Switching the database is easy:

```cpp id="hhu4mh"
Database* db = new SQLDB();
```

No changes required in `UserService`.

---

# Dependency Direction After DIP

Before:

```id="mrd3o8"
UserService
     ↓
MongoDB
```

After:

```id="pmr33u"
UserService
     ↓
Database
     ↑
MongoDB   SQLDB
```

The dependency is **inverted**.

---

# Why It Is Called "Inversion"

Normally:

```id="zvpcay"
High-Level → Low-Level
```

After applying DIP:

```id="h04ldq"
High-Level → Abstraction
Low-Level  → Abstraction
```

Both depend on the same interface.

This reverses the original dependency structure.

---

# Benefits

```id="o2n8sz"
• Loose coupling
• Easier testing (mock implementations)
• Easy to replace implementations
• Better extensibility
• Works well with dependency injection
```

---

# Relationship with Other SOLID Principles

### Open/Closed Principle (OCP)

DIP helps achieve OCP.

Because new implementations can be added without modifying existing classes.

Example:

```id="6n69ze"
Add CassandraDB → no change in UserService
```

---

### Liskov Substitution Principle (LSP)

All implementations of `Database` must behave correctly when substituted.

Example:

```id="1hyxak"
MongoDB
SQLDB
CassandraDB
```

Each must correctly implement `save()`.

---

# Practical Rule

Whenever a class directly depends on a concrete implementation like:

```cpp id="5a44cd"
class Service {
    MongoDB db;
}
```

there is a high chance **DIP is violated**.

Instead depend on an interface:

```cpp id="ueixx6"
class Service {
    Database* db;
}
```

---

# One-Line Summary

Dependency Inversion Principle ensures that **high-level business logic depends on abstractions rather than concrete implementations**, enabling flexible and loosely coupled systems.
