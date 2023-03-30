# Python practical question bank solved

## 1) WAP to create 3x3 matrix with 1 at the border and zero inside.
```python
import numpy as n
a=n.ones((3, 3))
a[1:-1,1:-1]=0
print(a)
```
Output
```
[[1. 1. 1.]
 [1. 0. 1.]
 [1. 1. 1.]]
```

## 2) WAP to calculate area of circle and area of rectangle using abstract class.
```python
from abc import ABC, abstractmethod
class test(ABC):
    @abstractmethod
    def area(self):
        pass
class Rec(test):
    def area(self):
        self. l=4
        self. b=2
        print(self.l*self.b)
class Cir(test):
    def area(self):
        self.r=5
        print(3.14*self.r*self.r)
R=Rec()
R. area()
C=Cir()
C. area()
```
Output
```
8
78.5
```
## 3) WAP to create dictionary where key is 1 to 10 and value is square of 1 to 10.
```python
a=dict()
for i in range(1,11):
    a[i]=i**2
print(a)
```
Output
`{1: 1, 2: 4, 3: 9, 4: 16, 5: 25, 6: 36, 7: 49, 8: 64, 9: 81, 10: 100}`

## 4) WAP to display result using inheritance.
```python
class Student:
    def accept(self):
        self. name=input("Name:")
class Test:
    def marks(self):
        self. m1=int(input("M1:"))
        self. m2=int(input("M2:"))
class Result(Student, Test):
    def total(self):
        self. t=self.m1+self.m2
    def disp(self):
        print(self.name)
        print(self.t)
r=Result()
r. accept()
r. marks()
r. total()
r. disp()
```
Output
```
Name:ramesh
M1:80
M2:70
ramesh
150
```
## 5) WAP to remove duplicates from dictionary.
```python
d={1:20, 1:20, 2:30}
res={}
for x, y in d. items() :
    if y not in d. items() :
        res[x]=y
print(res)
```
Output
`{1: 20, 2: 30}`

## 6) WAP to print sum of entered no. using function with arbitrary argument arguments.
```python
def sum(*x):
    n=0
    for i in x:
        n+=i
    print(n)
sum(1, 2,3,4,5)
```

Output
`15`

`fibonacci.py`
```python
def fib(n):
  n1, n2= 0,1
  for i in range(n):
    print(n1)
    nth=n1+n2
    n1=n2
    n2=nth
```
`fib.py`
```python
import fibonacci
print(fibonacci.fib(5))
```
To run the code, run `fib.py` file.

## 8) WAP to print following pattern.
```
***
**
*
```
```python
for i in range(4, 0, -1):
    for j in range(0, i-1):
        print(“*”, end= ‘ ’)
    print(" ")
```

## 9) WAP to print distinction, first class, second, third class and fail using if else.
```python
s1=int(input("English:"))
s2=int(input("Hindi:"))
s3=int(input("Marathi:"))
s4=int(input("Maths:"))
s5=int(input("Science:"))
a=(s1+s2+s3+s4+s5)/5
if a>=90:
    print("Distinction")
elif a>=75 and a<90:
    print("First class")
elif a>=45 and a<75:
    print("Second class")
elif a>=35 and a<45:
    print("Third class")
else:
    print("Failed")
```

Output
```
English:70
Hindi:80
Marathi:90
Maths:80
Science:70
First class
```
## 10) WAP to calculate area of circle and rectangle using method overriding.
```python
class Rec:
    def area(self):
        self. l=4
        self. b=2
        print("Area of rectangle=",self.l*self.b)
class Cir:
    def area(self):
        self. r=3.5
        print("Area of circle=",3.14*self.r*self.r)
r=Rec()
r. area()
c=Cir()
c. area()
```
Output
```
Area of rectangle= 8
Area of circle= 38.465
```

## 11) Check entered password is correct or not using user defined exception.

```python
class WrongPasswordException(Exception):
  pass
p=input("Enter password:")
try:
  if p!='abc12':
    raise WrongPasswordException
except WrongPasswordException:
  print("Incorrect password!")
else:
  print("Correct password!")
```
Output
```
Enter password:abc12
Correct password!
```
## 12) Create list and perform following operations.
1. print elements using for loop
2. del elements 3,4
3. del 4 and add 'o','n' 'a'
4. acces element 'd' from orignal list
5. find len of list

### 1.print elements using for loop
```python=
li = ['a','n','a','c',['o','n','d'],'a']
for i in li:
    print(i)
```
Output
```
a
n
a
c
['o', 'n', 'd']
a
```
### 2. del elements 3,4
### 3. del 4 and add 'o','n' 'a'
### 4. acces element 'd' from orignal list
### 5. find len of list
```python=
li = ['a','n','a','c',['o','n','d'],'a']
print("The length of list is: ", len(li))
```
Output
`The length of list is:  6`

## 13) WAP using numpy to generate six random integers between 20-30.
```python=
import numpy as n
a=n.random.randint(20,30,6)
print(a)
```
Output
`[24 27 29 25 22 22]`

## 14) WAP to concatenate dictionaries to create new one.
```python
d1={1:10}
d2={2:20}
d3={3:30}
d4={}
for i in d1, d2, d3:
    d4. update(i)
print(d4)
```
Output
`{1: 10, 2: 20, 3: 30}`

## 15) WAP to print unique values of following dict.
```python
d={1:10, 2:20, 3:30, 4:30}
d={1:10, 2:20, 3:30, 4:30}
u=set()
for i in d:
    for val in d.values() :
        u. add(val)
print(u)
```
Output
`{10, 20, 30}`

## 16) Create 3x4 matrix filled with 10-21.
```python
import numpy as n
a=n.arange(10,22).reshape((3,4))
print(a)
```
Output
```
[[10 11 12 13]
 [14 15 16 17]
 [18 19 20 21]]
```
## 17) WAP to create class Emp having data members name, salary use constructor to accept values and display information.
``` python
class Emp:
    def __init__(self, name, salary):
        self. name=name
        self. salary=salary
    def disp(self):
        print("Name:",self.name)
        print("Salary:",self.salary)
e=Emp("Abc",10000)
e. disp()
```
Output
```
Name: Abc
Salary: 10000
```
