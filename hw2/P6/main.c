#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <string.h>
#include<stdint.h>

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


  struct Deque *left  = NULL;
  struct Deque *right = NULL;

  push(&left, 1);
  
  right = left;

  push(&left, 2);
  push(&left, 3);
  push(&right, 99);
  push(&left, 4);

  printList(right);


  return 0;
}
