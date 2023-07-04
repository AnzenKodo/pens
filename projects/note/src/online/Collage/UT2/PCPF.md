## 1. Explain database manipulation.

Resources: https://youtu.be/dFEWzUqU5lo

In Prolog, database manipulation is typically done using a combination of
predicates and rules. A predicate is a logical statement that describes a
relationship between one or more objects, and a rule is a logical statement that
defines how one predicate can be derived from other predicates.

There are two type of Database Manipulation:

### Static Database Manipulation.

Static database manipulation refers to the process of modifying a database that
is not expected to change during the execution of a program. The data is
considered static, meaning it will not change after the program is started.

Database manipulation commands give us the power to alter the meaning of
predicates while we are executing statements. Predicates whose definitions are
altered during run-time are called dynamic predicates,

Example of static Database Manipulation:

```prolog
?- listing.
yes

?-assert(happy(maria)).

?- listing.
happy(maria).

?- assert(happy(vineet)).
yes

?- assert(happy(cassius)).
yes

?- assert(happy(brutus)).
yes

?- assert(happy(vineet)).
yes
```

### Dynamic Database Manipulation

Dynamic database manipulation refers to the process of modifying a database that
is expected to change during the execution of a program. The data is considered
dynamic, meaning it can change during the execution of the program.

Database manipulation is especially useful for storing in memory evaluation
results, to the effect that if we ever need to compute the same goal again in
the future, we don't have to redo the calculations: we only have to look up the
asserted fact. This is called memorization or caching, and it can greatly
increase computational speed.

Example of Dynamic Database Manipulation:

```prolog
:- dynamic lookup/3.
add_and_square(X,Y,Res) :- lookup(X,Y,Res). !.
add_and_square(X,Y,Res) is (X+Y) (X+Y), assert(lookup(X,Y.Res)).
```

## 2. What is imperative control flow?

PROLOG gives the programmer explicit control-flow features to completely control
how PROLOG processes the input that has been provided and how it evaluates the
result the use has requested. It is implemented using what is known in PROLOG as
the cut.

The cut, in PROLOG, is a predicate with no argument and written as T, which
always succeeds, but cannot be backtracked past. It means you cannot backtrack
after you encounter it. It is used to stop any unwanted backtracking and this in
turn stops any extra solutions from being found by PROLOG.

The cut should be used only when understood properly. There is a temptation many
programmers have to start using the cut as an experiment when the code is not
working as intended. If you do this, remember that wh debugging is complete, you
should be able to understand the need for every cut you used in your code. The
use o cut should hence be commented right next to where it is used precisely.
This is best practice.

Example: Suppose we have the following facts already present in our database:

```prolog
teaches(dr_frodo, history).   studies(ahmed, english).
teaches(dr_frodo, english).   studies(anshuman, english).
teaches(dr_frodo, chemistry). studies(andre, chemistry).
teaches(dr_fondu, physics).   studies(alex, physics).
```

Then consider the following query and its outputs:

```prolog
?- teaches(dr_frodo, course), studies(student, course).
course = english
student ahmed;

course = english
student =  anshuman;

course = chemistry
student = andre;

false.
```

Backtracking has not been stopped in any way, shape, or form over here.

Course is in the beginning bound to history in the first rule in the top-left,
but because there are no students of history, when this goal fails, backtracking
takes place and Course gets bound again to english, and the next goal is tried
and 2 answers are found in ahmed and anshuman, after which backtracking occurs
again, and Course is bound to chemistry, and a final Student, andre, is found.

Dr. Fondu and Alex are ignored by the way because the query makes it absolutely
clear that only Dr. Frodo's courses are to be checked. If you wondered this,
please read the information provided more carefully from the next time!

Now, let us start adding the cut to different parts of the query and understand
how it works.

**Case 1**

```prolog
?-teaches(dr_frodo, Course), !, studies (Student, Course).
false.
```

This time Course is first bound to history, then the cut is executed, and then
studies goal is tried and fails (because nobody studies history according to the
database). Because of the cut, we cannot backtrack to the teaches goal to find
another binding for Course, so the whole query fails, and the result is returned
as False.

