## 1. Write a PHP program using expressions and operator (ternary operator, arithmetic operators and comparison operators)
```php
<?php
  echo 1 > 2 ? 1 : 2;
  echo "<br>";
  echo 1 + 2;
?>
```
O/P
```
2
3
```

## 2. Write a PHP program to the use of decision making and control structures using:

### `if` statement
```php
<?php
$x = 1;
if ($x > 0) {
  echo "The number is positive";
}
```
O/P
```
The number is positive
```

### `if else` statement
```php
<?php
$x = "August";

if ($x > 0) {
  echo "The number is positive";
} else {
  echo "The number is negative";
}
?>
```
O/P
```
Happy Independence Day!!!
```

### `if elseif if` statement
```php
<?php
$x = "August";

if ($x > 0) {
  echo "The number is positive";
} elseif ( $x < 0 ) {
  echo "The number is negative";
} else {
  echo "The value is not number";
}
?>
```
O/P
```
The number is positive
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

## 3. Write a PHP program to the use of looping structure using:

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
  echo $x;
  $x++;
} while ($x <= 5);
?>
```
O/P
```
12345
```

### `for` statement
```php
<?php
for ($i = 1; $i <= 10; $i++) {
  echo $i;
}
?>
```
O/P
```
12345678910
```

## 4. Write a PHP program to the use of looping structure using for statement, for each statement.

### `for` statement
```php
<?php
for ($x = 0; $x <= 5; $x++) {
  echo $x;
}
?>
```
O/P
```
012345
```

### `foreach` statement
```php
<?php
$a = array("Hello", "World");

foreach ($a as $b) {
  echo $b." ";
}
?>
```
O/P
```
Hello World
```

## 5. Write a PHP program for creating and manipulating , associative array and multidimensional array.

### Indexed array
```php
<?php
$a = array("Red", "Blue", "Green");
echo "My fav color is: ".$a[0];
?>
```
O/P
```
My fav color is: Red
```

### Associative arrays
```php
<?php
$a = array("Red"=>1, "Blue"=>2, "Green"=>3);
echo $a["Red"].$a["Blue"],$a["Green"];
?>
```
O/P
```
123
```

### Multidimensional array
```php
<?php
$a = array(array("Red", "Blue", "Green"));
echo "My fav color is: ".$a[0][1];
?>
```
O/P
```
My fav color is: Blue
```

## 6. Write a PHP program to calculate

### Length of string
```php
<?php
  echo strlen("Hello world!");
?>
```
O/P
```
12
```

### Count the no of words in string
```php
<?php
  echo str_word_count("Hello world!");
?>
```
O/P
```
2
```

### Compare two string using string function.
```php
<?php
  echo strcmp("Hello world!", "Hello world");
?>
```
O/P
```
0
```

## 7. Write a PHP program using following string function:
- strrev()
- strpos()
- strrpos()
- str_replace()
- ucwords()
- strtoupper()
- strtolower()
```php
<?php
  echo strrev("Hello world!")."</br>";
  echo strpos("Hello world!", "world")."</br>";
  echo strrpos("I love php, I love php too!","php")."</br>";
  echo str_replace("world", "bvit", "Hello world!")."</br>";
  echo ucwords("Welcome to php world")."</br>";
  echo strtoupper("Information Technology")."</br>";
  echo strtolower("INFORMATION TECHNOLOGY")."</br>";
?>
```
O/P
```
!dlrow olleH
6
19
Hello bvit!
Welcome To Php World
INFORMATION TECHNOLOGY
information technology
```

## 8. Write a PHP program to use: and anonymous function.

### User define function
```php
<?php
  function writeMessage() {
    echo "Welcome to PHP world";
  }
  writeMessage();
?>
```
O/P
```
Welcome to PHP world
```

### Variable function
```php
<?php
  function writeMessage() {
    echo "Welcome to PHP world";
  }

  $w = "writeMessage";
  $w();
?>
```
O/P
```
Welcome to PHP world
```

### Anonymous function
```php
<?php
  $a=function() { echo "Anonymous function"; };
  $a();
?>
```
O/P
```
Anonymous function
```

## 9. Write a PHP program to create PDF document by using graphics concept.
```php
<?php
  require('fpdf.php');
  $pdf = new FPDF();
  $pdf->AddPage();
  $pdf->SetFont('Arial','B',16);
  $pdf->Cell(40,10,'Hello World!');
  $pdf->Output();
?>
```
O/P
```
Hello World
```

## 10. Write a PHP program
### a) To inherit member of superclass in subclass
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
?>
```
O/P
```
Hello World
Bye World
```

### b) Create constructor to initialize object of class by using object oriented concept.
```php
<?php
class Obj {
  public function __construct($name, $surname) {
    $this->name=$name;
    $this->surname=$surname;
  }
  public function showName() {
    echo "My name is ".$this->name." ".$this->surname;
  }
}

