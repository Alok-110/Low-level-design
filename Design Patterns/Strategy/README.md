# Strategy Design Pattern

## Definition

The Strategy Pattern defines a family of algorithms, encapsulates each one, and makes them interchangeable.
It allows the behavior of a class to be selected at runtime.

Instead of implementing different behaviors using conditionals (`if-else` or `switch`), the behavior is moved into separate classes called **strategies**.

---

# Problem

Suppose we design robots with different abilities.

Robots may have different behaviors such as:

* walking
* talking
* flying

If we use inheritance to represent every combination of behavior, the class hierarchy quickly becomes complex.

Example of bad design:

```
Robot
 ├── WalkRobot
 ├── FlyRobot
 ├── WalkAndTalkRobot
 ├── WalkTalkFlyRobot
 ├── FlyTalkRobot
 ...
```

As new behaviors are added, the number of classes increases rapidly.

This leads to:

* large inheritance trees
* duplicated code
* difficult maintenance

---

# Solution

Extract behaviors into separate classes and compose them into the main object.

Instead of hardcoding behavior inside the class, delegate it to a **strategy object**.

Example structure:

```
Robot
 ├── WalkStrategy
 ├── TalkStrategy
 └── FlyStrategy
```

Each behavior can now be changed independently.

---

# UML Structure

```
Client
   |
   v
Context
   |
   v
Strategy (interface)
   |
   ├── ConcreteStrategyA
   ├── ConcreteStrategyB
   └── ConcreteStrategyC
```

### Components

**Client**

* Chooses which strategy to use

**Context**

* Holds a reference to the strategy
* Delegates the work to the strategy

**Strategy**

* Defines the common interface for algorithms

**Concrete Strategy**

* Implements a specific algorithm

---

# Example (Robot System)

Strategies:

```
WalkableRobot
 ├── NormalWalk
 └── NoWalk
```

```
TalkableRobot
 ├── NormalTalk
 └── NoTalk
```

```
FlyableRobot
 ├── NormalFly
 └── NoFly
```

Robot contains these strategies:

```
Robot
 ├── WalkableRobot* walkBehaviour
 ├── TalkableRobot* talkBehaviour
 └── FlyableRobot* flyBehaviour
```

The robot delegates actions to the strategies.

Example flow:

```
Robot robot(
    NormalWalk,
    NormalTalk,
    NoFly
)

robot.walk() → NormalWalk.walk()
robot.talk() → NormalTalk.talk()
robot.fly()  → NoFly.fly()
```

---

# Benefits

### Eliminates large conditional statements

Bad design:

```
if(type == WALK)
if(type == FLY)
if(type == TALK)
```

Strategy replaces this with polymorphism.

---

### Open/Closed Principle

New behaviors can be added without modifying existing code.

Example:

```
class JetpackFly : public FlyableRobot
```

No existing class needs modification.

---

### Behavior can change at runtime

```
robot.setFlyStrategy(new JetpackFly())
```

---

### Promotes composition over inheritance

Behavior is composed rather than inherited.

---

# When to Use

Use the Strategy Pattern when:

* a class has multiple possible behaviors
* algorithms may change frequently
* conditional logic becomes complex
* behavior should be interchangeable

Examples:

* payment methods (card, UPI, PayPal)
* sorting algorithms
* compression algorithms
* game character abilities
* navigation routes

---

# Drawbacks

* increases number of classes
* client must know which strategy to choose
* slightly more complex structure

---

# Key Principles Used

Strategy pattern relies heavily on:

* **Open/Closed Principle**
* **Dependency Inversion Principle**
* **Composition over Inheritance**

---

# Key Idea

Instead of a class implementing many behaviors itself, it **delegates behavior to interchangeable strategy objects**.
