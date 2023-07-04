## 1. Explain the difference between declarative and imperative programming paradigm.

### Imperative Programing

Imperative programming consists of sets of detailed instructions that are given
to the computer to execute in a given order. It's called "imperative" because as
programmers we dictate exactly what the computer has to do, in a very specific
way.

```js
const nums = [1, 4, 3, 6, 7, 8, 9, 2];
const result = [];

for (let i = 0; i < nums.length; i++) {
  if (nums[i] > 5) result.push(nums[i]);
}

console.log(result); // Output: [ 6, 7, 8, 9 ]
```

### Declarative Programming

Declarative programming is all about hiding away complexity and bringing
programming languages closer to human language and thinking. It's the direct
opposite of imperative programming in the sense that the programmer doesn't give
instructions about how the computer should execute the task, but rather on what
result is needed.

```js
const nums = [1, 4, 3, 6, 7, 8, 9, 2];

console.log(nums.filter((num) => num > 5)); // Output: [ 6, 7, 8, 9 ]
```

## 2. Explain

Reference: https://youtu.be/fnZjrNfQVdo

### Names

Identifiers that allow us to refer to variables, constants, functions, types,
operations, and so on.

### Bindings

An association of a name with an object

### Scopes

The lifetime of a binding of a name to an object

**Example:**

```js
function x() {
  let y = "Hello World"; // Y is only avaiable inside x() scope
  return y;
}
console.log(x());
// "Hello World"
```

#### Static Scope

Scope of a variable determined at compile time.

#### Dynamic Scope

Scope of variable determined at runtime.

## 3. Explain different storage allocation mechanisms.