$sid=new Obj("Aman","Varma");
$sid->showName();
?>
```
O/P
```
My name is Aman Varma
```

## 11. Write a PHP program on

### Introspection
```php
<?php
if (!class_exists("Obj")) {
  echo "Class don't exists."
}
?>
```
O/P
```
Class don't exists
```

### Serialization.
```php
<?php
echo serialize(array("Red"));
?>
```
O/P
```
a:1:{i:0;s:3:"Red";}
```

## 12. Design a web page using following form controls:
- a) Textbox
- b) Radio button
- c) Check box
- d) Button
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

## 13. Design a web page using following form controls:
- a) List box
- b) Hidden field box
```php
<form action="<? $_PHP_SELF ?>" method="post">
  <input type="hidden" name="name" value="Jone">
  <select name="foods">
    <option value="Tomatoes">Tomatoes</option>
    <option value="Cucumbers">Cucumbers</option>
    <option value="Celery">Celery</option>
  </select>
  <br>
  <input type="submit" name="submit" value="Submit"/>
</form>

<?php
  if( isset($_POST["foods"]) ) {
    echo $_POST["name"]." have chosen ".$_POST["foods"];
  }
?>
```

## 14. Develop a web page with data validation.
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

## 15. Write a PHP program to:

### Create cookies
```php
<?php
setcookie("name", "Jone", time() + (86400 * 30), "/");
?>
<?php
if (isset($_COOKIE["name"])) {
  echo "Name: ".$_COOKIE["name"];
}
?>
```
O/P
```
Name: Jone
```

- Modify cookies value
Set cookie agien with setcookie function.

- Delete cookies
```php
<?php
setcookie("name", "", time() - 3600, "/");
?>
<?php
if (isset($_COOKIE["name"])) {
  echo "Name: ".$_COOKIE["name"];
} else {
  echo "Cookie is not set.";
?>
```
O/P
```
Cookie is not set.
```

## 16. Write a PHP program to:
- Start session
- Get session variable
- Destroy session
```php
<?php
  session_start();

  $_SESSION["color"] = "Red";
  $_SESSION["animal"] = "Lion";

  echo $_SESSION["color"]." ".$_SESSION["animal"];

  session_unset();
  session_destroy();
?>
```
O/P
```
Red Lion
```

## 17. Write a PHP program for sending and receiving plain text message (sending email).
```php
<?php
  $status = mail("AnzenKodo@altmail.com", "Title", "Hello World");
  if ($status) {
    echo "Mail is sent.";
  } else {
    echo "Mail can't be sent";
  }
?>
```
## 18. Write a PHP program to

### Create database
```php
<?php
// Create connection
$conn = mysqli_connect("localhost", "root", "", "test");
// Check connection
if ($conn->connect_error) {
  die("Connection failed.");
}

// Create database
$sql = "CREATE DATABASE myDB";
if (mysqli_query($conn, $sql)) {
  echo "Database created successfully";
} else {
  echo "Error creating database";
}

mysqli_close($conn);
?>
```

### Creation of table.
```php
<?php
// Create connection
$conn = mysqli_connect("localhost", "root", "", "test");
// Check connection
if (!$conn) {
  die("Connection failed");
}

// sql to create table
$sql = "CREATE TABLE MyGuests(id INT(6))";

if (mysqli_query($conn, $sql)) {
  echo "Table MyGuests created successfully";
} else {
  echo "Error creating table: " . $conn->error;
}

$conn->close();
?>
```

## 19. Write a PHP program to Inserting and retrieving the query result operations and Update ,Delete operations on table data.
```php
<?php
// Connecting to MySQL
$conn = mysqli_connect("localhost", "root", "", "test");
if (!$conn) {
  die("Error: ".mysqli_error($conn));
}

// Inserting data
$sql = "INSERT INTO my_table(id, name) VALUES (1, 'Jone'), (2, 'Jonney)";
if (!mysqli_query($conn, $sql)) {
  die("Error");
}

// Retrieving data
$sql = "SELECT * FROM my_table";
if ($result = mysqli_query($conn, $sql)) {
  if (mysqli_num_rows($result) > 0) {
    while ($row = mysqli_fetch_array($result)) {
      echo "ID: ".$row["id"].", Name: ".$row["name"];
    }
  } else {
    echo "Rows can't be zero";
  }
} else {
  die("Error: ".mysqli_error($conn));
}

// Update data
$sql = "UPDATE my_table SET name='tim' WHERE id=2";
if (!mysqli_query($conn, $sql) {
  die("Error");
}

// Delete data
$sql = "DELETE FROM my_table WHERE id=1";
if (!mysqli_query($conn, $sql) {
  die("Error"));
}

mysqli_close();
?>
```
