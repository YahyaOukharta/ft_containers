# single left rotate at node N:

- save initial_NODE_PARENT
```
N->parent = initial_NODE_PARENT->parent
initial_NODE_PARENT->parent->right = N // right or left // if exists
N->left = initial_NODE_PARENT
initial_NODE_PARENT->parent = N
```

# single right rotate at node N:

- save initial_NODE_PARENT
```
N->parent = initial_NODE_PARENT->parent
initial_NODE_PARENT->parent->left = N // right or left // if exists
N->right = initial_NODE_PARENT
initial_NODE_PARENT->parent = N
```
