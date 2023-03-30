## 2 Marks

### 1) Define Normalization?

Normalization is a database design technique that reduces data redundancy and
eliminates undesirable characteristics like Insertion, Update and Deletion
Anomalies. Normalization rules divides larger tables into smaller tables and
links them using relationships. The purpose of Normalisation in SQL is to
eliminate redundant (repetitive) data and ensure data is stored logically.

### 2) Explain Functional Dependency?

A functional dependency is a constraint that specifies the relationship between
two sets of attributes where one set can accurately determine the value of other
sets.

It is denoted as **X** → **Y**, where **X** is a set of attributes that is
capable of determining the value of **Y**.

The attribute set on the left side of the arrow, X is called **Determinant**,
while on the right side, Y is called the **Dependent**.

To better understand:
https://www.geeksforgeeks.org/types-of-functional-dependencies-in-dbms/

### 3) Consider the table

| Emp_id | Emp_Name | Department | Salary |
| ------ | -------- | ---------- | ------ |
| E01    | Ahmad    | Production | 92780  |
| E02    | Jack     | Sales      | 88320  |
| E03    | Amar     | Quality    | 75850  |
| E04    | Sagar    | Production | 80590  |

#### Write the SQL for following:

##### a) List the employee record working in Production Department.

```sql
SELECT * FROM Employee WHERE Department = "Production"
```

##### b) List all Employee records.

```sql
SELECT * from Employee
```

##### c) List Employee details having the salary less than 90000.

```sql
SELECT * FROM Employee WHERE Salary < 90000
```

### 4) Explain Default and Check Constraints?

#### Default

A default constraint is used to specify a default value for a column in a table.
If a value is not specified for the column when a new row is inserted, the
default value will be used.

**Example:** you may want to set a default value of "N/A" for a column called
"phone" in a "customers" table, so that if no phone number is provided for a new
customer, the value "N/A" will be inserted into the "phone" column.

#### Check Constraint

A check constraint is used to specify a condition that must be met by the data
in a column. If a new value is inserted into the column that does not meet the
condition, the insert operation will fail.

**Example:** you may want to set a check constraint on a column called "age" in
a "students" table, so that the age of students must be greater than 16 and less
than 25.

### 5) Explain nested queries with examples?

A nested query in SQL contains a query inside another query.

The result of the inner query will be used by the outer query.

For instance, a nested query can have two SELECT statements, one on the inner
query and the other on the outer query.

Example:

```sql
SELECT * FROM Students
WHERE class = "IT" IN (SELECT tec_name FROM Teachers);
```

## 3 Marks

### 1) Write notes on DCL Commands?

The Data Control Language (DCL) commands present in SQL are

- GRANT
  - GRANT is a DCL command used to grant(give access to) security privileges to
    specific database users.
  - It is mostly used to restrict user access to INSERT, DELETE, SELECT, UPDATE,
    EXECUTE, ALTER or to provide privileges to user's data.
- REVOKE
  - REVOKE is a DCL command that is used to revoke the permissions/access that
    was granted via the GRANT command.
  - It is mostly used to revert back to the time when no access was specified,
    i.e., withdrawing the permission that was authorized to carry out specific
    tasks.

### 2) Write short notes on inference rules for functional dependency?

Inference rules are used to determine functional dependencies (FDs) that hold
between attributes in a relation.

Here are a few commonly used inference rules for functional dependency:

- Union rule: If **X → Y** and **X → Z** hold, then **X → Y U Z** also holds.
- Trivial dependency: **X → X** is always true for any attribute X in a
  relation.
- Reflexive rule: If **X → Y** holds, then **X → {X} U Y** also holds, where
  **{X}** is the set containing only **X**.
- Augmentation rule: If **X → Y** holds, then **X → Y U Z** also holds, where
  **Z** is any set of attributes in the relation.

### 3) Explain Procedure with syntax?

Procedures are generally used to encapsulate a specific set of actions that are
often used in an application.

Syntax:

```sql
CREATE PROCEDURE procedure_name (parameter1 data_type, parameter2 data_type, ...)
BEGIN
    -- Procedure body (SQL statements)
END;
```

### 4) Explain function with syntax?

In a database, a function is a predefined, reusable routine that performs a
specific task or calculation. Functions can take one or more input parameters,
perform some operation on those inputs, and return a single output value.

Syntax:

```sql
CREATE FUNCTION function_name (parameter1 data_type, parameter2 data_type, ...)
RETURNS return_data_type
BEGIN
    -- Function body (SQL statements)
END;
```

### 5) Create a table student having columns std_id, std_name,class and dob. Also add two records into the table?

```sql
CREATE TABLE Students (std_id int, std_name varchar(100), class varchar(32), dob date);
INSERT INTO Students (std_id, std_name, class, dob) values (1, "Tommey", "IT", '01-12-2003');
INSERT INTO Students (std_id, std_name, class, dob) values (2, "Jimmey", "IT", '02-01-2006');
```

## 5 Marks

### 1) Explain DDL Commands with Syntax and Example?

There are 4 Data Definition Language (DDL) commands:

- CREATE
  - This command builds a new table.
  - Syntax: `CREATE object_type object_name ([name] [parameters]);`
  - Example: `CREATE TABLE Student (id int, name varchar)`
