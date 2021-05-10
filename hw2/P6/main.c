/* https://github.com/stephanoumenos/BinomialHeap/blob/master/binomial_heap.c
 * */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<stdint.h>
#include<limits.h>

typedef struct Node_t{
  int key;
  int degree;
  struct Node_t *parent;
  struct Node_t *sibling;
  struct Node_t *child;
}Node;


typedef struct BinomialHeap_t{
  Node *head;
  Node *min;
} BinomialHeap;


BinomialHeap* MakeBinomialHeap( )
{
  return NULL;
}

Node* BinomialHeapMinimum( BinomialHeap *bh , Node **prev, Node **node)
{
  Node *x = bh->head;
  Node *minNode = NULL;

  int min = INT_MAX;

  while( x ){
    if ( min < x->key){
      min = x->key;
      minNode = x;
    }
    x = x->sibling;
  }

  return minNode;
}

/* make n2 to be the parent of n1 */
void BinomialLink(Node *n1, Node *n2 )
{
  n1->parent  = n2;
  n1->sibling = n2->child;
  n2->child   = n1;
  n2->degree  = (n1->degree)+1;
}



Node* BinomialHeapMerge(Node *n1, Node *n2)
{
 	Node  *head = NULL;
	Node **pos = &head;

	while (n1 && n2) {

	  if (n1->degree < n2->degree) {
	  	*pos = n1;
	  	n1 = n1->sibling;
	  }
      else {
	  	*pos = n2;
	  	n2 = n2->sibling;
	  }

	  pos = &(*pos)->sibling;

	}

	if (n1)     *pos = n1;
	else        *pos = n2;

	return head;
}

void BinomialHeapUnion(BinomialHeap* heap, Node *node)
{
	Node *h1, *prev, *x, *sibling;

	if (!node) return;

	h1 = heap->head;

	if (!h1) {
		heap->head = node;
		return;
	}

	h1 = BinomialHeapMerge(h1, node);
	prev = NULL;
	x    = h1;
	sibling = x->sibling;

	while (sibling) {
	  if (x->degree != sibling->degree || (sibling->sibling && sibling->sibling->degree == x->degree)){
	  	prev = x;
	  	x    = sibling;
	  } else if (x->key< sibling->key) {
	  	x->sibling = sibling->sibling;
	  	BinomialLink(x, sibling);
	  } else {
	  	if (prev) prev->sibling = sibling;
	  	else h1 = sibling;
	  	BinomialLink(sibling, x);
	  	x = sibling;
      }

	sibling = x->sibling;

    }

    heap->head = h1;
}

Node* HeapReverse(Node *node)
{
    Node* tail = NULL;
    Node* sibling;

    if (!node)  return node;

    node->parent = NULL;

    while (node->sibling) {
      sibling       = node->sibling;
      node->sibling   = tail;
      tail       = node;
      node         = sibling;
      node->parent = NULL;
    }

    node->sibling = tail;

    return node;
}


Node* HeapExtractMin(BinomialHeap *h)
{
    Node *prev;
    Node *node;

    BinomialHeapMinimum(h, &prev, &node);

    if (!node) return NULL;
    if (prev)  prev->sibling = node->sibling;
    else       h->head = node->sibling;

    BinomialHeapUnion(h, HeapReverse(node->child));

    return node;
}


void HeapInsert(BinomialHeap *h, Node *node)
{
    Node *min;

    node->child  = NULL;
    node->parent = NULL;
    node->sibling   = NULL;
    node->degree = 0;

    if (h->min && node->key < h->min->key) {

        min = h->min;

        min->child  = NULL;
        min->parent = NULL;
        min->sibling   = NULL;
        min->degree = 0;

        BinomialHeapUnion(h, min);
        h->min   = node;
    } else  BinomialHeapUnion(h, node);

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