Reference:
[Storage allocation | Static, Stack& Heap | Compiler Design | Lec- 49](https://www.youtube.com/watch?v=nZG0bQYHB9U)

There are three types:

1. Static stroage allocation
2. Stack storage allocation
3. Heap storage allocation

### 1. Static stroage allocation

- In static allocation, names are bond to **storage locations**.
- If memory is created at compile time then the memory will be creted in static
  area adn only once.
- Static allocation supports the **dynamic data structure** that means, memory
  is created only at comple time and deallocated after program completion.
- The drawback with static storage allocation is that the size and position of
  data objects should be know at compile time.
- Another drawback is restriction of the recursion proccess.
- Example in JavaScript:
  ```js
  // Declare a variable with the "const" keyword
  const x = 10;

  // Access the value of the variable
  console.log(x); // Output: 10

  // Attempt to reassign the value of the variable
  x = 20;

  // This will throw an error because the value of a const variable cannot be changed
  ```

### 2. Stack storage allocation

- In this storage is organized as a **stack**(LIFO).
- Activation records are pushed and popped.
- Activation record contains the locals so that they are bound to fresh storage
  in each activation record.
- The value of local is deleted when the activation ends.
- It works on the basis of **LIFO** and this allocation supports the recursion
  process.
- Example in JavaScript:
  ```js
  function foo(x) {
    // Declare a local variable y
    let y = x + 1;

    // Access the value of the local variable
    console.log(y); // Output: x + 1

    // Reassign the value of the local variable
    y = x + 2;

    // The value of the local variable can be changed
    console.log(y); // Output: x + 2
  }

  // Call the function with an argument
  foo(10);
  ```

### 3. Heap storage allocation

- It is the most flexible allocation scheme.
- It is flexible because it is dynamica nature.
- Allocation and deallocation of memory can be done at any time and at any place
  depending upon the users requirement.
- Advantage of Heap allocation is used to allocate memory to the variables
  dynamically and when the variables are no more used then claim it back.
- Heap storage allocation supports teh recursion process.
- Example in JavaScript:
  ```js
  // Create a new object using the object literal notation
  let obj = {};

  // Add a property to the object
  obj.name = "John";

  // Access the value of the property
  console.log(obj.name); // Output: "John"

  // Reassign the value of the property
  obj.name = "Jane";

  // The value of the property can be changed
  console.log(obj.name); // Output: "Jane"
  ```

## 4. What is Lambda Calculus? Explain Free variable and Bound variable.

Lambda calculus is a formal system that is used to define and study functions
and their properties. It consists of three main elements: variables, functions,
and application.

- **Variables** are symbols that represent values. In lambda calculus, variables
  are denoted by a single lowercase letter, such as x or y.
- **Functions** are expressions that take one or more arguments and return a
  result. In lambda calculus, functions are denoted by the Greek letter "lambda"
  (λ), followed by a list of variables (the function's arguments), and a body
  expression (the function's result). For example, the function f(x, y) = x + y
  could be written as λx.λy.x + y in lambda calculus.
- **Application** is the process of applying a function to its arguments. In
  lambda calculus, application is denoted by placing the function expression and
  its arguments within parentheses, separated by spaces. For example, the
  application f(x, y) could be written as (f x y) in lambda calculus.

### Free variable

In lambda calculus, a free variable is a variable that is not bound to any
particular value or function. It can be used freely within an expression, and
its value is not determined until the expression is evaluated.

Example:

```
(λx.x + y) 2
```

### Bound variable.

A bound variable, on the other hand, is a variable that is bound to a particular
value or function within an expression. It cannot be used freely, and its value
is determined by the binding.

Example:

```
(λx.x + y) (λy.y * 2)
```

## 5. Different between

### Functional Programming

- Functional programming is the form of programming that attempts to avoid
  changing state and mutable data.
- In a functional program, the output of a function should always be the same,
  given the same exact inputs to the function.
- This is because the outputs of a function in functional programming purely
  relies on arguments of the function, and there is no magic that is happening
  behind the scenes.
- It works particularly well when there are no boundaries required, or those
  boundaries are already predefined.
- Functional programming provides the advantages like efficiency, lazy
  evaluation, nested functions, bug-free code, parallel programming.
- Each small function does its part and only its part.
- The function can be easily invoked and reused at any point. It also helps the
  code to be managed and the same thing or statements does not need to be
  written again and again.
- Example: if you call function getSum() it calculates the sum of two inputs and
  returns the sum. Given the same inputs for x and y, we will always get the
  same output for sum.

### Object Oriented Programming(OOP).

- Object oriented programming is a programming paradigm in which you program
  using objects to represent things you are programming about (sometimes real
  world things).
- The objects hold data about them in attributes.
- The attributes in the objects are manipulated through methods or functions
  that are given to the object.
- Example:
  - We might have a Person object that represents all of the data a person would
    have: weight, height, skin color, hair color, hair length, and so on.
  - Those would be the attributes.
  - Then the person object would also have things that it can do such as: pick
    box up, put box down, eat, sleep, etc.
  - These would be the functions that play with the data the object stores.
- The main deal with OOP is the ability to encapsulate data from outsiders.
  Encapsulation is the ability to hide variables within the class from outside
  access — which makes it great for security reasons, along with leaky, unwanted
  or accidental usage.

## 6. What is higher order function?

Higher-order functions are functions that either accept other functions as
arguments, or return a function as a result.

The result of one higher-order function can be used as the input to another
higher-order function. Any time we pass a lambda expression to a method, that
method is a higher-order function.

A higher order function (HOF) is a function that follows at least one of the
following conditions −

- Takes on or more functions as argument
- Returns a function as its result

### Example:

```js
function add(x) {
  return function (y) {
    return x + y;
  };
}

const addTwo = add(2);
console.log(addTwo(3)); // Output: 5
console.log(addTwo(4)); // Output: 6
```

The add function is a higher-order function because it takes a function as an
argument (in this case, the anonymous function that returns x + y) and returns a
function as a result (the addTwo function). The addTwo function is a closure,
which is a function that references variables from its outer scope. In this
case, the addTwo function closes over the variable x, which is set to 2. When
the addTwo function is called with an argument, it adds that argument to the
value of x and returns the result.

Higher-order functions are a powerful tool in functional programming, and are
widely used in many programming languages. They allow you to create flexible,
reusable code, and can make your programs more expressive and easier to
understand.

## 7. Difference between

### Normal Evaluation

Normal order evaluation, also known as call-by-name, is a evaluation strategy
that evaluates the arguments to a function before the function itself. This
means that the arguments are evaluated every time they are used within the
function, rather than being evaluated once before the function is called.

Example in Python:

```python
from functools import partial

def foo(x, y):
  print("x =", x)
  print("y =", y)
  return x + y

def bar(x):
  print("x =", x)
  return x * 2

lazy_bar = partial(bar, eval=lambda: bar(1))

print(foo(lazy_bar(), lazy_bar()))  # Output: x = 1, x = 1, y = 2, 3
```

### Application order evaluation

Application order evaluation, also known as call-by-value, is a evaluation
strategy that evaluates the function before the arguments. This means that the
arguments are evaluated once before the function is called, and the resulting
values are passed to the function as inputs.

Example in Python:

```python
def foo(x, y):
  print("x =", x)
  print("y =", y)
  return x + y

def bar(x):
  print("x =", x)
  return x * 2

print(foo(bar(1), bar(2)))  # Output: x = 1, x = 2, x = 2, y = 4, 6
print(foo(bar(2), bar(1)))  # Output: x = 2, x = 1, x = 1, y = 2, 4
```

## 8. What is paradigm and programming paradigm?

Programming paradigms are different ways or styles in which a given program or
programming language can be organized. Each paradigm consists of certain
structures, features, and opinions about how common programming problems should
be tackled.

There are several types of programming paradigms, including:

1. Imperative
2. Functional
3. Object-oriented
4. Logic
5. Event-driven
6. Procedural
7. Aspect-oriented

### Imperative Programing

Imperative programming consists of sets of detailed instructions that are given
to the computer to execute in a given order. It's called "imperative" because as
programmers we dictate exactly what the computer has to do, in a very specific
way.

```js
const nums = [1, 4, 3, 6, 7, 8, 9, 2];
const result = [];

for (let i = 0; i < nums.length; i++) {
  if (nums[i] > 5) result.push(nums[i]);
}

console.log(result); // Output: [ 6, 7, 8, 9 ]
```

### Declarative Programming

Declarative programming is all about hiding away complexity and bringing
programming languages closer to human language and thinking. It's the direct
opposite of imperative programming in the sense that the programmer doesn't give
instructions about how the computer should execute the task, but rather on what
result is needed.

```js
const nums = [1, 4, 3, 6, 7, 8, 9, 2];

console.log(nums.filter((num) => num > 5)); // Output: [ 6, 7, 8, 9 ]
```

### Functional Programing

Functional programming takes the concept of functions a little bit further.

In functional programming, functions are treated as first-class citizens,
meaning that they can be assigned to variables, passed as arguments, and
returned from other functions.

A pure function is one that relies only on its inputs to generate its result.
And given the same input, it will always produce the same result.

```js
const nums = [1, 4, 3, 6, 7, 8, 9, 2];

function filterNums() {
  const result = []; // Internal variable

  for (let i = 0; i < nums.length; i++) {
    if (nums[i] > 5) result.push(nums[i]);
  }

  return result;
}

console.log(filterNums()); // Output: [ 6, 7, 8, 9 ]
```

### Object-oriented Programing

The core concept of OOP is to separate concerns into entities which are coded as
objects. Each entity will group a given set of information (properties) and
actions (methods) that can be performed by the entity.

## 9. What is calling sequence?

The code sequence required to effect transfer of control to a subroutine or
procedure, including parameter passing and the recording of the return address.
Uniformity of calling sequences is vital if it is required to call procedures
written in a different language from the calling program.

## 10. What is parameter passing?

- Reference: [Parameter Passing – Real Python](https://youtu.be/fnZjrNfQVdo)
- A function is a self-contained block of code that encapsulates a specific task
  or related group of tasks.
- An argument(s) is a value(s) provided to a function to customize its behavior
  from one call to the next.
- A parameter (or parameter variable) is a variable in the function definition
  to store an argument.

### Example

- To pass an argument to a function is to provide that argument's value to the
  appropriate parameter variable.

  ```python
  def square(num):
    return num * num

  val = 4
  print(square(val))
  # 16
  ```
  The argument `4` is passed to the function `square`
  - `num` is given the vale `4` since that was the value of `val` when `square`
    was called.
- Never wolud we consider modifyin the value of `num` in this function.
