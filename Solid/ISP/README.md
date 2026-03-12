# Interface Segregation Principle (ISP)

## Definition

The **Interface Segregation Principle** states:

> Clients should not be forced to depend on interfaces they do not use.

In simpler terms:

An interface should contain **only the methods that its implementing classes actually need**.

Instead of **large “fat” interfaces**, create **smaller, focused interfaces**.

---

# The Problem ISP Solves

Bad design often creates **interfaces with too many responsibilities**.

Example:

```
Shape
 ├ area()
 └ volume()
```

Classes:

```
Circle
Square
Cube
```

Problem:

```
Circle → does not need volume()
Square → does not need volume()
Cube → might not need area() depending on context
```

Implementations end up like:

```cpp
double volume() {
    throw logic_error("Not supported");
}
```

This is a **design smell**.

---

# Why This Is Bad

When interfaces contain unnecessary methods:

* Classes implement **methods they don't need**
* Code becomes **misleading**
* It often leads to **runtime errors**
* It breaks **clean abstraction**

---

# ISP Violation Example

Bad design:

```cpp
class Shape {
public:
    virtual double area() = 0;
    virtual double volume() = 0;
};
```

Subclasses:

```
Circle
Square
Cube
```

Circle and Square must implement `volume()` even though they **do not have volume**.

---

# Correct Design (Applying ISP)

Split the interface into smaller ones.

Example:

```
Shape2D
 └ area()

Shape3D
 ├ area()
 └ volume()
```

Implementation:

```
Circle : Shape2D
Square : Shape2D
Cube   : Shape3D
```

Now each class implements **only the methods it needs**.

---

# Even Cleaner Design (Capability-Based)

Sometimes it's better to split by **capabilities** instead of hierarchy.

Example:

```
HasArea
HasVolume
```

Then classes implement only relevant capabilities:

```
Circle : HasArea
Square : HasArea
Cube   : HasArea, HasVolume
```

This avoids rigid inheritance hierarchies.

---

# Relationship with Other SOLID Principles

### LSP (Liskov Substitution Principle)

ISP violations often cause LSP violations.

Example flow:

```
Fat interface
      ↓
Class forced to implement unused method
      ↓
Method throws "not supported"
      ↓
LSP broken
```

So:

```
ISP prevents LSP violations.
```

---

### SRP (Single Responsibility Principle)

SRP focuses on **classes**.

ISP focuses on **interfaces**.

```
SRP → class should have one responsibility
ISP → interface should have minimal responsibilities
```

---

### OCP (Open/Closed Principle)

Fat interfaces often cause conditionals like:

```
if(type == X)
if(type == Y)
```

Splitting interfaces allows extending behavior without modifying existing code.

---

# Common Signs of ISP Violation

Look for these patterns:

```
throw "not supported"
empty method implementations
unused parameters
large interfaces with many unrelated methods
```

These usually indicate the interface should be **split**.

---

# Real World Example

Bad design:

```
Machine
 ├ print()
 ├ scan()
 └ fax()
```

A simple printer must implement:

```
scan()
fax()
```

even if it doesn't support them.

Better design:

```
Printer
Scanner
Fax
```

Classes implement only what they support:

```
SimplePrinter : Printer
MultiFunctionPrinter : Printer, Scanner, Fax
```

---

# Key Insight

ISP encourages designing **small, focused interfaces** that represent **specific capabilities**.

Instead of asking:

```
What is this object?
```

Ask:

```
What can this object do?
```

---

# Practical Rule

Whenever a class has to implement:

```
throw "not supported"
```

or leave methods empty, the interface is probably **too large**.

That is a strong signal that **ISP is violated**.

---

# One-Line Summary

Interface Segregation Principle ensures that **interfaces stay small and focused**, so classes only implement behavior they actually support.
