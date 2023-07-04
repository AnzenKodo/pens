# *22619* - Web Based Application development with PHP
- **Programme Name:** Computer/Information Technology Engineering
- **Programmecode:** CO/IF
- **Semester:** VI Sem
- **Marks:** 70

## Q.1) Attempt any FIVE of the following. *(10 Marks)*

### a) List any four advantages of PHP?
1. PHP is open source and free from cost.
2. It is platform independent.
3. PHP based application can run on any OS like UNIX, Linux and Windows, etc
4. Easy to learn.
5. Has built-in database connection modules.

### b) State the use of `str_word_count` along with its syntax.
- `str_word_count()` function counts the numbers of word in a string.
- Syntax:
  ```
  str_word_count(string,return,char)
  ```
- Example:
  ```php
  <?php
  echo set_word_count("Hello World");
  ?>
  ```
  O/P
  ```
  2
  ```

### c) Define serialization.
- Serialization of data means converting it into a string of bytes in such a way
  that you can produce the original data again from the string via a process as
  unserialization.
- After you have the ability to serialize/unserialize, you can store your
  serialized string anywhere and recreate a copy of the data again when needed.
- PHP offers two functions, serialize() and unserialize(), which take a value of
  any type (except type resource) and encode the value into string form and
  decode again, respectively.

### d) Write the syntax for creating Cookie.
- To set cookie in PHP, the `setcookie()` function is used.
- Syntex:
	```php
	setcookie($name, $value, $expire_time, $path, $domain)
	```
- `setcookie()` function the parameters.
	- **name** - Name of the cookie, which is used with $_COOKIE function to get
	value.
	- **value** - Value of the named variable.
	- **expire time** - Time when cookie will expire.
	- **path** - Directory where cookie will valied.
	- **domain** - The default server hostname.

### e) Write syntax of Connecting PHP Webpage with MySQL.
- Syntex:
  ```
  mysqli_connect(host, username, password, dbname, port, socket)
  ```
- Parameter:
  - **host** - Specifies a host name or an IP address.
  - **username** -Specifies the MySQL username
  - **password** - Specifies the MySQL password
  - **dbname** - Specifies the default database to be used
  - **port**  - Specifies the port number to attempt to connect to the MySQL
    server
  - **socket** - Specifies the socket or named pipe to be used

- Example:
	```php
	<?php
	mysqli_connect("localhost", "root", "", "/", "domain.com",
		"/run/mysql/mysql.sock")
	```

### f) Define GET and POST methods.

#### GET
- It sends the encoded user information appended to the page request (to the
	URL).
- The page and the encoded information are separated by the ? character.
- The GET method produces a long string the appears in our server logs, in the
	browser location box.
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

#### POST
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

### g) State the use of `$` sign in PHP.
- The $ operator in PHP is used to declare a variable.
- A variable starts with the $ sign followed by the name of the variable.
- Example:
  ```php
  <?php
  $var_name = "Hello World!";
  ?>
  ```

## Q.2) Attempt any THREE of the following. *(12 Marks)*

### a) Write a program using foreach loop.
```php
<?php
  //declare array
  $season = array ("Summer", "Winter", "Autumn", "Rainy");
  //access array elements using foreach loop
  foreach ($season as $element) {
    echo "$element";
    echo "</br>";
  }
?>
```

**Output:**

```
Summer
Winter
Autumn
Rainy
```

### b) Explain Indexed and Associative arrays with suitable example.

#### Indexed arrays
Indexed array: An array having only integer keys is typically referred to as an
indexed array and index arrays can store numbers, drinks and any object but
their index will be represented by number.

**Example:**

```php
<?php
  // Define an indexed array
  $colors = array("Red", "Green", "Blue");
  // Printing array structure
  print_r($colors);
?>
```


**Output:**

```
Array ( [0] => Red [1] => Green [2] => Blue )
```

#### Associative arrays
The associative arrays are very similar to numeric arrays in terms of
functionality but they are different in terms of their index. Associative arrays
will have their index as string so that you can establish a strong association
between key and values.

```php
<?php
  // Define an associative array
  $ages = array("Peter"=>22, "Clark"=>32, "John"=>28);
  // Printing array structure
  print_r($ages);
?>
```

**Output:**

```
Array ( [Peter] => 22 [Clark] => 32 [John] => 28 )
```

### c) Define Introspection and explain it with suitable example.
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

### d) Differentiate between Session and Cookies.
| SESSION                               | COOKIES                               |
|---------------------------------------|---------------------------------------|
| Session are stored in server side     | Cookies are stored in client browser. |
| Session is server resource.           | Cookies are client-side resource.     |
| It stores unlimeted data.             | It stores limited data.               |
| It holds multiple variables.          | It doen't hold multiple variables.    |
| Session values can't accessed easily. | Cookies values can accessed easily.   |
| It is more secure.                    | It is less secure.                    |

