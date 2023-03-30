# Python QB UT 2

## 1. Explain scope of a variable in Python.
- A variable is only available from inside the region it is created.
- This is called scope.
- There are two types of scopes in Python:

### Local scope
- A variable created inside a function belongs to the local scope, and can only
  be used inside that function.
- Example
  ```python
  def fun()
    x=10 # X is local variable
    print(x)

  fun()
  ```
  O/P
  ```
  10
  ```

### Global scope
- A variable created in the main body of the code is a global variable and
  belongs to the global scope.
- Global variables are available from within any scope global and local.
- Example:
  ```python
  a = 50 # a is global variable
  def fun()
    print(a)

  fun()
  print(a)
  ```
  O/P
  ```
  50
  50
  ```

## 2. Define class, data hiding, method overloading, inheritance, data abstraction, numpy, pandas.

### i) `class`
- Class is a blueprint for the object.
- We define a class by using the keyword class.
- Class objects are used to access different attributes.

### ii) Data Hiding
- Data hiding is one of the important features of Object Oriented Programming
  which allows preventing the functions of a program to access directly the
  internal representation of a class type.

### iii) Method Overloading
- Overloading is the ability of a function or an operator to behave in different
  ways based on the parameters that are passed to the function, or the operands
  that the operator acts on.

### iv) Inheritance
- Inheritance refers to defining a new class with little or no modification to
  an existing class.
- The new class is called as derived or child class and the old class is called
  as base or parent class.

### v) Data Abstraction
- Data abstraction refers to providing only essential information about the data
  to the outside world and hiding the background details.

### vi) Numpy
- Numpy is a python package which stands for "Numerical Python".

### vii) Pandas
- Pandas is an open source library that allows to perform data manipulation.
- Pandas library is built on the top of Numpy.

## 3. Explain Composition classes with program.
- Composition class is composed of one of or more instance of other classes.
- In simple words, one class is container and other class is content, if we
  delete the container objects then all of its contents objects are also
  deleted.
  ```python
  class test:
    def __init__(self, name, marks):
      self.name = name
      self.marks = marks

  class addr:
    def __init__(self, ad, name, marks):
      self.ad = ad
      self.ob = test(name, marks)

    def disp(self):
      print(self.ad, self.ob.name, self.ob.marks)

  t = addr("Virar", "ABC", 99)
  t.disp()
  ```
  O/P
  ```
  Virar ABC 99
  ```
## 4. WAP to create a file, write some contents in it and read the content from file.
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

## 5. WAP to check `ZeroDivisionError` Exception.
```python
x = int (input("x:"))
y = int(input("y:"))

try:
  x/y
except ZeroDivisionError:
  print("Error: Division by Zero")
else:
  print(x/y)
```
O/P
```
x: 0
y: 0

Error: Divison by Zero
```

## 6. WAP to throw an exception if age<18 (using raise).
```python
age = int(input("Age:"))
try:
  if age < 18:
    raise Exception
except Exception:
  print("Too small to vote!!")
else:
  print("You can vote!!")
```

## 7. List different modes of opening file.
Following are the different modes of opening file:
- `r`
- `rb`
- `r+`
- `rb+`
- `w`
- `wb`
- `wb`
- `w+`
- `wb+`

## 8. WAP to create class animal having method feed that prints 'I eat food'. It has a sub class herbivorous having method feed that prints "I eat only plants". Call the method by creating an object of each of the classes.
```python
class animal:
  def feed(self):
    print("I eat food")

class herbivorous(animal):
  def feed(self):
    print("I eat only plants")

a = animal()
a.feed()
h = herbivorous()
h.feed()
```

