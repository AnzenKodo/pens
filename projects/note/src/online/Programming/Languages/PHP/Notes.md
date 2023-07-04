# 1. Expressions and Control Statements in PHP

## 1. What is web application?
- A Web application is a computer software or program that performs some
  specific tasks at its client by using a Web browser.
- The Web-based applications are also known as Web apps.
- Web applications are usually based on the client-server architecture where
  the client input/request data while the server stores and responds with
  result.

## 3. What is PHP?
- PHP is a widely used open source language that is specifically used for web
  application development and can be embedded within HTML.
- PHP is a server-side scripting language that is used in Web based
  applications.
- PHP is a general-purpose programming language originally designed for web
  application development. PHP is a recursive. acronym for "PHP: Hypertext
  Preprocessor".

## 4. Enlist features of PHP.
- **Web Application Features** - PHP is a programming language support most
  commonly used Web application features like HTTP Cookie, Session, File
  Upload, etc.
- **CLI (Command Line Interface)** - PHP is commonly used to write Web
  applications to be integrated to Web servers using the Common Gateway
  Interface (CGI).
- **Built-in Modules** - The standard PHP build comes with many free and open
  source libraries included as built-in modules.
- **Object-Oriented Programming (OOP)** - PHP supports object-oriented
  programming features like object.
- **Pre-Compilation** - PHP Web applications are usually deployed in source
  code, which will be interpreted on-the-fly when Web requests arrive to the
  server.
- **Real Time Access Monitoring** - PHP provides access logging by creating the
  summary of recent accesses for the user.
- **File I/O** - PHP supports most commonly used file I/O features like local
  file and path management, remote resource access using Internet protocols
  like HTTP and FTP.

## 5. What is variable? How to declare it? Explain with example.
- PHP variables are nothing but a named storage locations in the memory.
- A variable is a named container in a PHP script in which a data value can be
  stored.
- A variable starts with the ($) sign, followed by the name of the variable.
- **Syntax** - $var
```php
$var = "Hello World";
echo $var;
```
O/P
```
Hello World
```

## 6. Explain constants in PHP with example.
- A PHP script is executed on the server, and the plain HTML result is sent
  back to the browser.
- A PHP script can be placed anywhere in the document. A PHP programming script
  starts with `<?php` and ends with `?>`.
- The default file extension for PHP files is ".php".
- A PHP file normally contains HTML tags and some PHP scripting code.
```php
<?phh
  $var = "Hello World"
  echo $var;
?>
```
O/P
```
Hello World
```

## 7. What are the decision statements used by PHP?
### `if` statement
```php
<?php
$x = -12;

if ($x > 0) {
  echo "The number is positive";
}

else{
  echo "The number is negative";
}
?>
```
O/P
```
The number is negative
```

### `if else` statement
```php
<?php
$x = "August";

if ($x == "January") {
  echo "Happy Republic Day";
} elseif ($x == "August") {
  echo "Happy Independence Day!!!";
} else {
  echo "Nothing to show";
}
?>
```
O/P
```
Happy Independence Day!!!
```

### Nested `if` statement
```php
<?php
$a = 10;
$b = 20;

if ($a == 10) {
  if ($b == $20) {
      echo "The addiotion is: ".($a + b);
  }
}
?>
```
O/P
```
The addition is 30
```
### `switch case` statement
```php
<?php
$n = "Monday";

switch($n) {
  case "Monday":
    echo "Its Monday";
    break;
  case "Tuesday":
    echo "Its Tuesday";
    break;
  case "Wednesday":
    echo "Its Wednesday";
    break;
  case "Thuesday":
    echo "Its Thuesday";
    break;
  case "Friday":
    echo "Its Friday";
    break;
  case "Saturday":
    echo "Its Saturday";
    break;
  case "Sunday":
    echo "Its Suday";
    break;
  default:
    echo "Doesn't exist";
}
?>
```
O/P
```
Its Monday
```
## 8. Describe loops in PHP.

