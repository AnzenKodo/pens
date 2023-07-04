A threaded binary tree is a binary tree in which the nodes are threaded, or
connected, in a way that allows them to be traversed efficiently. In a threaded
binary tree, each node has a left and right pointer, just like in a regular
binary tree. However, if the left or right pointer of a node is null, it is
replaced with a thread that points to the in-order predecessor or successor of
the node, respectively. This allows the tree to be traversed in-order without
the need to follow a null pointer and backtrack, making the traversal more
efficient.

Threaded binary trees have several advantages over regular binary trees. They
use less memory, as the threads take up less space than full pointers. They also
allow for faster in-order traversal, as there is no need to follow null pointers
and backtrack. However, they are more difficult to modify than regular binary
trees, as the threads must be updated whenever the tree is modified.

Overall, threaded binary trees are a useful data structure for certain types of
tree traversal, but they may not be the best choice for all applications.

## Resources

- [Threaded binary tree | data structure](https://www.youtube.com/watch?v=1E95XJd5bS0)
