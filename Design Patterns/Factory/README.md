# Factory Design Patterns (LLD Revision)

Factory patterns deal with **object creation**.  
Instead of creating objects directly using `new`, the client asks a **factory** to create objects.

This helps reduce **tight coupling** and keeps object creation logic centralized.

---

# Goals

- Hide object creation logic
- Reduce coupling between client and concrete classes
- Improve maintainability
- Follow **Dependency Inversion Principle**
- Support **extensibility**

---

# 1. Simple Factory

> Not an official GoF pattern but commonly used.

## Idea

A **single factory class** decides which object to create based on an input parameter.

## Structure

```
Client
   |
   v
Factory
   |
   v
Product (interface/abstract)
   |
   +---- ConcreteProductA
   +---- ConcreteProductB
   +---- ConcreteProductC
```

## Example

```cpp
class BurgerFactory{
public:
    Burger* createBurger(string type){
        if(type == "basic") return new BasicBurger();
        if(type == "standard") return new StandardBurger();
        if(type == "premium") return new PremiumBurger();
        return nullptr;
    }
};
```

## Flow

```
Client → Factory.createBurger("premium")
Factory decides which object to create
Factory returns Burger*
Client calls burger->prepare()
```

## Advantages

- Centralizes object creation
- Cleaner client code
- Easy to understand

## Drawbacks

Factory becomes a **God class**.

Adding a new product requires modifying the factory:

```cpp
if(type == "newBurger")
```

This violates **Open/Closed Principle**.

---

# 2. Factory Method

Factory Method removes the **single large factory problem** by delegating object creation to subclasses.

## Idea

Instead of one factory deciding everything, **each subclass factory decides which object to create**.

## Structure

```
Client
   |
   v
Creator (abstract factory)
   |
   +---- ConcreteCreatorA
   +---- ConcreteCreatorB
            |
            v
          Products
```

## Example

```cpp
class BurgerFactory{
public:
    virtual Burger* createBurger(string &type) = 0;
};

class BurgerKing : public BurgerFactory{
public:
    Burger* createBurger(string &type){
        if(type == "basic") return new BasicBurger();
        if(type == "standard") return new StandardBurger();
        if(type == "premium") return new PremiumBurger();
        return nullptr;
    }
};

class BurgerSingh : public BurgerFactory{
public:
    Burger* createBurger(string &type){
        if(type == "basic") return new BasicWheatBurger();
        if(type == "standard") return new StandardWheatBurger();
        if(type == "premium") return new PremiumWheatBurger();
        return nullptr;
    }
};
```

## Flow

```
Client creates factory
BurgerFactory* factory = new BurgerKing()

factory->createBurger("premium")

BurgerKing decides which burger to create
Factory returns PremiumBurger
```

## Advantages

- Removes single huge factory
- Supports polymorphism
- Easy to add new factory types

Example:

```
Add new restaurant → create new factory class
No change in client code
```

## Caveat

Factories may still contain conditional logic:

```
if(type == "basic")
if(type == "premium")
```

---

# 3. Abstract Factory

Abstract Factory is used when we need to create **families of related objects**.

Instead of creating a single product, a factory creates **multiple related products**.

## Structure

```
            AbstractFactory
           /               \
   ConcreteFactory1   ConcreteFactory2
        |                     |
        v                     v
    ProductA1            ProductA2
    ProductB1            ProductB2
```

## Example (Restaurant Meal)

Products:

```
Burger
Fries
```

Factories:

```
BurgerKingFactory
BurgerSinghFactory
```

Each factory produces its **own style of meal**.

Example mapping:

| Factory | Burger | Fries |
|-------|-------|-------|
| BurgerKing | BasicBurger | SaltedFries |
| BurgerSingh | BasicWheatBurger | PeriPeriFries |

## Example Code

```cpp
class MealFactory{
public:
    virtual Burger* createBurger(string &type) = 0;
    virtual Fries* createFries(string &type) = 0;
};
```

Concrete factory:

```cpp
class BurgerKing : public MealFactory{
public:
    Burger* createBurger(string &type){
        if(type == "premium") return new PremiumBurger();
        return nullptr;
    }

    Fries* createFries(string &type){
        if(type == "cheesy") return new CheesyFries();
        return nullptr;
    }
};
```

## Flow

```
MealFactory* factory = new BurgerKing()

Burger* burger = factory->createBurger("premium")
Fries* fries = factory->createFries("cheesy")
```

This ensures the products belong to the **same family**.

---

# Comparison

| Pattern | Purpose |
|------|------|
| Simple Factory | One factory decides which object to create |
| Factory Method | Subclasses decide which object to create |
| Abstract Factory | Factory creates multiple related objects |

---

# When to Use

Use factory patterns when:

- Object creation is **complex**
- Client should not know **concrete classes**
- Many **variations of objects** exist
- Objects belong to **families**

---

# Real World Examples

## UI Frameworks

```
WindowsFactory
    createButton()
    createCheckbox()

MacFactory
    createButton()
    createCheckbox()
```

Ensures UI components match the operating system.

---

## Database Connectors

```
MySQLFactory
PostgresFactory
MongoFactory
```

Client code remains independent of the database implementation.

---

# Common Mistakes

### Overusing factories

Factories add abstraction.  
If creation is simple, direct instantiation is fine.

```cpp
new Object();
```

---

### String-based factories

Too many conditions can make factories messy.

```
if(type == "...")
```

Better solutions:
- Separate factory classes
- Registry patterns

---

### Raw pointers in C++

Factories often return raw pointers.

```cpp
Product*
```

Better practice:

```cpp
std::unique_ptr<Product>
```

to avoid memory leaks.

---

# Key Insight

Factories move object creation from:

```
Client → new ConcreteClass()
```

to:

```
Client → Factory → Product
```

The client depends only on **abstractions**, not concrete implementations.

This follows the **Dependency Inversion Principle (SOLID)**.

---

# Mental Model

Think of factories like **restaurants**.

```
Customer → Restaurant → Food
```

The customer doesn't cook food.

The restaurant decides **how the food is prepared**.

---

# Summary

Factory patterns improve:

- decoupling
- scalability
- maintainability

They are widely used in **frameworks, APIs, UI systems, and backend services**.