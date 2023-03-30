**Note: WAP (write a program)**

## WAP to print Fibonacci Series

```python
term = int(input("Enter the term: "))

n1, n2 = 0, 1

if term < 0:
    print("Invalid term")
else:
    for i in range(term):
        print(n1)
        nth = n1 + n2
        n1 = n2
        n2 = nth
```

**Output**:
```
Enter the term: 7
0
1
1
2
3
5
8
```

## Factorial of a number

```python
n = int(input("Enter the number: "))
f = 1

for i in range(1, n + 1):
    f = f * i

print(f)
```

**Output**:
```
Enter the number: 6
720
```

## Perform `intersection()`, `union()`, `difference()`, `symmetric_difference()` on `set`

```python
set1 = {1, 5, 8, "Google", 9, 6}
set2 = {1, "Google", 6, 3, 2, 11}

i = set1.intersection(set2)
u = set1.union(set2);
d = set1.difference(set2)
s = set1.symmetric_difference(set2)

set1.clear()

print("Intersection =", i);
print("Union =", u);
print("Set Difference =", d);
print("Symmetric Difference =", s);
print("Clear Set =", set1);
```

**Output**:
```
Intersection =  {1, 'Google', 6}
Union =  {1, 2, 3, 5, 6, 8, 9, 11, 'Google'}
Set Difference =  {8, 9, 5}
Symmetric Difference =  {2, 3, 5, 8, 9, 11}
Clear Set =  set()
```

## WAP that takes the marks of 5 Subjects and displays the grade

```python
sub1 = int(input("Enter marks of subject 1: "))
sub2 = int(input("Enter marks of subject 2: "))
sub3 = int(input("Enter marks of subject 3: "))
sub4 = int(input("Enter marks of subject 4: "))
sub5 = int(input("Enter marks of subject 5: "))

total = ((sub1 + sub2 + sub3 + sub4 + sub5) / 5)
print("\nPercentage is", total)

if total > 75:
    print("Distinction")
elif total >= 65 and total < 75:
    print("First Class")
elif total >= 50 and total < 60:
    print("Second Class")
elif total >=35 and total < 50:
    print("Third Class");
else:
    print("Fail")
```

**Output**:
```
Enter marks of subject 1: 57
Enter marks of subject 2: 78
Enter marks of subject 3: 87
Enter marks of subject 4: 50
Enter marks of subject 5: 70

Percentage is 68.4
First Class
```

## Explain features of python
1. Python is easy to use and a high level programming language.
2. Python is interpreted language
3. Interactive mode
4. Free and Open Source
5. Platform independence
6. Portable
7. Object oriented language

## WAP to check whether entered character is vowel or not
```python
ch = input("Enter the character: ").lower()

if(ch == 'a' or ch == 'e' or ch == 'i' or ch == 'o' or ch == 'u'):
    print("Entered character is vowel.")
else:
    print("Entered character is not a vowel.")
```

**Output**:
```
Enter character: a
Entered character is a vowel.
```

## WAP to check number is prime or not
```python
num = int(input("Enter a number: "));

if num > 1:
    for i in range(2, num):
        if (num % i) == 0:
            print(num, "is not a prime number.")
            break;
    else:
        print(num, "is prime number.")
else:
    print(num, "is not a prime number.");
```

**Output**:
```
Enter the number: 11
11 is a prime number.
```

## WAP checks whether the number is palindrome or not.
```python
n = input("Enter number: ")
rev = n[ : :-1]

if rev == n:
    print(n, "is a palindrome.")
else:
    print(n, "is not a palindrome.")
```

**Output**:
```
Enter number: 33
33 is a palindrome.
```

## WAP to perform following operation on list
1. **max()** - Find largest number
2. **reverse()** - Find  Reverse of the list
3. **i % 2** - Select even item of the list
4. **sum()** - Sum of all item in a list

### Find largest number
```python
a = [8,2,5,1,2,4,6,11]
print("Largest number", max(a))
```

**Output**:
```
Largest number 11
```

### Reverse list
```python
a = [8,2,5,1,2,4,6,11]
a.reverse()
print("Reverse list", a)
```

