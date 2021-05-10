/* https://github.com/stephanoumenos/BinomialHeap/blob/master/binomial_heap.c
 * */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<stdint.h>
#include<limits.h>

typedef struct Node_t {
	struct Node_t* 	parent;
	struct Node_t* 	next;
	struct Node_t* 	child;

	unsigned int 	degree;
	int			    key;
	const void*	   	value;
	struct Node_t**	ref;
}Node;

typedef struct BHeap_t {
	struct Node_t* 	head;
	struct Node_t*	min;
}BHeap;


void iheap_init(BHeap* heap)
{
	heap->head = NULL;
	heap->min  = NULL;
}

void iheap_node_init_ref(Node** _h,
				      int key, const void* value)
{
	Node* h = *_h;
	h->parent = NULL;
	h->next   = NULL;
	h->child  = NULL;
	h->degree = INT_MAX;
	h->value  = value;
	h->ref    = _h;
	h->key    = key;
}

void iheap_node_init(Node* h, int key, const void* value)
{
	h->parent = NULL;
	h->next   = NULL;
	h->child  = NULL;
	h->degree = INT_MAX;
	h->value  = value;
	h->ref    = NULL;
	h->key    = key;
}

 const void* iheap_node_value(Node* h)
{
	return h->value;
}

 int iheap_node_in_heap(Node* h)
{
	return h->degree != INT_MAX;
}

 int iheap_empty(BHeap* heap)
{
	return heap->head == NULL && heap->min == NULL;
}

/* make child a subtree of root */
void __iheap_link(Node* root,
			       Node* child)
{
	child->parent = root;
	child->next   = root->child;
	root->child   = child;
	root->degree++;
}

/* merge root lists */
 Node* __iheap_merge(Node* a,
					     Node* b)
{
	Node* head = NULL;
	Node** pos = &head;

	while (a && b) {
		if (a->degree < b->degree) {
			*pos = a;
			a = a->next;
		} else {
			*pos = b;
			b = b->next;
		}
		pos = &(*pos)->next;
	}
	if (a)
		*pos = a;
	else
		*pos = b;
	return head;
}

/* reverse a linked list of nodes. also clears parent pointer */
 Node* __iheap_reverse(Node* h)
{
	Node* tail = NULL;
	Node* next;

	if (!h)
		return h;

	h->parent = NULL;
	while (h->next) {
		next    = h->next;
		h->next = tail;
		tail    = h;
		h       = next;
		h->parent = NULL;
	}
	h->next = tail;
	return h;
}

void __iheap_min(BHeap* heap,
			      Node** prev,
			      Node** node)
{
	Node *_prev, *cur;
	*prev = NULL;

	if (!heap->head) {
		*node = NULL;
		return;
	}

	*node = heap->head;
	_prev = heap->head;
	cur   = heap->head->next;
	while (cur) {
		if (cur->key < (*node)->key) {
			*node = cur;
			*prev = _prev;
		}
		_prev = cur;
		cur   = cur->next;
	}
}

void __iheap_union(BHeap* heap, Node* h2)
{
	Node* h1;
	Node *prev, *x, *next;
	if (!h2)
		return;
	h1 = heap->head;
	if (!h1) {
		heap->head = h2;
		return;
	}
	h1 = __iheap_merge(h1, h2);
	prev = NULL;
	x    = h1;
	next = x->next;
	while (next) {
		if (x->degree != next->degree ||
		    (next->next && next->next->degree == x->degree)) {
			/* nothing to do, advance */
			prev = x;
			x    = next;
		} else if (x->key < next->key) {
			/* x becomes the root of next */
			x->next = next->next;
			__iheap_link(x, next);
		} else {
			/* next becomes the root of x */
			if (prev)
				prev->next = next;
			else
				h1 = next;
			__iheap_link(next, x);
			x = next;
		}
		next = x->next;
	}
	heap->head = h1;
}

 Node* __iheap_extract_min(BHeap* heap)
{
	Node *prev, *node;
	__iheap_min(heap, &prev, &node);
	if (!node)
		return NULL;
	if (prev)
		prev->next = node->next;
	else
		heap->head = node->next;
	__iheap_union(heap, __iheap_reverse(node->child));
	return node;
}

/* insert (and reinitialize) a node into the heap */
void iheap_insert(BHeap* heap, Node* node)
{
	Node *min;
	node->child  = NULL;
	node->parent = NULL;
	node->next   = NULL;
	node->degree = 0;
	if (heap->min && node->key < heap->min->key) {
		/* swap min cache */
		min = heap->min;
		min->child  = NULL;
		min->parent = NULL;
		min->next   = NULL;
		min->degree = 0;
		__iheap_union(heap, min);
		heap->min   = node;
	} else
		__iheap_union(heap, node);
}

void __iheap_uncache_min(BHeap* heap)
{
	Node* min;
	if (heap->min) {
		min = heap->min;
		heap->min = NULL;
		iheap_insert(heap, min);
	}
}

