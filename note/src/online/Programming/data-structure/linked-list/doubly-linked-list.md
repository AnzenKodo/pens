A doubly linked list is a linear data structure that consists of a sequence of
nodes, where each node stores a value and pointers to the previous and next
nodes in the list. The first node in the list is called the head, and the last
node in the list is called the tail. The head node typically has a NULL prev
pointer, and the tail node typically has a NULL next pointer, to indicate the
beginning and end of the list, respectively.

Doubly linked lists are useful for storing and manipulating sequences of data,
as they allow for efficient insertion and deletion of elements at any position
in the list. They also allow for efficient access to both the next and previous
elements in the list, as each node stores pointers to both its neighbors.

## Difference between Doubly and Singly Linked List?

### Number of pointers

A singly linked list stores a single pointer per node, which points to the next
node in the list. In contrast, a doubly linked list stores two pointers per
node, which point to the next and previous nodes in the list.

### Accessibility

A singly linked list allows for efficient insertion and deletion of elements at
any position in the list, but does not allow for efficient access to elements at
arbitrary positions. In contrast, a doubly linked list allows for efficient
insertion and deletion of elements at any position in the list, as well as
efficient access to both the next and previous elements in the list.

### Memory usage

A doubly linked list uses more memory than a singly linked list, as it stores
two pointers per node instead of just one. This can make it less efficient in
situations where memory usage is a concern.

## Agorithm to create doubly linked list and display the list.

1. Declare a head pointer and make it as NULL. This will be used to keep track
   of the first node in the list.
2. Declare a tail pointer and make it as NULL. This will be used to keep track
   of the last node in the list.
3. Read in the values for the nodes in the list.
4. For each value, create a new node with the value and set its next and prev
   pointers to NULL.
5. If the list is empty, set the head and tail pointers to the new node.
6. If the list is not empty, set the next pointer of the tail node to the new
   node, and the prev pointer of the new node to the tail node. Then, update the
   tail pointer to point to the new node.
7. Repeat steps 4-6 until all values have been read in.
8. Traverse the list from the head and print the values of the nodes. To do
   this, set a pointer to the head of the list and follow the next pointers
   until you reach the end of the list.

## Resources

1. [Introduction to Doubly Linked List](https://www.youtube.com/watch?v=e9NG_a6Z0mg)