**Case 2:**

```prolog
?-teaches(dr_frodo, Course), studies (Student, Course), !.
Course english
Student = ahmed:
false.
```

Here the teaches goal is tried as usual, and Course is bound to history, again
as usual. Next the studies goal is tried and fails, so we don't get to the cut
at the end of the query at this point, and backtracking can occur.

Thus, the teaches goal is re-tried, and Course is bound to english. Then the
studies goal is tried again, and succeeds, with Student = ahmed. After that, the
cut is tried with it reaching the end of the query and of course succeeds, so no
further backtracking is possible and only one solution is thus found. If you
enter a semi-colon after the first solution, you get a false as shown.

```prolog
?-!, teaches(dr_frodo, Course), studies (Student, Course).
Course = english
Student = ahmed;
```

This means that: vineet will enjoy X if X is a taco and X is not a Big
BellyTaco. This is very similar to the original statement given: vineet enjoys
alltacos except Big BellyTacos.

_**Negation as failure**_ is an important tool for the following reasons:

1. It helps with expressivity. Especially, the ability to show exceptions
   safely.
2. Negation as failure instead of the cut-fail combination gives us better
   chance of not making the errors that often happen due to the use of cuts.
3. It is built-in for PROLOG, so we do not have to define it ourselves. In
   PROLOG, the operator \+ stands for negation as failure, so we can better
   describe vineet's preferences as shown:

```prolog
enjoys(vineet,X):- taco(X), 1+ big belly taco(X).
```

## 3. What is dynamic Database manipulation?

Dynamic database manipulation refers to the process of modifying a database that
is expected to change during the execution of a program. The data is considered
dynamic, meaning it can change during the execution of the program.

Dynamic Database manipulation is especially useful for storing in memory
evaluation results, to the effect that if we ever need to compute the same goal
again in the future, we don't have to redo the calculations: we only have to
look up the asserted fact. This is called memorization or caching, and it can
greatly increase computational speed.

Here is a simple example of this technique at work:

```prolog
:- dynamic lookup/3.
add_and_square(X,Y,Res) :- lookup(X,Y,Res). !.
add_and_square(X,Y,Res) is (X+Y) (X+Y), assert(lookup(X,Y.Res)).
```

What does this program do?

It takes two numbers X and Y, adds X to Y, and then squares the result.

But the point to understand is this: how does it do it? Let us check out the
code above.

First, notice that we have declared 'lookup' in the beginning as a dynamic
predicate.

This is mandatory if we want to use lookup during runtime.

Second, notice how there are two clauses defining add_and_square.

The second one in the third line will do the required arithmetic calculation and
add or 'assert' the result into the PROLOG factbase using the 'predicate'
lookup. This means that it caches and stores the result into memory.

Finally, the first clause checks the database to see if the evaluation we need
has already been done before and if it has been, the program will just return
the final value, and the cut will prevent it from entering the second clause.
When we run the code, we have the following result:

```prolog
?-add_and_square(2,4,X).
X = 36
yes
```

Here's an example of the program at work. Suppose we give PROLOG another query:

```prolog
?- add_and_square(1,5,Y). 
Y = 36 
yes
```

If we now ask for a listing, we see that the database now contains:

```prolog
lookup(2, 4, 36). 
lookup(1, 5, 36).
```

Should we a second time, request PROLOG to add and square 1 and 5 with the same
predicate 'add_and_square', it will not make the evaluation again. It will
simple return the calculated result from the database.

To round out our fundamentals of static and dynamic database manipulation, heed
a word of warning. Although manipulating databases in PROLOG is a very tempting
and necessary technique, it can lead to difficult, tangled code, especially when
using dynamic manipulations. If you depend on it a little too much in a program
with loads of backtracking involved and recursion to boot, understanding what is
going on and tracing your steps going back for debugging can be a nightmare. It
is a non-declarative feature of PROLOG that should be used sparingly and very
carefully.

## 4. What is logic programming?