### `while` statement
```php
<?php
$num = 0;

while ($num <= 10) {
  echo $num;
  $num++;
}
?>
```
O/P
```
012345678910
```

### `do while` statement
```php
<?php
$x = 1;

do {
  echo "The number is: $x <br>";
  $x++;
} while ($x <= 5);
?>
```
O/P
```
The number is: 1
The number is: 2
The number is: 3
The number is: 4
The number is: 5
```

### `for` loop
```php
<?php
for ($i = 1; $i <= 10; $i++) {
  echo $i." ";
}
?>
```
O/P
```
1 2 3 4 5 6 7 8 9 10
```

## 10. Define the term expressions with example.
- An expression is a piece of code that evaluates to a value.
- A value a number, a string of text, or a Boolean.
- An expression is a combination of values, variables, operators, and functions
  that results in a value.
- Like `$z = $x+$y`, where `$x + $y` is the expression.

## 11. Describe data types in PHP in detail.
- A data type is defined as, "a set of values and the allowable operations on
  those values".
- The data type determines the operations that we can perform on it.
- PHP supports eight primitive types:
  - Four Scalar Types:
    - **Integer** - The integer data type is used to specify a numeric value.
    - **Float** - Floating point numbers are real numbers, representing numeric
      values with decimal digits.
    - **String** - A string is a sequence of characters where a character is
      the same as a byte.
    - **Boolean** - .Boolean value can be either TRUE value or FALSE value.
  - Two Compound Types:
    - **Array** - An array stores group of values under single variable name.
    - **Object** - PHP supports Object Oriented Programming (OOP).
  - Two Special Types:
    - **Resource** - The resource is a special PHP data type that refers to
      external resource (e.g. file, image etc.).
    - **Null** - The null value represents a variable that has no value.

## 12. Explain variable scope in PHP.
- Scope of variable is an area or part of program in which it is
  accessible/visible.
- There are two type of scope in PHP:
  - **Local Scope** - A variable which is declared inside the function is
    called as local variable.
  - **Global Scope** - Variables declared outside function are by default
    global variables and can accessed from any part of program.
```php
<?php
$a = "Hello" // Global Scope

function func() {
  $b = "World"; // Local scope
}
```

## 13. Write the difference between break and continue statement of PHP with example.

### `break`
- You have already seen the break statement used in an earlier chapter of this
  tutorial. It was used to "jump out" of a switch statement.
- The break statement can also be used to jump out of a loop.
```php
<?php
for ($x = 0; $x < 10; $x++) {
  if ($x == 4) {
    break;
  }
  echo $x." ";
}
?>
```
O/P
```
0 1 2 3
```

### `continue`
- The continue statement breaks one iteration (in the loop), if a specified
  condition occurs, and continues with the next iteration in the loop.
```php
<?php
for ($x = 0; $x < 10; $x++) {
  if ($x == 4) {
    continue;
  }
  echo $x." ";
}
?>
```
O/P
```
0 1 2 3 5 6 7 8 9
```

## 16. Find output:
```php
<?php
  $a= "9 Lives." -1;
  var_dump($a);
?>
```
## 17. Find the output.
```php
<?php
  $str = "welcome";
  echo "You are $str";
?>
```
O/P
```
You are welcome
```

## 18. Write program to find a area of rectangle.
```php
<?php
 $length = 14;
 $width = 12;
 echo "area of rectangle is $length * $width= " . ($length * $width) . "<br />";
?>
```
O/P
```
area of rectangle is 14 * 12= 168
```

# 2. Arrays, Function and Graphics

## 2. How to create an array? Explain with example.
- An array is a special variable, which can hold more than one value at a time.
- To create array we use `array()` function.
```php
<?php
$array = array("Hello", "World");
print_r($array);
```
O/P
```
Array ( [0] => "Hello", [1] => "World" )
```

## 3. What is string?
- A string is collection of characters.
- A string is series of characters, where a character is the same as a byte.
```php
<?php
$string = "Hello World";
?>
```