- ALTER
  - An alter command modifies an existing database table. This command can add
    up additional column, drop existing columns and even change the data type of
    columns involved in a database table.
  - Syntax: `ALTER object_type object_name (parameters);`
  - Example: `ALTER TABLE Student ADD Address varchar(50);`
- DROP
  - A drop command is used to delete objects such as a table, index or view. A
    DROP statement cannot be rolled back, so once an object is destroyed,
    there’s no way to recover it.
  - Syntax: `DROP object_type object_name;`
  - Example: `DROP TABLE Student;`
- TRUNCATE
  - Similar to DROP, the TRUNCATE statement is used to quickly remove all
    records from a table. However, unlike DROP that completely destroys a table,
    TRUNCATE preserves its full structure to be reused later.
  - Syntax: `TRUNCATE TABLE table_name;`
  - Example: `TRUNCATE TABLE Student;`

### 2) Explain DML Commands with Syntax and Example?

There are 4 Data Definition Manipulation (DML) commands:

- SELECT
  - This command is used to retrieve rows from a table.
  - Syntax: `SELECT object_type FROM table_name where (parameters)`.
  - Example: `SELECT * FROM Student`
- UPDATE
  - This command modifies data of one or more records.
  - Syntax: `UPDATE table_name SET column_name = value where condition.
  - Example: `UPDATE Student SET name = "Jonny" WHERE roll_no is 5`
- INSERT:
  - This command adds one or more records to a database table. The insert
    command syntax is
  - Syntax: `INSERT INTO table_name [column(s)] VALUES [value(s)]`
  - Example: `INSERT INTO Student (roll_no, name) values (25, "Ron")`
- DELETE
  - This command removes one or more records from a table according to specified
    conditions.
  - Syntax: `DELETE FROM table_name where condition`
  - Example: `DELETE FROM Student where roll_no is 3`

### 3) Explain Program for JDBC with Example?

JDBC or Java Database Connectivity is a Java API to connect and execute the
query with the database.

Java application that needs to communicate with the database has to be
programmed using JDBC API.

Here is an example of a simple JDBC program that connects to a database, creates
a table, and inserts a record into that table:

```java
import java.sql.*;
 
public class JDBCDemo {
   
    public static void main(String args[]) throws SQLException, ClassNotFoundException {
        // Load driver class
        Class.forName("sun.jdbc.odbc.JdbcOdbcDriver");
 
        // Obtain a connection
        Connection con = DriverManager.getConnection(
            "jdbc:odbc:XE", "root", "12345");
 
        // Obtain a statement
        Statement st = con.createStatement();
 
        // Execute the query
        int count = st.executeUpdate("insert into students values(109, 'bhatt')");
        System.out.println(
            "number of rows affected by this query= "
            + count);
 
        con.close();
    }
}
```

### 4) Explain need of normalization along with all the normal forms?

Normalization is a database design technique that reduces data redundancy and
eliminates undesirable characteristics like Insertion, Update and Deletion
Anomalies. Normalization rules divides larger tables into smaller tables and
links them using relationships. The purpose of Normalisation in SQL is to
eliminate redundant (repetitive) data and ensure data is stored logically.

Here is a list of Normal Forms in SQL:

- 1NF (First Normal Form)
  - Each table cell should contain a single value.
  - Each record needs to be unique.
- 2NF (Second Normal Form)
  - Rule 1- Be in 1NF
  - Rule 2- Single Column Primary Key that does not functionally dependant on
    any subset of candidate key relation
- 3NF (Third Normal Form)
  - Rule 1- Be in 2NF
  - Rule 2- Has no transitive functional dependencies
- BCNF (Boyce-Codd Normal Form)
  - Even when a database is in 3rd Normal Form, still there would be anomalies
    resulted if it has more than one Candidate Key.
- 4NF (Fourth Normal Form)
  - If no database table instance contains two or more, independent and
    multivalued data describing the relevant entity, then it is in 4th Normal
    Form.
- 5NF (Fifth Normal Form)
  - A table is in 5th Normal Form only if it is in 4NF and it cannot be
    decomposed into any number of smaller tables without loss of data.
- 6NF (Sixth Normal Form)

### 5) Explain the types of functional dependency?

A functional dependency is a constraint that specifies the relationship between
two sets of attributes where one set can accurately determine the value of other
sets.

There are 4 type of functional dependency:

1. Trivial functional dependency
   - In Trivial Functional Dependency, a dependent is always a subset of the
     determinant.
   - i.e. If X → Y and Y is the subset of X, then it is called trivial
     functional dependency
2. Non-Trivial functional dependency
   - In Non-trivial functional dependency, the dependent is strictly not a
     subset of the determinant.
   - i.e. If X → Y and Y is not a subset of X, then it is called Non-trivial
     functional dependency.
3. Multivalued functional dependency
   - In Multivalued functional dependency, entities of the dependent set are not
     dependent on each other.
   - i.e. If a → {b, c} and there exists no functional dependency between b and
     c, then it is called a multivalued functional dependency.
4. Transitive functional dependency
   - In transitive functional dependency, dependent is indirectly dependent on
     determinant.
   - i.e. If a → b & b → c, then according to axiom of transitivity, a → c. This
     is a transitive functional dependency.
