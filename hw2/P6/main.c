#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <string.h>


struct Deque{
  int data;
  struct Deque *npx;
};


struct Deque* XOR(struct Deque *a, struct Deque *b)
{
  return (struct Deque*)((uintptr_t) (a) ^ (uintptr_t) (b));
}


void printList (struct Deque *root)
{
    struct Deque *curr = root;
 
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


void push(struct Deque **root, int data)
{
  struct Deque *newNode = (struct Deque *) malloc (sizeof (struct Deque) );
  newNode->data = data;
 
  newNode->npx = *root;
 
  if (*root != NULL)
  {
      (*root)->npx = XOR(newNode, (*root)->npx);
  }
 
  *root = newNode;
}
void pop(struct Deque **root)
{ 
  struct Deque *nextNode;
  struct Deque *nextnextNode;
  
  nextNode     = (*root)->npx;
  
  if (nextNode != NULL){
    nextnextNode = XOR(nextNode->npx, *root);
    nextNode->npx  = nextnextNode;
  
    free(*root);
    *root = nextNode;
  }
  else{
    free(*root); 
    *root = NULL;
  }
}

int main(){









  return 0;
}
