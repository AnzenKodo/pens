## Write a php program to find the largest number among three numbers.

```php
<?php
  function largest($x, $y, $z) {
    if ($x >= $y) {
      if($x >= $z) {
        echo $x;
      } else {
        echo $z;
      }
    }
    else {
      if($y >= $z) {
        echo $y;
      } else {
        echo $z;
      }
    }
  }

  largest(100, 50, 25);
?>
```

**Output:**
```
100
```

## Write a php code for creating a basic image.

```php
<?php
$image = imagecreatetruecolor(500, 300);
imagefilledrectangle($image, 20, 20, 480, 280);
header("Content-type: image/png");
imagepng($image);
?>
```

## Explain inheritance with examples.

In Inheritance  the new class can inherit the properties and methods from the
old class.

The old class is the base class also called a parent class and then the new
class is a derived  class also called a subclass.

**Example**:

```php
<?php
  class Person {
    var $name, $age;
  }
  class Employee extends Person {
    var $salary, $designation;
  }
?>
```

## Explain the concept of introspection in php with an example.

PHP Introspection is the ability of a program to examine an object's
characteristics such as its name, parent class (if any), properties and methods.

Introspection  in PHP offers a useful Ability  to examine classes' interfaces
properties methods. With introspection we can write  code that operates on any
object or class.

**Example**:

```php
<?php
  if (class_exists('MyClass')) {
    $myclass = new MyClass();
  }
?>
```

##  How to use overloading and overriding functions in php?

## Overloading

Method overloading is the ability to create a multiple function
of the same name with a different implementation  depending upon the types of
arguments.

How to use overloading in PHP?


```php
<?php
class First {
  function func() {
    echo "Hello World";
  }
}

class Second extends First {
  function func() {
    echo "Bye World";
  }
}

$o = new Second;
$o->func();
```
O/P
```
Bye World
```


## Overriding

In function overriding, both parent and child classes should have the same
function name with and number of arguments. It is used to replace the parent
method in child class.

```php
<?php
<?php
class First {
  function func() {
    echo "Hello World";
  }
}

class Second extends First {
  function func() {
    echo "Bye World";
  }
}

$f = new First;
$s = new Second;
$f->func();
$s->func();
```

**Output:**

```
Hello World
Bye World
```

## How to use the flip function in php.

The array_flip function flips/All keys with their associated values in array.

This function is very useful when we have a big/ large array.and we want to
know if a given value  is in the array.

**Syntax**:

```
array_flip(array_name)
```

**Example:**

```php
<?php
  $a = array("a");
  print_r(array_flip($a));  //flip function is used
?>
```

**Output:**

```
Array( [0]=> a )
```

## How to define properties and methods of a class? Explain with suitable examples.
1. Objects have access to special variables called. properties.
2. A property Can be valued as an array and even another object.
3. All properties go inside the curly braces.
4. The characteristics of a class are known as its properties.

**Example:**

```php
<?php
  class Student {
    var $roll_no;
    var $name;
    function display() {
      echo "Roll No: " . $this->roll_no. "<br>";
      echo "Name: " $this->name;
    }
  }

  $s1 = new Student;
  $s1->roll_no = 10;
  $s1->name = "Amar";
  $si->display();
?>
```

**Output:**

```
Roll No: 10
Name: Amar
```

A class method is exactly similar to PHP functions.

1.  Method is a function defined within the class.
2.  Methods on the other hand are functions that operate on the data.
3.  Method is also written within the braces {}.

The method can be accessed from outside the class.

**Example:**

```php
<?php
class Person {
	public $age = 25;

	public function printAge() {
		echo "The age is: $this->age";
	}
}

$person = new Person;
$person->age = 20;
$person->printAge();
?>
```

**Output:**

```
The age is: 20
```



## Explain the arithmetic operators that can be used in php with examples.

The PHP arithmetic operators are used with numeric values to perform common
arithmetical operations, such as addition, subtraction, multiplication etc.

**Example:**

```php
<?php
  $a = 42;
  $b = 20;

  $c = $a + $b;
  echo "Addition is: $c <br/>";
  $c = $a - $b;
  echo "Subtraction is: $c <br/>";
  $c = $a * $b;
  echo "Multiplication is: $c <br/>";
  $c = $a / $b;
  echo "Division is: $c <br/>";
  $c = $a % $b;
  echo "Modulus is: $c <br/>";
?>
```

**Output:**

```
Addition is: 62
Subtraction is: 22
Multiplication is: 840
Division is: 2.1
Modulus is: 2
```

## What is the use of anonymous functions in php? Explain with examples.

Anonymous functions, also known as closures, allow the creation of functions
which have no specified name. They are most useful as the value of callable
parameters, but they have many other uses.
```php
<?php
$func = function () { echo "Hello World"; };
$func();
```
O/P
```
Hello World
```

## Explain cloning objects with examples.

Object cloning is the process in PHP to create a copy of an object. An object
copy is created by using the clone keyword when the object is cloned PHP will
perform Shallow copy  of all the object properties and properties that are
referenced to their variables will remain references.

**Example:**