## 9. WAP to create base classes namely add, mul having method addition and multiplication that prints addition and multiplication respectively. Derive a class derived from add and mul that has method divide and returns division. Create object and call methods.
```python
class add:
  def addition(self, a, b):
    self.a = a
    self.b = b
    print(self.a + self.b)

class mul:
  def multiplication(self, a, b):
    self.a = a
    self.b = b
    print(self.a * self.b)

class derived(add, mul):
  def divide(self, a, b)
    self.a = a
    self.b = b
    return self.a / self.b

d = derived()
print(d.divide(28, 4))
d.multiplication(2, 4)
d.addition(5, 6)
```
O/P
```
7.0
8
11
```

## 10. WAP to implement multilevel inheritance.
```python
class Student:
  def accept(self):
    self.roll = 10

class Test(Student):
  def getdata(self):
    self.name = "ABC"

class Result(Test):
  def info(self):
    self.marks = 99
  def disp(self):
    print(self.roll, self.name, self.marks)

r = result()
r.accept()
r.getdata()
r.info()
r.disp()
```
O/P
```
10 ABC 99
```

## 11. Create a 3x4 matrix of random values using numpy and perform following:
1. print type of array
2. print dimension
3. print shape
4. print size
5. print type of elements
6. sort row wise
7. print min, max, sum, flatten
```python
import numpy as n

p = n.random.randint(30, size = (3, 3))
print(p)
print(type(p))
print(p.ndim)
print(p.shape)
print(p.size)
print(n.dtype)
print(n.sort(p))
pritt(p.min())
print(p.max())
print(sum(p))
print(p.flatten())
```
O/P
```
[[10, 20, 21]
 [14, 15, 13]
 [23, 24, 29]]
<class 'numpy.ndarray'>
2
(3, 3)
9
int64
[[10, 20, 21]
 [13, 14, 15]
 [23, 24, 29]]
10
29
[51 42 76]
[10 20 21 14 15 13 23 24 29]
```
## 12. WAP that accepts a string and calculate the number of upper and lower case letters (string="Viva College)
```python
c = input("Enter string.")
u = 0
i = 0

for i in c:
  if (i.isupper()):
    u += 1
  if (i.islower()):
    i += 1

print("Upper case letters are", u)
print("Lower case letters are", i)
```

## 13. WAP to generate a random float where the value is between 5 and 50
```python
import random
a = random.uiform(5, 50)
print(a)
```
O/P
```
20.80854522266047
```

## 14. Plot a line from position (10, 33) to position (80, 65) with following:
1. marker - 0
2. line-dotted, line color-red
3. x-label: student, y-label marks.
4. Add grid lines
```python
import matplotlib.pylot as p
import numpy as n

x = n.array([10, 33])
y = n.array([80, 64])

p.xlabel("Student")
p.ylable("Marks")
p.plot(x, y, marker = 'o', linestyle = 'dotted', color = 'r')
p.grid()
p.show()
```

## 15. WAP to print 3x3 matrix with o at border and I inside.
```python
import numpy as n
a = n.zeros((3, 3))
a[1:-1, 1:-1] = 1
print(a)
```
O/P
```
[[0. 0. 0.]
 [0. 1. 0.]
 [0. 0. 0.]]
```

## 16. WAP to create matrix with values 2-10.
```python
import numbpy as n
a = n.arange(2, 11).reshape(3, 3)
print(a)
```
O/P
```
[[2 3 4]
 [5 6 7]
 [8 9 10]]
```

## 17. Explain Exception Handling in python.
- When we executes a Python program, there may be a few uncertain conditions
  which occur, known as errors. Errors also referred to as bugs that are
  incorrect or inaccurate action that may cause the problems in the running of
  the program of program or may interrupt the execution of program.
- There are three types of error:
  - i) Compile Time Errors.
  - ii) Run Time Errors.
  - iii) Logical Errors.
- Errors occured at runtime are known as exception. Exception handling is a
  feature that is used for handling any unreported errors in program.
- By handling the exceptions, we can provide a meaningful message to the user
  about the problem rather than system generated error message, which may not be
  understandable to the user.
- Exception can be either built-in exception or user defined exceptions.