Logic programming is a paradigm of programming that is based on formal logic.

The most well-known logic programming language is Prolog, which stands for
"Programming in Logic".

Logic is shown in the form of relationships (called as facts and rules).

Logic programming languages use a declarative programming style, where the
programmer states the desired properties of the solution rather than describing
the steps to be taken to achieve it.

In logic programming, the program is a set of logical statements that describe
the relationships between different objects and their properties, and the goal
of the program is to find a set of values for the objects that satisfies all of
the logical statements.

The program then uses a reasoning engine, often based on resolution theorem
proving, to deduce the solution.

This approach is particularly well-suited for tasks that involve symbolic
reasoning and rule-based systems, such as natural language processing, expert
systems, and automated theorem proving.

## 5. Application of prolog.

Prolog (short for "Programming in Logic") is a programming language that is
particularly well-suited for tasks involving symbolic reasoning and rule-based
systems.

It is often used in artificial intelligence and natural language processing
applications, such as language translation, expert systems, and automated
theorem proving.

Prolog is also used in some database systems, as well as in some educational
settings as a tool for teaching logic and formal reasoning. Additionally, it can
be applied in medical diagnosis, natural language understanding, game playing,
and many other fields.

## 6. What is List in Prolog?

We have already seen simple items like parameters or arguments in PROLOG
programs. Now, as step up, in PROLOG, a widely used data-structure is the list.

Lists are written in the following way:

- They must start and end wit square brackets `[]`, and
- All the items they contain inside them must be separated by commas. Here is a
  simple list `[a, fawad, Variable, carrot]`

PROLOG has a special functionality to split the beginning of the list that we
call the head form the remainder of the list that we call the tail. We have to
write symbol '|'(pronounced 'bar') in the list to differentiate between the
first item of the list and the remainder of it.

**For exmple**

```prolog
[one, two, three] = [A|B]
```

where `A = one` and `B = [two, three]`

The unification here pulls through and succeeds. How? 'A' is bound to the first
item and 'B' to remainder of it.

Here are some more example:

```prolog
[a, b, c, d, e, f, g]
[carrots, parrots, bandana, sauna]
[] /* Note An empty list is still an actual list */
```

## 7. Explain Facts, Rules and Queries along with an example.

In Prolog, a program is made up of a collection of facts and rules that describe
relationships between different objects.

1. Facts are simple statements that describe a relationship between one or more
   objects. They are represented as predicates and are used to assert
   information into the program. An example of a fact would be: "John is a
   software engineer".

```prolog
person(john, age(30), job('software engineer')).
```

2. Rules are logical statements that define how one predicate can be derived
   from other predicates. They are used to express more complex relationships
   between objects, and are represented as a head predicate followed by a body
   of predicates. An example of a rule would be: "If a person is older than 30
   and has a job as a software engineer, then they are considered a senior
   software engineer."

```prolog
senior_software_engineer(X) :- person(X, age(Age), job('software engineer')), Age > 30.
```

3. Queries are used to ask the Prolog program to find solutions that satisfy a
   given predicate. Queries are used to retrieve information from the program
   and are represented as predicates with variables. An example of a query would
   be: "Who is a senior software engineer?". Copy code

```prolog
?- senior_software_engineer(X).
```

The Prolog interpreter will attempt to find a value for the variable X that
makes the predicate senior_software_engineer(X) true. In this case, X will be
bound to the value 'john' if the previously defined rule and fact are present in
the knowledge base.

In summary, facts are used to assert information, rules are used to express
complex relationships, and queries are used to retrieve information from the
program. Prolog uses a reasoning engine to deduce the solution based on the
facts and rules provided and the queries made by the user.

## 8. Explain the unification and resolution in prolog with example.

### Unification

The terminology for matching items elements with variables is known as
unification.

- Unification is the process of applying a correct substiution the two equal
  name predical identical (same).
- In unification one or more variables tagged with a values to make the two
  terms similar or identical.
