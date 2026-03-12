# Liskov Substitution Principle (LSP)

## Definition

The **Liskov Substitution Principle** states:

> Objects of a superclass should be replaceable with objects of a subclass **without altering the correctness of the program**.

In simpler terms:

If `B` is a subtype of `A`, then **`B` should be usable anywhere `A` is expected**, without breaking behavior.

---

# Core Idea

Inheritance implies a **behavioral contract**.

When a class inherits another class, it promises:

```
"Everything the parent guarantees, I can also guarantee."
```

If the subclass cannot fulfill that promise, **LSP is violated**.

---

# Classic LSP Violation

## Problem Example

```
Account
 ├ SavingsAccount
 ├ CurrentAccount
 └ FixedDepositAccount
```

Parent contract:

```
deposit()
withdraw()
```

But in real banking systems:

```
FixedDepositAccount cannot withdraw
```

Implementation often becomes:

```
void withdraw() {
    throw logic_error("Withdraw not allowed");
}
```

This breaks LSP because:

```
Account* acc = new FixedDepositAccount();
acc->withdraw();  // unexpected failure
```

The client expected all `Account` objects to support withdrawal.

---

# Why This Is Wrong

The base class **promised behavior** that some subclasses cannot support.

The abstraction was incorrect.

---

# Correct Fix

Separate behaviors into **smaller abstractions**.

```
Account
Depositable
Withdrawable
```

Then classes implement capabilities:

```
SavingsAccount : Account, Depositable, Withdrawable
CurrentAccount : Account, Depositable, Withdrawable
FixedDepositAccount : Account, Depositable
```

Now each class only promises behavior it can support.

---

# Key Design Insight

LSP violations usually mean:

```
The abstraction is wrong
```

Not that the subclass is wrong.

---

# LSP Violation Smells

Common signals that LSP is being broken:

```
throw "not supported"
empty override
return default values
runtime type checks
if(type == X)
```

Example:

```
if(account.type == FIXED_DEPOSIT)
```

This indicates the hierarchy is incorrect.

---

# Behavioral Contract Rule

A subclass must not:

### 1. Remove behavior

Parent:

```
withdraw()
```

Child:

```
withdraw() → throws exception
```

Violation.

---

### 2. Strengthen preconditions

Parent:

```
withdraw(amount > 0)
```

Child:

```
withdraw(amount > 1000)
```

Violation.

Child should **not require stricter inputs**.

---

### 3. Weaken postconditions

Parent guarantees:

```
withdraw() reduces balance
```

Child:

```
withdraw() sometimes does nothing
```

Violation.

---

# Identity vs Capability

A useful design rule:

```
Identity → what an object IS
Capability → what an object CAN DO
```

Example:

Identity:

```
Account
```

Capabilities:

```
Depositable
Withdrawable
InterestBearing
```

Classes combine capabilities:

```
SavingsAccount : Account, Depositable, Withdrawable
```

---

# Relationship with Other SOLID Principles

### OCP

Incorrect hierarchies force clients to write:

```
if(type == X)
```

Which violates OCP.

Fixing LSP removes these conditionals.

---

### ISP

Large interfaces cause subclasses to implement methods they don't need.

ISP suggests **splitting interfaces**, which prevents LSP violations.

---

# Real World Examples

### Bird Problem

Bad design:

```
Bird
 ├ Sparrow
 └ Penguin
```

Parent:

```
fly()
```

Penguins cannot fly.

Better design:

```
Bird
Flyable
```

```
Sparrow : Bird, Flyable
Penguin : Bird
```

---

### Vehicle Problem

Bad design:

```
Vehicle
 ├ Car
 └ Bicycle
```

Parent:

```
startEngine()
```

Bicycles cannot start engines.

Better design:

```
Vehicle
EnginePowered
```

```
Car : Vehicle, EnginePowered
Bicycle : Vehicle
```

---

# Interview Insight

When evaluating inheritance, ask:

```
Can the child replace the parent everywhere safely?
```

If the answer is **no**, inheritance is wrong.

---

# Mental Checklist

Before creating a subclass:

```
1. Does the child support all parent behaviors?
2. Will client code behave correctly if the child replaces the parent?
3. Are we modeling identity or capability?
```

If any answer is **no**, redesign the abstraction.

---

# One-Line Summary

LSP ensures that **inheritance preserves behavior contracts**, so subclasses can safely replace their parent classes without breaking program correctness.