/* merge addition into target */
void iheap_union(BHeap* target, BHeap* addition)
{
	/* first insert any cached minima, if necessary */
	__iheap_uncache_min(target);
	__iheap_uncache_min(addition);
	__iheap_union(target, addition->head);
	/* this is a destructive merge */
	addition->head = NULL;
}

 Node* iheap_peek(BHeap* heap)
{
	if (!heap->min)
		heap->min = __iheap_extract_min(heap);
	return heap->min;
}

 Node* iheap_take(BHeap* heap)
{
	Node *node;
	if (!heap->min)
		heap->min = __iheap_extract_min(heap);
	node = heap->min;
	heap->min = NULL;
	if (node)
		node->degree = INT_MAX;
	return node;
}

void iheap_decrease(BHeap* heap, Node* node,
				  int new_key)
{
	Node *parent;
	Node** tmp_ref;
	const void* tmp;
	int   tmp_key;

	/* node's priority was decreased, we need to update its position */
	if (!node->ref || new_key >= node->key)
		return;
	node->key = new_key;
	if (heap->min != node) {
		if (heap->min && node->key < heap->min->key)
			__iheap_uncache_min(heap);
		/* bubble up */
		parent = node->parent;
		while (parent && node->key < parent->key) {
			/* swap parent and node */
			tmp           = parent->value;
			tmp_key       = parent->key;
			parent->value = node->value;
			parent->key   = node->key;
			node->value   = tmp;
			node->key     = tmp_key;
			/* swap references */
			if (parent->ref)
				*(parent->ref) = node;
			*(node->ref)   = parent;
			tmp_ref        = parent->ref;
			parent->ref    = node->ref;
			node->ref      = tmp_ref;
			/* step up */
			node   = parent;
			parent = node->parent;
		}
	}
}

void iheap_delete(BHeap* heap, Node* node)
{
	Node *parent, *prev, *pos;
	Node** tmp_ref;
	const void* tmp;
	int tmp_key;

	if (!node->ref) /* can only delete if we have a reference */
		return;
	if (heap->min != node) {
		/* bubble up */
		parent = node->parent;
		while (parent) {
			/* swap parent and node */
			tmp           = parent->value;
			tmp_key       = parent->key;
			parent->value = node->value;
			parent->key   = node->key;
			node->value   = tmp;
			node->key     = tmp_key;
			/* swap references */
			if (parent->ref)
				*(parent->ref) = node;
			*(node->ref)   = parent;
			tmp_ref        = parent->ref;
			parent->ref    = node->ref;
			node->ref      = tmp_ref;
			/* step up */
			node   = parent;
			parent = node->parent;
		}
		/* now delete:
		 * first find prev */
		prev = NULL;
		pos  = heap->head;
		while (pos != node) {
			prev = pos;
			pos  = pos->next;
		}
		/* we have prev, now remove node */
		if (prev)
			prev->next = node->next;
		else
			heap->head = node->next;
		__iheap_union(heap, __iheap_reverse(node->child));
	} else
		heap->min = NULL;
	node->degree = INT_MAX;
}






/* Deque */
struct Deque{
  int data;
  struct Deque *npx;
};


struct Deque* XOR(struct Deque *a, struct Deque *b)
{
  return (struct Deque*)((uintptr_t) (a) ^ (uintptr_t) (b));
}


void printList (struct Deque *endPoint)
{
    struct Deque *curr = endPoint;

    struct Deque *prev = NULL;
    struct Deque *sibling;

    while (curr != NULL)
    {
        printf ("%d ", curr->data);
        sibling = XOR (prev, curr->npx);
        prev = curr;
        curr = sibling;
    }
  printf("\n");
}



void push(struct Deque **endPoint, int data)
{
  struct Deque *newNode = (struct Deque *) malloc (sizeof (struct Deque) );
  newNode->data = data;
  newNode->npx = *endPoint;

  if (*endPoint != NULL)
  {
      (*endPoint)->npx = XOR(newNode, (*endPoint)->npx);
  }

  *endPoint = newNode;
}


void pop(struct Deque **endPoint)
{
  struct Deque *siblingNode;
  struct Deque *siblingsiblingNode;

  siblingNode     = (*endPoint)->npx;

  if (siblingNode != NULL){

    siblingsiblingNode = XOR(siblingNode->npx, *endPoint);
    siblingNode->npx  = siblingsiblingNode;

    free(*endPoint);
    *endPoint = siblingNode;
  }
  else{
    free(*endPoint);
    *endPoint = NULL;
  }
}



int main(){


//  struct Deque *left  = NULL;
//  struct Deque *right = NULL;
//
//  push(&left, 1);
//
//  right = left;
//
//  push(&left, 2);
//  push(&left, 3);
//  push(&right, 99);
//  push(&left, 4);
//  pop(&left);
//  push(&right, -1);
//  push(&right, 0);
//  pop(&right);
//  push(&right, 55);
//
//
//  printList(left);


  return 0;
}