## 4. What is function?
- A function is a block of statements that can be used repeatedly in a program.
- A function will be executed by a call to the function.
```php
<?php
function func() {
  echo "Hello World";
}
func();
?>
```
O/P
```
Hello World
```

## 5. How to extract data from array? Explain with example.
- The extract() function imports variables into the local symbol table from an
  array.
- This function uses array keys as variable names and values as variable
  values. For each element it will create a variable in the current symbol
  table.
```php
<?php
$color["red"] = "#rrr";
extract($color);
echo $red;
```
O/P
```
#rrr
```

## 6. Enlist types of arrays. Describe with example.

### Indexed array
Indexed Arrays are arrays in which the elements are ordered based on index.
```php
<?php
$a = array("Red", "Blue", "Green");
echo "My fav color is: ".$a[0];
```
O/P
```
My fav color is: Red
```

### Associative Arrays
Associative arrays are arrays that use named keys that you assign to them.
```php
<?php
$a = array("Red"=>1, "Blue"=>2, "Green"=>3);
echo $a["Red"].$a["Blue"],$a["Green"];
```
O/P
```
123
```

### Multidimensional array
A multidimensional array is an array containing one or more arrays.
```php
<?php
$a = array(array("Red", "Blue", "Green"));
echo "My fav color is: ".$a[0][1];
```
O/P
```
My fav color is: Blue
```

## 8. How to add image in PHP? Explain with example.
```php
<?php
$image = imagecreatetruecolor(500, 300);
imagefilledrectangle($image, 20, 20, 480, 280);
header("Content-type: image/png");
imagepng($image);
?>
```

## 14. With the help of example describe traversing of array.
Traversing an array means to visit each and every element of array using a
looping structure and iterator functions.
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

## 16. Which operations performed on string in PHP?
- **strrev()** - Reverses a string.
- **strpos()** - Returns the position of the first occurrence of a string.
- **strrpos()** - Finds the position of the last occurrence of a string.
- **str_replace()** - Replaces some characters in a string.
- **ucwords()** - Converts the first character of each word in a string to
  uppercase.
- **strtoupper()** - Converts a string to uppercase letters.
- **strtolower()** - Converts a string to lowercase letters.
- **strcmp()** - Compares two strings.
- **str_word_count()** - Count the number of words in a string.
- **strlen()** - Returns the length of a string.
```php
<?php
strrev("Hello World");
strpos("Hello World", "Hello");
strrpos("Hello World", "Hello");
str_replace("Hello", "Bye", "Hello World");
ucwords("hello world");
strtoupper("Hello World");
strtolower("Hello World");
strcmp("Hello World", "Hello World");
str_word_count("Hello World");
strlen("Hello World");
```
O/P
```
dlroW olleH
0
0
Bye World
Hello World
HELLO WORLD
hello world
0
2
11
```

## 18. Explain the following types of functions with example:

### (i) User defined functions
A function is a block of statements that can be used repeatedly in a program.
```php
<?php
function func() {
  echo "Hello World";
}
```
O/P
```
Hello World
```

### (ii) Variable function
If a variable name has parentheses appended to it, PHP will look for a function
with the same name as whatever the variable evaluates
```php
<?php
function func() {
  echo "Hello World";
}

$f = "func";
$f();
```
O/P
```
Hello World
```

### (iii) Anonymous function.
Anonymous function is a function without any user defined name.
```php
<?php
$func = function () { echo "Hello World"; };
$func();
```
O/P
```
Hello World
```

## 18. How to create PDF in PHP? Describe with example.
```php
<?php
require('fpdf.php');
$pdf = new FPDF();
$pdf->AddPage();
$pdf->SetFont('Arial', 'B', 16);
$pdf->Cell(40, 10, "Hello World");
$pdf->Output();
?>
```

## 19. How to scaling an image in PHP?
```php
<?php
$image = imagecreatefrompng("image.png");
$img = imagescale($image, 500, 500);
header("Content-type: image/png");
imagepng($img);
```

## 20. Explain array_flip() function with example.
- The array_flip() function flips/exchanges all keys with their associated
  values in an array.