- Example:
  ```prolog
  name(X, Student). name(Student, Y)
    X = Student
    Y = Student / Student = Y

  name(x, Collage). name(Y, Computer)
    X != Y % (Variable to Variable does not match)
    Collage != Computer % Not equale string wrong unification
  ```
  _'%' is used when you want to comment something in Prolog._
- Variables only starts with Capital letters or an Underscore it will be a
  single letter.
- For instance PROLOG can unify **Collage(X)** and **Collage(Student)** by
  binding variable X to student that means we are assigning 'Student' to the
  variable X.

### Resolution

Resolution is one kind of proof technique that works this way:

1. Select two clauses that contain conflicting terms.
2. Combine those two clauses and cancel out the conficting terms. For example we
   have following statement:
   1. If it is a preasent day, you will do strawberry picking.
   2. If you are doing strawberry picking you are happy.

   Above statement can be written in propositional logic like this:
   1. strawberry_picking <- pleasent
   2. happy <- strawberry_picking

   And again these statement can be written in CNF
   1. (strawberry_picking v~ pleasent ) ^
   2. (happy v~ strawberry_picking)
3. For any propositional logic, there are two easy rules we follow:
   ```
   (p ∧ q) ≡ (p ∨ q)  
   ¬(p → ¬q) ≡ (p ∨ q)
   ```

   What do those symobls means? Lets say we have following clauses in PROLOG:
   ```prolog
   m:-b. and t:-p, m, z.
   ```
   The clause 'm' get replaced with `b` in the second clause and now we can say
   that:
   ```prolog
   t:-p, b, z.
   ```
   This is resolution. This means that when you resolve two clauses you reduce
   them to get one clause.
4. Another easy example, we have two sentances:
   - Man like joking.
   - Chandler is a man.

   Now we ask query 'Who likes joking.' So, by resolving the two sentences, we
   get one new sentence: Chandler like joking.

## 9. List operation in Prolog.

| Operations          | Definition                                                                                       | Predicates            |
| ------------------- | ------------------------------------------------------------------------------------------------ | --------------------- |
| Membership Checking | During this operation, we can verify whether a given element is member of specified list or not? | list_member(X,L)      |
| Length Calculation  | With this operation, we can find the length of a list.                                           | list_length(L,N)      |
| Concatenation       | Concatenation is an operation which is used to join/add two lists.                               | list_concat(L1,L2,L3) |
| Delete Items        | This operation removes the specified element from a list.                                        | list_delete(L1,L2,L3) |
| Append Items        | Append operation adds one list into another (as an item).                                        | list_append(L1,L2,L3) |
| Insert Items        | This operation inserts a given item into a list.                                                 | list_insert(X,L,R)    |

## 10. Lazy versus Eager evaluation order for function parameters.

In programming, the evaluation order of function parameters can be either lazy
or eager.

1. Lazy evaluation, also known as non-strict evaluation, is a technique where
   the evaluation of function parameters is delayed until they are actually
   needed. This means that the function arguments are only evaluated when they
   are needed to compute the final result. This can be useful when working with
   large or infinite data sets, as it can save a lot of computation time and
   resources.
2. Eager evaluation, also known as strict evaluation, is a technique where the
   evaluation of function parameters is done immediately, before the function is
   called. This means that all function arguments are evaluated, whether they
   are needed to compute the final result or not. This can be useful when
   working with small and well-defined data sets, as it can make the code easier
   to understand and debug.

In Prolog, the evaluation order is typically Lazy and it's driven by the query
made by the user. The Prolog engine uses a backtracking algorithm to explore
different possible solutions to a query and the evaluation of parameters is done
only when it's needed to find a solution.

## 11. What is dynamic database.

A dynamic database is a type of database that can be modified or updated during
the execution of a program. This is in contrast to a static database, which is a
type of database that is loaded into the program at the start and remains
unchanged throughout the execution.

Dynamic databases are often used in applications where the data is expected to
change frequently, such as in real-time data analysis, distributed systems, and
other applications that require the ability to modify the data in response to
changing conditions.

See also
[What is dynamic Database manipulation?](#-3.-what-is-dynamic-database-manipulation?)
for more.
