# Single Responsibility Principle (SRP)

## Idea

A class should have **one responsibility** and **one reason to change**.

If a class handles multiple concerns (business logic, printing, storage, etc.), changes in one area can unintentionally affect others.
SRP helps keep code **modular, maintainable, and easier to extend**.

---

## Example Scenario

We are designing a **shopping cart system**.

Responsibilities involved:

* Managing products in the cart
* Printing an invoice
* Saving the cart to a database

If one class handles all of these, it violates SRP.

---

# ❌ SRP Violated

The `ShoppingCart` class is doing multiple things:

* Managing cart items
* Printing invoice
* Saving to database

```
ShoppingCart
 ├── addProduct()
 ├── calculateTotal()
 ├── printInvoice()
 └── saveToDatabase()
```

Problems:

* If invoice format changes → modify `ShoppingCart`
* If database logic changes → modify `ShoppingCart`
* If cart logic changes → modify `ShoppingCart`

One class now has **multiple reasons to change**.

---

# ✅ SRP Followed

Each responsibility is moved to its own class.

```
ShoppingCart
 ├── addProduct()
 └── calculateTotal()

ShoppingCartPrinter
 └── printInvoice()

ShoppingCartStorage
 └── saveToDatabase()
```

Responsibilities are now separated:

| Class               | Responsibility                 |
| ------------------- | ------------------------------ |
| ShoppingCart        | Manage products and cart logic |
| ShoppingCartPrinter | Print invoice                  |
| ShoppingCartStorage | Store cart in database         |

Benefits:

* Changes in printing do not affect cart logic
* Database changes do not affect cart behavior
* Code becomes easier to maintain and test

---

# Code Files

* `violated.cpp` → Example where SRP is violated
* `fixed.cpp` → Refactored version following SRP

---

# Key Takeaway

When designing a class ask:

> **What is the single responsibility of this class?**

If the answer includes multiple concerns, the class likely violates SRP.

---

# Code Smell to Watch For

A class that:

* prints data
* saves data
* processes business logic

all together is often called a **God Class**, and usually violates SRP.

---

# Summary

SRP encourages:

* separation of concerns
* cleaner architecture
* easier code changes
* better maintainability
