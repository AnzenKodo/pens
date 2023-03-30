# Python

## a) Name different modes of Python.
Python has two basic modes:
1. Script mode (or Normal mode)
  - The mode where the scripted and finished .py files are in the Python
  Interpreter.
  2. Interactive mode
  - A command line shell which gives immediate feedback for each statement,
  while running previously fed statements in active memory.

## b) List identity Operators

| Operator | Description                                        | Example    |
|----------|----------------------------------------------------|------------|
| is       | Returns `True` if both variables are sames object  | x is y     |
| is not   | Returns `False` if both variables are sames object | x is not y |

## c) Give two differences between list and tuple.
### List
- Lists are mutable.
- The list is better for performing operations.
- Lists consume more memory.
- More likely error will occur.

### Tuple
- Tuples are immutable.
- The implication of iterations is faster.
- Tuple consume less memory.
- Less likely error will occur.

## d) Explain Local and Global variable.
| Local                                                                                                      | Global                                                                                            |
|------------------------------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------|
| It is declare  inside a function                                                                           | It is declared outside the function                                                               |
| It is created when the function starts execution and lost when the function terminate.                     | It is created before the program's global execution starts and lost when the program terminates.  |
| Local variables can be accessed with the help of statements, inside a function in which they are declared. | You can access global variables by any statement in the program.                                  |
| Parameters passing is required for local variables to access the value in other function.                  | Parameters passing is not necessary for a global variable as it is visible throughout the program |

## e) Define class and object in python.
### Class
- Class is a blueprint for the object.
- We define a class by using the keyword class.
- Class objects are used to access different attributes.
### Object
- Classes are the user-defined blueprints that help us create an “object”.
- Objects are the instances of a particular class.
- Every other element in Python will be an object of some class, such as the string, dictionary, number(10,40), etc.

## f) How to give single and multiline comment in python.
### Single-Line
- Add the hash (#) symbol before the comment:
```python
# This is your comment
```
### Multiline
-Python will ignore string literals that are not assigned to a variable, you can add a multiline string (triple quotes) in your code, and place your comment inside it:
```python
"""
This is a comment
written in
more than just one line
"""
```

## g) List different modes of opening file in python.
There are four different methods modes for opening a file:
- **r** - *Read* - Opens a file for reading. Error if the file does not exist.
- **w** - *Write* - Opens a file for writing. Creates the file if it does not
  exist.
- **x** - *Create* - Creates the specified file. Error if file exist.
- **a** - *Append* - Opens a file for appending. Creates the if it does not
	exist.

In addition, the file should be handled as binary or text mode:
- t - **Text** - Default value - *Text mode*.
- b - Binary - Binary mode (e.g. images).

## a) Write a program to print following:
```python
rows = int(input("Enter number of rows: "))

for i in range(rows):
    for j in range(i+1):
        print(j+1, end=" ")
    print("\n")
```

## b) Explain four Buit-in tuple functions python with example.
- `len()` - Returns the **length** of the tuple.
- `max()` - Highest value will returned.
- `min()` - Lowest value be returned.
- `count()` - Returns the number of times a specified value occurs in tuple.

## Explain how to use user defined function in python with example.
In Python, a user-defined function's declaration begins with the keyword def and followed by the function name.
```python
def printt():
    print("This is Python 3.2 Tutorial")
    print("This is Python 3.2 Tutorial")
    print("This is Python 3.2 Tutorial")
printt()
```
Output:
```
This is Python 3.2 Tutorial
This is Python 3.2 Tutorial
This is Python 3.2 Tutorial
```

## d) Write a program to create class EMPLOYEE with ID and NAME and display its contents.
```python
class Employee:
	name = ""
	department = ""
	salary = 0

	def setData(self):
		self.name = input("Enter Name: ")
		self.department = input("Enter Department: ")
		self.salary = int(input("Enter Salary: "))

	def showData(self):
		print("Name:", self.name)
		print("Department:", self.department)
		print("Salary:", self.salary)

e = Employee()
e.setData()
e.showData()
```
Output:
```
Enter Name: Jonney
Enter Department: Testing
Enter Salary: 20000
Name: Jonney
Department: Testing
Salary: 20000
```

## List Data types used in python. Explain any two with example.
Thare are three data type in python numbers, string & boolean.
### String
- String is a collection of group of characters.
- String are identified as a contiguous set of characters enclosed in single quotes(' ') or double quotes(" ").
- String can also can be define with str() function.
### Boolean
- Boolean represents the two values namely False and True.
- The true value is represented true as 1 and false as 0.

## b) Explain membership and assignment operators with example.
| Operator | Description                               | Example             |
|----------|-------------------------------------------|---------------------|
| in       | True if value in list or in sequence      | ('H' in x) is True  |
| not in   | False if value not in list or in sequence | ('H' in x) is False |

| Operator |                                                       Description                                                       | Syntax      |
|----------|:-----------------------------------------------------------------------------------------------------------------------:|-------------|
|     =    | Assign value of right side of expression to left side operand                                                           | x = y + z   |
|    +=    | Add and Assign: Add right side operand with left side operand and then assign to left operand                           | a += b      |
|    -=    | Subtract AND: Subtract right operand from left operand and then assign to left operand: True if both operands are equal | a -= b      |
|    *=    | Multiply AND: Multiply right operand with left operand and then assign to left operand                                  | a *= b      |

## c) Explain indexing and slicing in list with example.
- “Indexing” means referring to an element of an iterable by its position within the iterable.
- “Slicing” means getting a subset of elements from an iterable based on their indices.

## d) Write a program for importing module for addition and substraction of two numbers.
```python
a = int(input("Enter first number: "))
b = int( input("Enter second number: "))
Sum = a+b; #Add two numbers
Difference = a-b; #Subtract two numbers
# To print the result
print("Addition of two numbers = ",Sum)
print("Subtraction of two numbers = ",Difference)
```
Output:
```
Output:
Enter first number: 30
Enter second number: 20
Addition of two numbers = 50
Subtraction of two numbers = 10
```

## a) Write a program to create dictionary of students that includes their ROLL NO. and NAME:
i) Add three students in above dictionary
ii) Update name= 'Shreyas' of ROLL NO = 2
iii) Delete information of ROLL NO = 1
```python
students = {
  1: "ronney",
  2: "jay"
}

students[2] = "Shreyas"
del students[1]
print(students)
```
Output:
```
{ 2: "Shreyas" }
```

