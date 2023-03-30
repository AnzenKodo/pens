# PHP Unit 2 AB

### 1. Write the syntax for creating Cookie.
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

### 2. WAP to connect PHP with MySQL.
```php
<?php
$conn = mysqli_connect("localhost", "root", "", "test");
if ($conn) {
	echo "MySQL connected";
} else {
	echo "MySQL can't connect";
}
```
O/P
```
MySQL connected
```

### 3. Differentiate between Session and Cookies.
| SESSION                               | COOKIES                               |
|---------------------------------------|---------------------------------------|
| Session are stored in server side     | Cookies are stored in client browser. |
| Session is server resource.           | Cookies are client-side resource.     |
| It stores unlimeted data.             | It stores limited data.               |
| It holds multiple variables.          | It doen't hold multiple variables.    |
| Session values can't accessed easily. | Cookies values can accessed easily.   |
| It is more secure.                    | It is less secure.                    |

### 4. Define session and explain how it works.
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

### 5. Write update and delete operations on table.
```php
UPDATE:
<?php
$conn = mysqli_connect("localhost", "root", "", "test");
if (!$conn) {
	echo "Can't connect to MySQL";
}

$sql = "UPDATE my_table SET name='Jonney' WHERE id=2";
if (!mysqli_query($conn, $sql)) {
	die("Can't Update Table");
}
echo "Update data</br>";
?>
DELETE:
<?php
$sql = "DELETE my_table WHERE id=1";
if (!mysqli_query($conn, $sql)) {
	die("Can't Delete data");
}
echo "Deleted data</br>";

mysqli_close($conn);
?>
```
O/P
```
UPDATE:Update data
DELETE:Deleted data
```

### 6. Answer the following

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

### 7. Explain inserting and retrieving the query result operations.
- For inserting a data into the table we use the INSERT query.
- For retrieving the data, we use the SELECT query.
```php
<?php
$conn = mysqli_connect("localhost", "root", "", "test");
if (!$conn) {
	echo "Can't connect to MySQL";
}

// Insert the data
$sql = "INSERT INTO my_table(id, name) VALUES (1, 'Jonney'), (2, 'Jone')";
if (!mysqli_query($conn, $sql)) {
	echo "Can't Insert the data";
}

// Retriving
$sql = "SELECT * FROM my_table";
$result = mysqli_connect($conn, $sql);

if ($mysqli_num_rows($result) > 0) {
	while ($row = mysqli_fetch_array($result)) {
		echo "Name: ".$row['name'].", ID: ".$row['id']."<br/>";
	}
} else {
	echo "Rows can't be zero.";
}
```
### 8. Explain web page validation with example.
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

### 9.  Elaborate the following:

#### i) `mysqli_query()`
This function in php is used to pass a sql query to mysql database.
This function returns the query handle for SELECT queries, TRUE/FALSE for other
queries, or FALSE on failure.
- Syntex:
	```php
	mysqli_query(string, query, resource link_identifier])
	```

#### ii) `mysqli_connect()`
- This function opens a connection to a MySQL server.
- It returns a MySQL link identifier on success, or FALSE on failure.
- Syntax:
	```php
	mysqli_connect($server, $username, $password)
	```
- Example:
	```php
	$conn = mysqli_connect("mydb", "root", "root");
	```

### 10. Explain the use of mail() function in php.
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

### 11. How to use radio button in form? Give suitable example.
- The radio buttons are for single choice from multiple options.
- All radio buttons in the group have the same name attribute.
- Only one button can be selected per group.
- The value attribute is mandatory for checkboxes and radio buttons.
- Example:
	```php
	<form action="<?php $_PHP_SELF ?>" method="post">
		Color:
		<input type="radio" name="color" value="White">White</input>
		<input type="radio" name="color" value="Blue">Blue</input>
		<input type="radio" name="color" value="Red">Red</input>
		<input type="Submit">
	</form>

	<?php
	if (isset($_POST["color"])) {
		echo $_POST["color"];
	}
	?>
	```
### 12. WAP in php to counting no. of rows in table.
```php
<?php
$conn = mysqli_connect("localhost", "root", "", "test");
if (!$conn) {
	die("Can't connect to MySQL");
}

$sql = "SELECT * FROM my_table";
if ($result = mysqli_query($conn, $sql)) {
	echo "No of rows: ".mysqli_num_rows($result);
} else {
	echo "Can't connect";
}

mysqli_close($conn);
?>
```

### 13. WAP in php to counting no. of fields in table.
```php
<?php
$conn = mysqli_connect("localhost", "root", "", "test");
if (!$conn) {
	die("Can't connect to MySQL");
}

$sql = "SELECT * FROM my_table"
if ($result = mysqli_query($conn, $sql)) {
	echo "No of fields: ".mysqli_num_fields($result);
}
mysqli_close();
?>
```

### 14. WAP in php to create database and creation of table.
```php
Creating database:
<?php
$conn = mysqli_connect("localhost", "root", "");
if (!$conn) {
	die("Can't connect to MySQL");
}

$sql = "CREATE DATABASE db";
if (!mysqli_query($conn, $sql) {
	die("Can't create Database");
}
echo "Created database</br>";

mysqli_close($conn);
?>

Creating Table:
<?php
$conn = mysqli_connect("localhost", "root", "", "db");
if (!$conn) {
	die("Can't create Table");
}

$sql = "CREATE TABLE my_table(name VARCHAR(22), id INT(4))";
if(!mysqli_query($conn, $sql) {
	die("Error: ".mysqli_error($conn));
}
echo "Created table<br/>";

mysqli_close($conn);
?>
```
O/P
```
Created database
Created table
```

### 15. How to used list and button in form? Give suitable example.
- List
	- The list represents a windows control to display a list of items to a user.
	- A user can select an item from the list.
	- User can either select one option from a list or multiple options, depending
		on the type of list.
- Button
	- A button is a control, which is an interactive component that enables users
		to communicate with an application which we click and release to perform
		some actions.
	- A button can be clicked by using the mouse, ENTER key, or SPACEBAR if the
		button has focus.
- Example:
	```php
	<form action="<?php $_PHP_SELF ?>" method="post">
		<select name="language">
			<option name="C">C</option>
			<option name="C++">C++</option>
			<option name="PHP">PHP</option>
		</select>
		<input type="submit">
	</form>

	<?php
	if (isset($_POST["language"])) {
		echo "Selected: ".$_POST["language"];
	}
	?>
	```

### 16. Answer the following

#### i) Use of cookies
- Cookie save the data in browser, so next time refresh the browser it will not
	delete from browser.
- Cookie is used to identify the user.
- A cookie is a small file that server embeds to user's computer.
- Each time the same computer requests a page with a browser, it will send the
	cookie too.

#### ii) How to set the cookie?
- Use `setcookie` function to create cookie.
- Syntex:
	```
	setcookie($cookie_name, $cookie_value, $time, $location)
	```

#### iii) How to modify?
- Set cookie agien with `setcookie` function.

#### iv) How to delete the cookies?
- To delete cookie, we can use `setcookie` function with expiration date in
	past.
- Example:
	```
	setcookie($cookie_name, "", time() - 3600);
	```
- We can also put `null` in time section to delete cookie.
- Example
	```
	setcookie($cookie_name, "", null);
	```

### 17. Define GET and POST methods.
#### GET
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