## Q.3) Attempt any THREE of the following. *(12 Marks)*
### a) Differentiate between implode and explode functions.
| No.   | Implode                                                                                                                                                         | Explode                                                                                                                                                                     |
| ----- | --------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 1     | The implode() function returns a string from the elements of an array.                                                                                          | explode function breaks a string  into smaller parts and stores it  as an array.                                                                                            |
| 2     | The implode() function accepts its  parameters in either order.  However, for consistency with explode(),  you should use the documented order of  arguments.   | The explode() function splits  these strings based on a specific  delimiter and returns an array that  contains elements which are sustained  by the splitting operation.   |
| 3     | syntax :-string implode (pieces)                                                                                                                                | array explode (delimiter, string, limit)                                                                                                                                    |
| 4     | **Example**:  ```php <?php $arr = array("I", "love", "PHP."); $pole = implode(" ", $arr); \ echo "$pole"; ?> ```  Output: I love PHP.                           | Example: <?php  $string = "I love php."; $pole = explode(" ", $string); \ \ print_r($pole); ?>  Output: Array ( [0] => I [1] => love [2] => php. )                          |

### b) Write a program for cloning of an object.
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
**Output:**

```
Origenal: Jonney, Clone: JOne
```

### c) Define session and explain how it works.
- A session is a way to store information in variables to be used across
	multiple pages.
- Sessions allow us to store data on the web server that associated with a
	session ID.
- Once we create a session, PHP sends a cookie that contains the session ID to
	the web browser.
- A session is started with the session_start() function.
- The session_start() function first checks if a session is already started and
	if none is started then it starts one.
- Example:
	```php
	<?php
	session_start();
	$_SESSION["color"] = "Red";
	$_SESSION["animal"] = "Cat";
	echo $_SESSION["color"]." ".$_SESSION["animal"];
	?>
	```

### d) Write Update and Delete operations on table data.

## Q.4) Attempt any THREE of the following. *(12 Marks)*
### a) State the variable function.Explain it with example.
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
### b) Explain the concept of Serialization with example.
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

### c) Answer the following:
#### i) Get session variables
- The session variables are not passed individually to each new page, instead
	they are retrieved from the session we open at the beginning of each page.
- All session variable values are stored in the global `$_SESSION` variable.

#### ii) Destroy session.
- To remove all global session variables and destroy the session, we use
	`session_unset()` and `session_destroy()` functions.
- No arguments are needed in `session_destroy()` function.
- Example:
	```php
	<?php
	session_start();
	$_SESSION["color"] = "red";
	$_SESSION["animal"] = "Lion";
	echo $_SESSION["color"]." ".$_SESSION["animal"];
	session_unset();
	session_destroy();
	?>
	```

## Q.5) Attempt any TWO of the following. *(12 Marks)*

### a) Explain any three data types used in PHP.
1. **Integer:** integer data type used to specify a numeric value  without a fractional component the range of integers.
2. **Strings:** a string is a sequence of characters where characters are the same as a byte.
3. **Boolean:** boolean  value can be either true or false both are  case-insensitive.

### b) Write a program to connect PHP with MySQL.
```php
<?php
$conn = mysqli_connect("mydb", "root", "root");
if ($conn) {
	echo "Connection Successful";
} else {
	echo "Connection Unsuccessful";
}
```
O/P
```
Connction Successful
```

### c) Explain the concept of overriding in detail.
In function overriding, both parent and child classes should have the same
function name with and number of arguments. It is used to replace the parent
method in child class.

```php
<?php
class ParentClass {
  function helloWorld() {
    echo "Parent";
  }
}
class ChildClass extends ParentClass {
  function helloWorld() {
    echo "Child";
  }
}
$p = new ParentClass;
$c = new ChildClass;
$p->helloWorld();
$c->helloWorld();
?>
```

**Output:**

```
Parent
Child
```

## Q.6) Attempt any TWO of the following. *(12 Marks)*

### a) Explain web page validation with example.
- For validating a web page we use preg_match() function.
- The preg_match() function searches string for pattern, returning true if
	pattern exists, and false otherwise.
- Example:
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

### b) Write a program to create PDF document in PHP.
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

### c) Elaborate the following:
#### i) __call()
- The __call() method is invoked automatically when a non-existing method or
  inaccessible method is called.
- The __call() method accepts two arguments:
  - $name is the name of the method that is being called by the object.
  - $arguments is an array of arguments passed to the method call.
- Syntax:
  ```
  public __call ( string $name , array $arguments ) : mixed
  ```
- Example:
  ```php
  <?php
	class Obj {
		function __call($method, $argument) {
			print_r($method);
			print_r($argument);
		}
	}

	$o = new Obj;

	$o->hello("World");
  ?>
  ```
	O/P
	```
	hello
	Array([0]=>"World")
	```

#### ii) mysqli_connect()
- This function opens a connection to a MySQL server.
- It returns a MySQL link identifier on success, or FALSE on failure.
- Syntax:
	```php
	mysqli_connect($server, $username, $password)
	```
- Example:
	```php
  <?php
	$conn = mysqli_connect("mydb", "root", "root", "text");
  ?>
	```
