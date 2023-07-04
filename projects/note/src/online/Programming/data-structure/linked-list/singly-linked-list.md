A singly linked list is a linear data structure that consists of a sequence of
nodes, where each node stores a value and a pointer to the next node in the
list. The first node in the list is called the head, and the last node in the
list is called the tail. The tail node typically has a NULL next pointer to
indicate the end of the list.

Singly linked lists are useful for storing and manipulating sequences of data,
as they allow for efficient insertion and deletion of elements at any position
in the list. However, they do not allow for efficient access to elements at
arbitrary positions, as you have to traverse the list from the beginning to
access elements further down the list.

For example, to access the third element in a singly linked list with four
nodes, you would have to start at the head of the list and follow the next
pointers twice to reach the third node. This requires you to traverse the list
from the beginning, which can be inefficient if the list is large and you need
to access elements towards the end of the list.

In contrast, data structures like arrays or random-access lists allow for
efficient access to elements at arbitrary positions, as you can directly access
any element by its index. However, they may not be as efficient for inserting or
deleting elements at specific positions, as this may require shifting elements
around in the data structure.

Singly linked lists are efficient for inserting or deleting elements at specific
positions because they only require a single pointer per node, which makes it
easy to update the next pointers of the nodes around the insertion or deletion
point. Example:

1. Create a new node with the desired value.
2. Set the next pointer of the new node to point to the current fourth node in
   the list.
3. Set the next pointer of the second node in the list to point to the new node.

## Example:

```
  head                                      tail
+------+    +------+    +------+    +------+
| data |    | data |    | data |    | data |
+------+    +------+    +------+    +------+
| next |--->| next |--->| next |--->| next |---> NULL
+------+    +------+    +------+    +------+
```

## Algorithm to insert new nodes at the beginning of singly Linked list

1. **Declare a head pointer and make it as NULL:** The head pointer is a pointer
   that points to the first node in the list. By initializing it to NULL, you
   create an empty list with no nodes.
2. **Create a new node with the given data:** To insert a new node at the
   beginning of the list, you first need to create a new node with the desired
   data. This can be done using a function that allocates memory for the new
   node and sets its data field to the given value.
3. **Make the new node points to the head node:** After creating the new node,
   you need to update its next pointer to point to the current head node. This
   will make the new node the first node in the list, with the head node as the
   second node.
4. **Finally, make the new node as the head node:** To complete the insertion,
   you need to update the head pointer to point to the new node. This will make
   the new node the first node in the list and the head of the list.

## Resources

1. [Singly Linked Lists Tutorial - What is a Linked List?](https://youtu.be/HB7TcYklBHY)
