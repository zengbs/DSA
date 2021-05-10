#ifndef BINARY_HEAP

#define BINARY_HEAP

#include <stdlib.h>
#include <limits.h>

typedef struct Node_ {
    int key;
    int degree;
    struct Node_* p;
    struct Node_* child;
    struct Node_* sibling;
} Node;

typedef struct {
    Node* head;
} Binomial_heap;

Binomial_heap*
make_binomial_heap(void);

void
binomial_link(Node* y, Node* z);


Binomial_heap*
binomial_heap_union(Binomial_heap* h1, Binomial_heap* h2);

Binomial_heap*
binomial_heap_insert(Binomial_heap* H, Node* x);

#endif