- **Syntax** - `array_flip($array)`
```php
<?php
$a = array("Hello", "World");
print_r(array_flip($a));
```
O/P
```
Array ( [Hello] => 0, [World] => 1 )
```

# 3. Apply Object Oriented Concepts in PHP

## 1. What is OOP?
- In object oriented programming, everything will be around the objects and
  class.
- By using OOP in PHP we can create modular web application.
- By using OOP in PHP we can perform any activity in the object model structure.
- OPP helps in building complex, reusable web applications.
- Object Oriented is an approach to software development that models
  application around real world objects such as employees, cars, bank accounts,
  etc.
- A class defines the properties and methods of a real world object.
- An object is an occurrence of a class.

## 2. What is object?
- An object is an instance or occurrence of a class.
- Anything in the world is an object like laptop, books, car etc. even object
  has two thing properties and behaviors.
- The data associated with an object are called its properties.
- The functions associated with an object are called its methods.
- We can group similar objects with the same characteristics and behaviors in
  into one class.

## 5. What is inheritance?
- The old class is the base class, also called as parent class or super class,
  and the new class is the derived class also called as child class or sub
  class.
- The derived class has its own variables and methods plus variables and
  methods from the base class.
- The `extends` keyword is used for the inheritance.
```php
<?php
class Class1 {
  function func() {
    echo "Hello World";
  }
}

class Class2 extends Class1 {
  function echo() {
    echo "Bye World";
  }
}

$o = new Class2;
$o->func();
$o->echo();
```
O/P
```
Hello World
Bye World
```

## 6. Describe method overloading with example.
If the derived class is having the same method name as the base class then the method in the derived class takes precedence over or overrides the base class method.
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

## 7. Explain sleep and wakeup functions?
- These functions are used to notify objects that they are being serialized or
  unserialised.

### `__sleep()`
- serialize() checks if our class has a function with the magic name sleep().
- If so, that function is executed prior (i.e. just before) to any
  serialization.

### `__wakeup()`
- unserialize() checks for the presence of a function with the magic name ___
  wakeup().
- If present, this function can reconstruct any resources that the object may
  have.

```php
<?php
class Obj {
  function __sleep() {
    $this->name = "Jonney";
    echo "Obj is serialize()";
    return array("name");
  }

  function __wakeup() {
    echo "Obj is unserialize()";
  }
}

$o = new Obj;
$s = serialize($o);
unserialize($s);
?>
```
O/P
```
Obj is serialize()
Obj is unserialize()
```

## `__call`
- The __call() method is invoked automatically when a non-existing method or
  inaccessible method is called.
- The __call() method accepts two arguments:
    - $name is the name of the method that is being called by the object.
    - $arguments is an array of arguments passed to the method call.
```php
<?php
class Obj {
  function __call($method, $parameters) {
    print_r($method);
    print_r($parameters);
  }
}

$o = new Obj;
$o->hello("World");
```
O/P
```
hello
Array ( [0] => "World" )
```

## 8. What serialization in PHP?
- Serialization of data means converting it into a string of bytes in such a
  way that you can produce the original data again from the string via a
  process as unserialization.
- After you have the ability to serialize/unserialize, you can store your
  serialized string anywhere and recreate a copy of the data again when needed.
```php
<?php
echo serialize(array("Red"));
?>
```
O/P
```
a:1:{i:0;s:3:"Red";}
```
- O/P means:
  - a:1 - **a**rray - There are **1** array.
  - i:0 - **i**tem - This is **0**th item.
  - s:3 - **s**tring - There are **3** string in **"Red"**.

## 10. Define method overriding.
- In function overriding, both parent and child classes should have same
  function name with and number of arguments.
- It is used to replace parent method in child class.
- The purpose of overriding is to change the behavior of parent class method.
- The two methods with the same name and same parameter is called overriding.
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

