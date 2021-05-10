/* https://github.com/stephanoumenos/BinomialHeap/blob/master/binomial_heap.c
 * */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <string.h>
#include<stdint.h>
#include "binomial_heap.h"

typedef struct Node_t{
  int key;
  int degree;
  struct Node_t parent;
  struct Node_t sibling;
  struct Node_t child;
} Node;


typedef struct BinomialHeap_t{
  Node *head;
} BinomialHeap;


BinomialHeap* MakeBinomialHeap( )
{
  return NULL;
}

Node* BinomialHeapMinimum( BinomialHeap *bh )
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
    struct Deque *next;
 
    while (curr != NULL)
    {
        printf ("%d ", curr->data);
        next = XOR (prev, curr->npx);
        prev = curr;
        curr = next;
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
  struct Deque *nextNode;
  struct Deque *nextnextNode;
  
  nextNode     = (*endPoint)->npx;
  
  if (nextNode != NULL){

    nextnextNode = XOR(nextNode->npx, *endPoint);
    nextNode->npx  = nextnextNode;
  
    free(*endPoint);
    *endPoint = nextNode;
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

  Node *Node1 = (Node*)malloc(sizeof(Node));
  Node1->key = 1;

  Binomial_heap H1 = make_binomial_heap();

  H1 = binomial_heap_insert( H1, Node1 );

  return 0;
}
