# 1. Introduction and Syntax of Python Program

## 3. Enlist applications for Python programming.
Python is often used as a support language for software developers, for build
control and management, testing, and in many other ways.

## 4. What are the features of Python?
- Easy to learn and use
- Interpreted Language
- Interactive Mode
- Free and Open Source
- Cross Platform/Portable
- OOP Language

## 5. List any four editors used for Python programming.
- IDEA
- Sublime Text
- Vim
- Notepad++

## 6. 'Python programming language is interpreted an interactive' comment this sentence.
Python has two basic modes:
- Script mode
- Interactive mode

### Script mode
The normal script mode is the mode where the scripted and finished `.py` files
are run in the Python interpreter.

### Interactive mode
The interactive mode is a command line shell which gives immediate feedback for
each statement while running previously fed statements in active memory.

## 7. How to run python scripts? Explain in detail.
Open a command line and type the word python followed by the path to your script
file, like this: python `first_script.py` Hello World! Then you hit the ENTER
button from the keyboard and that's it.

## 8. What is interpreter? How it works? 9. Explain the following features of Python programming:

### (i) Simple
Python is considered one of the easiest programming languages to learn.

### (ii) Platform independent
Python is a binary platform-independent programming language. The same Python
code can run on virtually all operating systems and platforms.

### (iii) Interactive
Interactive mode is a command line shell which gives immediate feedback for each
statement, while running previously fed statements in active memory.

### (iv) Object Oriented.
Object-oriented Programming is a programming paradigm that uses objects
and classes in programming. It aims to implement real-world entities like
inheritance, polymorphisms, encapsulation, etc. in the programming.

## 12. Write in brief about characters set of Python.
The character set is a set of alphabets, letters, symbols and some special
characters that are valid in Python programming language.

### Keywords
- Python keywords are reserved word with that have special meaning and
  function.
- Keywords should not be used as variable name, constant, function name, or
  identifier in the program code.
- Example: `and`, `as`, `assert`, `break` and many more.

## 13. Write in brief about any five keywords in Python.
1. `True` - is used as the Boolean true value in Python code.
2. `False` - is used as the Boolean false value in Python code.
3. `break` - is used to break the loop.
4. `def` - is used to define the function in Python.
5. `while` - is used to make while loop in Python.

## 15. What is the role of indentation in Python?
- A code block starts with indentation and ends with first unindented line.
- The amount of indention is up to us, but it must be consistent throughout
  that block.

