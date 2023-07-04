An Entity Relationship Diagram (ERD) is a visual representation of different
data using conventions that describe how these data are related to each other.

Example of ER Diagram:

![ER Diagram](./ER.svg)

In the diagram, the elements inside rectangles are called entities while the
items inside diamonds denote the relationships between entities.

In the diagram, the elements inside rectangles are called entities while the
items inside diamonds denote the relationships between entities.

## Features

### Entity

- An entity can be a person, place, event, or object that is relevant to given
  system.
- For Example, a school system may include student, teacher, major courses,
  subject, fees, and other items.
- Entites are represented in ER diagrams by a rectangles and named using
  singular nouns.

### Weak Entity

- A weak entity is an entity that depends on teh existence of another entity.
- A weak entity is represented in a database by a separated table, but it does
  not have a primary key of its own.
- It relies on the primary key of the entity on which it depends.
- Example:
  - Consider a databse of orders placed by customers at a retail store.
    "customer" entity might be the identifying entity, while the "order" entity
    is the weak entity. Each order is associated with specific customer, and the
    customer's primary key (e.g. a customer ID) is used as the primary key for
    the order as well. This means that the order cannot be uniquely identified
    without also specifying the customer to which it belongs.
- The single identifying entity can have multiple weak entities associated with
  it.
- Diagram:
  ```
  +---------+      +--------------+
  |         |      |+------------+|
  | Orders  |------||Orders Items||
  |         |      |+------------+|
  +---------+      +--------------+
  ```

### Attribute

- An attributes is a characterstic or property of an entity.
- Attributes are represented as columns in a database table, with each row
  representing a single entity and each column representing an attribute of that
  entity.
- Example: A "customer" table might include attributes such as "name",
  "address," and "phone number," with each attribute storing information about a
  perticular customer.
- There are two types of attributes:
  - Multivalued Attribute
  - Derived Attribute

#### Multivalued Attribute

- If an attribute can have more than one value it is called an multivalued
  attribute.
- It is important to note that this is different to an attribute having it own
  attributes.
- Example: A "customer" entity can have multiple "phone_numbers" values.
- Diagram: ![Multivalued Attribute Diagram](./Multivalued-Attribute.svg)

#### Derived Attribute

- An attribute based on another attribute.
- Example: "Age" can be derived from "Date of birth".
- Diagram: ![Derived Attribute Diagram](./Derived-Attribute.svg)

### Relationship

- A relationship describes how entities interact.
- Example: The entity “carpenter” may be related to the entity “table” by the
  relationship “builds” or “makes”.
- Relationships are represented by diamond shapes and are labeled using verbs.

#### Recursive Relationship

- The same entity participates more than once in the relationship.
- Example: An employee can be a supervisor and be supervised, so there is a
  recursive relationship.

## Extended Features

### Generalization

- A generalization hierarchy is a form of abstraction that specifies that two or
  more entities that share common attributes can be generalized into a
  higher-level entity type called a super type or generic entity.
- The lower level of entities becomes the subtypes, or categories, to the super
  type. Subtypes are dependent entities.
- Example: Account is the higher-level entity set and saving account and current
  account are lower-level entity sets.
- Diagram: ![Generalization Diagram](./Generalization.webp)

### Specialization

- Specialization is the process of taking subsets of the higher-level entity set
  to form lower-level entity sets.
- It is a process of defining a set of subclasses of an entity type, which is
  called the super class of the specialization.
- The process of defining subclass is based on the basis of some distinguish
  characteristics of the entities in the super class.
- Diagram: ![Specialization Diagram](./Specialization.webp)

### Aggregration

- Aggregration is a process when relation between two entities is treated as a
  single entity.
- Example: The relationship between Center and Course together, is acting as an
  Entity, which is in relationship with another entity Visitor.
- Diagram: ![Aggregration Diagram](./Aggregration.webp)

## Resources

- [What is an Entity Relationship Diagram (ERD)?](https://www.lucidchart.com/pages/er-diagrams)
- [The Enhanced ER Model](https://www.studytonight.com/dbms/generalization-and-specialization.php)