**Output**:
```
Reverse list [11, 6, 4, 2, 1, 5, 2, 8]
```

### Even items
```python
a = [8,2,5,1,2,4,6,11]

for i in a:
  if (i % 2) == 0:
    print(i)
```

**Output**:
```
8
2
2
6
4
```

### Sum of all items
```python
a = [8,2,5,1,2,4,6,11]
print("Sumof all items:", sum(a))
```

**Output:**
```
Sum of all items: 39
```

## Compare list and sets
| Lists                                         | Sets                                                 |
|-----------------------------------------------|------------------------------------------------------|
| Lists are Ordered.                            | Sets are Unordered.                                  |
| Lists are Mutable.                            | Sets are mutable but only stored immutable elements. |
| Elements can be changed or replaced in Lists. | Elements cannot be changed or replaced.              |

## Describe various list functions
1. **extend()** - add  all elements of of list to the another list
2. **insert()** - insert and item from the list
3. **clear()** - removes all elements from the list
4. **copy()** - returns a copy of the list
5. **reverse()** - reverse the order of element in the list
6. **sort()** - sort the element list

**Note:** **Given below example will not come in exam. This is only for reference.**

### extend()
```python
list1 = [1, 5, 8, 9, 6]
list2 = [1, 6, 3, 2, 11]

list1.extend(list2)
print("Extend:", list1)
```

**Output:**
```
Extend: [1, 5, 8, 9, 6, 1, 6, 3, 2, 11]
```

### insert()
```python
list1 = [1, 5, 8, 9, 6]

list1.insert(3, 100)
print("Insert:", list1)
```
**Output:**
```
Insert: [1, 5, 8, 100, 9, 6]
```

### clear()

```python
list1 = [1, 5, 8, 9, 6]

list1.clear()
print("Clear:", list1)
```

**Output:**
```
Clear: []
```

### reverse()
```python
list1 = [1, 5, 8, 9, 6]

list1.reverse()
print("Reverse:", list1)
```

**Output:**
```
Reverse: [6, 9, 8, 5, 1]
```

### sort()
```python
list1 = [1, 5, 8, 9, 6]

list1.sort()
print("Sort:", list1)
```

**Output:**
```
Sort: [1, 5, 6, 8, 9]
```

## Write a program convert US Dollars to Indian Rupees.
```python
usd = float(input("Enter currency in USD: "))
inr = usd * 75
print("The currency in INR is", inr)
```

**Output**:
```
Enter currency in USD: 2
The currency in INR: 150.0
```

## Explain operator in python

An operator is Single set of special symbols that performs predefined
operations  on operators. Python provides a variety of operators, which are
described as follows.

| Name                 | Operators             |
|----------------------|-----------------------|
| Arithmetic operators | +, -, *, /, %, **, // |
| Assignment Operators | +=, =, -=, /=, //=    |
| Logical Operators    | and, or, not          |
| Bitwise Operators    | &, >>, <<, ^          |
| Membership Operators | in, not in            |
| Identity Operators   | is, is not            |

**Note:** **Given below example will not come in exam. This is only for reference.**

### Arithmetic operators
```python
num1 = int(input("Enter first number: "))
num2 = int(input("Enter second number: "))

print(num1, "+", num2, "=", num1 + num2)
print(num1, "-", num2, "=", num1 - num2)
print(num1, "*", num2, "=", num1 * num2)
print(num1, "/", num2, "=", num1 / num2)
print(num1, "%", num2, "=", num1 % num2)
print(num1, "**", num2, "=", num1 ** num2)
print(num1, "//", num2, "=", num1 // num2)
```

**Output:**
```
Enter first number: 10
Enter second number: 10
10 + 10 = 20
10 - 10 = 0
10 * 10 = 100
10 / 10 = 1.0
10 % 10 = 0
10 ** 10 = 10000000000
10 // 10 = 1
```

### Assignment Operators
```python
a = 3
b = 5

a += b

print(a)
```

**Output:**
```
8
```

