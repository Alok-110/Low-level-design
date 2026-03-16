# Singleton Design Pattern (C++)

## Intent

Ensure a class has **only one instance** and provide a **global access point** to that instance.

Common use cases:

* Logger
* Configuration manager
* Cache
* Database connection manager
* Thread pool

These represent **shared resources** where multiple objects could cause inconsistency.

---

# Core Rules

Singleton works using three main ideas:

1. **Private constructor**

   * Prevents external object creation.

2. **Static instance**

   * Stores the single object.

3. **Static accessor method**

   * Provides global access (`getInstance()`).

---

# 1. Lazy Singleton (Basic Idea)

Object created only when requested.

```cpp
if(instance == nullptr)
    instance = new Singleton();
```

Problem:

* Not **thread safe**

Two threads could create two objects simultaneously.

---

# 2. Thread-Safe Singleton

Use a **mutex** to protect creation.

```cpp
lock_guard<mutex> lock(mtx);

if(instance == nullptr)
    instance = new Singleton();
```

Now only **one thread enters the critical section**.

Problem:

* Mutex is used **every time `getInstance()` is called**
* Locking is relatively expensive.

---

# 3. Optimization Idea

Avoid locking when instance already exists.

Move lock **inside the condition**.

```cpp
if(instance == nullptr){
    lock_guard<mutex> lock(mtx);
    instance = new Singleton();
}
```

Reason:

* Once the instance exists, most calls should **skip the mutex**.

Problem:

* Still unsafe.

---

# Race Condition

Two threads could execute:

```
Thread A → instance == nullptr
Thread B → instance == nullptr
```

Both enter the block.

Result:

```
Two Singleton objects created
```

---

# 4. Double-Checked Locking

Solution: **Check twice**.

```cpp
if(instance == nullptr){
    lock_guard<mutex> lock(mtx);

    if(instance == nullptr)
        instance = new Singleton();
}
```

Why second check is needed:

```
Thread A → passes first check
Thread B → passes first check
Thread A → creates instance
Thread B → acquires lock later
```

Second check prevents **duplicate creation**.

---

# Memory Model

```
Class Singleton
     |
     |-- static instance pointer
     |
Heap
     |
     |-- Singleton Object
```

All calls return the **same object**.

---

# Advantages

* Controlled instance creation
* Shared resource management
* Global access point

---

# Disadvantages

* Acts like a global variable
* Harder to test
* Hidden dependencies
* Tight coupling

---

# Modern C++ Alternative (Meyers Singleton)

Since **C++11 guarantees thread-safe static initialization**, the cleanest implementation is:

```cpp
static Singleton& getInstance(){
    static Singleton instance;
    return instance;
}
```

Advantages:

* Thread safe
* No mutex
* Simpler implementation

---

# 5. Eager Initialization Singleton

Instead of creating the object on first request, the instance is created **when the program starts**.

```
static Singleton* instance = new Singleton();
```

`getInstance()` simply returns the already-created object.

```cpp
static Singleton* getInstance(){
    return instance;
}
```

### Characteristics

**Advantages**

* Simple implementation
* Naturally thread-safe (object created before threads run)

**Disadvantages**

* Object is created even if it is never used
* Can increase startup memory usage

### When to use

Useful when:

* Singleton is **always required**
* Initialization cost is small
* Lazy loading is unnecessary

----

# Implementations in This Repo

* `ThreadSafeSingleton.cpp`
* `DoubleCheckedSingleton.cpp`

Full code is in the source files.
This README focuses on **concepts and reasoning**.