$f = new First;
$s = new Second;
$f->func();
$s->func();
```
O/P
```
Hello World
Bye World
```

## 12. What is object cloning? Describe with example.
- Object cloning is the process in PHP to create a copy of an object.
- An object copy is created by using the clone keyword when the object is
  cloned PHP will perform Shallow copy of all the object properties and
  properties that are referenced to their variables will remain references.
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

## 13. Define the terms:

### (i) Object
Objects are the things you create out of a class.

### (ii) Class
A class is what you use to define the properties, methods and behavior of objects.

### (iii) Inheritance
- The old class is the base class, also called as parent class or super class,
  and the new class is the derived class also called as child class or sub
  class.

### (iv) Constructor.
- When we create a new object it is useful to initialize its properties.
- PHP provides us with a special method to help initialize an object's
  properties called a constructor.

## 16. Differentiate between constructor and destructor.
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

## 17. Compare object and class.
- A class is what you use to define the properties, methods and behavior of
  objects.
- Objects are the things you create out of a class.

## 18. How to examine classes in introspection? Explain with example.
- PHP Introspection is the ability of a program to examine an object's
  characteristics such as its name, parent class (if any), properties and
  methods.
- Introspection in PHP offers a useful Ability to examine classes' interfaces
  properties methods. With introspection we can write code that operates on any
  object or class.
```php
<?php
class Obj {}

class Obj2 extends Obj {
  public $hello = "world";
  function func() {}
}
$o = new Obj2;

if (class_exists('Obj2')) {
  echo "Class exists";
}
if (is_object($o)) {
  echo "Is object";
}

print_r(get_class($o));
print_r(get_class_methods($o));
print_r(get_class_vars('Obj'));
print_r(get_parent_class($o));
?>
```
O/P
```
class exists
Is object
Obj2
Array ( [0] => func )
Array ( [hello] => world )
Obj
```

## Examining an Object
- `is_object()` - Checks if an object.
- `get_class()` - Return object's class name.
- `method_exists()` - Checks if method exists.
- `class_exists()` - Checks if class exists.

```php
<?php
class Obj {
  function func() {
    echo "Hello World";
  }
}

$o = new Obj;
echo is_object($o);
echo get_class($o);
echo method_exists($o, 'func');
echo class_exists('Obj');
```
O/P
```
1
Obj
1
1
```

# 4. Creating and Validating forms

## 1. What is form? How to create it?

### What is form?
- Forms are essential parts in web development. Forms are used to get input from
  the user and submi it to the web server for processing.
- Forms are used to communicate between users and the server.

### How to create it?
- A document that containing blank fields, that the user can fill the data or
  user can select the data. It is known as Form.
- Generally, the data will store in the database. We can create and use forms
  in PHP. To get form data, we need to use PHP superglobals `$_GET`and $_POST
- The form request may be get or post. To retrieve data from get request, we
  need to use `$_GET`, for post request `$_POST`
```php
<form action="<?php $_SELF_PHP ?>" method="post">
  <input type="text" name="name">
  <input type="submit">
</form>