### Logical Operators
```python
num1 = int(input("Enter first number: "))
num2 = int(input("Enter second number: "))

if (num1 < num2 and num1 <= num2):
    print(num1, "<", num2, "and", num1, "<=", num2)
elif (num1 > num2 or num1 >= num2):
    print(num1, ">", num2, "or", num1, ">=", num2)
elif not(num1 < num2 and num1 <=num2):
    print("Not:", num1, "<", num2, "and", num1, "<=", num2)
```

**Output:**
```
Enter first number: 10
Enter second number: 1
10 > 1 or 10 >= 1
```

### Bitwise Operators
```python
num1 = int(input("Enter first number: "))
num2 = int(input("Enter second number: "))

print(num1, "&", num2, "=", num1 & num2)
print(num1, "|", num2, "=", num1 | num2)
print(num1, "^", num2, "=", num1 ^ num2)
print(num1, ">>", num2, "=", num1 >> num2)
print(num1, "<<", num2, "=", num1 << num2)
print("~",num1, "=", ~num1)
```

**Output:**
```
Enter first number: 10
Enter second number: 10
10 & 10 = 10
10 | 10 = 10
10 ^ 10 = 0
10 >> 10 = 0
10 << 10 = 10240
~ 10 = -11
```

### Membership Operators
```python
x = ["apple", "banana"]
y = ["pineapple", "orange"]

print("apple in x:", "apple" in x)
print("pineapple not in x:", "pineapple" not in x)
```

**Output:**
```
apple in x: True
pineapple not in x: True
```

### Identity Operators
```python
x = ["apple", "banana"]
y = ["pineapple", "orange"]

print("x is y:", x is y)
print("x is not y:", x is not y)
```

**Output:**
```
x is y: False
x is not y: True
```

## Explain `continue`, `pass`, `break`, `else` with example.

### continue
The **continue **statement skips the code that comes after it, and the control
is passed back to the next iteration.

**Example**:
```
for i in range(6):
    if i == 7:
        continue
    print("The Number is:" , i)
```

**Output**:
```
The number is: 0
The number is: 1
The number is: 2
The number is: 3
The number is: 4
The number is: 5
The number is: 6
```

### pass
Python pass statement is used as a placeholder inside loops, functions, class,
if-statement that is meant to be implemented later.

**Example**:
```
a = 10
b = 20
if a < b:
  pass
else:
  print("b < a")
```

**Output**:
No output

### break
The **break** statement takes care of terminating the loop in which it is used.
If the break statement is used inside nested loops, the current loop is
terminated, and the flow will continue with the code followed that comes after
the loop.

**Example**:
```python
for i in range(4):
    for j in range(4):
        if j==2:
            break
        print("The number is", i, j)
```

**Output**:
```
This number is 0 0
This number is 0 1
This number is 1 0
This number is 1 1
This number is 2 0
This number is 2 1
This number is 3 0
This number is 3 1
```

### else
**else **statement can be combined with an if statement. An else statement
contains the block of code that executes if the conditional expression in the
if statement resolves to 0 or a FALSE value.

**Example**:
```python
num = 3
if num >= 0:
    print("Positive or Zero")
else:
    print("Negative number")
```

**Output**:
```
Positive or Zero
```

## Define dictionary explain `access`, `delete`, `update()` dictionary
Dictionary in Python is an unordered collection of data values, used to store
data values like a map, which, unlike other Data Types that hold only a single
value as an element, Dictionary holds key:value pair.

### acces
You can access the items of a dictionary by referring to its key name

**Example**:
```python
di = {"Name": "VIVA","Dept": "TYCO", "add":"Virar", "No":123}
x = di["Name"]
print(x)
```

**Output:**
```
VIVA
```

### update()
Updates the dictionary with the specified key-value pairs

**Example:**
```python
di = {"Name": "VIVA","Dept": "TYCO", "add":"Virar", "No": 123}
di.update({"No":456})
print(di)
```

**Output:**
```
{'Name': 'VIVA', 'Dept': 'TYCO', 'add': 'Virar', 'No': 456}
```

### del
The del keyword is used delete the dictionary completely

**Example:**
```python
di = {"Name": "VIVA", "Dept": "TYCO", "add":"Virar", "No": 123}
del di
print(di)
```

**Output:**
```
NameError: name 'di' is not defined
```
