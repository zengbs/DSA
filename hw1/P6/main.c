#include<stdio.h>
#include<stdbool.h>
#include<stdint.h>
#include<stdlib.h>
#include <string.h>


struct List{
  int data;
  struct List *npx;
};

struct List* XOR(struct List *a, struct List *b)
{
  return (struct List*)((uintptr_t) (a) ^ (uintptr_t) (b));
}



void printList (struct List *root)
{
    struct List *curr = root;

    struct List *prev = NULL;
    struct List *next;
 
    while (curr != NULL)
    {
        if (curr == NULL){
          printf("root is NULL! %d\n", __LINE__);
          exit(0);
        }
        printf ("%d ", curr->data);
        next = XOR (prev, curr->npx);
        prev = curr;
        curr = next;
    }
  printf("\n");
}

void push(struct List **root, int data)
{
  // Allocate memory for new node
  struct List *newNode = (struct List *)malloc(sizeof (struct List) );
  newNode->data = data;
 
  /* Since new node is being inserted at the
     beginning, npx of new node will always be
     XOR of current head and NULL */
  newNode->npx = *root;
 
  /* If linked list is not empty, then npx of
     current head node will be XOR of new node
     and node next to current head */
  if (*root != NULL)
  {
      // *(root)->npx is XOR of NULL and next.
      // So if we do XOR of it with NULL, we get next
      (*root)->npx = XOR(newNode, (*root)->npx);
  }
 
  // Change head
  *root = newNode;
}

/* delete the item at the position `pos` counted from the root. The root is designated by zero */
void delete(struct List **root, int pos)
{
  struct List *nextnext = NULL;
  struct List *next     = NULL;
  struct List *cursor   = *root;  /* this pointer will point to the target to be deleted */
  struct List *prev     = NULL;
  struct List *prevprev = NULL;


  for (int i=1; i<=pos;i++){
    next   = XOR(cursor->npx, prev);
    prev   = cursor;
    cursor = next;
  }

  cursor    = prev;
  prev      = XOR(cursor->npx, next);
  

  if (prev == NULL){
    nextnext  = XOR(next->npx, cursor);
    next->npx = XOR(NULL, nextnext);
 
    *root = next;
  }
  else if (next == NULL){
    prevprev  = XOR(prev->npx, cursor);
    prev->npx = XOR(next,prevprev);
  }
  else{
    prevprev  = XOR(prev->npx, cursor);
    prev->npx = XOR(next,prevprev);
    nextnext  = XOR(next->npx, cursor);
    next->npx = XOR(prev, nextnext);
  }

  free(cursor);
  cursor = NULL;

}

/* insert `data` before the position `pos` counted from the root. The root is designated by zero */

void insert(struct List **root, int pos, int data)
{
  struct List *new = (struct List *)malloc(sizeof (struct List) );
  new->data = data;

  struct List *next     = NULL;
  struct List *cursor   = *root;  /* this pointer will point to the target to be deleted */
  struct List *prev     = NULL;
  struct List *prevprev = NULL;

  if (cursor != NULL){

    for (int i=1; i<=pos;i++){
      next   = XOR(cursor->npx, prev);
      prev   = cursor;
      cursor = next;
    }

    cursor = prev;
    prev   = XOR(cursor->npx, next);

    new->npx = XOR(cursor, prev);
    cursor->npx = XOR(next,new);
    prev->npx = XOR(new, prevprev);
  }
  else{

  }
}

int main()
{

struct List *root = NULL;
push(&root, 1);
push(&root, 2);
push(&root, 3);
push(&root, 4);
push(&root, 5);
push(&root, 6);
delete(&root,1);
//insert(&root, 4, 999);

printList(root);
//printList(end);
}
