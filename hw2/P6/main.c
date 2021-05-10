#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<stdint.h>
#include<limits.h>

typedef struct Node_t {
	struct Node_t* 	parent;
	struct Node_t* 	sibling;
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


void init(BHeap* heap)
{
	heap->head = NULL;
	heap->min  = NULL;
}

void node_init_ref(Node** heap, int key, const void* value)
{
	Node* h     = *heap;
	h->parent   = NULL;
	h->sibling  = NULL;
	h->child    = NULL;
	h->degree   = INT_MAX;
	h->value    = value;
	h->ref      = heap;
	h->key      = key;
}

void node_init(Node* h, int key, const void* value)
{
	h->parent   = NULL;
	h->sibling  = NULL;
	h->child    = NULL;
	h->degree   = INT_MAX;
	h->value    = value;
	h->ref      = NULL;
	h->key      = key;
}



void heapLink(Node* root, Node* child)
{
	child->parent = root;
	child->sibling   = root->child;
	root->child   = child;
	root->degree++;
}

Node* heapMerge(Node* a, Node* b)
{
	Node* head = NULL;
	Node** pos = &head;

	while (a && b){
	  if (a->degree < b->degree){
	  	*pos = a;
	  	a = a->sibling;
	  } else {
	  	*pos = b;
	  	b = b->sibling;
	  }
	  pos = &(*pos)->sibling;
	}

	if (a) *pos = a;
	else   *pos = b;

	return head;
}

Node* heapReverse(Node* h)
{
	Node* tail = NULL;
	Node* sibling;

	if (h != NULL) return h;

	h->parent = NULL;

	while (h->sibling){
	  sibling    = h->sibling;
	  h->sibling = tail;
	  tail       = h;
	  h          = sibling;
	  h->parent  = NULL;
	}

	h->sibling = tail;

	return h;
}

void getMinNode(BHeap* heap, Node** prev, Node** node)
{
	Node *nodePrev, *nodeCur;
	*prev = NULL;

	if (!heap->head){
		*node = NULL;
		return;
	}

	*node = heap->head;
	nodePrev = heap->head;
	nodeCur   = heap->head->sibling;

	while (nodeCur){

	  if (nodeCur->key < (*node)->key){
	  	*node = nodeCur;
	  	*prev = nodePrev;
	  }

	  nodePrev = nodeCur;
	  nodeCur   = nodeCur->sibling;
	}
}

void heapUnion(BHeap* heap, Node* h2)
{
	Node* h1;
	Node *prev, *x, *sibling;

	if (!h2) return;

	h1 = heap->head;

	if (!h1){
      heap->head = h2;
      return;
	}

	h1      = heapMerge(h1, h2);
	prev    = NULL;
	x       = h1;
	sibling = x->sibling;

	while (sibling){
	  if (x->degree != sibling->degree || (sibling->sibling && sibling->sibling->degree == x->degree)){
	  	prev = x;
	  	x    = sibling;
	  } else if (x->key < sibling->key){
	  	x->sibling = sibling->sibling;
	  	heapLink(x, sibling);
	  } else {

	  	if (prev) prev->sibling = sibling;
	  	else      h1 = sibling;

	  	heapLink(sibling, x);
	  	x = sibling;
	  }
	  sibling = x->sibling;
	}

	heap->head = h1;
}

Node* extractMin(BHeap* heap)
{
	Node *prev, *node;

	getMinNode(heap, &prev, &node);

	if (!node) return NULL;

	if (prev) prev->sibling = node->sibling;
	else      heap->head = node->sibling;

	heapUnion(heap, heapReverse(node->child));

	return node;
}

void insert(BHeap* heap, Node* node)
{
	Node *min;
	node->child     = NULL;
	node->parent    = NULL;
	node->sibling   = NULL;
	node->degree    = 0;

	if (heap->min && node->key < heap->min->key){

	  min = heap->min;
	  min->child     = NULL;
	  min->parent    = NULL;
	  min->sibling   = NULL;
	  min->degree    = 0;
	  heapUnion(heap, min);
	  heap->min      = node;

	} else heapUnion(heap, node);
}

void uncacheMin(BHeap* heap)
{
	Node* min;
	if (heap->min){
		min = heap->min;
		heap->min = NULL;
		insert(heap, min);
	}
}


Node* peek(BHeap* heap)
{
	if (!heap->min)
		heap->min = extractMin(heap);
	return heap->min;
}

Node* take(BHeap* heap)
{
	Node *node;

	if (!heap->min) heap->min = extractMin(heap);

	node = heap->min;
	heap->min = NULL;

	if (node) node->degree = INT_MAX;

	return node;
}

void decrease(BHeap* heap, Node* node, int new_key)
{
	Node *parent;
	Node** tmp_ref;
	const void* tmp;
	int   tmp_key;

	if (!node->ref || new_key >= node->key) return;

	node->key = new_key;

	if (heap->min != node){

		if (heap->min && node->key < heap->min->key) uncacheMin(heap);

		parent = node->parent;

		while (parent && node->key < parent->key){
			tmp           = parent->value;
			tmp_key       = parent->key;
			parent->value = node->value;
			parent->key   = node->key;
			node->value   = tmp;
			node->key     = tmp_key;

			if (parent->ref) *(parent->ref) = node;

			*(node->ref)   = parent;
			tmp_ref        = parent->ref;
			parent->ref    = node->ref;
			node->ref      = tmp_ref;
			node           = parent;
			parent         = node->parent;
		}
	}
}

void delete(BHeap* heap, Node* node)
{
	Node *parent, *prev, *pos;
	Node** tmp_ref;
	const void* tmp;
	int tmp_key;

	if (!node->ref) return;

	if (heap->min != node){
	  parent = node->parent;

	  while (parent){
	  	tmp           = parent->value;
	  	tmp_key       = parent->key;
	  	parent->value = node->value;
	  	parent->key   = node->key;
	  	node->value   = tmp;
	  	node->key     = tmp_key;

	  	if (parent->ref) *(parent->ref) = node;

	  	*(node->ref)   = parent;
	  	tmp_ref        = parent->ref;
	  	parent->ref    = node->ref;
	  	node->ref      = tmp_ref;
	  	node   = parent;
	  	parent = node->parent;
	  }

	  prev = NULL;
	  pos  = heap->head;

	  while (pos != node){
	  	prev = pos;
	  	pos  = pos->sibling;
	  }

	  if (prev) prev->sibling = node->sibling;
	  else      heap->head    = node->sibling;

	  heapUnion(heap, heapReverse(node->child));

	} else heap->min = NULL;


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