<?php
if (isset($_POST["name"])) {
  echo "Your name is: ".$_POST["name"];
}
?>
```

## 2. What is form control?
- There are different types of form controls that we can use to collect data
  using form namely, Textbox, Checkbox, Radio button, and so on.
- **TEXTBOX** - A text input field allows the user to enter a singel text.
- **TEXTAREA** - A textarea field is similar a text input field but it allows
  the user to enter multiple lines of text.
- **RADIO BUTTON** - The radio buttons are for single choice from multiple
  options. All radio buttons in the group have the same name attribute.
- **CHECKBOX** - A checkbox field is a simple toggle button. It can be either
  ON or OFF. The value attribute should contain the value that will be sent to
  the server when the checkbox is selected.
- **LIST** - There are two type of list:
  - **Singleline LIST** - The list represents a Windows control to display a
    list of items to a user. A user can select an item from the list.
  - **Multiline LIST** - A multi-select list allows the user to select multiple
    items. To turn a normal list into a multi-select list, add the attribute
    multiple with a value of "multiple" to the select element.

## 3. Write short note on: Server role.
- PHP is a server-side scripting language.
- Using PHP we can create dynamic web sites.
- That means its processing happens in the server by consuming server's
  resources and sends only the output to the client.

## 5. When to use GET and POST method.

### GET
- It sends the encoded user information appended to the page request (to the
	URL).
- The page and the encoded information are separated by the ? character.
- The GET method produces a long string the appears in our server logs, in the
	browser' location box.
- The GET method is restricted to send up to 1024 characters only.
- Never use GET method if we have password or other sensitive information.
- GET cannot be used to send binary data to the server.
- The php provides $_GET assoiative array to a access all the sent information
	using GET method.
- Example:
	```php
	<form action="<?php $_PHP_SELF ?>" method="GET">
		Name: <input type="text" name="name">
		<input type="submit">
	</form>

	<?php
	if ($_GET["name"]) {
		echo $_GET["name"];
	}
	?>
	```
- Output:
	```
	Name: Joey
	Submit

	Joey
	```

### POST
- It transfers information via HTTP header, not throought the URL.
- The POST method does not have any restriction on data size.
- The POST method can be used to send ASCII as well as binary data.
- The data sent by POST  method goes through HTTP header, so security depends on
	HTTP protocol.
- By using secure HTTP, we can make sure that our information is secure.
- The PHP provides $_POST associative array to access all the sent information
	using POST method.
- Example:
	```php
	<form action="<?php $_PHP_SELF ?>" method="post">
		Name: <input type="text" name="name">
		<input type="submit">
	</form>

	<?php
	if ($_POST["name"]) {
		echo $_POST["name"];
	}
	?>
	```
- Output
	```
	Name: Joey
	Submit

	Joey
	```

## 7. What is cookie? How to create it? Explain with example.

### What is cookie?
- Cookie save the data in browser, so next time refresh the browser it will not
	delete from browser.
- Cookie is used to identify the user.
- A cookie is a small file that server embeds to user's computer.
- Each time the same computer requests a page with a browser, it will send the
	cookie too.

### How to create it?
- Use `setcookie` function to create cookie.
- Syntex:
	```
	setcookie($cookie_name, $cookie_value, $time, $location)
	```

### Example
```php
<?php
setcookie("name", "Jonney", time() + (86400 * 30), "/");
if (isset($_COOKIE["name"])) {
  echo "Name: ".$_COOKIE["name"];
}
```
O/P
```
Name: Jonney
```

## 8. What is session? Explain with example.
- A session is a way to store information in variables to be used across
	multiple pages.
- Sessions allow us to store data on the web server that associated with a
	session ID.
- Once we create a session, PHP sends a cookie that contains the session ID to
	the web browser.
- A session is started with the session_start() function.
- The session_start() function first checks if a session is already started and
	if none is started then it starts one.
```php
<?php
session_start()
?>
<?php
$_SESSION["name"] = "Jonney";
echo "Name: ".$_SESSION["name"];
?>
```
O/P
```
Name: Jonney
```

## 9. How we can get the cookie values and destroy the cookies?

### To get cookie value.
```php
<?php
setcookie("name", "Jonney", time() + (83400 * 30), "/");

if ( isset($_COOKIE["name"]) ) {
  echo "Name: ".$_COOKIE["name"];
}
?>
```

### To destroy the cookie.
```php
<?php
setcookie("name", "", time() - 3600, "/");
?>
```

## 11. What is form validation? Explain with suitable example.
- For validating a web page we use preg_match() function.
- The preg_match() function searches string for pattern, returning true if
	pattern exists, and false otherwise.
```php
<form action="<?php $_PHP_SELF ?>" method="post">
  <input type="text" name="name" required>
  <input type="submit">
</form>