```php
<?php
class Obj {
  public $name;
}

$o = new Obj;
$c = clone $o;

$o->name = "Jonney";
$c->name = "Jone";

echo "Origenal: ".$o->name.", Clone: ".$c->name;
?>
```
O/P
```
Origenal: Jonney, Clone: Jone
```

## Explain indexed and associative arrays with examples.

Indexed array: An array having only integer keys is typically referred to as an
indexed array and index arrays can store numbers, drinks and any object but
their index will be represented by number.

**Example:**

```php
<?php
  $colors = array("Red");
  print_r($colors);
?>
```
**Output:**
```
Array ( [0] => Red )
```

The associative arrays are very similar to numeric arrays in terms of
functionality but they are different in terms of their index. Associative arrays
will have their index as string so that you can establish a strong association
between key and values.

```php
<?php
  $ages = array( "Peter"=>22 );
  print_r($ages);
?>
```

**Output:**

```
Array ( [Peter] => 22 )
```

## How to define constructor and destructor in php with an example?

- **constructor** - When we create a new object it is useful to initialize its
  properties.
- **destructor** - The destructor method will be called as soon as there are no
  other references to a particular object.
```php
<?php
class Obj {
  function __construct() {
    echo "Class created";
  }

  function __destruct() {
    echo "Class destroyed";
  }
}

$o = new Obj;
?>
```
O/P
```
Class Created
Class Destroyed
```

## Explain the following string function with an example.
1. strpos()
2. strlen()
3. strcmp()
4. str_word_count()
5. strpos()

- **strpos()** - Returns the position of the first occurrence of a string.
- **strlen()** - Returns the length of a string.
- **strcmp()** - Compares two strings.
- **str_word_count()** - Count the number of words in a string.
- **strrpos()** - Finds the position of the last occurrence of a string.
```php
<?php
echo strpos("Hello World", "Hello");
echo strlen("Hello World");
echo strcmp("Hello World", "Hello World");
echo str_word_count("Hello World");
echo strrpos("Hello World", "Hello");
```
O/P
```
0
11
0
2
0
```

## Write a program using a foreach loop.

**Example:**
```php
<?php
$a = array(1, 2, 3, 4, 5);
foreach ($a as $n) {
  echo $n;
}
```
O/P
```
12345
```

## Explain serialization with suitable examples.

A string representation of any object in the form of byte-stream is obtained by
serialize() function in PHP. All property variables of the object are contained
in the string and methods are not saved. This string can be stored in any file.

**Example:**
```php
<?php
echo serialize(array("Red"));
?>
```
O/P
```
a:1:{i:0;s:3:"Red";}
```

## Define `imagecolorallocate()` function along with suitable examples.

`imagecolorallocate()` function is another inbuilt PHP function mainly used to
implement a new color to an image. It returns the color of an image in an RGB
format (RED GREEN BLUE).

**Example:**

```php
<?php
  $im = imagecreate(100, 100);
  // sets background to red
  $background = imagecolorallocate($im, 255, 0, 0);
  // sets some colors
  $white = imagecolorallocate($im, 255, 255, 255);
  $black = imagecolorallocate($im, 0, 0, 0);
  // hexadecimal way
  $white = imagecolorallocate($im, 0xFF, 0xFF, 0xFF);
  $black = imagecolorallocate($im, 0x00, 0x00, 0x00);
?>
```

## Write a program to create a filled rectangle.
```php
<?php
$image = imagecreatetruecolor(500, 300);
imagefilledrectangle($image, 20, 20, 480, 280);
header("Content-type: image/png");
imagepng($image);
?>
```

## Explain any three data types used in php.

1. **Integer:** integer data type used to specify a numeric value  without a fractional component the range of integers.
2. **Strings:** a string is a sequence of characters where characters are the same as a byte.
3. **Boolean:**   boolean  value can be either true or false both are  case-insensitive.

## Differentiate between implode and explode function.
| No.   | Implode                                                                                                                                                         | Explode                                                                                                                                                                     |
| ----- | --------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 1     | The implode() function returns a string from the elements of an array.                                                                                          | explode function breaks a string  into smaller parts and stores it  as an array.                                                                                            |
| 2     | The implode() function accepts its  parameters in either order.  However, for consistency with explode(),  you should use the documented order of  arguments.   | The explode() function splits  these strings based on a specific  delimiter and returns an array that  contains elements which are sustained  by the splitting operation.   |
| 3     | syntax :-string implode (pieces)                                                                                                                                | array explode (delimiter, string, limit)                                                                                                                                    |
| 4     | **Example**:  ```php <?php $arr = array("I", "love", "PHP."); $pole = implode(" ", $arr); \ echo "$pole"; ?> ```  Output: I love PHP.                           | Example: <?php  $string = "I love php."; $pole = explode(" ", $string); \ \ print_r($pole); ?>  Output: Array ( [0] => I [1] => love [2] => php. )                          |

## State the variable function. Explain it with an example.

PHP supports the concept of variable function means that we can call a function
based on a value of a variable if a variable name has a round parentheses
appended to it PHP will look for a function with the same name as a whatever
variable Evaluates to and will attempt to execute it.

**Example:**
```php
<?php
  function add($x, $y){
    echo $x + $y;
  }
  $var =  "add";
  $var(10,20);
?>
```

**Output:**
```
30
```
