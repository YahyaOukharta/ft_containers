single left rotate at node N:

initial_NODE_R
initial_NODE_P

N->parent = initial_NODE_P->parent
initial_NODE_P->parent->right = N // right or left // if exists


N->left = initial_NODE_P
initial_NODE_P->parent = N

single right rotate at node N:


initial_NODE_L
initial_NODE_P


N->parent = initial_NODE_P->parent
initial_NODE_P->parent->left = N // right or left // if exists


N->right = initial_NODE_P
initial_NODE_P->parent = N