<?php
if ( isset($_POST["name"]) ) {
  if ( !preg_match("/^[a-zA-Z_ ]*$/", $_POST["name"]) ) {
    echo "Only Words and Whitespaces are allowed.";
  }
}
?>
```
## 14. How to send e-mail? Describe with example.
- `mail()` function is useful to sending the mail.
- Syntex:
	```php
	mail($to, $subject, $message, $header, $parametes);
	```
- `mail()` function parametes:
	- **to** - represents the address of receiver.
	- **subject** - it specifies the subject of mail.
	- **message** - it defines the message which is to be sent.
	- **headers** - it is optional and specifies the additional headers like Cc, Bcc.
	- **parameters** - it is optional and specifies the additional parameters.
```php
<?php
$sent = mail("AnzenKodo@altmail.com", "Title", "Message");

if (!$sent) {
  echo "Message is not sent.";
} else {
  echo "Message is sent.";
}
```
O/P
```
Message is sent.
```

# 5. Database Operations

## 1. What is database?
- A database is a collection of related data.
- A database is a collection of information that is organized so that it can
  easily be accessed, managed and updated.
- With PHP, we can connect to and manipulate databases.

## 2. What is DBMS?
- A DataBase Management System (DBMS) is system software for creating and
  managing databases.
- The DBMS provides users and programmers with a systematic way to create,
  retrieve, update and manage data.

## 3. What is MySQL? How it is used in PHP?
- MySQL is an open-source relational database management system (RDBMS).
- It is the most popular database system used with PHP.
- Using my sql:
  ```php
  <?php
    // Creating connection
    $conn = mysqli_connect("localhost", "root", "", "test");

    // Checking connection
    if (!$conn) {
        die("Connection failed.");
    }
    echo "Connected successfully";
  ?>
  ```

## 4. How to create and delete a database in MySQL?
- We can create a MySQL database by using MySQL Command Line Client.
- Open the MySQL console and write down password, if we set one while
  installation.
- We will get the following:
  - To create the data base enter `CREATE DATABASE database_name`
  - To check the database is crated enter `SHOW DATABASES`
- Creating database through php:
  ```php
  <?php
  $conn = mysqli_connect("localhost", "root", "", "test");

  if (!$conn) {
    die("Can't connect to MySQL ");
  }

  $sql = "CRATE DATABASE emp";

  if (!mysqli_query($conn, $sql)) {
    die("Can't create database ".mysqli_error($conn);
  }

  echo "Created database <br/>";
  ?>
  ```
  O/P
  ```
  Created database
  ```

## 5. Explain mysqli_connect() function with example.
- The mysqli_connect() function is used to connect with MySQL database.
- It returns resource if connection is established or null.
- Syntax: `mysqli_connect(server, username, password, dbname, port, socket)`
- Example:
  ```php
  <?php
  $conn = mysqli_connect("localhost", "root", "", "test");

  if (!$conn) {
    echo "Can't connect to database.";
    exit();
  } else {
    echo "Databse is connected.";
  }
  mysqli_close($conn);
  ```

## 7. Write a program to create an employee table to perform insert, delete and update operations.
```php
<?php
// Connect MySQL
$conn = mysqli_connect("localhost", "root", "", "test");
if (!$conn) {
  echo "Error: ".mysqli_error($conn);
}

// Create table
$table = "CREATE TABLE employee(id INT(4), name VARCHAR(22), salary INT(4))";
if (!mysqli_query($conn, $table)) {
  echo "Can't create table.";
}
echo "Created table<br/>";

// Insert data
$insert = "INSERT INTO employee(id, name, salary) VALUES (1, 'Sam', 3200), (2, 'Jonney', 4500), (3, 'Jone', 2000)";
if (!mysqli_query($conn, $insert)) {
  echo "Can't insert data.";
}

// Dalete data
$delete = "DELETE FROM employee WHERE id=2";
if (!mysqli_query($conn, $delete)) {
  echo "Can't delete data.";
}

// Retrive data
$retrive = "SELECT * FROM employee";
$result = mysqli_query($conn, $retrive);

if (mysqli_num_rows($result)) {
  while ($row = mysqli_fetch_assoc($result)) {
    echo "Name: ".$row['name'].", Salary: ".$row['salary'].", ID: ".$row['id']."</br>";
  }
}
?>
```
