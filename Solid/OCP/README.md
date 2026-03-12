# Open Closed Principle (OCP)

## Idea

Software entities (classes, modules, functions) should be:

**Open for extension**
**Closed for modification**

This means we should be able to **add new functionality without changing existing code**.

---

# Problem Without OCP

Suppose we design a class responsible for saving a shopping cart to different databases.

```id="bad_ocp_structure"
class ShoppingCartStorage {
    saveToSQL()
    saveToMongo()
    saveToRedis()
}
```

Problems:

* If a new database is added (Postgres, Firebase, etc.)
* We must **modify the existing class**

Example:

```
Add new DB → modify ShoppingCartStorage
```

This violates OCP because existing code keeps changing.

---

# OCP Solution

Instead of one class handling all database types, we introduce an **abstraction**.

```id="ocp_structure"
Persistence (abstract class)
      |
      |--- SQLPersistence
      |--- MongoPersistence
      |--- RedisPersistence
```

Each class handles its own implementation.

Now the system depends on the **abstraction**, not the specific database.

---

# Implementation Example

### Abstract Base Class

```cpp
class Persistence{
public:
    virtual void save(ShoppingCart cart) = 0;
};
```

This defines a rule:

> Any persistence implementation must implement `save()`.

---

### Implementations

```cpp
class MongoPersistence : public Persistence{
public:
    void save(ShoppingCart cart) override{
        cout << "Saving cart to Mongo";
    }
};
```

```cpp
class SQLPersistence : public Persistence{
public:
    void save(ShoppingCart cart) override{
        cout << "Saving cart to SQL";
    }
};
```

```cpp
class RedisPersistence : public Persistence{
public:
    void save(ShoppingCart cart) override{
        cout << "Saving cart to Redis";
    }
};
```

---

# Using Polymorphism

```cpp
Persistence* db = new SQLPersistence();
db->save(cart);
```

The system works with the **Persistence abstraction**, so we can switch implementations easily.

Example:

```cpp
Persistence* db = new MongoPersistence();
```

No changes to existing code are required.

---

# Adding New Functionality

To support a new database:

```
PostgresPersistence
```

We simply create a new class:

```cpp
class PostgresPersistence : public Persistence
```

No existing classes need to be modified.

This follows the **Open Closed Principle**.

---

# Key Concepts Used

OCP is usually implemented using:

* **Inheritance**
* **Abstract classes**
* **Virtual functions**
* **Polymorphism**

---

# Code Smell to Watch For

If you see logic like:

```
if(type == SQL)
else if(type == Mongo)
else if(type == Redis)
```

inside a class, it often means the design violates OCP.

---

# Summary

Bad design:

```
One class handles all behaviors
```

Good design:

```
Abstract base class
Multiple implementations
```

Benefits:

* Easy to extend
* Less risk of breaking existing code
* Cleaner architecture