## b) Explain decision making statements If-else, if-elif-else with example.
The if…elif…else statement is used in Python for decision making.
```python
num = 3.4

if num > 0:
    print("Positive number")
elif num == 0:
    print("Zero")
else:
    print("Negative number")
```

## c) Explain use of format () method with example.
Python format() function has been introduced for handling complex string formatting more efficiently.
```python
txt = "I have {an:.2f} Ruppes!"
print(txt.format(an = 4))
```
Output:
```
I have 4.00 Ruppes!
```

## d) Explain building blocks of python.
- The core data structures to learn in Python are List (list), Dictionary (dict), Tuple (tuple), and Set (set).
- To indicate a block of code in Python, you must indent each line of the block by the same amount.

## e) Write a program illustrating use of user defined package in python.
Packages are a way of structuring many packages and modules which helps in a well-organized hierarchy of data set, making the directories and modules easy to access.

file1.py:
```python
class Bmw:
    # First we create a constructor for this class
    # and add members to it, here models
    def __init__(self):
        self.models = ['i8', 'x1', 'x5', 'x6']

    # A normal print function
    def outModels(self):
        print('These are the available models for BMW')
        for model in self.models:
            print('\t%s ' % model)
```
file2.py
```python
from Bmw import Bmw
```

## Write the output of the following:
```
>>> a = [2, 5, 1, 3, 6, 9, 7]
>>> a[2:6] = [2, 4, 9, 0]
>>> print (a)
```
Ans:
```
[2, 5, 2, 4, 9, 0, 7]
```
```
b = ["Hello", "Good"]
b.append("python")
print (b)
```
Ans:
```
['Hello', 'Good', 'python']
```
```
t1 = [3, 5, 6, 7]
print (t1[2])
print (t1[-1])
print (t1[2:])
print(t1[:])
```
Ans:
```
6
7
[6, 7]
[3, 5, 6, 7]
```

## Explain method overloading in python with example.
- overloading is the ability of a function or an operator to behave in different ways based on the parameters that are passed to the function, or the operands that the operator acts on.
```python
class A:
    def __init__(self, a):
        self.a = a

    # adding two objects
    def __add__(self, o):
        return self.a + o.a
ob1 = A(1)
ob2 = A(2)
ob3 = A("Geeks")
ob4 = A("For")

print(ob1 + ob2)
print(ob3 + ob4)
```

## Write a program to open a file in write mode and some contents at the end of file.
```python
o = open("name.txt", "w")
o.write("I am a programmer")
o.close()
o = open("name.txt", "r")
print(o.read())
o.close()
```
O/P
```
I am a programmer
```

## a) Explain package Numpy with example.
- Numpy is a python package which stands for "Numerical Python".
```python
import numpy as n
a=n.ones((3, 3))
a[1:-1,1:-1]=0
print(a)
```
Output:
```
[[1. 1. 1.]
 [1. 0. 1.]
 [1. 1. 1.]]
```

## 6) Write a program to implement the concept of inheritance in python.
```python
class Parent:
	parentname = ""
	childname = ""
	def show_parent(self):
		print(self.parentname)

class Child(Parent):
	def show_child(self):
		print(self.childname)

c = Child()
c.parentname = "Arati"
c.childname = "Purva"
c.show_parent()
c.show_child()
```

## c) Explain Try-except block used in exception handling in python with example.
- When an exception occurs, Python will normally stop and generate an error message.
- These exceptions can be handled using the try statement.
- The except block lets you handle the error.
```python
try:
  print(x)
except NameError:
  print("Variable x is not defined")
```