## 16. How to comment specific line(s) in Python program?
- Comments are created by beginning a line with hash (#) character.

## 17. What is variable? What are the rules and conventions for declaring a variables?
- A variable is like a container that stores values that we can access or
  change.
- Example:
  ```python
  name = "Jone Nuts"
  ```
- Basic rules to declare variables:
  - A variable name must start with a letter or the underscore character
  - A variable name cannot start with a number
  - A variable name can only contain alpha-numeric characters and underscores (A-z, 0-9, and _ )
  - Variable names are case-sensitive (age, Age and AGE are three different variables)

## 18. What are the various data types available in Python programming.

### Numbers
- Number data types store numeric values.
- Python 3 types of number category:
  - Integers
  - Floating Point Numbers
  - Complex Numbers

#### Integers(int)
- An int data type represents an integer number.
- An integer number is number without any decimal or fractional point.

#### Floating Point Numbers
- The float data types represents that floating point number.
- The floating point number is number that contains a decimal point.
- Example: 0.1, -3.443

#### Complex Number
- A complex number is a number that is written in the form of `a+bj`.

### Boolean
- Boolean represents the two values namely `False` and `True`.
- The true value is represented true as 1 and false as 0.

### String
- String is a collection of group of characters.
- String are identified as a contiguous set of characters enclosed in single
  quotes(' ') or double quotes(" ").
- String can also can be define with `str()` function.

## 19. What are four built-in numeric data types in Python? Explain.
The built-in numeric data types are Numbers, Integers, Float and Complex
Number.

### Numbers
- Number data types store numeric values.
- Python 3 types of number category:
  - Integers
  - Floating Point Numbers
  - Complex Numbers

### Integers(int)
- An int data type represents an integer number.
- An integer number is number without any decimal or fractional point.

### Floating Point Numbers
- The float data types represents that floating point number.
- The floating point number is number that contains a decimal point.
- Example: 0.1, -3.443

### Complex Number
- A complex number is a number that is written in the form of `a+bj`.

## 20. What is the difference between interactive mode and script mode of Python.
Python has two basic modes:
- Script mode
- Interactive mode

### Script mode
The normal script mode is the mode where the scripted and finished `.py` files
are run in the Python interpreter.

### Interactive mode
The interactive mode is a command line shell which gives immediate feedback for
each statement while running previously fed statements in active memory.

## 22. Define the following terms:

### (i) Identifier
- A Python identifier is a name given to a function, class variable, module or
  other objects that is used in Python program.
- An identifier can a combination of uppercase letters, lowercase letters,
  underscores, and digits.
- Example: `Name`, `myClass`, `Emp_Salary`, `var_1`, `_Address`

### (ii) Literal
- A literal refers to the fixed value that directly appears in the program.

### (iii) Data type
Data types are the classification or categorization of data items. It represents
the kind of value that tells what operations can be performed on a particular
data.

### (iv) Tuple
- Tuple is an ordered sequence of items same as list.
- Tuple is immutable cannot be modified unlike list.
- It is defined within parentheses () where items are separated by commas (,).
- Example:
  ```python
  a = (10, 'abc', 32)
  ```

### (v) List.
- List is an ordered sequence of items.
- In list items separated by commas (,) are enclosed within brackets [].
- List are mutable which means that value of element of a list can be altered by
  using index.
- Example:
  ```python
  first = [10, 20, 30]
  ```

## 23. Explain dictionary data tune in detail
- Dictionary is an unordered collection of key-value pairs.
- Dictionary is collection which is ordered*, changeable and do not allow
  duplicates.
- Dictionary are written with curly brackets, and have keys and values.
- Example:
  ```python
  car = { "brand": "Ford", "model": "Mustang", "year": 1264 }
  ```

## Sets
- Set items are unordered, unchangeable, and do not allow duplicate values.
- Set is defined by values separated by comma inside braces {}.
- Example:
  ```python
  a = {5, 2, 3, 1, 4}
  ```

## Difference between List, Set, Tuple, and Dictionary
|             | List                | Set                       | Tuple                        | Dictionary         |
|-------------|---------------------|---------------------------|------------------------------|--------------------|
| Mutable     | Mutable             | Mutable                   | Immutable                    | Mutable            |
| Order       | Ordered             | Unordered                 | Ordered                      | Ordered            |
| Can item be | Replaced or Changed | Can't Replaced or Changed | Can't be Replaced or Changed | Replace or Changed |

## String methods
| Operation             | Explanation                                                       | Example                                |
|-----------------------|-------------------------------------------------------------------|----------------------------------------|
| upper                 | Converts to uppercase                                             | `x.upper()`                            |
| lower                 | Converts to lowercase                                             | `x.lower()`                            |
| title                 | Capitalize the first letter of each word in a string              | `x.title()`                            |
| find, index           | Search for the target in a string.                                | `x.find("hello")`, `index("hello")`    |
| rfind, rindex         | Search for the target in a string                                 | `x.xfind("hello")`, `x.xfind("hello")` |
| replace               | Replaces the target with new string                               | `r.replace("hello", "word")`           |
| strip, rstrip, lstrip | Removes whitespace or other characters from the ends of a string. | `x.strip()`                            |
| encode                | Converts a Unicode string to a bytes object.                      | `x.encode("utf_8")`                    |

# 2. Python Operators and Control Flow Statements

## 1. What is operator? Which operators used in Python?
- An operator is a symbol which specifies a specifies a specific action.
- Operators are used to perform operations on variables and values.
- In python the operators can be unary operators or binary operator.

### Unary Operators
- Unary operators perform mathematical operation only on one operand.
- The example of unary operators are `+`, `-`, `~`.

### Binary Operators
- Binary operators are operators that require two operands to perform any
  mathematical operation.
- Example of Binary operators are `**`, `/`, `%`, `+`, `-`.

## 2. What is meant by control flow of a program?
- A program's control flow is the order in which the program's code executes.
- The control flow of a Python program is regulated by conditional statements,
  loops, and function calls.

## 3. Define the terms:

### (i) Loop
A loop statement allows us to execute a statement or group of statements
multiple times, this is called loop.
### (ii) Program
A program is a sequence of statements that have been crafted to do something.
### (iii) Operator
Unary operators perform mathematical operation only on one operand.
### (iv) Control flow.
A program's control flow is the order in which the program's code executes.

## 4. What are the different loops available in Python?
- There are 4 types of loops available in Python:
  - `while` loop
  - `for` loop
  - Nested `for` and `while` loop
  - `do..while` loop

## 5. What happens if a semicolon (;) is placed at the end of a Python statement?
In Python a semicolon works as a separated between statements and not as a
terminator of statements.

## 6. Explain about different logical operators in Python with appropriate examples.
| Operator | Description                                               | Example              |
|----------|-----------------------------------------------------------|----------------------|
| AND      | If both the values are true then condition becomes true   | (a and b) is False   |
| Or       | If any of two values are true then condition becomes true | (a or b) is True     |
| Not      | Used to reverse the local state of its value              | not(a and b) is True |

## 7. Explain about different relational operators in Python with examples.
| Operator | Name                     | Example |
|----------|--------------------------|---------|
| ==       | Equal                    | x == y  |
| !=       | Not equal                | x != y  |
| >        | Greater than             | x > y   |
| <        | Less than                | x < y   |
| >=       | Greater than or equal to | x >= y  |
| <=       | Less than or equal to    | x <= y  |

## 8. Explain about membership operators in Python.
| Operator | Description                               | Example             |
|----------|-------------------------------------------|---------------------|
| in       | True if value in list or in sequence      | ('H' in x) is True  |
| not in   | False if value not in list or in sequence | ('H' in x) is False |

## 9. Explain about Identity operators in Python with appropriate examples.
| Operator | Description                                                    | Example               |
|----------|----------------------------------------------------------------|-----------------------|
| is       | True if the variable on either side points to the same object  | (a is b) is False     |
| is not   | False if the variable on either side points to the same object | (a is not b) is False |

## 10. Explain about arithmetic operators in Python.
| Operator | Name           | Example |
|----------|----------------|---------|
| +        | Addition       | x + y   |
| -        | Subtraction    | x - y   |
| *        | Multiplication | x * y   |
| /        | Division       | x / y   |
| %        | Modulus        | x % y   |
| **       | Exponentiation | x ** y  |
| //       | Floor division | x // y  |

## 11. List different conditional statements in Python.
Python conditional statements includes:
- `if`
- `if-else`
- `nested-if`
- `if-elif-else`

## 12. What are the different nested loops available in Python?
- There are two types of nested loop `while` and `for` loop.
```python
# for loop
for i in range(1, 5):
  for j in range(1, (i+1)):
    print(j, end=' ')
  print()

# while loop
i = 1
while i < 5:
  j = 1
  while j < (i+1):
    print(j, end=' ')
    j = j + 1
  i = i + 1
  print()
```

## 13. What are the different loop control (manipulation) statements available in Python? Explain with suitable examples.
There three loop control statements available in Python:
- `break`
- `continue`
- `pass`

```python
for i in range(1, 11):
  if i%2 == 0:
    pass
  if i%3 == 0;
    continue
  if i%4 == 0;
    break
```
## 14. Explain if-else statement with an example.
- `if` statements executes when the conditions following if is true and it does
  noting when the conedition is `false`.
- The `if-else` statement takes care of a `true` as well as `false` condition.
```python
i = 20
if (i < 15):
  print("i is less then 15")
else:
  print("i is greater then 15")
```

## 15. Explain continue statement with an example.
The continue statement in Python returns the control to the beginning of the
while loop.
```python
i = 0
while i < 10:
  i = i + 1
  if i == 5:
    continue
```

## 16. Explain use of break statement in a loop with example.
The `break` statement in Python terminates the current loop and resumes
ececution at next statement.
```python
i = 0
while i<10:
  i=i+1
  if i == 5:
    break
  print("i = ", i)
```

## 17. Predict output and justify your answer:

### (i) -11 % 9
```
>>> print(-11 % 9)
-2
```

### (ii) 7.7 // 7
```
>>> print(7.7 // 7)
1.0
```

### (iii) (200 - 70) * 10 / 5
```
>>> print((200 - 70) * 10 / 5)
260.0

```

### (iv) 5 * 1 ** 2
```
>>> print(5 * 1 ** 2)
5
```

## 18. What the difference is between == and is operator in Python?
- `=` - if the values of operands are equal, then the condition becomes true.
- `is` - return true, if the variables on either side of  the operator point to
  same object.

## 19. List different operators in Python, in the order of their precedence.
| Operators            | Example   |
|----------------------|-----------|
| Arithmetic Operators | a + b     |
| Assignment Operators | c = a + b |
| Comparison Operators | a == b    |
| Logical Operators    | a and b   |
| Bitwise Operators    | a & b     |
| Identity Operators   | a = 3     |
| Membership Operators | a in b    |

## 20. Write a Python program to print factorial of a number. Take input from user.
## 21. Write a Python program to calculate area of triangle and circle and print the result.
## 22. Write a Python program to check whether a string is palindrome.
## 23. Write a Python program to print Fibonacci series up to n terms.
```python
num = int(input("Enter a num: "))
x = 0
y = 1

if num < 0:
  print("Invalid term")
else:
  for i in range(num):
    print(x)
    z = x + y
    x = y
    y = z
```
O/P
```
Enter a num: 3
0
1
1
```

## 24. Write a Python program to print all prime numbers less than 256.
```python
num = int(input("Enter number: ")
for n in range(2, num):
  if n % 1 == 0:
    break
  else:
    print(n)
```

## 25. Write a Python program to find the best of two test average marks out of three test's mark accepted from the user.

## Assignment Operator
| Operator | Example | Same As    |
|----------|---------|------------|
| =        | x = 5   | x = 5      |
| +=       | x += 3  | x = x + 3  |
| -=       | x -= 3  | x = x - 3  |
| *=       | x *= 3  | x = x * 3  |
| /=       | x /= 3  | x = x / 3  |
| %=       | x %= 3  | x = x % 3  |
| //=      | x //= 3 | x = x // 3 |
| **=      | x **= 3 | x = x ** 3 |
| &=       | x &= 3  | x = x & 3  |
| \|=      | x \|= 3 | x = x \| 3 |
| ^=       | x ^= 3  | x = x ^ 3  |
| >>=      | x >>= 3 | x = x >> 3 |
| <<=      | x <<= 3 | x = x << 3 |

## Relational or Comparison Operators
| Operator | Name                     | Example |
|----------|--------------------------|---------|
| ==       | Equal                    | x == y  |
| !=       | Not equal                | x != y  |
| >        | Greater than             | x > y   |
| <        | Less than                | x < y   |
| >=       | Greater than or equal to | x >= y  |
| <=       | Less than or equal to    | x <= y  |

## Bitwise Operators
| Operator | Name                 | Description                                                                                             |
|----------|----------------------|---------------------------------------------------------------------------------------------------------|
| &        | AND                  | Sets each bit to 1 if both bits are 1                                                                   |
| \|       | OR                   | Sets each bit to 1 if one of two bits is 1                                                              |
|  ^       | XOR                  | Sets each bit to 1 if only one of two bits is 1                                                         |
| ~        | NOT                  | Inverts all the bits                                                                                    |
| <<       | Zero fill left shift | Shift left by pushing zeros in from the right and let the leftmost bits fall off                        |
| >>       | Signed right shift   | Shift right by pushing copies of the leftmost bit in from the left, and let the rightmost bits fall off |

# 3. Data Structures in Python

## 1. What is data structure? Which data structure used by Python?
- A data structure is specialized format for organizing and storing data, so
  that various operations can be performed on it easily.
- Python use data structure like list, tuple, dictionary.

## 2. How to define and access the elements of list?
- A list is created by placing all the items inside a square brackets [],
  separated by commas.
- Example of define the list:
  ```python
  li = ["Hello", 50]
  ```
- To access values in lists, use the square brackets for slicing along with the
  index or indices to obtain value available at that index.
  ```python
  li = ["Hello", 50]
  print(li[1])
  ```
  O/P
  ```
  50
  ```

## 3. What is list? How to create list?
- List are used to store multiple items in single variable.
- List are created using square brackets.
- Example:
  ```python
  li = ["Hello" , 50]
  ```

## 4. What are the different operation that can be performed on a list? Explain with examples
- `append()` - is used to add elements at the end of the list.
- `extend()` - is used to add more then one element at the end of the list.
- `insert()` - can add an element at a given position in the list.
- `remove()` - is used to remove an element form the list.
- `pop()` - can remove an element from any position in the list.
- `reverse()` - is used to reverse the element of the list.
- `len()` - returns the length of the list.
- `min()` - returns the minimum value in the list.
- `max()` - returns the maximum value in the list.
- `count()` - returns the number of occurrence of given element in the list.
- `index()` - returns the position of the first occurrence.
- `sort()` - sorts the list.
- `clear()` - erases all the elements.
- **slice** - is used to print a section of the list.
- **concatenate** - is used to merge two lists and return a single list.
- **multiply** - the list *n* times.
Example:
```python
li = ["Hello", "World"]
li.append("Bye")
li.extend(["World", "Forever"])
li.insert(0, "Bye")
li.remove("World")
li.pop(0)
li.reverse()
len(li)
max(li)
li.count("o")
li.index("Forever")
li.sort()
li.clear()
```
O/P
```
['Hello', 'World']
['Hello', 'World', 'Bye']
['Hello', 'World', 'Bye', 'World', 'Forever']
['Bye', 'Hello', 'World', 'Bye', 'World', 'Forever']
['Bye', 'Hello', 'Bye', 'World', 'Forever']
['Hello', 'Bye', 'World', 'Forever']
['Forever', 'World', 'Bye', 'Hello']
4
World
0
0
['Bye', 'Forever', 'Hello', 'World']
[]
```

## 5. Explain any two methods under lists in Python with examples.

### `append()`
- Is used to add elements at the end of the list.
- Syntax:
  ```python
  list.append(item)
  ```
- Example:
  ```python
  li = ["Hello", 30]
  li.append("World")
  print(li)
  ```
  O/P
  ```
  ["Hello", 30, "World"]
  ```

### `extend()`
- Is used to add more then one element at the end of the list.
- Syntax:
  ```python
  list.extend(list2)
  ```
- Example:
  ```python
  li = ["Hello", "World"]
  li2 = ["What's", "Up"]
  li.extend(li2)
  print(li)
  ```
  O/P
  ```
  ["Hello", "World", "What's", "Up"]
  ```

## 6. Write a python program to describe different ways of deleting an element form the given List.
`remove()` - is used to remove an element form the list.
```python
li = ["Hello", "World"]
li.remove("Hello")
print(li)
```
O/P
```
World
```

## 7. What is tuple in Python? How to create and access it?
- Tuple is an ordered sequence of items same as list.
- Tuple is immutable cannot be modified unlike list.
- It is defined within parentheses () where items are separated by commas (,).
- To access values in tuple, use the square brackets[].
- Example:
  ```python
  a = (10, 'abc', 32)
  print(a[0])
  ```
  O/P
  ```
  10
  ```

## 8. What are mutable and immutable types?
- **Mutable** - is when something is changeable or has the ability to change.
- **Immutable** - when no change is possible over time.

## 9. Is tuple mutable? Demonstrate any two methods of tuple.
- Tuple is immutable that means it can't be changed or replace.
- `max()` - Returns item from the tuple with max value.
- `min()` Return item from the tuple with min value.
```python
a = (10, 32, 3)
max(a)
min(a)
```
O/P
```
10
3
```

## 10. Write in brief about Tuple in Python. Write operations with suitable examples
- Tuple is an ordered sequence of items same as list.
- Tuple is immutable cannot be modified unlike list.
- It is defined within parentheses () where items are separated by commas (,).
- To access values in tuple, use the square brackets[].

### Tuple Operations
- We can use + operator to combine two tuples.
- We can also repeat elements by using the * operator.
- We can test if an item exist in tuple or not.
- Iteration over a tuple specifies the way.

```python
t1 = (1, 2)
t2 = (3, 4)

print(t1 + t2)
print(t1 * 2)
print(1 in t1)

for t in t1:
  print(t)
```
O/P
```
(1, 2, 3, 4)
(1, 2, 1, 2)
True
1
2
```

## 11. Write in brief about Set in Python. Write operations with suitable example.
- Set items are unordered, unchangeable, and do not allow duplicate values.
- Set is defined by values separated by comma inside braces {}.
- To access values in set, use the square brackets[].
```python
a = {5, 2, 3, 1, 4}
a[1]
```

## 12. Explain the properties of dictionary keys.
- Dictionary values have no restrictions.
- They can be any arbitrary Python object, either standard objects or
  user-defined objects.
- However, same is not true for the keys, more then one entry per key not
  allowed.

## 13. Explain directory methods in Python.
- `clear()` - removes all the elements from the dictionary.
- `copy()` - returns a copy of the dictionary.
- `fromkeys()` - the `fromkeys()` method creates a new dictionary with default
  value or all specified keys.
- `gets()` - returns the value of the specified key.
- `item()` - returns a list containing a tuple for each key value pair.
- `keys()` - returns a list containing the dictionary's keys.
- `pop()` - removes the element with the specified key.
- `popitem()` - removes the last inserted key-value pair.
- `setdefault()` - returns the value of the specified key.
- `update()` - Updates the dictionary with the specified key.
- `values()` - returns a list of all the values in the dictionary.

## 14. How to create directory in Python? Give example.
- Dictionary are written with curly brackets, and have keys and values.
```python
d = { "name": "Jone", "age": 30 }
print(d)
```
O/P
```
{ "name": "Jone", "age": 30 }
```

## 15. Write in brief about Dictionary in Python. Write operation with suitable examples.
- Dictionary is an unordered collection of key-value pairs.
- Dictionary is collection which is ordered*, changeable and do not allow
  duplicates.
- Dictionary are written with curly brackets, and have keys and values.
- Example:
  ```python
  car = { "brand": "Ford", "model": "Mustang", "year": 1264 }
  ```

### Operation of Dictionary
```python
d = { "brand": "Ford", "model": "Mustang", "year": 1264 }
print("brand" in d)

for i in d:
  print(i, d[i])
```
O/P
```
True
brand Ford
model Mustang
year 1264
```

## 16. What is the significant difference between list and dictionary?

### List
- List is collection of index values pairs.
- List is created by placing elements in [] separated by commas ",".
- We can access the elements using the index value.
- List are mutable.
- List is created using `list()` function.

### Dictionary
- Dictionary is collection of key-value pairs.
- All key-value go inside brackets{} separated by a comma.
- The keys in dictionary are of any given data type.
- We can access the elements using the keys.
- Dictionaries are mutable, but keys don't allow duplicates.
- Dictionary object is created using `dict()` function.

## 17. Compare List and Tuple.

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

## 19. How append() and extend() are different with reference to list in Python?

### `append()`
- Append uses `.append()` to add element at end of the list.
- Syntax:
  ```python
  list.append("hello")
  ```
- Example:
  ```python
  li = ["hello", "world"]
  li.append("bye")
  print(li)
  ```
  O/P
  ```
  ["hello", "world", "bye"]
  ```

### `extend()`
- Extend uses `.extend()` to add multiple elements to the list.
- Syntax:
  ```python
  list.extend(["hello", "world"])
  ```
- Example:
  ```python
  li = ["hello", "world"]
  li.extend(["bye", "world"]
  print(li)
  ```
  O/P
  ```
  ["hello", "world", "bye", "world"]
  ```

## 20. Write a program to input any two tuples and interchange the tuple variable.
```python
a = 1
b = 2
(a, b) = (b, a)
print("a =", a, "b =", b)
```
O/P
```
a = 2 b = 1
```
## 21. Write a Python program to multiply two matrices
## 22. Write a Python code to get the following dictionary as output: `{1:1, 3:9, 5:25, 7:49, 9:81}`
```python
di = {1:1, 3:9, 5:25, 7:49, 9:81}
print(di)
```
O/P
```
{1:1, 3:9, 5:25, 7:49, 9:81}
```
## 23. Write the output for the following:
```
>>>a=[1,2,3]
>>>b=[4,5,6]
>>>c=a+b
[1, 2, 3, 4, 5, 6]
>>>[1,2,3]*3
[1, 2, 3, 1, 2, 3, 1, 2, 3]
>>>t=['a', 'b', 'c', 'd', 'e', 'f']
>>>t[1:3]=['x', 'y']
>>>print(t)
['a', 'x', 'y', 'd', 'e', 'f']
```
## 24. Give the output of Python code:
```
Str="Maharashtra State Board of Technical Education'
print(x[15::1])
print(x[-10:-1:2])
```
O/P
```
te Board of Technical Education
 dcto
```

## 25. Give the output of following Python code:
```
t=(1,2,3, (4,), [5,6])
print(t[3])
t[4][0]=7
print(t)
```
O/P
```
(4,)
(1, 2, 3, (4,), [7, 6])
```
## 26. Write the output for the following if the variable fruit="banana":
```
>>>fruit[:3]    o/p='ban'
>>>fruit[3:]    o/p='ana'
>>>fruit[3:3]   o/p=' '
>>>fruit[:]     o/p='banana'
```

## 27. What is string? How to create it? Enlist various operations on strings.
- String is a collection of group of characters.
- String are identified as a contiguous set of characters enclosed in single
  quotes(' ') or double quotes(" ").
- String can also can be define with `str()` function.

```python
s1 = "Hello World"

print(s1[0])         # String indices and accessing string
print("Hello" in s1) # 'in' and 'not in' operator
print(s1[1:])        # String slicing
print(s1>"Hello")    # String comparison
```
O/P
```
H
True
ello World
True
```

# 5. Object Oriented Programming in Python
## 1. What is OOP?
## 2. List the features and explain about different Object Oriented features supported by Python.
## 3. List and explain built in class attributes with example.
## 4. Design a class that store the information of student and display the same.
## 5. What are basic overloading methods?
## 6. What is method overriding? Write an example.
## 7. Explain class inheritance in Python with an example.
## 8. How to declare a constructor method in python? Explain.
## 9. How operator overloading can be implemented in Python? Give an example.
## 10. Write a Python program to implement the concept of inheritance.
## 11. Create a class employee with data members: name, department and salary. Create suitable methods for reading and printing employee information.
## 12. What is data abstraction? Explain in detail. 13. Define the following terms:
### (1) Object
### (ii) Class
### (iii) Inheritance
### (iv) Data abstraction.
## 14. Describe the term composition classes with example.
## 15. Explain customization via inheritance specializing inherited methods.

# 6. File I/O Handling and Exception Handling

## 1. What is file? Enlist types of files in Python programming.
- File is a named location on disk to store related information.
- It is used to permanently store data in a volatile memory.
- Files are divided into following two categories:
  1. Text Files
  2. Binary files

### Text Files
- Text files are simple texts in human readable format.
- A text file is structured as sequence of lines of text.

### Binary Files
- Binary files have binary data which is understood by the computer.

## 2. What is exception?
An exception is also called as runtime error that can halt the execution of the
program.

## 3. Explain the term exception handling in detail.
- Python provides a Exception handling for handling any unreported errors in
  program.
- By handling the exception, we can provide a meaning full message to the user
  about the problem.

## 4. Explain different modes of opening a file.
| Mode | Description                                                                                                        |
|------|--------------------------------------------------------------------------------------------------------------------|
| r    | Opens a file for reading.                                                                                          |
| w    | Opens a file for writing.                                                                                          |
| x    | Opens a file for exclusive creation. If the file already exists, the operation fails.                              |
| a    | Opens a file for appending at the end of the file without truncating it.  Creates a new file if it does not exist. |
| t    | Opens in text mode.                                                                                                |
| b    | Opens in binary mode.                                                                                              |
| +    | Opens a file for updating (reading and writing)                                                                    |

## 5. Write the syntax of `fopen()` with example.
- Syntax:
  ```python
  f = open("filename", "modes")
  ```
- Example:
  ```python
  o = open("text.txt", "w")
  o.write("Hello World")
  o.close()

  o = open("text.txt", "r")
  print(o.read())
  o.close()
  ```
  O/P
  ```
  Hello World
  ```

## 6. What are various modes of file object? Explain any five as them.
| Mode | Description                                                                           |
|------|---------------------------------------------------------------------------------------|
| r    | Opens a file for reading.                                                             |
| w    | Opens a file for writing.                                                             |
| x    | Opens a file for exclusive creation. If the file already exists, the operation fails. |

## 7. Explain exception handling with example using try, except, raise keywords.
- Exception handling for handling any unreported errors in program.
- By handling the exception, we can provide a meaningful message to the user
  about the problem rather then system generated error message.
```python
age = int(input("Enter your age: "))

try:
  if age < 18:
    raise Exception;
except Exception:
  print("You are not 18")

```
O/P
```
Enter your age: 16
You are not 18
```
