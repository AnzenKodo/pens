# PHP

## Attempt any FIVE :

### (a) Describe advantage of PHP.
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

### (b) What is array ? How to store data in array ?
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

### (c) List types of inheritance.
- Single
- Multiple
- Multilevel Inheritance.

### (d) How can we destroy cookies ?
- To delete cookie, we can use `setcookie` function with expiration date in
```php
<?php
setcookie("name", "", time() - 3600, "/");
?>
```

### (e) List any four data types in MySQL.
- int
- float
- char
- json
- boolean
- xml

### (f) Write syntax of PHP.
```php
<?php
$hello = "Hello World";
?>
```

### (g) How to create session variable in PHP ?
A session is a way to store information in variables to be used across multiple pages.
```php
<?php
session_start();

$_SESSION["color"] = "Red";
$_SESSION["animal"] = "Cat";
echo $_SESSION["color"]." ".$_SESSION["animal"];
?>
```

## 2. Attempt any THREE :

### (a) Write down rules for declaring PHP variable.
- A variable starts with the $ sign, followed by the name of the variable.
- A variable name must start with a letter or the underscore character.
- A variable name cannot start with a number.

### (b) Write a program to create associative array in PHP.
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

### (c) Define Introspection and explain it with suitable example.
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

### (d) Write difference between get( ) & post( ) method of form (Any four points).

#### GET
- It sends the encoded user information appended to the page request (to the URL).
- The page and the encoded information are separated by the ? character.
- The GET method produces a long string the appears in our server logs, in the browser' location box.
- The GET method is restricted to send up to 1024 characters only.
- Never use GET method if we have password or other sensitive information.
- GET cannot be used to send binary data to the server.
- The php provides $_GET assoiative array to a access all the sent information using GET method.

#### POST
- It transfers information via HTTP header, not throought the URL.
- The POST method does not have any restriction on data size.
- The POST method can be used to send ASCII as well as binary data.
- The data sent by POST  method goes through HTTP header, so security depends on HTTP protocol.
- By using secure HTTP, we can make sure that our information is secure.
- The PHP provides $_POST associative array to access all the sent information using POST method.

## 3. Attempt any THREE :

### (a) Define function. How to define user defined function in PHP ? Give example.
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

### (b) Explain method overloading with example.
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

### (c) Define session & cookie. Explain use of session start.
#### What is cookie?
- Cookie save the data in browser, so next time refresh the browser it will not
	delete from browser.
- Cookie is used to identify the user.
- A cookie is a small file that server embeds to user's computer.
- Each time the same computer requests a page with a browser, it will send the
	cookie too.

#### How to create it?
- Use `setcookie` function to create cookie.
- Syntex:
	```
	setcookie($cookie_name, $cookie_value, $time, $location)
	```

#### Example
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
#### Session
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

### (d) Explain delete operation of PHP on table data.
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

## 4. Attempt any THREE :

### (a) Write PHP script to sort any five numbers using array function.
```php
<?php
$cars = array("Volvo", "BMW", "Toyota");
sort($cars);
?>
```
Output:
```
BMW
Toyota
Volvo
```

### (b) Write PHP program for cloning of an object.
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
Output:
```
Origenal: Jonney, Clone: JOne
```

### (c) Create customer form like customer name, address, mobile no, date of birth using different form of input elements & display user inserted values in new PHP form.
```php
<form action="<?php 1_SELF_PHP ?>" method="post">
  Name:
  <input type="text" name="name">
  Sex:
  <input type="radio" name="sex" value="male">Male</input>
  <input type="radio" name="sex" value="female">Female</input>
  Vehical:
  <input type="checkbox" name="vehicle[]" value="bike">Bike</input>
  <input type="checkbox" name="vehicle[]" value="car">Car</input>
  <input type="checkbox" name="vehicle[]" value="scooter">Scooter</input>
  <button name="submit">Submit</button>
</form>

<?php
if ( isset($_POST["submit"]) ) {
  echo $_POST["name"]." is ".$_POST["sex"]." will travel by ";
  foreach ($_POST["vehicle"] as $selected) {
    echo $selected." ";
  }
}
?>
```

### (d) Inserting and retrieving the query result operations.
```php
<?php
$server= "localhost";
$user = "root";
$password = "";
$db = "feedback";
// Create connection
$conn = new mysqli($server, $user, $password, $db);
// Check connection
if ($conn->connect_error)
{
die("Connection failed: " . $conn->connect_error);
}
$sql = INSERT INTO data VALUES('ashok','you are awesome bro');
[if](if) ($conn->query($sql) === TRUE)
{
echo "feedback sucessfully submitted";
}
else
{
echo "Error: " . $sql . "<br>" . $conn->error;
}
$conn->close();
?>
```

### (e) How do you validate user inputs in PHP ?
```php
<form action="<?php $_PHP_SELF ?>" method="post">
  Name:<input type="text" name="name" required>
  <input type="submit">
</form>

<?php
  if (!preg_match("/^[a-zA-Z_ ]*$/", $_POST["name"])) {
    echo "Only letter and whitespace is allowed";
  }
?>
```

## 5. Attempt any TWO :

### (a) Explain different loops in PHP with example.
#### `while` statement
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

#### `do while` statement
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

#### `for` loop
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

### (b) How do you connect MySQL database with PHP.
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

### (c) Create a class as "Percentage" with two properties length & width. Calculate area of rectangle for two objects.
```php
<?php
class Rectangle {
  public $width = 0;
  public $height = 0;

  function setSize($w = 0, $h = 0) {
    $this->width = $w;
    $this->height = $h;
  }

  function getArea() {
    return ($this->width * $this->height);
  }

  function getPerimeter() {
    return ( ($this->width + $this->height) * 2 );
  }

  function isSquare() {
    if ($this->width == $this->height) {
       return true;
     } else {
        return false;
     }
  }

}
```

## 6. Attempt any TWO :

### (a) Write a PHP program to demonstrate use of cookies.
- Cookie save the data in browser, so next time refresh the browser it will not
	delete from browser.
- Cookie is used to identify the user.
- A cookie is a small file that server embeds to user's computer.
- Each time the same computer requests a page with a browser, it will send the
	cookie too.

#### How to create it?
- Use `setcookie` function to create cookie.
- Syntex:
	```
	setcookie($cookie_name, $cookie_value, $time, $location)
	```

#### Example
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

### (b) Explain any four string functions in PHP with example.
- **strrev()** - Reverses a string.
- **strpos()** - Returns the position of the first occurrence of a string.
- **strrpos()** - Finds the position of the last occurrence of a string.
- **str_replace()** - Replaces some characters in a string.

### (c) What is inheritance?
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

### (ii) Write update operation on table data.
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
